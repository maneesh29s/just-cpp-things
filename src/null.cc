#include <cstdio>
#include <cstring>
#include <iostream>

int main(){
    printf("NULL: %s\n" , NULL);
    printf("NULL: %d\n" , NULL);
    printf("NULL: %f\n" , NULL);
    printf("NULL: %p\n" , NULL);
    printf("nullptr: %s\n" , nullptr);
    printf("nullptr: %s\n" , (char*)nullptr);
    printf("nullptr: %p\n" , (int*)nullptr);
    printf("nullptr: %d\n" , (int*)nullptr);

    std::cout << "--------------------" << std::endl;

    std::cout << "Passing NULL to cout " << NULL << std::endl;
    std::cout << "Passing nullptr to cout " << nullptr << std::endl;

    char* nlchar = nullptr;

    // Undefined behaviour
    // see << operator for outstream
    std::cout << "Passing char* nullptr to cout " << nlchar << std::endl;

    std::cout << "cout WILL NOT PRINT this line !!!!";

}