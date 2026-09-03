# Design Principles

## 1. KISS — Keep It Simple, Stupid

**What it means:**
Prefer the **simplest solution that correctly solves the current problem**.

**Key idea to remember:**

> Don't add complexity unless the problem requires it.

* Don't introduce design patterns just to show knowledge.
* A simple `if/else` is better than Strategy Pattern if the problem is simple.
* A single class is fine if it isn't becoming messy.
* Add abstraction/patterns **when complexity or changing requirements justify them**.

**Interview mindset:**

> Start simple → identify actual complexity → introduce abstraction when needed.

---

## 2. DRY — Don't Repeat Yourself

**What it means:**
Avoid duplicating the same logic/business rule in multiple places.

**Key idea to remember:**

> One piece of knowledge/logic should ideally have one source of truth.

**Example:**

* Same email validation in 3 places → extract shared validation logic.

But don't overdo DRY:
Code that looks similar may have different responsibilities. Forcing it into one abstraction can create unnecessary coupling.

**Interview mindset:**

> Don't eliminate duplication blindly. Ask whether the logic is **conceptually the same**.

---

## 3. YAGNI — You Aren't Gonna Need It

**What it means:**
Implement what is required now, not hypothetical future requirements.

**Key idea to remember:**

> Don't build features just because they might be needed later.

**Example:**

* Parking lot requirements don't mention EV charging → don't build an EV charging architecture "just in case."

**Important:**
YAGNI does not mean designing badly for change.

You can:

* keep the design reasonably extensible
* avoid hard-to-change decisions

But don't implement unrequested features.

**Interview mindset:**

> Design for reasonable extension, but implement only current requirements.


## 4. Separation of Concerns

**What it means:**

Different parts of the system should handle **different responsibilities**, instead of mixing unrelated logic together.

**Key idea to remember:**

> Keep different concerns separate so that each part of the system has a clear responsibility.

* UI/display logic should not contain business logic.
* Business logic should not depend on how data is stored.
* Input handling should be separate from core application logic.
* Each class/module should focus on a clear responsibility.

**Example:**

Instead of having a `TicTacToe` class handle:

* taking user input
* displaying the board
* validating moves
* checking the winner

Separate these responsibilities into appropriate classes such as:

```cpp
Board
InputHandler
Display
```

**Important:**

Separation of Concerns is closely related to **Single Responsibility Principle**, but they aren't exactly the same.

* **SRP:** A class should have one reason to change.
* **Separation of Concerns:** Different concerns/responsibilities should be kept separate throughout the system.

**Interview mindset:**

> Don't mix unrelated responsibilities. Separate concerns so changes in one area don't unnecessarily affect others.

---

## 5. Law of Demeter — Principle of Least Knowledge

**What it means:**

An object should interact mainly with its **immediate collaborators** instead of navigating through a chain of unrelated objects.

**Key idea to remember:**

> Don't make a class depend on the internal structure of other objects.

**Example:**

Instead of:

```cpp
order.getCustomer().getAddress().getZipCode();
```

Prefer:

```cpp
order.getCustomerZipCode();
```

Now `Order` handles the navigation internally.

**Why it matters:**

Deep navigation creates **tight coupling**.

If the structure changes:

```text
Order → Customer → Address → ZipCode
```

the caller may need to change too.

With:

```cpp
order.getCustomerZipCode();
```

the internal structure can change without affecting the caller.

**Important:**

Method chaining itself is **not** a violation.

For example:

```cpp
builder.setName("John")
       .setAge(30)
       .build();
```

is generally fine because the builder methods operate on the same object.

The problem is chaining through **different objects to reach their internals**.

**Interview mindset:**

> Ask objects for what you need instead of navigating through their internal object graph.
