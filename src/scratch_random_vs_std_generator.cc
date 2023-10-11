#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include "helper.hpp"

int main() {
    const size_t SIZE = std::pow(2, 20);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(10.f, 5.f);

    std::vector<float> arr(SIZE);

    Timer<std::chrono::microseconds> t;

    t.start_timer();

    for (std::size_t i = 0; i < arr.size(); ++i) {
        arr[i] = distribution(generator);
    }

    t.stop_timer();

    std::cout << "Time elapsed for std c++ generator: " << t.time_elapsed() << " us" << std::endl;

    t.start_timer();

    std::vector<float> arr2 = generateRandomData<float>(SIZE, 10.0f, 5.0f);

    t.stop_timer();

    std::cout << "Time elapsed for custom random generator: " << t.time_elapsed() << " us" << std::endl;

    t.start_timer();

    std::vector<float> arr3 = generateSequentialData<float>(SIZE, 10.0f, 1.0f);

    t.stop_timer();

    std::cout << "Time elapsed for custom sequential generator: " << t.time_elapsed() << " us" << std::endl;
}