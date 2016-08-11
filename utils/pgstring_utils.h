#ifndef _PGSTRING_UTILS_H_
#define _PGSTRING_UTILS_H_

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <boost/tokenizer.hpp>

namespace pgstring_utils {

static std::stringstream float_ss_;
static std::stringstream double_ss_;

// helper classes and objects
// --------------------------

// trait classes and specializations
template <typename T>
class conversion_traits;

template <>
class conversion_traits<int> {
  public:

    static int string2type(const std::string &s) { 
      return std::stoi(s); 
    }

    static std::string type2string(const int &v) { 
      return std::to_string(v); 
    }
};

template <>
class conversion_traits<unsigned long> {
  public:

    static unsigned long string2type(const std::string &s) { 
      return std::stoul(s); 
    }

    static std::string type2string(const unsigned long &v) { 
      return std::to_string(v); 
    }
};

template <>
class conversion_traits<float> {
  public:

    static float string2type(const std::string &s) { 
      return std::stof(s); 
    }

    static std::string type2string(const float &v) { 
      float_ss_.str(""); float_ss_.clear(); 
      float_ss_.precision(10); float_ss_ << v;
      return float_ss_.str();
    }

};

template <>
class conversion_traits<double> {
  public:
    static double string2type(const std::string &s) { 
      return std::stod(s); 
    }

    static std::string type2string(const double &v) { 
      double_ss_.str(""); double_ss_.clear();
      double_ss_.precision(19); double_ss_ << v;
      return double_ss_.str();
    }
};

// fuctions converting text => binary type
// ---------------------------------------

// functions that convert postgres text data to fundamental types 
inline void string2type(const std::string &s, int &v) { 
  v = conversion_traits<int>::string2type(s); 
}

inline void string2type(const std::string &s, float &v) { 
  v = conversion_traits<float>::string2type(s); 
}

inline void string2type(const std::string &s, double &v) { 
  v = conversion_traits<double>::string2type(s); 
}

// function that convert postgres text data to std::vector
template <typename T> 
void string2type(const std::string &s, std::vector<T> &v, 
    const std::string &enclosure_chars="{}",
    const boost::char_separator<char> &sep = 
    boost::char_separator<char>(",", "", boost::keep_empty_tokens)) {

  v.clear();

  size_t first_idx = s.find_first_not_of(enclosure_chars);
  size_t last_idx = s.find_last_not_of(enclosure_chars);
  if (first_idx == std::string::npos || last_idx == std::string::npos) { return; }

  boost::tokenizer<boost::char_separator<char>> tok(
      s.begin()+first_idx, s.begin()+last_idx+1, sep);

  transform(tok.begin(), tok.end(), 
            std::back_inserter(v), 
            conversion_traits<T>::string2type);
}

// fuctions converting binary type => string (with controlled precision)
// ---------------------------------------------------------------------

template <typename T> 
inline std::string type2string(const T &v) {
  return conversion_traits<T>::type2string(v);
}

// function that converts std::vector to postgres text data. 
template <typename T> 
std::string type2string(const std::vector<T> &v) {

  if (v.empty()) { return "{}"; }

  std::string s = "\"{";

  for (const auto &e : v) {
    s += type2string(e) + ",";
  }

  s.pop_back(); s += "}\"";
  return s;
}

}

#endif
