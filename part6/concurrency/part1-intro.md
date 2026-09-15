## What is a Process?

A **process** is a running instance of a program managed by the OS.

It has its own **address space** and resources, including:

* heap
* global/static variables
* other OS-managed resources

A process contains at least one thread that executes its code.

## What is a Thread?

A **thread** is an independent execution path inside a process.

Each thread has its own:

* stack
* program counter
* registers

Threads belonging to the same process share:

* heap
* global/static variables
* process resources

## Why Does Concurrency Matter?

When multiple threads access **shared mutable state** concurrently, problems can occur.

An operation that looks atomic to us may actually consist of multiple steps. If threads are not properly coordinated, their operations can **interleave**, causing incorrect or inconsistent results.

For example:

Two threads check whether a seat is available. Both see that a seat is available, and both book it.

This is a **correctness problem caused by a race condition**.

## Concurrency Toolbox

Different concurrency problems require different synchronization primitives:

1. **Atomics** — for certain simple shared-state operations
2. **Locks / Mutexes** — protect critical sections
3. **Semaphores** — control access based on available permits
4. **Condition Variables** — allow threads to wait for a condition
5. **Blocking Queues** — coordinate producers and consumers

These are synchronization/coordination mechanisms provided by the language/runtime/OS.

## Three Common Types of Concurrency Problems

### 1. Correctness Problems

Shared state becomes incorrect because multiple threads access or modify it concurrently.

Example:

> There is 1 seat left. Two threads both check availability, both see 1, and both book the seat.

### 2. Coordination Problems

Threads need to **wait for or hand work to other threads**.

Example:

> A producer adds tasks to a queue. Consumers process those tasks. If the queue is empty, consumers should wait instead of continuously checking and wasting CPU.

### 3. Scarcity Problems

A resource is limited, but many threads want to use it.

Example:

> There are 10 database connections but 100 concurrent requests. Some requests must wait until a connection becomes available.
