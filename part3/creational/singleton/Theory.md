# Singleton

## What is Singleton?

Singleton is a **creational design pattern** that ensures that **only one instance of a class exists** and provides a way to access that instance.

It is useful when the application genuinely needs **one shared instance** of something.

Common examples:

* Logger
* Configuration Manager
* Application-wide Resource Manager

For example:

```cpp
Logger::getInstance().log("Application started");
```

Every call to `getInstance()` returns the **same Logger instance**.

---

## How does Singleton ensure one instance?

A Singleton typically has:

1. **Private constructor**
   Prevents other classes from directly creating objects.

2. **A single stored instance**
   The class keeps the one instance internally.

3. **A public `getInstance()` method**
   Provides access to that instance.

Conceptually:

```text
Client
  |
  v
getInstance()
  |
  v
Single Singleton Instance
```

---

## When should I use Singleton?

Use Singleton when the design genuinely requires **exactly one shared instance**.

Examples:

```text
Logger
Configuration Manager
Application-wide Resource Manager
```

However, don't use Singleton simply because multiple classes need to access the same object.

---

## Why can Singleton be problematic?

Singleton introduces **global shared state**.

Because the Singleton can be accessed from many places:

```cpp
SingletonLogger::getInstance()
```

many classes can directly depend on it.

This can cause:

* **Hidden dependencies** — a class may depend on the Singleton without showing it in its constructor.
* **Harder testing** — replacing the Singleton with a mock/fake implementation becomes difficult.
* **Tighter coupling** — classes become directly coupled to the Singleton.
* **Global shared state** — many parts of the application access the same object.

### Example

Instead of:

```cpp
class UserService {
public:
    UserService(Logger& logger)
        : logger(logger) {}

private:
    Logger& logger;
};
```

the class could directly access:

```cpp
SingletonLogger::getInstance();
```

The first version makes the dependency obvious:

```text
UserService
     |
     v
   Logger
```

When someone sees:

```cpp
UserService(Logger& logger)
```

they immediately know:

> UserService needs a Logger.

With:

```cpp
SingletonLogger::getInstance();
```

the dependency is hidden inside `UserService`.

---

## Prefer Dependency Injection when possible

If we simply need to **share an object**, we don't necessarily need Singleton.

We can create the shared object at a higher level and pass it to the classes that need it:

```cpp
Logger logger;

UserService userService(logger);
OrderService orderService(logger);
PaymentService paymentService(logger);
```

Now the dependencies are explicit:

```text
             Logger
            /  |  \
           /   |   \
          v    v    v
       User  Order Payment
      Service Service Service
```

This also makes testing easier because we can pass a mock/fake Logger.

### Important distinction

> **Singleton:** We need exactly one instance.

> **Dependency Injection:** We need to share/provide an object.

Don't automatically use Singleton just because an object is shared.

---

## Singleton vs normal class

### Normal class

Multiple instances can exist:

```cpp
Logger logger1;
Logger logger2;
```

```text
Logger 1
Logger 2
```

### Singleton

Only one instance is allowed:

```text
        getInstance()
              |
              v
       Single Logger
        /    |    \
       /     |     \
   Service Service Service
```

---
## Advantages
1. Guarantees a single instance

The class controls its own construction, ensuring that only one instance exists.

2. Provides a common access point

All parts of the application can access the same instance through getInstance().

3. Avoids repeated creation of expensive resources

If creating an object is expensive and the design genuinely requires only one instance, Singleton can avoid unnecessary repeated initialization.

4. Maintains shared state

When the application genuinely needs one shared state or resource, Singleton provides a single place to maintain it.

---

## Disadvantages

1. Introduces global shared state

The Singleton behaves similarly to global state, making its state accessible from many parts of the application.

2. Hides dependencies

A class can access the Singleton internally without declaring it as a dependency in its constructor.

```cpp
class UserService {
public:
    void createUser() {
        SingletonLogger::getInstance().log("Creating user");
    }
};
```

It is not immediately obvious that UserService depends on Logger.

3. Makes testing harder

Because the class directly accesses the Singleton, replacing it with a mock or fake during testing can be difficult.

4. Increases coupling

Classes that directly call getInstance() become coupled to the Singleton implementation.

5. Concurrency concerns

In a multithreaded application, Singleton initialization and access must be implemented safely to ensure that multiple instances aren't accidentally created.

6. Can become a "god object"

If too much functionality is placed inside a Singleton, it can become a central object that many unrelated parts of the system depend on, making the design harder to maintain.

---

## Interview Summary

If asked **"What is Singleton?"**:

> Singleton is a creational design pattern that ensures only one instance of a class exists and provides a global access point to that instance.

If asked **"Why not always use Singleton?"**:

> Singleton introduces global shared state, can hide dependencies, increase coupling, and make testing harder. If we only need to share an object, dependency injection is often a better approach.

### Remember

```text
Singleton
    ↓
Exactly ONE instance
    +
Global access to it
```

And:

> **Shared object ≠ automatically Singleton.**

Use Singleton when **the domain/design requires one instance**, not merely because many classes need access to the object.