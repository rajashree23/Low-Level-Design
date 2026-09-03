# 5. D — Dependency Inversion Principle (DIP)

**Meaning:**
High-level modules should not depend directly on low-level concrete implementations. Both should depend on abstractions.

**Remember:**

Depend on interfaces/abstractions, not concrete implementations.

## Bad

```cpp
class PaymentService {
    StripePayment stripe;

public:
    void pay() {
        stripe.pay();
    }
};
```

PaymentService is tightly coupled to StripePayment.

## Better

```cpp
class PaymentMethod {
public:
    virtual void pay() = 0;
};

class PaymentService {
    PaymentMethod* paymentMethod;

public:
    PaymentService(PaymentMethod* method)
        : paymentMethod(method) {}

    void pay() {
        paymentMethod->pay();
    }
};
```

Now PaymentService doesn't care whether payment is:

* Stripe
* Razorpay
* PayPal
* UPI
* MockPayment

It depends only on the abstraction.

**Interview clue:**
If you see:

```text
HighLevelClass → ConcreteDependency
```

ask whether it should become:

```text
HighLevelClass → Interface ← ConcreteDependency
```
