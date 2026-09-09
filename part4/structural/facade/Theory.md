# Facade Pattern

## What is Facade?

Facade is a **structural design pattern** that provides a **simple
interface to interact with a complex system**, instead of making the
client call multiple subsystem classes directly.

The key idea is:

> **Expose a single simple interface to hide complex subsystem
> interactions.**

The Facade does **not replace the subsystems**. It simply provides a
convenient entry point to use them.

------------------------------------------------------------------------

## Why do we need Facade?

Without a Facade, the client may need to know about and coordinate
multiple classes:

``` cpp
CPU cpu;
Memory memory;
HardDrive hardDrive;

cpu.start();
memory.load();
hardDrive.read();
cpu.execute();
```

The client is now coupled to the internal steps of the system.

With a Facade:

``` cpp
Computer computer;
computer.start();
```

The Facade internally coordinates the subsystems:

``` cpp
class Computer {
private:
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;

public:
    void start() {
        cpu.start();
        memory.load();
        hardDrive.read();
        cpu.execute();
    }
};
```

The client only needs to know about `Computer`.

### Main problem Facade solves

**Complex subsystem interaction leaking into the client.**

------------------------------------------------------------------------

## Structure

``` text
Client
  |
  v
Facade
  |
  +----> Subsystem A
  |
  +----> Subsystem B
  |
  +----> Subsystem C
```

The client depends mainly on the **Facade**, while the Facade
coordinates the subsystem classes.

------------------------------------------------------------------------

## When should I use Facade?

Use Facade when:

-   A system has **many classes/subsystems** that the client must
    coordinate.
-   The client needs to know too much about the **internal workflow**.
-   You want to provide a **simple entry point** to a complex subsystem.
-   You want to reduce **coupling between clients and subsystem
    implementation details**.
-   You are exposing a complex module/library/API to other parts of the
    application.

### Don't use Facade just to hide every class

If the subsystem is already simple, adding a Facade can be unnecessary
abstraction.

------------------------------------------------------------------------

## Simple Example

Imagine an order checkout system:

``` cpp
class Inventory {
public:
    bool checkStock() {
        return true;
    }
};

class Payment {
public:
    void pay() {
        // process payment
    }
};

class Shipping {
public:
    void ship() {
        // arrange shipping
    }
};
```

Without a Facade:

``` cpp
Inventory inventory;
Payment payment;
Shipping shipping;

if (inventory.checkStock()) {
    payment.pay();
    shipping.ship();
}
```

The client knows the complete checkout workflow.

With a Facade:

``` cpp
class OrderFacade {
private:
    Inventory inventory;
    Payment payment;
    Shipping shipping;

public:
    void placeOrder() {
        if (inventory.checkStock()) {
            payment.pay();
            shipping.ship();
        }
    }
};
```

Now the client only does:

``` cpp
OrderFacade order;
order.placeOrder();
```

The workflow is hidden behind the Facade.

------------------------------------------------------------------------

## Facade vs Adapter

  -----------------------------------------------------------------------
  Facade                              Adapter
  ----------------------------------- -----------------------------------
  Simplifies a complex subsystem      Makes incompatible interfaces work
                                      together

  Usually coordinates multiple        Usually wraps one existing class
  classes                             

  Focuses on **simplicity**           Focuses on **compatibility**

  Client uses a simpler interface     Client expects a specific interface
  -----------------------------------------------------------------------

**Easy way to remember:**

> **Facade = simplify**\
> **Adapter = convert**

------------------------------------------------------------------------

## Facade vs Decorator

  -----------------------------------------------------------------------
  Facade                              Decorator
  ----------------------------------- -----------------------------------
  Provides a simpler interface        Adds/responsibilities to an object

  Hides subsystem complexity          Wraps an object to extend behavior

  Usually coordinates multiple        Usually wraps one component
  objects                             

  Does not primarily add behavior to  Adds behavior dynamically
  the wrapped object                  
  -----------------------------------------------------------------------

**Easy way to remember:**

> **Facade = simplify access**\
> **Decorator = add behavior**

------------------------------------------------------------------------

## Real-World Examples

-   **Payment service:** One `pay()` method internally handles
    validation, payment gateway, fraud checks, and receipt generation.
-   **Video/Audio processing:** One `convert()` method hides decoding,
    processing, encoding, and file writing.
-   **Database access:** A repository/service can hide connection,
    query, transaction, and mapping details.
-   **Framework APIs:** A high-level API often provides a simpler entry
    point over several lower-level components.

------------------------------------------------------------------------

## Advantages

-   **Reduces coupling** between clients and subsystem classes.
-   **Hides implementation complexity**.
-   Provides a **simple and clean API**.
-   Makes client code easier to understand.
-   Makes subsystem changes less likely to affect clients.

------------------------------------------------------------------------

## Disadvantages

-   Can become a **God class** if too much logic is placed inside the
    Facade.
-   Adds another abstraction layer when the system is already simple.
-   Clients may still need direct access to subsystems for advanced use
    cases.

------------------------------------------------------------------------

## Important Interview Point

A Facade **does not necessarily restrict access** to the subsystem.

The subsystems can still be used directly when needed.

The Facade simply provides a **higher-level, simpler interface** for
common operations.

------------------------------------------------------------------------

## Interview Recognition

If the interviewer describes:

> "There are many subsystem classes, and the client has to call them in
> a particular sequence. We want to expose one simple method instead."

Think:

**Facade Pattern**

Typical keywords:

-   Complex subsystem
-   Simplified interface
-   Hide implementation details
-   Single entry point
-   Reduce client coupling
-   Coordinate multiple components

------------------------------------------------------------------------

## One-Line Interview Definition

> **Facade is a structural design pattern that provides a simple,
> unified interface over a complex subsystem, hiding its internal
> interactions from the client.**
