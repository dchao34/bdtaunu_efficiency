#ifndef _MCWEIGHT_ASSIGNER_H_
#define _MCWEIGHT_ASSIGNER_H_

#include <string>
#include <unordered_map>

// MCWeightAssigner provides convenient lookup of a 
// given cached mode/run event weight file, 
//
// example usage:
// 
//     MCWeightAssigner mcw("mc_weights.dat");
//     mcw.get_weight(1237, 3);
//     mcw.get_weight(11444, 6);
//
class MCWeightAssigner {

  public: 

    // construct an assigner object loaded with the contents of `fname`. 
    MCWeightAssigner(const std::string &fname);

    // retrieve the weight of an mc event generated 
    // from sp mode `mode` and data taking run `run`. 
    double get_weight(int mode, int run) const;

  private:
    int hash_mode_run(int mode, int run) const;

    std::unordered_map<int, double> weight_map_;
};

inline int MCWeightAssigner::hash_mode_run(int mode, int run) const {
  return mode*10+run;
}

inline double MCWeightAssigner::get_weight(int mode, int run) const {
  return weight_map_.at(hash_mode_run(mode, run));
}

#endif
