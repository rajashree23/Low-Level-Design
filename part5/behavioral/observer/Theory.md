# Observer Design Pattern

## What is Observer?

Observer is a **behavioral design pattern** where one object maintains a list of dependents and **automatically notifies them when its state changes**.

Simple words:

> **One-to-many notification mechanism — when one object changes, all interested objects are notified.**

---

## Core Structure

* **Subject (Observable)** — maintains state and a list of observers.
* **Observer** — defines the notification interface.
* **Concrete Subject** — changes state and triggers notification.
* **Concrete Observers** — react when notified.

```text
          Subject
             │
      notifies multiple
        ┌────┼────┐
        ▼    ▼    ▼
   Observer Observer Observer
```

---

## Why do we need it?

Without Observer, the Subject may directly depend on every component that needs updates.

For example:

```text
StockPrice
   ├── update Display
   ├── update MobileApp
   ├── update AlertSystem
   └── update Analytics
```

This creates **tight coupling**.

With Observer:

```text
StockPrice
    │
    └── notify()
          ├── Display
          ├── MobileApp
          ├── AlertSystem
          └── Analytics
```

The Subject only knows about the **Observer interface**, not the concrete components.

---

## When to use?

Use Observer when:

* Multiple objects depend on another object's state.
* A state change should trigger updates in multiple components.
* You want to avoid tight coupling between the publisher and subscribers.
* Observers can be added or removed dynamically.
* The system naturally follows **publish → notify → react**.

### Interview Recognition

If the problem says:

> **"When X changes, notify/update multiple components."**

Think **Observer**.

---

## Important Properties

* **One-to-many relationship**
* Subject maintains a collection of observers.
* Observers subscribe/unsubscribe.
* Subject notifies observers when its state changes.
* Subject depends on the **Observer abstraction**, not concrete observers.
* Promotes **loose coupling**.

---

## Observer vs Strategy

|              | Observer                  | Strategy                       |
| ------------ | ------------------------- | ------------------------------ |
| Type         | Behavioral                | Behavioral                     |
| Purpose      | Notify interested objects | Choose an algorithm/behavior   |
| Relationship | One-to-many               | Usually one strategy at a time |
| Focus        | **Communication**         | **Behavior selection**         |
| Example      | Stock price → displays    | Order → payment method         |

---

## Observer vs Pub-Sub

They are related but not exactly the same.

**Observer:**

```text
Subject → Observers
```

The Subject directly maintains and notifies its observers.

**Pub-Sub:**

```text
Publisher → Message Broker → Subscribers
```

Publisher and subscribers are usually decoupled through a broker/event bus.

---

## Advantages

* Loose coupling between Subject and Observers.
* Easy to add/remove observers.
* Supports one-to-many communication.
* Subject doesn't need to know concrete observer implementations.

## Disadvantages

* Large number of observers can cause many updates.
* Notification order may matter.
* Can make control flow harder to trace/debug.
* Care is needed to avoid stale subscriptions or memory/lifecycle issues.

---

## Real-World Examples

* Stock price → multiple displays
* YouTube channel → subscribers
* Order placed → inventory, notification, analytics
* UI event → multiple listeners
* Weather station → multiple displays
* Event/listener systems

---

## One-Line Interview Definition

> **Observer is a behavioral pattern that establishes a one-to-many relationship where changes in a subject automatically notify its subscribed observers.**
