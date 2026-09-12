# State Design Pattern

## What is State?

State is a **behavioral design pattern** where an object's behavior changes depending on its **current internal state**.

Simple words:

> **When an object's behavior changes based on its current state, encapsulate each state's behavior in a separate class.**

---

## Core Structure

* **Context** — maintains the current state and delegates operations to it.
* **State** — defines the interface for state-specific behavior.
* **Concrete States** — implement behavior for a particular state.

```text
              Context
           VendingMachine
                 │
          currentState
                 │
                 ▼
               State
                 │
        ┌────────┼────────┐
        ▼        ▼        ▼
     NoCoin   HasCoin   Dispense
```

---

## Why do we need it?

Without State, the Context may contain many `if/else` or `switch` statements based on the current state.

For example:

```text
VendingMachine

insertCoin()
    ├── if NoCoin
    ├── if HasCoin
    └── if Dispensing

selectProduct()
    ├── if NoCoin
    ├── if HasCoin
    └── if Dispensing

dispense()
    ├── if NoCoin
    ├── if HasCoin
    └── if Dispensing
```

As states and operations grow, the logic becomes **hard to maintain and extend**.

With State:

```text
VendingMachine
       │
       │ delegates
       ▼
Current State
       │
   ┌───┼──────────┐
   ▼   ▼          ▼
 NoCoin HasCoin Dispense
```

Each state contains the behavior appropriate for that state.

---

## How does it work?

The Context maintains the current state:

```text
VendingMachine
      │
      │ owns
      ▼
unique_ptr<State>
```

When an operation is called:

```text
machine.insertCoin()
        │
        ▼
currentState->insertCoin(*this)
        │
        ▼
NoCoinState
```

The current state handles the operation.

If a transition is required:

```text
NoCoinState
     │
     │ insertCoin()
     ▼
VendingMachine
     │
     │ setState(...)
     ▼
HasCoinState
```

So the basic flow is:

> **Context receives request → delegates to current State → State performs state-specific behavior → State/Context transitions to next State.**

---

## When to use?

Use State when:

* An object's behavior changes significantly based on its current state.
* There are multiple distinct states.
* Different operations behave differently in different states.
* There are many `if/else` or `switch` statements based on state.
* There are clear **state transition rules**.
* You want each state's behavior to be isolated in its own class.

### Interview Recognition

If the problem says:

> **"The object's behavior depends on its current state, and it can transition between different states."**

Think **State**.

---

## Important Properties

* Context maintains the **current state**.
* State defines state-specific operations.
* Each concrete state implements its own behavior.
* Context delegates operations to the current state.
* States can trigger transitions to another state.
* State objects are usually owned by the Context.
* In C++, `unique_ptr<State>` is a natural choice when the Context owns the current State.
* State Pattern replaces **complex state-dependent conditionals** with polymorphism.

---

## State Transition

A state machine can be represented as:

```text
NoCoin
   │
   │ insertCoin()
   ▼
HasCoin
   │
   │ selectProduct()
   ▼
Dispense
   │
   │ dispense()
   ▼
NoCoin
```

Each arrow represents a **state transition**.

The state diagram is often useful in LLD interviews because it clearly shows:

* Available states
* Valid operations
* State transitions
* Invalid operations

---

## State vs Strategy

They can have a similar class structure, but their intent is different.

|            | State                                  | Strategy                                                 |
| ---------- | -------------------------------------- | -------------------------------------------------------- |
| Type       | Behavioral                             | Behavioral                                               |
| Purpose    | Change behavior based on current state | Choose an algorithm/behavior                             |
| Focus      | **State-dependent behavior**           | **Behavior selection**                                   |
| Transition | States can transition to other states  | Strategy usually doesn't represent lifecycle transitions |
| Example    | Vending machine → NoCoin/HasCoin       | Order → CreditCard/UPI                                   |

Simple way to remember:

> **Strategy = "How should I do this?"**

> **State = "What behavior should I have because of my current state?"**

---

## State vs Observer

They can also appear together in the same LLD.

### State

```text
Order
  │
  └── State
       ├── Created
       ├── Paid
       └── Shipped
```

Controls **what the object can do** based on its state.

### Observer

```text
Order
  │
  └── notify()
       ├── User
       ├── Inventory
       └── NotificationSystem
```

Controls **who gets notified** when something changes.

---

## State vs Enum

Having an enum for state is **not automatically wrong**.

For simple state logic:

```cpp
enum class State {
    ON,
    OFF
};
```

may be enough.

State Pattern becomes useful when:

* State-specific behavior becomes complex.
* There are many operations affected by state.
* State transitions become complicated.
* `if/else` or `switch` logic starts spreading across the Context.

Simple rule:

> **Don't convert every enum into classes. Use State when state-dependent behavior has become complex enough to justify separate state objects.**

---

## Advantages

* Removes complex `if/else` and `switch` logic.
* Each state's behavior is isolated.
* Easier to add new states.
* Makes state transitions explicit.
* Improves maintainability.
* Follows polymorphism instead of repeated conditionals.
* Context doesn't need to contain all state-specific behavior.

---

## Disadvantages

* Can introduce many classes.
* May be overkill for simple state logic.
* State transitions can become complicated.
* More objects and abstractions can make simple systems unnecessarily complex.
* Control flow can be harder to follow if there are many states and transitions.

---

## Real-World Examples

* Vending machine → NoCoin, HasCoin, Dispensing
* Order lifecycle → Created, Paid, Shipped, Delivered
* ATM → Idle, CardInserted, Authenticated
* Traffic light → Red, Yellow, Green
* Media player → Playing, Paused, Stopped
* Document workflow → Draft, Review, Published
* Game character → Idle, Running, Attacking, Dead
* Elevator → Idle, MovingUp, MovingDown

---

## C++ Ownership

The Context typically **owns the current State**:

```cpp
class VendingMachine {
private:
    std::unique_ptr<VendingMachineState> currentState;
};
```

When changing states:

```cpp
machine.setState(
    std::make_unique<HasCoinState>()
);
```

The Context owns the new state, and the old state is automatically destroyed.

The State does **not** own the Context.

Instead, the Context can be passed by reference:

```cpp
void insertCoin(VendingMachine& machine);
```

This allows the State to request a transition:

```cpp
machine.setState(
    std::make_unique<HasCoinState>()
);
```

---

## One-Line Interview Definition

> **State is a behavioral pattern that encapsulates state-dependent behavior into separate state classes, allowing an object to change its behavior as its internal state changes.**
