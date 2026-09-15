# Concurrency — C++ Implementation

## 1. `std::lock_guard` — ✅ Done

* Basic mutex locking
* Protect critical section
* RAII unlock

---

## 2. Shared Locks

* `std::shared_mutex`
* `std::shared_lock` for readers
* `std::unique_lock` for writers

---

## 3. `std::unique_lock`

* Write a small example
* Understand why/when it is more flexible than `lock_guard`
* Especially useful later with `condition_variable`

---

## 4. Fine-Grained Locking

Implement ticket booking with **one mutex per seat**.

### Test

* Different seats → can proceed concurrently
* Same seat → one waits

### Then

Implement a **two-seat operation** and handle deadlock using:

* Consistent lock ordering
* `std::scoped_lock`

---

## 5. Atomic

* Implement an atomic booking counter
* Implement a simple CAS example
* Understand when atomic is enough vs. when a mutex is needed
