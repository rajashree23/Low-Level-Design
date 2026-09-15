## Problem: Ticket Booking Race Condition

Suppose multiple users try to book the same seat concurrently.

The booking operation is logically:

```text
1. Check whether the seat is available
2. If available, assign it to the user
```

Without synchronization, two threads may interleave like this:

```text
Thread 1                    Thread 2

Check seat → available
                            Check seat → available

Book seat
                            Book seat
```

Both threads believe the seat is available and proceed with the booking.

This violates the business invariant:

> **A seat must be assigned to at most one user.**

This is a **correctness problem caused by a race condition**.

The important point is that the problem is not merely that threads share a resource. The problem is that multiple threads access **shared mutable state** without protecting a multi-step operation that must be performed atomically.

---

## Solution: Coarse-Grained Locking

A mutex can protect the entire critical section:

```cpp
std::lock_guard<std::mutex> lock(bookingMutex);

if (seats.find(seatId) != seats.end()) {
    return;
}

seats[seatId] = userId;
```

Here, the following operations are protected together:

1. Check whether the seat exists
2. Assign the seat if it is available

Only one thread can execute this critical section at a time.

### What is Coarse-Grained Locking?

**Coarse-grained locking** means using a single lock to protect a relatively large portion of shared state or a whole object.

In the ticket booking example:

```text
TicketBooking
    ├── seats
    └── bookingMutex
```

All booking operations acquire the same mutex before checking or modifying the booking state.

If one thread holds the mutex, other threads trying to acquire that mutex must wait until it is released.

Reference examples:

* `WithoutMutex.cpp`
* `WithMutex.cpp`

---

## Things to Avoid

### 1. Do not release the lock between check and update

Incorrect:

```cpp
lock();

bool available = checkSeat();

unlock();

if (available) {
    bookSeat();
}
```

Another thread can modify the seat after the check but before the update.

The check and update together form one logical atomic operation, so they must remain inside the same critical section.

### 2. Do not use separate locks for the check and update

Using one mutex for checking and another mutex for updating does not automatically protect the complete operation.

The lock boundary should be based on the **business invariant**.

For ticket booking:

> "Check availability and reserve the seat" must be protected as one operation.

---

## Trade-offs of Coarse-Grained Locking

### Advantages

* Simple to implement
* Easy to reason about
* Easier to maintain
* Lower risk of lock-ordering and deadlock issues compared with multiple locks
* Often sufficient when the critical section is short and contention is acceptable

### Disadvantages

Coarse-grained locking can unnecessarily serialize unrelated operations.

For example:

```text
Thread 1 → books seat 7A
Thread 2 → books seat 12B
```

These operations do not logically conflict because they involve different seats.

However, if both operations use the same booking mutex:

```text
Thread 1 → acquires lock → books 7A → releases lock
Thread 2 → waits          → books 12B
```

Thread 2 must wait even though it could safely operate on a different seat.

This can reduce concurrency and become a throughput bottleneck under high contention.

### When is it a good choice?

Coarse-grained locking is usually a good starting point when:

* the critical section is short
* the shared state is relatively small or naturally treated as one unit
* contention is acceptable
* simplicity and correctness are more important than maximizing parallelism

Do not optimize for fine-grained locking prematurely. First establish a correct implementation, then measure or reason about whether lock contention is a real bottleneck.

---

## Read-Write Lock / Shared Mutex

A read-write lock allows:

* Multiple readers to access shared data concurrently
* Only one writer to access the data at a time
* Writers to exclude readers while modifying the data

In C++, the relevant primitive is:

```cpp
std::shared_mutex
```

Read access uses a shared lock:

```cpp
std::shared_lock<std::shared_mutex>
```

Write access uses an exclusive lock:

```cpp
std::unique_lock<std::shared_mutex>
```

### When is it useful?

Read-write locks can be useful when:

* reads significantly outnumber writes
* read operations can safely run concurrently
* the cost of blocking readers is meaningful
* the workload benefits from concurrent read access

Example:

> A configuration store is read on almost every request but updated rarely.

However, a read-write lock is not automatically better than a normal mutex. It introduces additional coordination overhead, and performance depends on the workload, implementation, contention, and critical-section duration.

### Mental Model

```text
Mutex:
One thread enters at a time.

Read-write lock:
Multiple readers can enter together,
but a writer requires exclusive access.
```

Use a read-write lock based on the actual access pattern, not simply because reads exist.


## Solution: Fine-Grained Locking

**Fine-grained locking** means protecting smaller, independent portions of shared state with separate locks instead of using one lock for the entire resource.

### Why?

#### Coarse-Grained Locking

```text
              One Mutex
                 |
        +--------+--------+
        |                 |
      Seat A            Seat B
```

Even if two threads access different seats, they may block each other.

#### Fine-Grained Locking

```text
     Mutex A              Mutex B
        |                    |
      Seat A               Seat B
```

Threads operating on different seats can proceed concurrently, while threads operating on the **same seat** still synchronize.

#### Example

```text
Thread 1 → Book 7A  → Lock 7A
Thread 2 → Book 12B → Lock 12B
```

These can execute concurrently.

But:

```text
Thread 1 → Book 7A → Lock 7A
Thread 2 → Book 7A → Wait
```

The same seat is still protected.

### Trade-offs

#### Coarse-Grained Locking

* Simpler
* Easier to reason about
* More contention
* Less concurrency

#### Fine-Grained Locking

* More concurrency
* Less unnecessary blocking
* More complex
* More difficult to reason about
* Higher risk of deadlocks when multiple locks are needed

### Deadlock

Fine-grained locking can require acquiring multiple locks.

Example:

```text
Thread 1: Lock A → waits for B
Thread 2: Lock B → waits for A
```

Neither can proceed → **deadlock**.

A common solution is:

> **Always acquire multiple locks in a consistent order.**

For example, always lock the smaller seat ID first.

### Interview Takeaway

> Fine-grained locking improves concurrency by protecting smaller independent portions of shared state, but increases complexity and deadlock risk. I would use it when contention on a coarse-grained lock is significant enough to justify the added complexity.

### Key Mental Model

```text
Coarse lock
→ simple
→ more contention

Fine-grained locks
→ more concurrency
→ more complexity / deadlock risk
```


## Solution: Atomic variable

## Solution: Thread Confinement (Shared Nothing)

## Patterns
* Check then act
* Read modify write