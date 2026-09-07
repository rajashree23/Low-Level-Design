# Decorator Pattern

## What is Decorator?

Decorator is a **structural design pattern** that provides a way to **add behavior/responsibilities to an individual object without modifying its base class**.

The key idea is:

> **Wrap an object with another object that implements the same interface and adds some extra behavior.**

For example, consider a coffee ordering system.

We have a basic coffee:

```cpp
Coffee
```

Now a customer may optionally add:

```text
Milk
Sugar
Cream
Whipped Cream
```

Instead of creating subclasses for every possible combination:

```text
MilkCoffee
SugarCoffee
MilkSugarCoffee
MilkCreamCoffee
MilkSugarCreamCoffee
...
```

we create decorators:

```text
Coffee
  ↓
MilkDecorator
  ↓
SugarDecorator
  ↓
CreamDecorator
```

Each decorator **wraps the previous object**, adds its own behavior, and still behaves like a `Coffee`.

So decorators can be **stacked/composed dynamically**.

---

## Core Structure

There are usually four participants:

```text
             Component
                 ↑
        ┌────────┴────────┐
        │                 │
ConcreteComponent     Decorator
                          ↑
                 ┌────────┴────────┐
                 │                 │
          ConcreteDecoratorA  ConcreteDecoratorB
```

### 1. Component

Defines the common interface.

```cpp
class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
};
```

### 2. Concrete Component

The original/basic object.

```cpp
class SimpleCoffee : public Coffee {
public:
    string getDescription() override {
        return "Coffee";
    }

    double getCost() override {
        return 100;
    }
};
```

### 3. Decorator

Also implements the same interface and **contains a Component**.

```cpp
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;

public:
    CoffeeDecorator(Coffee* coffee) : coffee(coffee) {}
};
```

### 4. Concrete Decorator

Adds some additional behavior.

```cpp
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* coffee)
        : CoffeeDecorator(coffee) {}

    string getDescription() override {
        return coffee->getDescription() + ", Milk";
    }

    double getCost() override {
        return coffee->getCost() + 20;
    }
};
```

Another decorator:

```cpp
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* coffee)
        : CoffeeDecorator(coffee) {}

    string getDescription() override {
        return coffee->getDescription() + ", Sugar";
    }

    double getCost() override {
        return coffee->getCost() + 10;
    }
};
```

Now we can compose them:

```cpp
Coffee* coffee = new SimpleCoffee();

coffee = new MilkDecorator(coffee);
coffee = new SugarDecorator(coffee);
```

The final object behaves like a `Coffee`, but now has:

```text
Coffee + Milk + Sugar
```

---

# Why do we need Decorator?

The main problem Decorator solves is **subclass explosion caused by combinations of optional features**.

Suppose we have:

```text
Coffee
 ├── MilkCoffee
 ├── SugarCoffee
 ├── CreamCoffee
 ├── MilkSugarCoffee
 ├── MilkCreamCoffee
 ├── SugarCreamCoffee
 └── MilkSugarCreamCoffee
```

As the number of optional features increases, the number of combinations grows rapidly.

Decorator replaces this with independent, composable decorators:

```text
Coffee
 ├── MilkDecorator
 ├── SugarDecorator
 └── CreamDecorator
```

They can be freely combined.

---

# When should I use Decorator?

Use Decorator when:

* You need to add **optional features/behavior** to objects.
* Features can be **combined in different ways**.
* The combinations would otherwise lead to many subclasses.
* You want to add behavior **without modifying the original class**.
* The behavior should be applied to **individual objects**, rather than every instance of a class.
* Decorators may need to be **stacked dynamically**.

A good interview signal is:

> **"I have a base object and multiple optional/composable responsibilities that can be added independently."**

Think **composition instead of inheritance**.

---

# Important Properties

## 1. Decorator follows the same interface

This is one of the most important characteristics.

The decorator should generally implement the same interface as the object it decorates.

```text
Coffee
 ↑
MilkDecorator
```

Therefore:

```cpp
Coffee* coffee = new MilkDecorator(
    new SimpleCoffee()
);
```

The caller doesn't need to know whether it has a `SimpleCoffee` or a decorated coffee.

This gives us **transparency**.

---

## 2. Decorators can be stacked

This is one of the biggest advantages.

```cpp
Coffee* coffee = new SimpleCoffee();

coffee = new MilkDecorator(coffee);
coffee = new SugarDecorator(coffee);
coffee = new CreamDecorator(coffee);
```

Conceptually:

```text
CreamDecorator
      ↓
SugarDecorator
      ↓
MilkDecorator
      ↓
SimpleCoffee
```

Each decorator adds its own behavior while delegating the existing behavior to the wrapped object.

---

## 3. Decorators use composition

Instead of:

```text
MilkCoffee extends Coffee
```

we have:

```text
MilkDecorator HAS-A Coffee
```

So Decorator is fundamentally an example of:

> **Composition over inheritance.**

---

## 4. Behavior is added dynamically

The important distinction is that we don't have to decide the complete combination at class-design time.

For example:

```cpp
Coffee* coffee = new SimpleCoffee();

if (addMilk)
    coffee = new MilkDecorator(coffee);

if (addSugar)
    coffee = new SugarDecorator(coffee);
```

The final behavior is determined at runtime.

---

# Decorator vs Inheritance

### Inheritance

Inheritance creates behavior combinations at the **class level**.

```text
Coffee
  ↓
MilkCoffee
```

If we have many combinations, we can end up with many subclasses.

### Decorator

Decorator creates combinations at the **object level**.

```text
MilkDecorator(
    SugarDecorator(
        Coffee
    )
)
```

This makes behavior more flexible and composable.

---

# Decorator vs Strategy

These two patterns can look similar because both use composition.

### Strategy

Usually answers:

> **"Which algorithm/behavior should this object use?"**

Example:

```text
PaymentService
      ↓
PaymentStrategy
 ├── CardPayment
 ├── UpiPayment
 └── CashPayment
```

Typically, we choose **one strategy**.

### Decorator

Usually answers:

> **"What additional responsibilities should this object have?"**

Example:

```text
Coffee
  ↓
Milk
  ↓
Sugar
  ↓
Cream
```

Multiple decorators can be **stacked**.

A useful distinction:

> **Strategy replaces/chooses behavior; Decorator adds behavior around existing behavior.**

---

# Real-World Examples

Decorator appears frequently in real software.

### Java I/O

Java's I/O streams are a classic example.

Conceptually:

```text
FileInputStream
      ↓
BufferedInputStream
      ↓
DataInputStream
```

Each layer adds additional functionality while exposing a compatible interface.

### Web / Backend

Middleware is often decorator-like:

```text
Request
  ↓
Authentication
  ↓
Logging
  ↓
Rate Limiting
  ↓
Handler
```

Each layer wraps the next one and adds behavior.

### Logging / Caching / Authorization

A service can be wrapped with:

```text
LoggingDecorator
CachingDecorator
AuthorizationDecorator
```

without changing the original service implementation.

---

# Advantages

### 1. Avoids subclass explosion

We don't need a class for every feature combination.

### 2. Follows Open/Closed Principle

We can introduce new decorators without modifying the existing component.

### 3. Flexible composition

Decorators can be combined and reordered.

### 4. Runtime flexibility

Features can be added based on runtime requirements.

### 5. Single Responsibility

Each decorator can focus on one additional responsibility.

---

# Disadvantages

### 1. Many small classes

A decorator-heavy design can result in many small classes.

### 2. Debugging can become harder

The runtime object may look like:

```text
A(
  B(
    C(
      D(
        Component
      )
    )
  )
)
```

Tracing behavior through many layers can become difficult.

### 3. Order can matter

Decorators are not always commutative.

For example:

```text
Logging(
    Caching(
        Service
    )
)
```

may behave differently from:

```text
Caching(
    Logging(
        Service
    )
)
```

So the order of decorators can sometimes be important.

---

# Interview Recognition

When you see a requirement like:

> "The base object can have multiple optional features, and these features can be combined in different ways."

Think:

**Decorator.**

Examples:

```text
Coffee + Milk + Sugar
Notification + SMS + Email + Push
Service + Logging + Caching + Authorization
InputStream + Buffering + Compression
```

The key question to ask yourself is:

> **"Can I avoid creating subclasses for every possible combination by wrapping the object with independent feature classes?"**

If yes, Decorator is a strong candidate.

---

# One-Line Interview Definition

> **Decorator is a structural design pattern that dynamically adds responsibilities to an individual object by wrapping it with objects that implement the same interface, allowing multiple behaviors to be composed without creating subclasses for every combination.**
