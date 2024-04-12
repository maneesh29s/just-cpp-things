#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <valarray>

#include "universal/number/posit/posit.hpp"

#define N 128
#define E 4

int main()
{
  // a = 7.0
  // b = c = 3.5 + 3 * 2^-111
  sw::universal::posit<N, E> a (7.0);
  sw::universal::posit<N, E> three_five (3.5);
  sw::universal::posit<N, E> two (2);
  sw::universal::posit<N, E> exp (-111);
  sw::universal::posit<N, E> three (3);
  sw::universal::posit<N, E> c = three_five + three * pow(two, exp);
  sw::universal::posit<N, E> b = c;

  sw::universal::posit<N, E> s = (a + b + c) / two;
  sw::universal::posit<N, E> area_sq = (s * (s - a) * (s - b) * (s - c));
  // sw::universal::posit<N, E> area = sw::universal::sqrt(area_sq);

  std::cout << "Str: " << to_string(area_sq, 60) << std::endl;
  std::cout << "Hex: " << to_hex(area_sq) << std::endl;
  std::cout << "Hex: " << to_binary(area_sq) << std::endl;

  return 0;

}