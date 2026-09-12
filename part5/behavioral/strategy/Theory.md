# Strategy

## What is Strategy?

**Strategy is a behavioral design pattern that encapsulates a family of interchangeable algorithms or behaviors, allowing them to be selected or changed at runtime.**

The main idea is to **replace growing conditional logic with composition and polymorphism**.

In simple words:

> **Strategy = Encapsulate different ways of doing something and make them interchangeable.**

---

## Core Structure

Strategy has three main participants:

```text
             Context
                │
                │ HAS-A
                ▼
             Strategy
                ▲
       ┌────────┼────────┐
       │        │        │
 StrategyA  StrategyB  StrategyC
```

### 1. Strategy

Defines the common interface for all interchangeable behaviors.

### 2. Concrete Strategy

Implements a specific algorithm or behavior.

Examples:

* `CardPayment`
* `UpiPayment`
* `CashPayment`

### 3. Context

Uses a Strategy and delegates the relevant operation to it.

The Context does not need to know the internal implementation of each algorithm.

---

## Why Do We Need Strategy?

Without Strategy, a class may contain growing `if-else` or `switch` statements for different algorithms.

For example:

```text
PaymentService
 ├── Card payment logic
 ├── UPI payment logic
 └── Cash payment logic
```

This creates tight coupling and makes the class harder to maintain.

With Strategy:

```text
PaymentService ──► PaymentStrategy
                         ├── CardPayment
                         ├── UpiPayment
                         └── CashPayment
```

Each algorithm is isolated, and the Context delegates to the selected Strategy.

> **The Context focuses on what it needs to do; the Strategy defines how it is done.**

---

## When Should I Use Strategy?

Use Strategy when:

* You have **multiple interchangeable algorithms or behaviors**.
* The behavior can vary independently of the object using it.
* You have growing conditional logic for selecting behavior.
* You want to select or change behavior at runtime.
* You want each algorithm to be independently testable.
* You want to add new behaviors without modifying the Context.

### Interview Recognition

> **"The system should support multiple ways of performing an operation, and the behavior should be selectable or changeable independently."**

Think:

> **Composition over inheritance + programming to an interface.**

---

## Important Properties

### 1. Encapsulation of algorithms

Each Strategy contains one variation of the behavior.

```text
CardPayment → Card-specific logic
UpiPayment  → UPI-specific logic
CashPayment → Cash-specific logic
```

### 2. Common interface

All Concrete Strategies implement the same interface, allowing the Context to treat them interchangeably.

### 3. Composition

The Context **HAS-A Strategy**, rather than inheriting from every possible behavior.

### 4. Runtime flexibility

The Strategy can be selected or replaced based on user choice, configuration, or application requirements.

**Note:** Strategy removes algorithm-specific logic from the Context. The selection logic may still exist elsewhere, such as a factory or composition root.

---

## Strategy vs Factory

These patterns are often confused because both may involve interfaces and multiple implementations, but their purposes are different.

| Strategy                                                  | Factory                                                                  |
| --------------------------------------------------------- | ------------------------------------------------------------------------ |
| **Behavioral pattern**                                    | **Creational pattern**                                                   |
| Encapsulates interchangeable algorithms                   | Encapsulates object creation                                             |
| Focuses on **how an operation is performed**              | Focuses on **which object to create**                                    |
| Context uses a Strategy to perform work                   | Client uses a Factory to obtain an object                                |
| Can change behavior at runtime                            | Usually decides which concrete object to instantiate                     |
| Example: `CardPayment`, `UpiPayment` as payment behaviors | Example: `PaymentFactory` creating `CardPayment` or `UpiPayment` objects |

### Simple distinction

> **Strategy decides how to do something. Factory decides which object to create.**

### Can they be used together?

**Yes.** A Factory can create the appropriate Strategy, and the Context can then use it.

```text
Factory → Creates Strategy
              ↓
           Context
```

For example:

```text
PaymentFactory
 ├── creates CardPayment
 └── creates UpiPayment

PaymentService
 └── uses PaymentStrategy
```

**Important:** A Factory is not a replacement for Strategy. One handles creation; the other handles interchangeable behavior.

---

## Strategy vs Decorator

| Strategy                                | Decorator                                   |
| --------------------------------------- | ------------------------------------------- |
| Behavioral pattern                      | Structural pattern                          |
| Encapsulates interchangeable algorithms | Adds responsibilities through wrapping      |
| Usually selects one behavior            | Can stack multiple behaviors                |
| Focuses on **how something is done**    | Focuses on **what extra behavior is added** |
| Context delegates to a Strategy         | Decorator delegates to a wrapped Component  |

> **Strategy changes how an operation is performed; Decorator adds responsibilities to an existing object.**

---

## Strategy vs State

| Strategy                                 | State                                                  |
| ---------------------------------------- | ------------------------------------------------------ |
| Focuses on selecting an algorithm        | Focuses on behavior based on internal state            |
| Usually selected by client/configuration | Changes as the Context's state changes                 |
| Strategies are interchangeable behaviors | States represent different conditions of an object     |
| Example: `CardPayment`, `UpiPayment`     | Example: `PendingState`, `PaidState`, `CancelledState` |

> **Strategy is about choosing behavior; State is about behavior changing because the object's state changes.**

---

## Real-World Examples

| Use Case    | Strategies                     |
| ----------- | ------------------------------ |
| Payment     | Card, UPI, Cash                |
| Sorting     | QuickSort, MergeSort, HeapSort |
| Routing     | Fastest, Shortest, AvoidTolls  |
| Discount    | Festival, Premium, Seasonal    |
| Compression | ZIP, GZIP, NoCompression       |

---

## Advantages

* **Reduces conditional complexity** by separating algorithms.
* **Follows Open/Closed Principle** — new strategies can be added without modifying the Context.
* **Improves testability** — strategies can be tested independently.
* **Supports runtime flexibility** — behavior can be changed by replacing the Strategy.
* **Promotes composition over inheritance.**

---

## Disadvantages

* May introduce **many small classes**.
* The client or composition layer must decide which Strategy to use.
* Can be **overengineering for simple, stable logic**.
* Strategies may become awkward if they require excessive shared data from the Context.

---

## Interview Recognition

When you see:

> **"There are multiple ways to perform an operation, and the system should support changing or selecting the behavior without modifying the main class."**

Think:

**Strategy.**

Examples:

```text
Payment → Card / UPI / Cash
Sorting → QuickSort / MergeSort
Routing → Fastest / Shortest
Discount → Festival / Premium
```

### Key Question

> **"Do I have a family of interchangeable algorithms that should be encapsulated and selected independently of the object using them?"**

If yes, Strategy is a strong candidate.

---

## One-Line Interview Definition

> **Strategy is a behavioral design pattern that encapsulates a family of interchangeable algorithms behind a common interface, allowing an object to select or change its behavior at runtime without modifying the object that uses it.**
