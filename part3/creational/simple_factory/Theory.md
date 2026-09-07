# Simple Factory

## What is Simple Factory?

**Simple Factory** is a creational design approach that centralizes object creation logic in a single factory class and returns the appropriate object based on some input or condition.

The client asks the factory for an object instead of directly creating the concrete object.

> **Note:** Simple Factory is commonly discussed alongside the Factory patterns, but it is **not the formal GoF Factory Method pattern**.

## Why do we need Simple Factory?

Simple Factory hides object creation logic from the client and reduces the client's dependency on concrete classes.

For example, instead of the client doing:

```cpp
if (type == "email")
    new EmailNotification();
else if (type == "sms")
    new SMSNotification();
```

the client does:

```cpp
NotificationFactory::create(type);
```

The factory decides which concrete object to create.

### Benefit

If a new notification type is added, the creation logic is centralized in the **Factory** class instead of being scattered throughout the client code.


## Real-World Use Cases

Factories are commonly used in **frameworks and APIs** where the framework needs to create implementation-specific objects while exposing only an abstraction to the client.

### Example: Database Connection

Instead of the application directly creating concrete connection objects:

```cpp
new MySQLConnection();
new PostgreSQLConnection();
new MongoConnection();
```

the framework can provide:

```cpp
auto db = DatabaseFactory::create("mysql");
```

The factory decides which concrete implementation to create:

```text
Your Application
       |
       ↓
DatabaseFactory
       |
   ┌───┼────┐
   ↓   ↓    ↓
 MySQL  PG  Mongo
```

The application only works with the common abstraction, such as:

```cpp
Database* db;
```

This allows the framework to change the underlying implementation without requiring changes in client code.

### Why Frameworks Use Factories

* Hide concrete implementation details
* Centralize or control object creation
* Reduce coupling between client code and concrete classes
* Allow the framework to change implementations internally

> **Interview takeaway:** Factories are commonly used in frameworks and APIs where the framework needs to create implementation-specific objects while exposing only an abstraction to the client.

---

## Advantages
1. Centralizes object creation

All creation logic is kept in one place instead of being scattered across the client code.

2. Reduces coupling

The client depends on the common abstraction rather than directly depending on concrete classes.

auto notification = NotificationFactory::create(type);

The client doesn't need to know how EmailNotification or SMSNotification is instantiated.

3. Simplifies client code

The client doesn't need to contain repeated if/else or switch logic for choosing and creating objects.

4. Makes changes easier to manage

When object creation logic changes, we generally only need to update the Factory rather than every client that creates the object.

---

## Disadvantages
1. Factory can become a large conditional block

As more types are added, the factory can turn into:

```cpp
if (type == "email")
    return new EmailNotification();
else if (type == "sms")
    return new SMSNotification();
else if (type == "push")
    return new PushNotification();
else if (type == "slack")
    return new SlackNotification()
```

The Factory itself can become difficult to maintain.

2. Adding a new type requires modifying the Factory

If we add WhatsAppNotification, we usually need to modify the Factory.

This means the Simple Factory does not fully follow the Open/Closed Principle.

This is one of the important reasons the Factory Method Pattern exists.

3. Can be unnecessary for simple object creation

If there are only one or two concrete classes and the creation logic is trivial, introducing a Factory may add unnecessary abstraction.

---

### TODO
Factory Method