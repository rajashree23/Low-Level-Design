# Parking Lot LLD — Interview Cheat Sheet

## 1. Core Design

| Question                          | Crisp Answer                                                                                                                                                                                         |
| --------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Main classes?**                 | `ParkingLot` is the orchestrator. Core entities are `ParkingFloor`, `ParkingSpot`, `Vehicle`, and `Ticket`. Supporting components include `PaymentProcessor`, `PriceCalculator`, and `SpotStrategy`. |
| **What does Ticket contain?**     | `ticketId`, `spotId`, `vehicle`, `timestamp`, `status`, and optionally `entryGateId`.                                                                                                                |
| **Why store `spotId` in Ticket?** | At exit, we use `spotId` to locate the exact parking spot occupied by that vehicle.                                                                                                                  |
| **Why store `entryGateId`?**      | It tells us which gate the vehicle entered from without storing the entire `EntryGate` object.                                                                                                       |

---

# 2. Entry Flow

### Question: Explain the vehicle entry flow.

```text
Vehicle + EntryGate
        ↓
Check vehicle isn't already parked
        ↓
SpotStrategy finds suitable spot
        ↓
Assign spot
        ↓
Generate Ticket
        ↓
Store in activeTickets
```

**Answer:**
Check for an existing active ticket, then use the spot-selection strategy to find a suitable spot. Assign it, generate the ticket, and store it in `activeTickets`.

---

### Question: What if no spot is available?

**Answer:**
Reject the parking request and don't create a ticket.

---

### Question: What if spot assignment fails?

**Answer:**
Parking should fail and the system should not create/store an active ticket.

---

# 3. Exit Flow

### Question: Explain the exit flow.

```text
Vehicle
   ↓
Validate Ticket
   ↓
Find Spot
   ↓
Calculate Fee
   ↓
Process Payment
   ↓
Release Spot
   ↓
Mark Ticket Processed
   ↓
Remove from activeTickets
```

**Answer:**
First validate the ticket and vehicle. Then calculate the fee and process payment; only after successful payment do we release the spot and mark the ticket processed.

---

### Question: What if vehicle number doesn't match the ticket?

**Answer:**
Reject the exit request immediately. Don't calculate fees, process payment, or release the spot.

---

### Question: What if the ticket is already processed?

**Answer:**
Reject the request. A processed ticket cannot be used for another exit.

---

# 4. Payment Failures

### Question: What if payment fails?

**Answer:**

* Spot remains occupied.
* Ticket remains `Active`.
* `activeTickets` still contains the ticket.
* User can retry payment.

The vehicle has **not successfully exited**.

---

### Question: What if payment succeeds but spot release fails?

**Answer:**
Retry the spot-release operation. Until release succeeds, keep the ticket active and don't remove it from `activeTickets`.

Ideally, spot release should be **idempotent** so retries are safe.

---

# 5. Concurrency

### Question: What happens if two vehicles try to take the same spot?

**Answer:**
Both threads could see the spot as available and attempt to assign it.

The **check + assignment must be atomic** to prevent double assignment.

---

### Question: Why shouldn't we do this?

```text
isEmpty()
   ↓
assignSpot()
```

**Answer:**
Another thread could occupy the spot between the two calls.

Instead, `assignSpot()` should perform the check and assignment under the same lock.

---

## Coarse-Grained Locking

### Question: How would you solve concurrency using coarse-grained locking?

```text
ParkingLot mutex
      ↓
Find spot
      ↓
Assign spot
      ↓
Update activeTickets
```

**Answer:**
Use one mutex at the `ParkingLot` level covering the complete critical section.

**Pros:** Simple and easy to reason about.
**Cons:** Serializes parking operations even when vehicles use different spots.

---

## Fine-Grained Locking

### Question: How would you solve it using fine-grained locking?

```text
Spot A → mutex
Spot B → mutex
Spot C → mutex

activeTickets → separate mutex

ticketId → atomic
```

**Answer:**
Each `ParkingSpot` has its own mutex, allowing different spots to be assigned concurrently.

Other shared resources such as `activeTickets` have their own synchronization.

---

# 6. Atomic vs Mutex

### Question: Why use `atomic` for ticket ID?

**Answer:**
Ticket ID is a simple shared counter, so `std::atomic<int>` is sufficient.

It allows thread-safe increment without a mutex.

---

### Question: Why not make `activeTickets` atomic?

**Answer:**
`activeTickets` is a complex `unordered_map` containing multiple operations and `unique_ptr`s.

A mutex is appropriate for protecting the entire map.

---

# 7. Strategy Pattern

### Question: Why use Strategy Pattern?

**Answer:**
Spot selection can have multiple algorithms, such as:

* `FirstAvailableSpotStrategy`
* `NearestSpotStrategy`
* `HighestFloorStrategy`

`ParkingLot` delegates the selection algorithm to `SpotStrategy`.

---

### Question: What happens when we add a new strategy?

**Answer:**
Create a new concrete `SpotStrategy`.

`ParkingLot` doesn't need to change its core orchestration logic.

---

# 8. Multiple Floors

### Question: How do you support multiple floors?

```text
ParkingLot
    |
    +-- ParkingFloor 1
    |       |
    |       +-- Spots
    |
    +-- ParkingFloor 2
            |
            +-- Spots
```

**Answer:**
`ParkingLot` contains multiple `ParkingFloor` objects, and each floor owns its parking spots.

The strategy decides how to search across floors.

---

# 9. Multiple Entry / Exit Gates

### Question: How do you model multiple gates?

```text
ParkingLot
   |
   +-- EntryGates
   |      +-- Gate 1
   |      +-- Gate 2
   |
   +-- ExitGates
   |      +-- Gate 1
   |      +-- Gate 2
   |
   +-- ParkingFloors
```

**Answer:**
`ParkingLot` maintains lists of entry and exit gates separately from parking floors.

---

### Question: How does NearestSpotStrategy know which gate to use?

**Answer:**
Pass the entry gate, or its `Location`, to `findSpot()`.

```text
findSpot(floors, vehicle, entryGate)
```

The strategy uses the gate's location to calculate the nearest suitable spot.

---

### Question: Why store `entryGateId` instead of the entire EntryGate in Ticket?

**Answer:**
The ticket only needs to identify the gate.

Storing `entryGateId` reduces coupling; the actual gate can be looked up from `ParkingLot` when needed.

---

### Question: Where should distance calculation happen?

**Answer:**
Inside `NearestSpotStrategy`.

Distance calculation is part of the **spot-selection algorithm**, not the responsibility of `ParkingLot` or `ParkingSpot`.

---

# 10. activeTickets

### Question: Why use vehicle number as the key?

```cpp
unordered_map<string, unique_ptr<Ticket>> activeTickets;
```

**Answer:**
Our exit operation starts with the vehicle, so `vehicleNo` gives direct access to its active ticket.

It also makes vehicle-ticket validation straightforward.

---

### Question: What if the same vehicle tries to enter twice?

**Answer:**
Before creating a new ticket, check whether `activeTickets` already contains that vehicle.

If it does, reject the new parking request.

---

### Question: What concurrency issue exists here?

**Answer:**
The **check and insertion must be synchronized together**.

Otherwise two concurrent requests could both see that the vehicle isn't parked and create duplicate tickets.

---

# 11. Pricing

### Question: How do you calculate partial hours?

**Answer:**
Round the elapsed duration **up** to the next full hour.

For example:

```text
1 hour 10 minutes → 2 hours
2 hours 00 minutes → 2 hours
```

---

### Question: What if pricing becomes more complex?

For example:

* Weekend pricing
* Peak-hour pricing
* Holiday pricing
* Dynamic pricing

**Answer:**
Introduce a pricing strategy/component.

```text
PriceCalculator
      ↓
PricingStrategy
      ↓
Normal / Weekend / Peak / Dynamic
```

This keeps pricing logic separate from `ParkingLot`.

---

# 12. Failure-State Rules

| Situation         | Spot                 | Ticket    | activeTickets   |
| ----------------- | -------------------- | --------- | --------------- |
| Payment fails     | Occupied             | Active    | Keep            |
| Payment succeeds  | Occupied temporarily | Active    | Keep            |
| Release succeeds  | Free                 | Processed | Remove          |
| Release fails     | Occupied             | Active    | Keep + retry    |
| Invalid ticket    | Occupied             | Unchanged | Keep            |
| Already processed | Free                 | Processed | Already removed |

---

# 13. The 5 Flows to Remember

## Entry

```text
Vehicle + EntryGate
        ↓
Already parked?
        ↓
Strategy finds spot
        ↓
Assign spot
        ↓
Generate Ticket
        ↓
activeTickets
```

## Exit

```text
Vehicle
   ↓
Validate Ticket
   ↓
Find Spot
   ↓
Calculate Fee
   ↓
Payment
   ↓
Release Spot
   ↓
Processed
   ↓
Remove activeTicket
```

## Fine-Grained Locking

```text
ParkingSpot → own mutex
activeTickets → own mutex
ticketId → atomic
```

## Strategy

```text
              SpotStrategy
                   |
        +----------+----------+
        |          |          |
   FirstAvailable Nearest HighestFloor
```

## Failure Handling

```text
Payment fails
    ↓
Keep spot + ticket active

Release fails
    ↓
Retry release
    ↓
Keep ticket active until successful
```

---

# 14. Interview Mental Model

When designing the Parking Lot, think in this order:

```text
1. Entities
      ↓
2. Responsibilities
      ↓
3. Entry flow
      ↓
4. Exit flow
      ↓
5. Failure cases
      ↓
6. Concurrency
      ↓
7. Extensibility / Design Patterns
```

The key principle:

> **ParkingLot orchestrates. Entities hold state. Strategies handle variable algorithms. Synchronization protects shared state.**


# 15. Nearest Spot — Location and Distance

### How do we represent the location of a gate/spot?

Each `EntryGate` and `ParkingSpot` can have a `Location` containing:

```cpp
class Location {
    int x;
    int y;
};
```

`x` and `y` represent the physical position on the parking-lot layout.

---

### How does `NearestSpotStrategy` find the nearest spot?

The strategy gets the **entry gate's `(x, y)` coordinates** and compares them with each eligible parking spot's coordinates.

For two points:

```text
Gate    = (x1, y1)
Spot    = (x2, y2)
```

Distance can be calculated using:

```text
distance = √((x2 - x1)² + (y2 - y1)²)
```

The strategy calculates this for all suitable spots and selects the one with the **minimum distance**.

---

### Example

```text
Gate  = (2, 3)

Spot A = (5, 7)
Spot B = (3, 4)
Spot C = (10, 10)
```

The strategy calculates:

```text
distance(Gate, A)
distance(Gate, B)
distance(Gate, C)
```

and selects **Spot B** because it has the smallest distance.

---

### Where does this logic belong?

The distance calculation belongs inside:

```text
NearestSpotStrategy
```

because calculating distance and selecting the nearest spot are both part of the **spot-selection algorithm**.

The responsibilities remain:

```text
EntryGate
    → has Location

ParkingSpot
    → has Location

NearestSpotStrategy
    → calculates distance
    → finds nearest suitable spot

ParkingLot
    → orchestrates the overall flow
```

### Interview answer

> "I would give the entry gate and parking spots an `(x, y)` location. `NearestSpotStrategy` would take the entry gate's location, calculate the distance to each eligible spot using the Euclidean distance formula, and select the spot with the minimum distance."
