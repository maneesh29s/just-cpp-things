#pragma once

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ostream>

namespace custom {

class String {
   public:
    String() = default;  // creates size 0 string

    String(const char* string) {
        printf("String char* constructor! ");
        this->size = strlen(string);
        this->data = new char[this->size];
        memcpy(this->data, string, this->size);
        // this->print();
    }

    // Copy Constructor
    String(const String& other) {
        printf("String copy constructor! ");
        this->size = other.size;
        this->data = new char[this->size];
        memcpy(this->data, other.data, this->size);
        // this->print();
    }

    // Move constructor
    String(String&& other) noexcept {
        printf("String move constructor! ");
        this->size = other.size;
        this->data = other.data;

        other.size = 0;
        other.data = nullptr;
        // this->print();
    }

    // Copy operator
    String& operator=(const String& other) {
        if (this != &other) {
            printf("String copy operator! ");
            delete[] this->data;

            this->size = other.size;
            this->data = new char[this->size];
            memcpy(this->data, other.data, this->size);

            // this->print();
        }

        return *this;  // useful for operator chaining
    }

    // Move operator
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            printf("String move operator! ");
            delete[] this->data;

            this->size = other.size;
            this->data = other.data;

            // valid but unspecified state
            other.size = 0;
            other.data = nullptr;
            // this->print();
        }

        return *this;  // useful for operator chaining
    }

    ~String() {
        // this->print();
        printf("String Destroyed!! ");
        delete[] this->data;
    }

    // friend std::ostream& operator<<(std::ostream &os, const String& str){
    //     // printf("str.data = %s", str.data);
    //     if (str.size == 0) os << "<empty>";
    //     else os << string();
    //     return os;
    // }

    void prettyPrint(){
        printf("[String] data: %s , size : %zu ! ", data, size);
    }

   private:
    char* data;
    size_t size;
};

}  // namespace custom
