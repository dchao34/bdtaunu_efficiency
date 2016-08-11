#include <iostream>

#include "BrfCorrectionTable.h"

int main() {
  BrfCorrectionTable table("brf_corrections.dat");
  std::cout << table.brf(BrfReweightCode::Bp_Dstar0_a1p) << " ";
  std::cout << table.fluc(BrfReweightCode::Bp_Dstar0_a1p) << " ";
  std::cout << std::endl;
  return 0;
}
