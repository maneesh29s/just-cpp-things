#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <string>

#define MAXGENRAND 4294967296

template <typename T>
class Timer {
   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

   public:
    void start_timer() {
        this->start = std::chrono::high_resolution_clock::now();
    }
    void stop_timer() {
        this->end = std::chrono::high_resolution_clock::now();
    }

    std::string time_elapsed() {
        auto time_taken = std::chrono::duration_cast<T>(this->end - this->start).count();

        std::string unit = "";
        if (std::is_same<T, std::chrono::seconds>::value)
            unit = "s";
        else if (std::is_same<T, std::chrono::milliseconds>::value)
            unit = "ms";
        else if (std::is_same<T, std::chrono::microseconds>::value)
            unit = "us";
        else if (std::is_same<T, std::chrono::nanoseconds>::value)
            unit = "ns";

        return std::to_string(time_taken) + " " + unit;
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

template <typename T>
std::vector<T> generateSequentialData(const size_t arrSize, T start, T diff) {
    std::vector<T> arr(arrSize);

    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = start + (T)(i * diff);
    }
    return arr;
}

template <typename T>
std::vector<T> generateRandomData(const size_t arrSize, T offset, T range, long seed) {
    std::vector<T> arr(arrSize);

    /* std::mt19937 gen(seed);
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = offset + range * gen() / MAXGENRAND;
    } */

    srand(seed);
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = offset + range * (std::rand() / (T)RAND_MAX);
    }

    return arr;
}

template <typename T>
void printVector(const std::vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}