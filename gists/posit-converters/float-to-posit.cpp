#include <cstdint>
#include "universal/number/posit/posit.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <gmpxx.h>

#define N 32
#define E 2

std::string convert_bin_to_int(std::string binary_string) {
  mpz_class val(binary_string, 2);
  return val.get_str(10);
}

int main(int argc, char **argv) {
  // Usage: argv[0] a_side exponent
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " float_value";
    return 1;
  }

  double valf = std::atof(argv[1]);

  sw::universal::posit<N, E> valp(valf);
  // perform operations on the posit instance itself to get more accurate values
  
  std::regex dot_regex("(0b|\\.)");
  std::string cleaned_binary =
      std::regex_replace(to_binary(valp), dot_regex, "");

  std::cout << "Str: " << to_string(valp, 60) << std::endl;
  std::cout << "Hex: " << to_hex(valp) << std::endl;
  std::cout << "Bin: " << cleaned_binary << std::endl;
  std::cout << "Int: " << convert_bin_to_int(cleaned_binary) << std::endl;

  return 0;
}