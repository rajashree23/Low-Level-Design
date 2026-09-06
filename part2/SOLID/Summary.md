# The 5 Questions to Remember

## SRP

**Does this class have too many responsibilities?**

## OCP

**Will adding a new behavior require repeatedly modifying existing code?**

## LSP

**Can the child genuinely substitute the parent?**

## ISP

**Is the interface forcing clients/classes to implement things they don't need?**

## DIP

**Is my high-level code directly coupled to a concrete implementation?**

---

# SOLID in One Example

Suppose you're designing a payment system.

```text
PaymentService
      ↓
 PaymentMethod
   ↙       ↘
Card       UPI
```

You might be applying:

### SRP

→ PaymentService handles payment orchestration, not database + email + logging + everything else.

### OCP

→ Add PayPalPayment without rewriting the core payment flow.

### LSP

→ CardPayment and UPIPayment must behave correctly wherever PaymentMethod is expected.

### ISP

→ Don't create one huge interface containing unrelated payment operations.

### DIP

→ PaymentService depends on PaymentMethod, not directly on CardPayment.
