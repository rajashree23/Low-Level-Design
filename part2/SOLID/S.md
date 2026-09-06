# S — Single Responsibility Principle (SRP)

**Meaning:**
A class should have one responsibility / one reason to change.

**Remember:**

One class should focus on one kind of responsibility.

### Bad

```cpp
class Order {
    void calculatePrice();
    void saveToDatabase();
    void sendEmail();
};
```

The class handles business logic, persistence, and notification.

### Better

```text
Order              → order data / business behavior
OrderRepository    → database
NotificationService → notifications
```

**Interview clue:**
If a class is doing many unrelated things → think SRP.
