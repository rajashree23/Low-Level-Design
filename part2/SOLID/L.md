# L — Liskov Substitution Principle (LSP)

**Meaning:**
A child class should be usable wherever the parent class is expected without breaking the expected behavior/contract.

**Remember:**

If B is a subtype of A, replacing A with B should not break the program.

## Example

```cpp
class Bird {
public:
    virtual void fly() = 0;
};

class Penguin : public Bird {
public:
    void fly() override {
        // Penguin cannot fly
        throw std::runtime_error("I can't fly!");
    }
};
```

```cpp
Bird* bird = new Penguin();
bird->fly();   // breaks
```

The abstraction is wrong because Penguin cannot properly fulfill the Bird::fly() contract.

**Interview clue:**
If a subclass:

* throws "not supported"
* ignores a parent method
* changes expected behavior
* requires special checks before using it

→ suspect LSP violation.

**Key distinction:**

> LSP = Is the inheritance relationship actually valid?

**Different betwen ISP and LSP:**

| Principle | Question                                              |
| --------- | ----------------------------------------------------- |
| **ISP**   | "Am I forcing you to implement stuff you don't need?" |
| **LSP**   | "Can I safely treat you as the parent?"               |
