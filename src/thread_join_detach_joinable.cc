

// Ref:
// https://www.youtube.com/watch?v=r-PDHNWYdes&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp&index=6

#include <iostream>
#include <mutex>
#include <thread>

// Tip: bash command to monitor threads. May change based on executable name
// watch -n 1 "ps -T aux | grep -E '[P]ID|[t]hread_join_detach'"

int counter = 0;
/* 
The mutex class is a synchronization primitive that can be used to protect shared data from
being simultaneously accessed by multiple threads. there are different types of mutex, e.g.
timed, recursive, shared etc. this program shows example of non-blocking and blocking mutex
 */
std::mutex mtx;

using namespace std::chrono_literals;

void try_lock() {
    int local_counter = 0;
    for (int i = 0; i < 1000000; i++) {
        // non-blocking mutex
        if (mtx.try_lock()) {
            ++counter;
            ++local_counter;
            mtx.unlock();
        }
    }
    // running some heavy work
    std::this_thread::sleep_for(4s);

    std::cout << std::endl;
    std::cout << "try_lock counter : " << local_counter << std::endl;
    std::cout << "closing try_lock() thread" << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(2s);
}

void lock() {
    int local_counter = 0;
    for (int i = 0; i < 1000000; i++) {
        // blocking mutex
        mtx.lock();
        ++counter;
        ++local_counter;
        mtx.unlock();
    }
    // running some heavy work
    std::this_thread::sleep_for(4s);

    std::cout << std::endl;
    std::cout << "lock counter : " << local_counter << std::endl;
    std::cout << "closing lock() thread" << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(2s);
}

int main() {
    // thread starts running as soon as the thread object is constructed with a function
    std::thread t1(try_lock);
    std::thread t2(lock);

    // empty thread object, does not execute, thus non-joinable
    std::thread t3;

    std::cout << std::endl;
    std::cout << "t1.joinable: " << t1.joinable() << std::endl;
    std::cout << "t2.joinable: " << t2.joinable() << std::endl;
    std::cout << "t3.joinable: " << t3.joinable() << std::endl;
    std::cout << std::endl;

/*  
    RULE: all running/active thread objects must "not be joinable" at the end of main thread

    once thread object starts executing, its "joinable" state becomes true

    once main thread exits, it will destroy the thread objects t1 and t2
    destructor of the thread checks if the thread object is still joinable
    if it is joinable, then it will abort the program throwing "terminate called without an
    active exception"

    we must handle each active thread object by either calling join() or detach()
    only these 2 functions can manipulate the "joinable" state of a active thread object

    join() is a blocking call
    main thread will not go ahead until the respective thread has finished
    after succesful join(), thread object's "joinable" state becomes false

    detach() is a non-blockig cal
    The main thread will continue to run independent of the thread object
    When main thread exits, child will also exit (even if it is not finished)
    Once detached, thread object's "joinable" state becomes false 
*/

    // try different combinations here of join and detach
    t1.detach();
    t2.detach();

    // t3.join() ; // will throw std::system_error. Should not call join/detach on a
    // non-joinable thread.

    std::this_thread::sleep_for(2s);

    std::cout << std::endl;
    std::cout << "Main thread counter :" << counter << std::endl;
    std::cout << "t1.joinable: " << t1.joinable() << std::endl;
    std::cout << "t2.joinable: " << t2.joinable() << std::endl;
    std::cout << "t3.joinable: " << t3.joinable() << std::endl;
    std::cout << "Main thread sleeping " << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for(6s);

    std::cout << "closing main thread" << std::endl;
}