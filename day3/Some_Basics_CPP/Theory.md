# Class & Object

```cpp
class Car {
public:
    string brand;
};

Car c1;  // object
```

## Access modifiers

* `public` → accessible from outside
* `private` → only inside class
* `protected` → class + derived classes

## Constructors

* Default constructor
* Parameterized constructor
* Constructor overloading

```cpp
Car() {}
Car(string b) {}
```

## Destructor

```cpp
~Car() {}
```

## this pointer

```cpp
Car(string brand) {
    this->brand = brand;
}
```

## Inheritance

```cpp
class Dog : public Animal {};
```

## Polymorphism

* `virtual`
* pure virtual function `= 0`
* `override`
* abstract class

## Composition

```cpp
class Car {
    Engine engine;
};
```

## Pointers & references

Understanding the foundational difference between **Pointers** (`T*`) and **References** (`T&`) in C++:

- `T*` → **Pointer**: Stores the memory address of an object.
- `T&` → **Reference**: Acts as an alias/another name for an existing object.

---

### 1. Pointer Approach (`PaymentMethod*`)

#### Declaration & Constructor
```cpp
class PaymentService {
private:
    PaymentMethod* method;

public:
    PaymentService(PaymentMethod* method) : method(method) {}

    void process() {
        method->pay(); // Use arrow operator (->) for pointers
    }
};
```

#### Usage (Pass the Address)
```cpp
PaymentMethod payment;
PaymentService service(&payment); // Pass address using & operator
```

---

### 2. Reference Approach (`PaymentMethod&`)

#### Declaration & Constructor
```cpp
class PaymentService {
private:
    PaymentMethod& method;

public:
    PaymentService(PaymentMethod& method) : method(method) {}

    void process() {
        method.pay(); // Use dot operator (.) for references
    }
};
```

#### Usage (Pass the Object Itself)
```cpp
PaymentMethod payment;
PaymentService service(payment); // Pass the object directly
```

---

## Member Access Summary

| Type | Syntax | Access Inside Function |
| :--- | :--- | :--- |
| **Pointer (`T*`)** | `PaymentService(&payment);` | `method->pay();` |
| **Reference (`T&`)** | `PaymentService(payment);` | `method.pay();` |

---

## Key Idea to Remember

- `*` → Pointer to an object
- `&` → Reference to an object

## Smart pointers — basic

* `unique_ptr`
* `shared_ptr`
* `make_unique`
* `make_shared`

### `unique_ptr`

**What it is:**

`unique_ptr` is a smart pointer that represents **unique ownership** of an object.

It automatically destroys the object when the `unique_ptr` goes out of scope, so we don't need to manually call `delete`.

**Why do we need it?**

With a normal pointer:

```cpp
Notification* notification = new EmailNotification();

notification->send("hello");

delete notification;
```

We are responsible for managing the object's lifetime.

If we forget:

```cpp
delete notification;
```

we can cause a **memory leak**.

With `unique_ptr`:

```cpp
std::unique_ptr<Notification> notification =
    std::make_unique<EmailNotification>();

notification->send("hello");
```

The object is automatically cleaned up when `notification` goes out of scope.

**Key difference:**

```text
Normal pointer (*)     → points to an object
unique_ptr             → owns an object
```

**Syntax:**

Normal pointer:

```cpp
Notification* notification = new EmailNotification();

notification->send("hello");

delete notification;
```

`unique_ptr`:

```cpp
std::unique_ptr<Notification> notification =
    std::make_unique<EmailNotification>();

notification->send("hello");
```

No `delete` is required.

---

### `make_unique`

**What it is:**

`make_unique` is a helper function used to **create an object and return a `unique_ptr` that owns it**.

```cpp
auto notification = std::make_unique<EmailNotification>();
```

Here:

```text
make_unique
    ↓
creates EmailNotification
    ↓
returns unique_ptr<EmailNotification>
```

So:

```cpp
std::unique_ptr<EmailNotification> notification =
    std::make_unique<EmailNotification>();
```

and:

```cpp
auto notification =
    std::make_unique<EmailNotification>();
```

are essentially the same. `auto` lets C++ infer the type.

**Important distinction:**

```text
unique_ptr     → smart pointer / ownership type

make_unique    → helper used to create the object
```

---

### `unique_ptr` with Polymorphism

`unique_ptr` can also hold a derived object through a base-class pointer:

```cpp
std::unique_ptr<Notification> notification =
    std::make_unique<EmailNotification>();

notification->send("hello");
```

Here:

```text
unique_ptr<Notification>
        ↓
EmailNotification object
```

This gives us both:

* **Runtime polymorphism** through the base class
* **Automatic memory management** through `unique_ptr`

**Interview takeaway:**

> Use `unique_ptr` when one object should have ownership of another object and that object should be automatically destroyed when the owner goes out of scope.

**For LLD:**

Prefer modern C++ ownership with `unique_ptr` rather than manually using `new` and `delete` when you have **single ownership**.





### NOTE: 
All the above topics can be covered as you proceed further in LLD designs; don't spend days mastering CPP concepts and then do LLD. Do these as you encounter them. Learn as you code princple.