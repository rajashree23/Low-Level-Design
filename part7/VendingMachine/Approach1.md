# Vending Machine LLD — Final Revision Notes

**Language:** C++  
**Focus:** LLD interviews, class design, state machines, concurrency, failure handling  
**Revision dates:** October 27 and October 29

---

## 1. Functional Requirements

The vending machine should:

1. Store multiple products with ID, name, price, and quantity.
2. Allow customers to select a product and quantity.
3. Validate product availability.
4. Accept cash in supported denominations.
5. Calculate and return exact change.
6. Dispense the selected product.
7. Support transaction cancellation and refunds.
8. Handle hardware failures and unknown outcomes.
9. Allow only one active customer session at a time.

### Out of Scope

- UI implementation
- Customer support system
- Distributed deployment
- Detailed hardware implementation

---

## 2. Core Classes and Responsibilities

| Class | Responsibility |
|---|---|
| `VendingMachine` | Main orchestrator; manages state, active session, and transaction flow |
| `Product` | Stores product details, physical quantity, and reserved quantity |
| `Request` | Stores requested product ID and quantity |
| `Transaction` | Tracks payment, returned change, refunds, and transaction status |
| `CashInventory` | Manages denominations, calculates exact change, and updates cash inventory |

### Design Principle

`VendingMachine` should coordinate operations rather than implement every responsibility itself.

For example:

- `Product` handles inventory reservation.
- `CashInventory` handles denomination calculations.
- `Transaction` tracks money and transaction status.
- `VendingMachine` coordinates the workflow.

---

## 3. Machine State

```cpp
enum class VMState {
    IDLE,
    CHOOSE_PRODUCT,
    PROCESS_PAYMENT,
    DISPENSE_PRODUCT,
    MAINTENANCE
};
```

### Happy Path

```text
IDLE
  |
  v
CHOOSE_PRODUCT
  |
  v
PROCESS_PAYMENT
  |
  v
DISPENSE_PRODUCT
  |
  v
IDLE
```

### Important Rules

- New sessions can start only in `IDLE`.
- Payment can be accepted only in `PROCESS_PAYMENT`.
- Product dispensing happens only in `DISPENSE_PRODUCT`.
- Unresolved hardware or refund failures may move the machine into `MAINTENANCE`.

**Machine state and transaction status are separate concepts.**

---

## 4. Transaction Status

```cpp
enum class TrxStatus {
    ACTIVE,
    SUCCESS,
    FAILED,
    CANCELLED,
    REFUND_PENDING,
    RECONCILIATION_PENDING
};
```

| Status | Meaning |
|---|---|
| `ACTIVE` | Transaction is in progress |
| `SUCCESS` | Product was successfully dispensed |
| `FAILED` | Transaction definitively failed |
| `CANCELLED` | Customer cancelled the transaction |
| `REFUND_PENDING` | Refund is still unresolved |
| `RECONCILIATION_PENDING` | Hardware outcome is unknown |

---

## 5. Important Methods

### 5.1 `chooseProduct()`

**Responsibility:** Validate selection, reserve stock, and initialize the transaction.

Steps:

1. Verify machine state is `IDLE`.
2. Validate product ID.
3. Validate requested quantity is positive.
4. Atomically check and reserve the requested stock.
5. Create the active `Request`.
6. Create the active `Transaction`.
7. Move to `PROCESS_PAYMENT`.

**Important:** Inventory reservation must be atomic.

### 5.2 `insertCash()`

**Responsibility:** Accept cash and process change.

Steps:

1. Verify machine state is `PROCESS_PAYMENT`.
2. Validate denomination and quantity.
3. Record inserted cash and denominations.
4. Compare total inserted money with product cost.
5. If insufficient, wait for additional money.
6. If sufficient, calculate required change.
7. Find an exact denomination combination.
8. Dispense change.
9. Record the amount actually returned.
10. Move to `DISPENSE_PRODUCT` after successful payment handling.

**Important:** Calculate change using total inserted money, not only the latest insertion.

### 5.3 `dispenseProduct()`

**Responsibility:** Dispense the product and finalize the transaction.

Three possible hardware outcomes:

| Result | Action |
|---|---|
| `SUCCESS` | Reduce physical stock, release reservation, mark transaction successful |
| `FAILED` | Refund outstanding amount, release reservation, mark failed or refund pending |
| `UNKNOWN` | Persist reconciliation pending; don't blindly refund or modify physical stock |

After confirmed success:

```text
Transaction -> SUCCESS
Product stock -> Reduced
Reserved quantity -> Released
Machine -> IDLE
```

### 5.4 `cancelTransaction()`

Steps:

1. Validate session ownership.
2. Ensure cancellation is allowed in the current state.
3. Calculate outstanding refund.
4. Attempt refund if money is owed.
5. Persist the final or pending transaction status.
6. Release reserved inventory when cancellation is confirmed.
7. Clear active request and session when safe.
8. Return to `IDLE` or enter `MAINTENANCE` if necessary.

---

## 6. Inventory Reservation

Maintain:

```cpp
int totalQty;
int reservedQty;
```

Formula:

```text
SellableQty = totalQty - reservedQty
```

### Example

```text
Total stock = 10
Reserved stock = 3
Sellable stock = 7
```

### Atomic Reservation

```cpp
bool Product::tryReserve(int requestedQty) {
    lock_guard<mutex> lock(productMutex);

    if (requestedQty <= 0)
        return false;

    if (totalQty - reservedQty < requestedQty)
        return false;

    reservedQty += requestedQty;

    return true;
}
```

### Important Rules

- Reservation reduces sellable quantity.
- Reservation does not immediately reduce physical stock.
- Confirmed dispensing reduces physical stock and releases the reservation.
- Confirmed cancellation releases the reservation.
- Unknown dispensing must not blindly restore or reduce stock.

---

## 7. Concurrency and Atomicity

Two types of shared state need protection.

| Mutex | Responsibility |
|---|---|
| `sessionMutex` | Prevent multiple active customer sessions |
| `productMutex` | Protect stock checks, reservations, and updates |

### Atomicity Rule

**Always protect the check and update together.**

Incorrect:

```cpp
if (availableQty >= qty) {
    // Another thread could reserve stock here.
    reservedQty += qty;
}
```

Correct:

```cpp
lock_guard<mutex> lock(productMutex);

if (totalQty - reservedQty < qty)
    return false;

reservedQty += qty;
```

### Lock Scope

Avoid holding mutexes while performing slow operations such as:

- Hardware dispensing
- Refund processing
- External payment calls

For more robust designs:

1. Claim the operation under a mutex.
2. Release the mutex.
3. Perform the external operation.
4. Reacquire the mutex.
5. Finalize the transaction safely.

---

## 8. Cash Inventory and Denominations

Store denomination counts using:

```cpp
map<int, int> denominations;
```

Example:

```cpp
{
    {5, 2},
    {10, 3},
    {20, 1},
    {50, 2},
    {100, 1}
}
```

This means the machine has:

- Two ₹5 coins
- Three ₹10 notes/coins
- One ₹20 note
- Two ₹50 notes
- One ₹100 note

### Exact Change Example

Product price = ₹70  
Customer inserted = ₹100

```text
Change = 100 - 70 = ₹30
```

Possible change plan:

```cpp
{
    {20, 1},
    {5, 2}
}
```

### Important Design

Separate calculation from physical dispensing:

```cpp
optional<map<int, int>> calculateChange(int amount);

bool dispenseChange(const map<int, int>& change);
```

`calculateChange()` should not modify inventory.

Cash inventory should be updated based on confirmed physical cash movements.

### Greedy vs Backtracking

Greedy chooses the largest available denomination first.

However, greedy does not always find a valid combination.

Example:

```text
Available:
₹10 x 1
₹6  x 2

Required change: ₹12
```

Greedy chooses ₹10 and fails to find ₹2.

But:

```text
₹6 + ₹6 = ₹12
```

For arbitrary denominations with limited quantities, backtracking or bounded dynamic programming can find a valid combination.

In interviews, explain the tradeoff and confirm whether greedy is an acceptable simplification.

#### Greedy Algo
```cpp
```
----
#### DP Algo
```cpp
```
----
## 9. Transaction Accounting

**Most important formula:**

```text
Outstanding Amount =
    Total Inserted
    - Change Returned
    - Refund Returned
```

### Example

Customer inserts ₹100.

Product costs ₹70.

Machine successfully returns ₹20 change, but fails to return the remaining ₹10.

```text
Inserted = ₹100
Change returned = ₹20
Refund returned = ₹0

Outstanding = 100 - 20 - 0
            = ₹80
```

### Two Different Outcomes

**Product successfully dispensed:**

The customer is owed only the remaining ₹10 change.

**Product definitely not dispensed and transaction cancelled:**

The customer is owed ₹80 because the product was not delivered.

**Product dispensing outcome unknown:**

Do not immediately refund. Reconcile first.

---

## 10. Failure Handling

### Confirmed Failure

We know the operation did not happen.

Possible actions:

- Refund outstanding money.
- Release reserved inventory.
- Mark transaction failed.
- Reset the machine if safe.

### Unknown Outcome

We don't know whether the operation happened.

Example:

```cpp
DispenseResult result = dispenseHardware(...);
```

Hardware times out.

The product may have been dispensed even though no response was received.

Correct handling:

1. Mark `RECONCILIATION_PENDING`.
2. Persist the transaction and operation ID.
3. Don't blindly refund.
4. Don't blindly update physical stock.
5. Move to `MAINTENANCE` if the machine cannot safely continue.
6. Reconcile using hardware logs or sensors.

### Refund Failure

If refunding fails or its outcome is unknown:

```cpp
transaction.setStatus(TrxStatus::REFUND_PENDING);
persistTransaction(transaction);
```

Do not claim the refund succeeded.

---

## 11. Idempotency

**Idempotency means retrying an operation must not repeat its business effect.**

Example:

```text
Transaction ID = T101
Dispense operation ID = D101
```

If the dispense request times out, retrying with the same operation ID is safe only when the hardware/service guarantees deduplication.

### Important Points

- Use stable transaction and operation IDs.
- Detect duplicate operations.
- Return the previously recorded result when appropriate.
- Persist operation status when crash recovery matters.
- Reconcile uncertain operations before unsafe retries.

**A mutex alone does not guarantee idempotency.**

---

## 12. Common Interview Mistakes

1. Checking stock without an atomic reservation.
2. Reserving one product when multiple units were requested.
3. Treating insufficient payment as transaction failure.
4. Calculating change from the latest cash insertion.
5. Deducting cash during change calculation instead of after confirmed dispensing.
6. Refunding money already returned as change.
7. Treating a hardware timeout as confirmed failure.
8. Resetting a transaction before preserving pending refund information.
9. Forgetting to release inventory reservations.
10. Holding locks during slow hardware operations.
11. Mixing machine state with transaction status.
12. Adding unnecessary design patterns before establishing a simple working design.

---

## 13. Interview Explanation Template

When asked to design a Vending Machine:

**Step 1 — Requirements**

Clarify supported products, quantities, payment methods, denominations, refunds, and concurrency assumptions.

**Step 2 — Classes**

Identify `VendingMachine`, `Product`, `Request`, `Transaction`, and `CashInventory`.

**Step 3 — State Machine**

Explain the happy path and invalid transitions.

**Step 4 — Core APIs**

Define:

```cpp
bool chooseProduct(int productId, int qty);

bool insertCash(int denomination, int quantity);

bool dispenseProduct();

bool cancelTransaction(int sessionId);
```

**Step 5 — Critical Invariants**

- Only one active session.
- Stock cannot be over-reserved.
- Cash returned must be tracked accurately.
- Unknown hardware outcomes must not trigger unsafe compensation.
- Successful transactions must not be processed twice.

**Step 6 — Failure Handling**

Explain confirmed failure, unknown outcome, refunds, reconciliation, and idempotency.

---

## 14. Active Recall Checklist

During revision, close these notes and answer:

- [ ] Can I identify all core classes and responsibilities?
- [ ] Can I reconstruct the state machine?
- [ ] Can I explain inventory reservation and atomicity?
- [ ] Can I implement `chooseProduct()`?
- [ ] Can I explain denomination-based change?
- [ ] Can I calculate outstanding refunds after partial change?
- [ ] Can I handle `SUCCESS`, `FAILED`, and `UNKNOWN`?
- [ ] Can I explain reconciliation and idempotency?
- [ ] Can I identify which mutex protects which resource?

---

## 15. Personal Improvement Areas

### Strengths

- Class responsibility identification
- State machine reasoning
- Inventory reservation concepts
- Understanding unknown hardware outcomes
- Refund and reconciliation reasoning

### Areas to Improve

- Translating design into C++ methods
- Checking return values from helper methods
- Maintaining consistent class interfaces
- Correct transaction accounting
- Cleanup after failed operations
- Avoiding unnecessary complexity

### Revision Strategy

**October 27:** Reconstruct the design without notes for 20 minutes.

**October 29:** Review Vending Machine and Parking Lot together for 30 minutes.

**October 30:** Complete a timed LLD mock interview.

**Main takeaway:** Focus on implementing correct class responsibilities and business invariants before adding advanced failure-handling complexity.