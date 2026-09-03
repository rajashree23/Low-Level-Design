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
