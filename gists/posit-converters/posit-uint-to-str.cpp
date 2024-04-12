#include <iostream>
#include <string>
#include <cstdint>
#include "universal/number/posit/posit.hpp"
#include <fstream>
#include <gmpxx.h>

#define N 32
#define E 2

std::string convert_int_to_bin(std::string int_string) {
  mpz_class val(int_string, 10);
  return val.get_str(2);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: <number>" << std::endl;
        return 1;
    }

    std::string int_string = argv[1];
    std::string bin_string = convert_int_to_bin(int_string);
    
    // to make the number of bits equal to N
    if(bin_string.length() < N){
        int num_zeros = N - bin_string.length();
        for(int i = 0 ; i < num_zeros ; i++){
            bin_string = "0" + bin_string;
        }
    }

    sw::universal::internal::bitblock<N> bits;
    bits.load_bits(bin_string);

    sw::universal::posit<N, E> p;
    p.setBitblock(bits);

    std::cout << "Hex: " << to_hex(p) << std::endl;
    std::cout << "Str: " << to_string(p, 60) << std::endl;
    std::cout << "Bin: " << bin_string << std::endl;
}