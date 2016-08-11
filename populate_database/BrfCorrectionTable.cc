#include <fstream>
#include <iostream>

#include "BrfCorrectionTable.h"

BrfCorrectionTable::BrfCorrectionTable(const std::string &fname) {

  int N_modes = static_cast<int>(BrfReweightCode::null);
  for (int i = 0; i < N_modes; ++i) {
    BrfReweightCode c = static_cast<BrfReweightCode>(i);
    name2brfcode_[brfcode2string(c)] = c;
  }

  // open file. check that it was successful. 
  std::ifstream fin(fname);
  if (!fin.is_open()) {
    throw std::runtime_error(
      "CsvReader<>::open() : file " + fname + " does not exist. "
    );
  }

  // read contents
  std::string name; double brf, fluc;
  while (fin >> name >> brf >> fluc) {
    BrfReweightCode c = name2brfcode_.at(name);
    table_[c] = { brf, fluc };
  }

}
