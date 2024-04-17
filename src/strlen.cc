#include <cstdio>
#include <cstring>


int main(){
    // strlen() function checks for null character and prints the length
    // it is possible that strlen() crosses objects memory limit

    char arr[6] = {'a','b','c', 'd'};
    // adding null character at index 4
    arr[4] = 0;
    // should print 4
    printf("len: %zu \n", strlen(arr));
    
    // filling up rest of the array
    arr[4] = arr[5] = 'b' ;
    
    // address sanitizer will throw error of out of bound acccess
    // will run without address sanitzer
    printf("len: %zu \n", strlen(arr));
}