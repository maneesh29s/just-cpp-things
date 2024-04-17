#include <iostream>
#include <ostream>

#include "Entity.hpp"

#define NL printf("\n")

// References:
// Move Semantics: https://youtu.be/ehMg6zvXuMY
// std::move and Move operator: https://youtu.be/OWNeCTd7yQE
// https://en.cppreference.com/w/cpp/utility/move
// MUST READ:
// https://www.nextptr.com/tutorial/ta1211389378/beware-of-using-stdmove-on-a-const-lvalue

int main() {
    // first, creating a string
    custom::String apple("apple"); NL;

    std::cout << "--------------------------" << std::endl;

    {  // lvalue constructor
        Entity entity(apple); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    {  // rvalue constructor
        Entity entity2("banana"); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    {
        // Copy constructor
        Entity temp("apple"); NL;
        Entity entity3(temp); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    {  // Copy ellison Entity->Entity
        Entity entity4(Entity("orange")); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    {  // rvalue constructor, moves apple
        Entity entity6(std::move(apple)); NL;
        entity6.getString().prettyPrint(); NL;
        apple.prettyPrint(); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    return 0;
}