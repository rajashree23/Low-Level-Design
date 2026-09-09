# Proxy Pattern

## What is Proxy?

Proxy is a **structural design pattern** that provides a **substitute or placeholder object** that controls access to another real object.

The key idea:

> **Expose the same interface as the real object while controlling how, when, or whether the real object is accessed.**

The Proxy acts as an **intermediary between the client and the real object**.

---

## Why do we need Proxy?

We use Proxy when:

* We want to **control access** to an object.

* The real object is **expensive to create or use**.

* We want to add **authentication/authorization** before accessing the real object.

* We want to add **caching, logging, lazy loading, or remote access** without modifying the real object.

### Simple Example

```text
Client

  ↓

Proxy

  ↓

Real Object
```

The client interacts with the Proxy instead of directly accessing the Real Object.

The Proxy decides whether/how to forward the request to the Real Object.

---

## When should I use Proxy?

Use Proxy when:

> **You want to control access to an object without changing the object itself.**

### Interview recognition

If the problem says:

* "Check authentication/authorization before accessing..."

* "Create an expensive object only when it is actually needed"

* "Cache the result of expensive operations"

* "Log requests before forwarding them"

* "Control access to the real service"

* "Client should not directly interact with the real object"

Think:

> **Proxy Pattern**

---

## Advantages

* Provides **access control** without modifying the real object.

* Supports **lazy initialization** of expensive objects.

* Can add **caching, logging, authentication, etc.**

* Keeps the client **decoupled from the real object**.

* Can control access to **remote or expensive resources**.

---

## Disadvantages

* Adds an **extra layer/class**.

* Can make the design slightly more complex.

* May introduce **additional overhead**.

* Proxy can become tightly coupled to the Real Object if it handles too much logic.

---

## Important Interview Point

### Proxy vs Adapter

**Proxy:**

> Provides the **same interface** as the real object and controls access to it.

**Adapter:**

> Converts an **incompatible interface** into the interface expected by the client.

### Easy way to remember

```text
Proxy   → Access control

Adapter → Interface mismatch
```

---

### Proxy vs Decorator

**Proxy:**

> Controls **access** to an object.

**Decorator:**

> Adds **additional behavior/responsibility** to an object.

### Easy way to remember

```text
Proxy     → Control

Decorator → Enhance
```

**---**

## Important Implementation Point in C++

A Proxy commonly uses:

### 1. Same Interface

Both the Proxy and Real Object implement the same interface.

```cpp
class Service
{
public:
    virtual void request() = 0;
    virtual ~Service() = default;
};
```

### 2. Composition

The Proxy **contains or holds a reference/pointer to the Real Object**.

```cpp
class Proxy : public Service
{
private:
    RealService service;

public:
    void request() override
    {
        // access control / logging / caching
        service.request();
    }
};
```

The client interacts with the **interface**, not directly with the Real Object.

```text
Client
  ↓
Service Interface
  ↑
Proxy
  ↓
RealService
```

**---**

## Common Types of Proxy

### Virtual Proxy

Controls creation of an **expensive object**.

> Example: Lazy loading an image.

### Protection Proxy

Controls access based on **permissions/authentication**.

> Example: Only authenticated users can access a video.

### Caching Proxy

Stores results and returns the **cached result** when possible.

> Example: Cache database/API responses.

### Remote Proxy

Represents an object that exists in a **different process/server**.

> Example: Client interacts with a remote service through a local proxy.

---

## One-Line Interview Definition

> **Proxy is a structural design pattern that provides a substitute object with the same interface as the real object and controls access to it.**
