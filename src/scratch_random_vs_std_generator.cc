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
    std::vector<double> arr(SIZE);
    Timer<std::chrono::milliseconds> t;

    // C++ generator + distributor
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(10.0, 5.0);
    t.start_timer();
    for (std::size_t i = 0; i < arr.size(); ++i) {
        arr[i] = distribution(generator);
    }
    t.stop_timer();

    std::cerr << "Time elapsed for std c++ distributor + generator: " << t.time_elapsed() << std::endl;
    arr.clear();

    // C++ mercene twister generator - equivalent to python's random
    t.start_timer();
    arr = generateRandomData<double>(SIZE, 10.0f, 5.0f, 0);
    t.stop_timer();

    std::cerr << "Time elapsed for generateRandomData: " << t.time_elapsed() << std::endl;
    arr.clear();

    // Sequential generator
    t.start_timer();
    arr = generateSequentialData<double>(SIZE, 10.0f, 1.0f);
    t.stop_timer();

    std::cerr << "Time elapsed for custom sequential generator: " << t.time_elapsed() << std::endl;
    arr.clear();
}