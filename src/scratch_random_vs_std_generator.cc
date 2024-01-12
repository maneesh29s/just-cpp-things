#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include "helper.hpp"

int main(int argc, char **argv) {

    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " size-exponent" << std::endl;
        return 1;
    }

    int exponent = std::atoi(argv[1]);

    const size_t SIZE = std::pow(2, exponent);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(10.f, 5.f);

    std::vector<float> arr(SIZE);

    Timer<std::chrono::milliseconds> t;

    t.start_timer();

    for (std::size_t i = 0; i < arr.size(); ++i) {
        arr[i] = distribution(generator);
    }

    t.stop_timer();

    std::cerr << "Time elapsed for std c++ distributor + generator: " << t.time_elapsed() << std::endl;

    t.start_timer();

    std::vector<float> arr2 = generateRandomData<float>(SIZE, 10.0f, 5.0f, 0);

    t.stop_timer();

    std::cerr << "Time elapsed for mt19937 random generator: " << t.time_elapsed() << std::endl;

    t.start_timer();

    std::vector<float> arr3 = generateSequentialData<float>(SIZE, 10.0f, 1.0f);

    t.stop_timer();

    std::cerr << "Time elapsed for custom sequential generator: " << t.time_elapsed() << std::endl;
}