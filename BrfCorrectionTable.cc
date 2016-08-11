#include <fstream>
#include <iostream>

#include "BrfCorrectionTable.h"

BrfCorrectionTable::BrfCorrectionTable(const std::string &fname) {

  int N_modes = static_cast<int>(BrfReweightCode::null);
  for (int i = 0; i < N_modes; ++i) {
    BrfReweightCode c = static_cast<BrfReweightCode>(i);
    name2brfcode_[brfcode2string(c)] = c;
  }

  std::ifstream fin(fname);
  std::string name; double brf, fluc;
  while (fin >> name >> brf >> fluc) {
    BrfReweightCode c = name2brfcode_.at(name);
    table_[c] = { brf, fluc };
  }

}
