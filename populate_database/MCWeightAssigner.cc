#include <fstream>
#include <string>

#include "MCWeightAssigner.h"

// read in the weight data file. internally, weight_map_ is 
// keyed by the integer 10*mode+run. this is ok since run is 
// at most 7 and mode has far less digits than 2^32.
MCWeightAssigner::MCWeightAssigner(const std::string &fname) 
 : weight_map_() {

  std::ifstream fin;

  fin.open(fname);
  if (!fin.is_open()) {
    throw std::runtime_error(
        "MCWeightAssigner(): cannot open " + fname +
        ". Does the file exist? "
    );
  }

  int mode, run; double weight;
  while (fin >> mode >> run >> weight) {
    if (!weight_map_.insert({hash_mode_run(mode, run), weight}).second) {
      throw std::runtime_error(
          "MCWeightAssigner(): mode " + std::to_string(mode) + 
          " run " + std::to_string(run) + " was already inserted. ");
    }
  }

  fin.close();
}
