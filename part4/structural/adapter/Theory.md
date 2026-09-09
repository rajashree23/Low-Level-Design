# Adapter Pattern

## What is Adapter?

Adapter is a **structural design pattern** that allows two **incompatible interfaces** to work together.

The key idea:

> **Expose an interface expected by the client while internally adapting an existing/legacy interface.**

The Adapter acts as a **bridge between the client and an incompatible existing class**.

---

## Why do we need Adapter?

We use Adapter when:

* An existing class has a useful implementation but its interface **doesn't match what the client expects**.
* We want to integrate **legacy code** with new code.
* We cannot or don't want to modify the existing class.
* We need to make **incompatible interfaces work together**.

### Simple Example

```text
Client
  ↓
Expected Interface
  ↓
Adapter
  ↓
Existing / Legacy Class
```

The client only knows about the expected interface.
The Adapter translates the client's calls into calls understood by the existing class.

---

## When should I use Adapter?

Use Adapter when:

> **You have an existing class that works, but its interface doesn't match what your client expects.**

### Interview recognition

If the problem says:

* "Existing/legacy class cannot be modified"
* "Interfaces are incompatible"
* "Need to integrate an old system with a new system"
* "Client expects interface X, but existing class provides interface Y"

Think:

> **Adapter Pattern**

---

## Advantages

* **Reuses existing code** without modifying it.
* **Decouples** the client from the incompatible/legacy class.
* Makes integration of **third-party or legacy components** easier.
* Follows the **Open/Closed Principle** — we can adapt existing behavior without modifying the existing class.

---

## Disadvantages

* Adds an **extra layer/class**.
* Can make the design slightly more complex.
* Too many adapters can make the code harder to understand.

---

## Important Interview Point

### Adapter vs Facade

**Adapter:**

> Converts **one interface into another interface** so incompatible classes can work together.

**Facade:**

> Provides a **simplified interface** over multiple complex subsystems.

### Easy way to remember

```text
Adapter → Interface mismatch
Facade  → Complexity hiding
```

---

## Important Implementation Point in C++

An Adapter can commonly be implemented using:

### 1. Composition

```cpp
class Adapter : public Target
{
    Adaptee adaptee;
};
```

The Adapter **contains** the existing class.

### 2. Inheritance

The Adapter can inherit from the target interface and adapt the existing class.

In most real-world designs, **composition is preferred** because it gives better flexibility and lower coupling.

---

## One-Line Interview Definition

> **Adapter is a structural design pattern that converts the interface of an existing class into an interface expected by the client, allowing incompatible classes to work together.**
