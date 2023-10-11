#pragma once

#include <cstddef>
#include <iostream>
#include <string>
#include <chrono>

template <typename T>
class Timer {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  std::chrono::time_point<std::chrono::high_resolution_clock> end;

public:
  void start_timer() { this->start = std::chrono::high_resolution_clock::now(); }
  void stop_timer() { this->end = std::chrono::high_resolution_clock::now(); }

  std::string time_elapsed() {
    auto time_taken =
        std::chrono::duration_cast<T>(this->end - this->start).count();

    return std::to_string(time_taken);
  }
};

void logInfo(std::string message) {
    std::cout << "INFO: " << message << std::endl;
}

void logDebug(std::string message) {
    #ifdef DEBUG_LOG
        std::cout << "DEBUG: " << message << std::endl;
    #endif
}

void logError(std::string message) {
    std::cerr << "ERROR: " << message << std::endl;
}

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