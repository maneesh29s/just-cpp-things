#include <iostream>
#include <ostream>

#include "String.hpp"

#define NL printf("\n")

// References:
// Move Semantics: https://youtu.be/ehMg6zvXuMY
// std::move and Move operator: https://youtu.be/OWNeCTd7yQE
// https://en.cppreference.com/w/cpp/utility/move
// MUST READ:
// https://www.nextptr.com/tutorial/ta1211389378/beware-of-using-stdmove-on-a-const-lvalue

int main() {
    // char* constructor
    custom::String apple("apple"); NL;

    std::cout << "--------------------------" << std::endl;

    // Copy constructor
    {
        custom::String apple2(apple); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    // Copy elison
    {
        custom::String apple3(custom::String("apple")); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    // Move constructor
    {
        custom::String banana("banana"); NL;
        custom::String banana2(std::move(banana)); NL;
        banana.prettyPrint(); NL;
        banana2.prettyPrint(); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    // Copy operator
    {
        custom::String copied("before_copying"); NL;
        printf("before copy "); copied.prettyPrint(); NL;
        copied = apple; NL;
        printf("after copy "); copied.prettyPrint(); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    // Move operator
    {
        custom::String moved;
        printf("[debug] created empty String\n");
        printf("before move "); moved.prettyPrint(); NL;
        moved = std::move(apple); NL;
        printf("after move "); moved.prettyPrint(); NL;
        printf("after move "); apple.prettyPrint(); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    return 0;
}