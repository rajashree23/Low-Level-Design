# 4. I — Interface Segregation Principle (ISP)

**Meaning:**
Clients should not be forced to depend on methods they don't need.

**Remember:**

Prefer small, focused interfaces over large "do everything" interfaces.

## Bad

```cpp
class Machine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};
```

A basic printer shouldn't have to implement scan() and fax().

## Better

```cpp
class Printer {
public:
    virtual void print() = 0;
};

class Scanner {
public:
    virtual void scan() = 0;
};

class Fax {
public:
    virtual void fax() = 0;
};
```

**Interview clue:**
If a class implements methods like:

* throw NotSupportedException();
* or has many methods it doesn't actually need → think ISP.

**Key distinction:**

> ISP = Is my interface too large?
