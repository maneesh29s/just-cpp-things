#include <iostream>

#include "String.hpp"

// Ref:
// https://youtu.be/fbYknr-HPYE
// https://en.cppreference.com/w/cpp/language/value_category

#define NL printf("\n")

using namespace custom;

// returns a temporary rvalue by copy
String getRvalue() {
    String val = String("mango"); NL;
    return val;
}

// returns a lvalue reference (i.e. `* const` ) to a variable
String& getLRef() {
    // must define as static OR use global variable
    // static executed only once when the function is called for the first time
    printf("inside getLRef\n");

    printf("[debug] defining ref ! ");
    static String ref = String("mango"); NL;
    return ref;
}

// returns a rvalue reference (i.e. `* const` ) to a variable
String&& getRRef() {
    // must define as static OR use global variable
    // static is executed only once when the function is called for the first time
    printf("inside getRRef\n");

    printf("[debug] defining ref ! ");
    static String ref = String("mango"); NL;

    return std::move(ref);
}

int main() {
    // can not assign value to a rvalue
    // getRvalue() = 'orange';

    std::cout << std::endl << "--------------------------" << std::endl;

    {
        // can assign value to a lvalue reference
        String banana("banana"); NL; NL;
        getLRef() = banana; NL; NL;
        // below will call "copy" operator
        banana = getLRef(); NL; NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    {
        // can assign value to a rvalue reference
        String pineapple("pineapple"); NL; NL;
        // NOTE: even if getRRef() returns a "rvalue ref", it is still a reference to a
        // fixed location in memory. In this case, static variable "ref".
        getRRef() = pineapple; NL; NL;
        // below will call "move" operator instead of copy. This is the real application
        // of rvalue ref.
        pineapple = getRRef(); NL; NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;

    {
        getRvalue().prettyPrint(); NL; NL;
        getLRef().prettyPrint(); NL; NL;
        // Rref's "ref" variable is empty since we moved it earlier
        getRRef().prettyPrint(); NL;
    }

    std::cout << std::endl << "--------------------------" << std::endl;
}