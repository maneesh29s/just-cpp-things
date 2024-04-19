#include <cstdio>
#include <iostream>
#include <memory>

#include "String.hpp"

#define NL printf("\n")

// Ref: https://www.youtube.com/watch?v=UOB7-B2MfwA

// Purpose of smart pointer is to
// 1. create heap allocated objects using `new` keyword
// 2. Own the object and its lifecycle
// 3. Make sure the memory is deallocated with `delete` once out-of-scope

// When to use smart pointers?
// When you NEED to generate create allocated objects, and don't want to worry about
// memory leaks

// What smart pointer is not?
// Smart pointer is not regular pointer.

int main() {
    custom::String fruit("apple");
    std::cout << std::endl << "-------------------------------" << std::endl;

    {
        // Unique pointer

        // using make_unique (recommended)
        // in this case, make_unique will call "copy constructor" of String to create a
        // new object. and it will NOT point to name.
        std::unique_ptr<custom::String> unqPtr =
            std::make_unique<custom::String>((fruit)); NL; NL; // calls move constructor 

        // using new operator
        std::unique_ptr<custom::String> unqPtr2(new custom::String("strawberry")); NL; NL;

        *unqPtr = "guava"; NL; NL;

        // unqPtr2 = unqPtr; // not allowed

        std::cout << "name: ";
        fruit.prettyPrint(); NL;
        std::cout << "*ptr: ";
        unqPtr->prettyPrint(); NL; NL;
    }

    std::cout << std::endl << "-------------------------------" << std::endl;

    {  // Shared pointer
        // multiple smart pointers can point to same object
        // in this case, make_shared will call "copy constructor" of String to create a
        // new object. and it will NOT point to fruit.
        std::shared_ptr<custom::String> ptrFruit = std::make_shared<custom::String>(fruit); NL; NL;

        // points to the same object stored inside ptrFruit
        printf("[debug] ptrFruit2 = ptrFruit ");
        std::shared_ptr<custom::String> ptrFruit2 = ptrFruit; NL; NL;

        fruit.prettyPrint(); NL;
        ptrFruit->prettyPrint(); NL;
        ptrFruit2->prettyPrint(); NL;

        fruit = "banana"; NL; NL;

        *ptrFruit = "pineapple"; NL; NL;

        fruit.prettyPrint(); NL;
        ptrFruit->prettyPrint(); NL;
        ptrFruit2->prettyPrint(); NL; NL;

        // gives number of "shared_ptr" pointing to the object
        std::cout << "ptrFruit usecount() : " << ptrFruit.use_count() << "\n"; NL;
    }

    std::cout << std::endl << "-------------------------------" << std::endl;

    {  // weak pointer
        // std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to
        // an object that is managed by std::shared_ptr.

        std::shared_ptr<custom::String> ptrFruit = std::make_shared<custom::String>("coconut"); NL; NL;

        printf("[debug]  weakFruitPtr = ptrFruit");
        std::weak_ptr<custom::String> weakFruitPtr = ptrFruit; NL; NL;

        // weak pointer does not increase use_count() of shared_ptr
        std::cout << "ptrFruit usecount() : " << ptrFruit.use_count() << "\n";

        // weak_ptr must be converted to std::shared_ptr in order to access the referenced
        // object. Use weak_ptr.lock() to get shared_ptr instance
        if (!weakFruitPtr.expired())  // just to check if object is not deleted
        {                             // the scope of "tempPtr" shared_ptr is local
            std::shared_ptr tempPtr = weakFruitPtr.lock();
            std::cout << "ptrFruit usecount() inside scope : " << ptrFruit.use_count() << "\n";
        }

        // temporary shared_ptr has been be  destroyed, decreasing the use_count
        std::cout << "ptrFruit usecount() : " << ptrFruit.use_count() << "\n"; NL;
    }

    std::cout << std::endl << "-------------------------------" << std::endl;
}
