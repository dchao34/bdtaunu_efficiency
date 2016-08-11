#ifndef __BRFCORRECTIONTABLE_H__
#define __BRFCORRECTIONTABLE_H__

#include <string>
#include <unordered_map>

#include "BrfReweightCode.h"

class BrfCorrectionTable {

  public:
    BrfCorrectionTable(const std::string &fname);
    ~BrfCorrectionTable() {}

    bool is_valid_entry(BrfReweightCode c) const;
    double brf(BrfReweightCode c) const { return table_.at(c).brf_; }
    double fluc(BrfReweightCode c) const { return table_.at(c).fluc_; }

  private:

    struct EnumClassHash {
      template <typename T>
      size_t operator()(T t) const {
          return static_cast<size_t>(t);
      }
    };

    struct TableValue {
      double brf_;
      double fluc_;
    };

    std::unordered_map<std::string, BrfReweightCode> name2brfcode_;

    std::unordered_map<BrfReweightCode, TableValue, EnumClassHash> table_;


};

inline bool BrfCorrectionTable::is_valid_entry(BrfReweightCode c) const {
  return table_.find(c) != table_.end();
}

#endif
