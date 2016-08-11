#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "pgstring_utils.h"

namespace pgutils = pgstring_utils;

int main() {

  std::cout << std::setprecision(19);

  int i = 3;
  std::cout << pgutils::type2string(i) << std::endl;

  float f = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
  std::cout << std::to_string(f) << " " << pgutils::type2string(f) << std::endl;

  double d = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
  std::cout << std::to_string(d) << " " << pgutils::type2string(d) << std::endl;

  std::vector<int> int_vec = { 1, 2, 3, 4 };
  std::cout << pgutils::type2string(int_vec) << std::endl;

  std::vector<float> float_vec = { 1.0000001111, 2.0000002222, 3.0000003333, 4.3, 3.1415926535897932384626433832795028841971693993751058209749445923078164062 };
  std::cout << pgutils::type2string(float_vec) << std::endl;

  std::vector<double> double_vec = { 1.0000001111, 2.0000002222, 3.0000003333, 4.3, 3.1415926535897932384626433832795028841971693993751058209749445923078164062 };
  std::cout << pgutils::type2string(double_vec) << std::endl;

  std::string si = "5"; pgutils::string2type(si, i);
  std::cout << i << std::endl;

  std::string sf = "3.1415926535897932384626433832795028841971693993751058209749445923078164062"; 
  pgutils::string2type(sf, f);
  std::cout << f << std::endl;

  std::string sd = "3.1415926535897932384626433832795028841971693993751058209749445923078164062"; 
  pgutils::string2type(sd, d);
  std::cout << d << std::endl;

  std::string svi = "{1,2,3,4,5}";
  std::vector<int> vi;
  pgutils::string2type(svi, vi);
  for (const auto &v : vi) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  std::string svf = "{1.01234567890123456789,2.01234567890123456789,3.01234567890123456789}";
  std::vector<float> vf;
  pgutils::string2type(svf, vf);
  for (const auto &v : vf) {
    std::cout << v << " ";
  }
  std::cout << std::endl;


  std::string svd = "{1.01234567890123456789,2.01234567890123456789,3.01234567890123456789}";
  std::vector<double> vd;
  pgutils::string2type(svd, vd);
  for (const auto &v : vd) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  return 0;
}
