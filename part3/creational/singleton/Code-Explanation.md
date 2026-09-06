# Singleton — C++ Syntax Explained

This note explains the C++ syntax used in the Singleton implementation.

---

```cpp
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() = default;
};
```
---

# 1. The class

```cpp
class Singleton {
};
```

`class` is used to define a new type.

Here we are creating a type called:

```cpp
Singleton
```

We can normally create an object like:

```cpp
Singleton obj;
```

But Singleton will prevent this using a private constructor.

---

# 2. `public`

```cpp
class Singleton {
public:
    // accessible from outside
};
```

Anything under `public:` can be accessed from outside the class.

For example:

```cpp
Singleton::getInstance();
```

works because `getInstance()` is public.

---

# 3. `private`

```cpp
private:
    Singleton() = default;
```

Anything under `private:` cannot normally be accessed from outside the class.

The constructor is private, so this is not allowed:

```cpp
Singleton obj;  // ❌
```

This is one of the key things that makes Singleton work.

---

# 4. Constructor

A constructor has the same name as the class:

```cpp
Singleton()
```

Normally we could write:

```cpp
Singleton() {
}
```

But:

```cpp
Singleton() = default;
```

tells C++:

> Generate the normal/default constructor for me.

The important part here is that the constructor is **private**.

---

# 5. `static` function

```cpp
static Singleton& getInstance()
```

`static` here means the function belongs to the **class itself**, rather than to a particular object.

Therefore we can call:

```cpp
Singleton::getInstance();
```

Notice the `::`.

We don't need:

```cpp
Singleton obj;
obj.getInstance();
```

In fact, we can't create `obj` because the constructor is private.

---

# 6. `::` — scope resolution operator

```cpp
Singleton::getInstance();
```

`::` means:

> Access something belonging to `Singleton`.

For example:

```cpp
Singleton::getInstance()
```

means:

> Call `getInstance()` belonging to the `Singleton` class.

---

# 7. Return type

Look at:

```cpp
Singleton& getInstance()
```

The return type is:

```cpp
Singleton&
```

`Singleton` means the type.

`&` means **reference**.

So this function returns a reference to an existing Singleton object.

It does not create and return a new object.

---

# 8. Static local variable

Inside the function:

```cpp
static Singleton instance;
```

There are two important parts.

### `Singleton instance`

This normally means:

> Create an object called `instance` of type `Singleton`.

### `static`

The `static` means the local variable is created once and continues to exist between function calls.

So:

```cpp
static Singleton instance;
```

means:

> Create this Singleton object once and reuse it.

Conceptually:

```text
First call
    ↓
create instance
    ↓
return instance

Second call
    ↓
use existing instance
    ↓
return instance
```

---

# 9. `return`

```cpp
return instance;
```

This returns the object from the function.

Because the function returns:

```cpp
Singleton&
```

the returned value is a reference to the existing object.

---

# 10. Reference `&`

Consider:

```cpp
Singleton& obj = Singleton::getInstance();
```

`obj` is a reference to the existing Singleton.

Think of a reference as another name/access path to the same object.

```text
        Singleton object
              ↑
              |
          obj (reference)
```

It does not create another Singleton.

---

# 11. Copy constructor

This line:

```cpp
Singleton(const Singleton&) = delete;
```

is the **copy constructor**.

Don't worry about every piece yet.

The important idea is:

```cpp
Singleton a = b;
```

normally means:

> Create `a` by copying `b`.

Singleton does not want that because copying could create another instance.

So we write:

```cpp
Singleton(const Singleton&) = delete;
```

which means:

> Copying a Singleton is forbidden.

---

# 12. `const Singleton&`

In:

```cpp
Singleton(const Singleton&)
```

the parameter is a reference to a `const Singleton`.

This is the standard form of a copy constructor.

For now, remember:

```cpp
const Singleton&
```

is commonly used when passing an existing object to be copied.

---

# 13. `= delete`

```cpp
Singleton(const Singleton&) = delete;
```

`= delete` tells C++:

> This function exists, but you are not allowed to use it.

So:

```cpp
Singleton a = Singleton::getInstance();
```

is rejected.

---

# 14. Assignment operator

This line:

```cpp
Singleton& operator=(const Singleton&) = delete;
```

is the **copy assignment operator**.

It handles code like:

```cpp
a = b;
```

For Singleton, we don't want copying/assignment to create or replace Singleton state unexpectedly.

So we delete it.

---

# 15. `operator=`

```cpp
operator=
```

is C++ syntax for the assignment operator:

```cpp
a = b;
```

You can think of:

```cpp
Singleton& operator=(const Singleton&)
```

as:

> Define what happens when one Singleton is assigned to another.

Here we delete it.

---

# 16. Complete code with comments

```cpp
class Singleton {

public:

    // Static function.
    // Can be called using Singleton::getInstance()
    static Singleton& getInstance() {

        // Created only once.
        static Singleton instance;

        // Return reference to that same instance.
        return instance;
    }

    // Don't allow copying.
    Singleton(const Singleton&) = delete;

    // Don't allow assignment.
    Singleton& operator=(const Singleton&) = delete;


private:

    // Constructor is private.
    // Outside code cannot create Singleton objects.
    Singleton() = default;
};
```

---

# 17. How we use it

```cpp
Singleton& a = Singleton::getInstance();
Singleton& b = Singleton::getInstance();
```

Both `a` and `b` refer to the same object.

```text
                 Singleton
                     ↑
              ┌──────┴──────┐
              │             │
              a             b
           reference      reference
```

There is still only **one actual Singleton object**.

---

# 18. What to memorize vs understand

### Memorize this implementation

```cpp
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() = default;
};
```

### Understand these concepts

```text
private constructor
        ↓
can't create objects directly

static local instance
        ↓
one instance

static getInstance()
        ↓
access without creating object

delete copy operations
        ↓
can't create another one by copying
```

You **do not need to memorize every syntax explanation**. The goal is to understand what each part is doing so you can reproduce the implementation in an interview.


### Is it thread safe?

Yes. Since C++11, initialization of a function-local static variable is guaranteed to be thread-safe. Therefore static Singleton instance will be initialized exactly once even when multiple threads call getInstance() concurrently.
However, operations on Singleton's class state may require synchronisation.