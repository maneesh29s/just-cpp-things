#include <cmath>
#include <vector>
#include <cstddef>


template<typename T>
std::vector<T> generateSequentialData(const size_t arrSize,
                                          T start, T diff) {
  std::vector<T> arr(arrSize);

  for (size_t i = 0; i < arr.size(); i++) {
    // logic
    arr[i] = start + (T)(i * diff);
  }
  return arr;
}

template<typename T>
std::vector<T> generateRandomData(const size_t arrSize,
                                      T range, T offset) {
  std::vector<T> arr(arrSize);

  time_t seed = time(0);
  srand(seed);

  for (size_t i = 0; i < arr.size(); i++) {
    arr[i] = offset + range * (rand() / (T)RAND_MAX);
  }

  return arr;
}