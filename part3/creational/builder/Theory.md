# Builder

## What is Builder?

Builder is a **creational design pattern** used to create an object **step by step**, without putting all the construction logic into a large constructor.

It is useful when an object has **many optional parts or configuration choices**.

Instead of using a constructor with many parameters, where some parameters may be `null` or difficult to understand:

```cpp
User user(
    "John",
    25,
    "john@gmail.com",
    "123456",
    "India",
    true,
    false,
    ...
);
```

we can build the object incrementally:

```cpp
User user = UserBuilder()
    .setName("John")
    .setAge(25)
    .setEmail("john@gmail.com")
    .setCountry("India")
    .build();
```

This makes object creation more **readable, flexible, and easier to maintain**.

### When should I use Builder?

Builder is useful when:

* The object has **many optional fields**.
* There are many possible configurations of the same object.
* A constructor would have too many parameters.
* We want to avoid **telescoping constructors**.
* Object creation involves multiple configuration steps.

For example, an HTTP request may have:

```text
URL       -> required
Method    -> required
Headers   -> optional
Body      -> optional
Timeout   -> optional
Auth      -> optional
```

Instead of having a constructor with many parameters, we can build it step by step.

```cpp
RequestBuilder()
    .setUrl("/users")
    .setMethod("POST")
    .setHeader("Authorization", token)
    .setBody(body)
    .setTimeout(30)
    .build();
```

Other common examples:

* HTTP request builders
* Database/query builders
* Configuration objects
* Objects with many optional settings

### Important interview point

**Don't use Builder just because it exists.**

If the object only has 2-4 simple required fields:

```cpp
User user("John", 25, "john@gmail.com");
```

a normal constructor is usually enough.

If the interviewer has not described an object with **many optional fields or configuration choices**, Builder probably isn't necessary.

---

## Why do we need Builder?

The main problem Builder solves is the **telescoping constructor problem**.

Imagine:

```cpp
Computer(
    cpu,
    ram,
    storage,
    gpu,
    wifi,
    bluetooth,
    keyboard
);
```

As the number of optional parameters grows, the constructor becomes:

* Hard to read
* Easy to misuse
* Difficult to maintain
* Difficult to remember which argument corresponds to which field

Builder allows us to express the same construction clearly:

```cpp
ComputerBuilder()
    .setCPU("i7")
    .setRAM("32GB")
    .setStorage("1TB SSD")
    .setGPU("RTX 4070")
    .enableWiFi()
    .enableBluetooth()
    .build();
```

The code itself now explains **what is being configured**.

---

## Benefits

### 1. Readability

Instead of:

```cpp
User("John", 25, "john@gmail.com", "India", true, false);
```

we have:

```cpp
UserBuilder()
    .setName("John")
    .setAge(25)
    .setEmail("john@gmail.com")
    .setCountry("India")
    .setPremium(true)
    .build();
```

It is much easier to understand what each value represents.

### 2. Handles optional fields cleanly

We don't need to pass `null` or dummy values for fields we don't want.

```cpp
UserBuilder()
    .setName("John")
    .setAge(25)
    .setEmail("john@gmail.com")
    .build();
```

Optional fields can simply be left unset.

### 3. Avoids large constructors

Instead of having constructors with 8-10 parameters, the Builder handles the configuration.

### 4. Supports different configurations

The same Builder can create different versions of the same object:

```cpp
ComputerBuilder()
    .setCPU("i5")
    .setRAM("16GB")
    .build();
```

or:

```cpp
ComputerBuilder()
    .setCPU("i9")
    .setRAM("64GB")
    .setGPU("RTX 5090")
    .enableWiFi()
    .build();
```

Both create a `Computer`, but with different configurations.

---

## How does Builder work?

The basic flow is:

```text
Client
   |
   v
Builder
   |
   +-- setA()
   +-- setB()
   +-- setC()
   |
   +-- build()
         |
         v
      Product
```

The Builder stores the configuration and `build()` finally creates the actual object.

Example:

```cpp
class ComputerBuilder {
private:
    string cpu;
    string ram;
    string gpu;

public:
    ComputerBuilder& setCPU(string cpu) {
        this->cpu = cpu;
        return *this;
    }

    ComputerBuilder& setRAM(string ram) {
        this->ram = ram;
        return *this;
    }

    ComputerBuilder& setGPU(string gpu) {
        this->gpu = gpu;
        return *this;
    }

    Computer build() {
        return Computer(cpu, ram, gpu);
    }
};
```

The `return *this` allows method chaining:

```cpp
builder
    .setCPU(...)
    .setRAM(...)
    .setGPU(...);
```

This is commonly called a **fluent interface** or **method chaining**.

---

## Builder vs Factory

This is an important interview distinction.

### Factory

Factory answers:

> **Which object should I create?**

For example:

```cpp
ShapeFactory::create("circle");
```

The Factory decides which concrete type to create:

```text
Factory
   |
   +-- Circle
   +-- Square
   +-- Rectangle
```

### Builder

Builder answers:

> **How should I configure this object?**

For example:

```cpp
ComputerBuilder()
    .setCPU("i7")
    .setRAM("32GB")
    .setGPU("RTX 4070")
    .build();
```

The Builder is creating/configuring a `Computer` with different options:

```text
Builder
   |
   v
Computer
   |
   +-- CPU
   +-- RAM
   +-- GPU
   +-- WiFi
```

### Easy way to remember

> **Factory → Which object?**

> **Builder → How should the object be configured?**

---

## Builder vs Constructor

### Constructor

Use a constructor when object creation is simple:

```cpp
User("John", 25);
```

### Builder

Use Builder when there are many optional/configurable fields:

```cpp
UserBuilder()
    .setName("John")
    .setAge(25)
    .setEmail("john@gmail.com")
    .setCountry("India")
    .build();
```

So Builder is **not a replacement for constructors**.

It is useful when constructors become difficult to manage.

---


## Advantages
1. Improves readability

Named builder methods make it clear what each value represents.

```cpp
UserBuilder()
    .setName("John")
    .setAge(25)
    .setEmail("john@gmail.com")
    .build();
```

2. Handles optional parameters cleanly

We don't need constructors with many parameters or null/dummy values for fields that are not required.

3. Avoids telescoping constructors

Instead of creating multiple constructors with increasing numbers of parameters:

```cpp
User(name);
User(name, age);
User(name, age, email);
User(name, age, email, country);
```

we can use a single Builder with optional configuration methods.

4. Supports different configurations

The same Builder can create different configurations of the same object without creating separate subclasses.

---

## Disadvantages

1. Adds boilerplate

We introduce an additional Builder class and configuration methods.

For a simple object:

```cpp
User("John", 25);
```

may be better than:

```cpp
UserBuilder()
    .setName("John")
    .setAge(25)
    .build();
```
2. More code to maintain

The Builder adds another abstraction that needs to be maintained along with the actual object.

3. Can be overengineering

If an object has only a few simple parameters and no complicated construction logic, a normal constructor is usually sufficient.

## Interview Summary

If asked **"What is Builder Pattern?"**:

> Builder is a creational design pattern used to construct an object step by step. It is especially useful when an object has many optional fields or configuration choices. It avoids telescoping constructors and makes object creation more readable and maintainable.

### Remember

```text
Constructor
    ↓
Simple object creation

Factory
    ↓
Choose WHICH object to create

Builder
    ↓
Configure HOW an object is built
```
