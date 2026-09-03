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
