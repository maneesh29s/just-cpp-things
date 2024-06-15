#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

using Vec3D = std::array<float, 3>;

int main() {
    std::array<Vec3D, 4> arr;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0.f, 1.f);

    for (std::size_t i = 0; i < arr.size(); ++i) {
        arr[i] = {distribution(generator), distribution(generator), distribution(generator)};

        std::cout << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << std::endl;
    }
}