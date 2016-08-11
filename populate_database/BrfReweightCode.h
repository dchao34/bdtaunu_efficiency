#ifndef __BRFREWEIGHTCODE_H__
#define __BRFREWEIGHTCODE_H__

#include <vector>
#include <string>

enum class BrfReweightCode {
#   define X(a) a,
#   include "BrfReweightCode.def"
#   undef X
    null
};

char const* const BrfReweightCodeStr[] = {
#   define X(a) #a,
#   include "BrfReweightCode.def"
#   undef X
    0
};

const int n = static_cast<int>(BrfReweightCode::null);

inline BrfReweightCode int2BrfReweightCode(int i) {
  return (i >= 0 && i < n) ? static_cast<BrfReweightCode>(i) : BrfReweightCode::null;
}

inline std::string int2brfcodestring(int i) {
  return (i >= 0 && i < n) ? std::string(BrfReweightCodeStr[i]) : "null";
}

inline std::string brfcode2string(BrfReweightCode c) {
  return int2brfcodestring(static_cast<int>(c));
}

#endif
