// Tip: bash command to monitor threads. May change based on executable name
// watch -n 1 "ps -T aux | grep -E '[P]ID|[t]hread_join_detach'"

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

using namespace std::chrono_literals;

int counter        = 0;
int shared_counter = 0;

/* The mutex class is a synchronization primitive that can be used to protect shared data
(critical section) from being simultaneously accessed by multiple threads

simple mutex. only one thread can own the mutex at a time
methods: lock, unlock, try_lock */
std::mutex mtx;

/* shared mutex. multiple threads can share ownership of the same mutex.
supports both exclusive and shared access to a resource
e.g. exclusive for write, but shared for read
methods: lock, unlock, try_lock; lock_shared, unlock_shared, try_lock_shared */
std::shared_mutex shrd_mtx;

// similar to smart pointers, c++ provides RAII-style mutex locks:
// lock_guard, unique_lock, shared_lock, scoped_lock

void ex_critical_section() {
    /* std::lock_guard and std::unique_lock are exclusive locks.
    They support any type of mutex which has lock()/unlock() methods (i.e. BasicLockable)
    Both call mtx.lock() during construction, and mtx.unlock() at destruction

    NOTE: only one lock can be used inside a scope, as calling lock() on owned mutex will
    result in resource_deadlock */

    // basic RAII-style lock. Can not be copied/moved. No methods.
    // std::lock_guard<std::mutex> lock(mtx);

    // unique_lock is movable; Has more methods; Supports timed, deferred locks.
    std::unique_lock<std::mutex> lock(mtx);
    counter++;

    // lock is destructed, unlock() is called on owned mutex
}

void shared_critical_section() {
    /* std::shared_lock supports ONLY shared type mutexes
    Calls mtx.lock_shared() during construction, and mtx.unlock_shared() at destruction */

    // shared_lock is movable; has more methods; supports timed , deferred locks.
    std::shared_lock<std::shared_mutex> sharedlock(shrd_mtx);
    shared_counter++;

    // sharedlock is destructed, unlock_shared() is called on owned mutex
}

void feature() {
    for (int i = 0; i < 10000; i++) {
        // fixed result
        ex_critical_section();

        // unexpected result as multiple writes may override each other
        shared_critical_section();
    }

    std::this_thread::sleep_for(3s);
}

int main() {
    std::thread t1(feature);
    std::thread t2(feature);
    std::thread t3(feature);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Main thread prints counter: " << counter << std::endl;
    std::cout << "Main thread prints shared_counter: " << shared_counter << std::endl;

    std::this_thread::sleep_for(3s);

    return 0;
}

/* Bonus: semaphores

https://en.cppreference.com/w/cpp/thread/counting_semaphore
A counting_semaphore contains an internal counter initialized by the constructor. This
counter is Decremented by calls to acquire() and related methods, and is Incremented by
calls to release(). When the counter is zero, acquire() blocks until the counter is
incremented.

e.g.
```
std::counting_semaphore smph(1); //at least one process can always access the critical
section
main: { smph.acquire() ; // accessing critical section. counter = 0
    smph.release(2); // allows 2 more threads to access critical section }
thread1.acquire() // allowed
thread2.acquire() // allowed
thread3.acquire() // blocked
```

Semaphores are also often used for the Semantics of Signaling/Notifying rather than mutual
exclusion.
For this, initialise the semaphore with ​0​ which will block the receiver(s) that
try to acquire(), until the notifier "signals" by invoking release(n).
In this respect semaphores can be considered alternatives to std::condition_variables, often
with better performance.
 */

// Recursive mutex: https://en.cppreference.com/w/cpp/thread/recursive_mutex

// Condition variable:
// https://en.cppreference.com/w/cpp/thread/condition_variable
