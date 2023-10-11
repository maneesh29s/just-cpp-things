#include <array>
#include <chrono>
#include <cstdlib>
#include <experimental/simd>
#include <iostream>
#include <random>

using simd_vector = std::experimental::native_simd<float>;
// typedef std::experimental::native_simd<float> simd_vector;

// using simd_vector = std::experimental::fixed_size_simd<double, 10>;

void print(simd_vector const& a) {
    for (std::size_t i = 0; i != std::size(a); ++i) std::cout << a[i] << ' ';

    std::cout << '\n';
}

int main() {
    // asssiging value to all elements of the vector
    simd_vector a = 2;
    simd_vector b = 5;

    simd_vector c = a + b;
    simd_vector d = a * b;

    print(c);
    print(d);

    // creating an array of SIMD vector data type
    std::vector<simd_vector> vec_2D(5);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(50.f, 10.f);

    // storing data
    for (std::size_t i = 0; i < vec_2D.size(); ++i)
        // need to iterate through each element of SIMD vector
        for (std::size_t j = 0; j != simd_vector::size(); ++j)
            vec_2D[i][j] = distribution(generator);

    // printing data from SIMD vector
    for (std::size_t i = 0; i < std::size(vec_2D); ++i) print(vec_2D[i]);

    std::cout << std::endl;

    // in fixed size, it gives the nearest higher power of 2, to the given size
    // in native simd, it will give maximum size of vec register supported by machine
    // 16, 32, 64 bytes etc.
    std::cout << sizeof(simd_vector) << std::endl;

    // in fixed size gives actual number of elements in each vector register
    // not necessarily divisible by 2
    // always use this to iterate through the elemtns
    std::cout << simd_vector::size() << std::endl;
}