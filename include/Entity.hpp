#pragma once

#include <cstdio>
#include <utility>

#include "String.hpp"

class Entity {
   public:
    Entity(const custom::String& name) : name(name) {
        // this->print();
        printf("Entity lvalue constructor! ");
    }

    Entity(custom::String&& string) : name(std::move(string)) {
        // this->print();
        printf("Entity rvalue constructor! ");
    }

    Entity(const Entity& other): name(other.name){
        // this->print();
        printf("Entity copy constructor! ");
    }

    Entity(Entity&& other): name(std::move(other.name)){
        // this->print();
        printf("Entity move constructor! ");
    }

    custom::String getString() {
        return name;
    }

    ~Entity(){
        // this->print();
        printf("Entity Destroyed!! ");
    }

   private:
    custom::String name;
};
