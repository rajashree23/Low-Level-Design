# Abstraction

**Q) What is Abstraction?**

Abstraction means hiding complex implementation details and exposing only a clear and simple interface for the user to interact with.

For example, if my API processes different types of payments such as Credit Card and UPI, I can expose a simple `process()` method. The internal implementation of how each payment type is processed is hidden from the caller.

**Key Idea-**

> Hide complex implementation + expose a simple interface

---

**Q) Encapsulation vs Abstraction?**

**Encapsulation->** Internal state shouldn't be exposed. We should have controlled methods to modify the internal state.

**Abstraction->** Hide unnecessary implementation for the user and provide a simple, clean interface.

---

**Q) CPP Class members are private by default.**

---

**Q) Header files (.h) are for class declarations/interfaces**

---

**Q) Implementation files (.cpp) are for defining logic**

---

**Q) Enums/ enum class**

```cpp
enum class PaymentMethod

{

    UPI,

    CREDIT_CARD

};
```

---

**Q) How do I compile and run multiple C++ files?**

```bash
g++ *.cpp -o main

./main
```
