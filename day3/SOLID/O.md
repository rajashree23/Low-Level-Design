# O — Open/Closed Principle (OCP)

**Meaning:**
Software should be open for extension but closed for modification.

**Remember:**

Adding a new behavior should ideally require adding new code, rather than repeatedly modifying existing working code.

## Example

**Bad:**

```cpp
if (paymentType == "CARD") {
    ...
}
else if (paymentType == "UPI") {
    ...
}
else if (paymentType == "PAYPAL") {
    ...
}
```

Every new payment method requires modifying this code.

**Better:**

```cpp
class PaymentMethod {
public:
    virtual void pay() = 0;
};

class CardPayment : public PaymentMethod {
    void pay() override { ... }
};

class UPIPayment : public PaymentMethod {
    void pay() override { ... }
};
```

Now a new payment method can be added as another implementation.

**Interview clue:**
If you keep adding if/else or switch cases for new types → think OCP and potentially Strategy Pattern.

**Important:**
OCP does not mean "never modify existing code."
Don't introduce abstractions for every hypothetical future requirement → balance with KISS/YAGNI.
