// simple swapping without data types
#include <stdio.h>

#define SWAP(x, y)                                                          \
  tmp2 = *x;                                                                   \
  *x = *y;                                                                     \
  *y = tmp2;

#define DEFINE_SWAP(FUN_SWAP, T)                                                       \
  void FUN_SWAP(T *x, T *y) {                                                   \
    T tmp = *x;                                                                \
    *x = *y;                                                                   \
    *y = tmp;                                                                  \
  }

static void funSwapInt(int *a, int *b);

static void funSwapFloat(float *a, float *b);

// generic swap function using macro
DEFINE_SWAP(funSwapInt, int);

DEFINE_SWAP(funSwapFloat, float);

int main() {
  int a = 5;
  int b = 10;
  int tmp2;

  printf("a = %d , b = %d \n", a, b);

  // during pre-processing, the whole DEFINE_SWAP block will be replaced here
  SWAP(&a, &b);


  printf("a = %d , b = %d \n", a, b);
  
  funSwapInt(&a, &b);

  printf("a = %d , b = %d \n", a, b);

  float fa = 1.0, fb = 5.0;

  printf("fa = %f , fb = %f \n", fa, fb);

  funSwapFloat(&fa, &fb);

  printf("fa = %f , fb = %f \n", fa, fb);
}

