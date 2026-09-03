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

Particularly because LLD designs often pass dependencies:

```cpp
PaymentService(PaymentMethod* method)
```

## Smart pointers — basic

* `unique_ptr`
* `shared_ptr`
* `make_unique`
* `make_shared`


### NOTE: 
All the above topics can be covered as you proceed further in LLD designs; don't spend days mastering CPP concepts and then do LLD. Do these as you encounter them. Learn as you code princple.