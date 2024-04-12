#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <quadmath.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <valarray>

int main()
{
  char* outstr = new char[1000];

  __float128 a = 7.0Q;
  __float128 b = 3.5Q + 3.0Q * powq(2.0Q,-15);
  __float128 c = b;
  
  quadmath_snprintf(outstr, 1000, "%.50Qg", a);
  std::cout << "a = " << outstr << std::endl;
  quadmath_snprintf(outstr, 1000, "%.50Qg", b);
  std::cout << "b = c = " << outstr << std::endl;

  __float128 s =  (a + b + c) / 2.0Q;
  __float128 area_sq = (s * (s - a) * (s - b) * (s - c));

  quadmath_snprintf(outstr, 1000, "%.50Qg", area_sq);
  std::cout << "area_sq of a triangle: " << outstr << std::endl;

  // getting byte representation
  uint8_t* byte = reinterpret_cast<uint8_t*>(&a);  
  std::stringstream strstream;
  for(size_t i = 0 ; i < 16; i++){
      for (size_t j = 0 ; j < 8 ; j ++){
        uint8_t multiplier = 1 << j;
        uint8_t ans = byte[i] & multiplier;
        if (ans == 0){
          strstream << "0";
        }
        else {
          strstream << "1";
        }
      }
  }
  std::string bin_str = strstream.str();
  std::reverse(bin_str.begin(), bin_str.end());

  std::cout << "area_sq of triangle in binary: " << bin_str ;

  delete[] outstr;

  return 0;
}
