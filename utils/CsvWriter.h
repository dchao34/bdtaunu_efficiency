#ifndef __CSV_WRITER_H__
#define __CSV_WRITER_H__

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdexcept>
#include <cassert>

// class for writing a csv file with a specified column ordering
class CsvWriter {

  public:

    CsvWriter() {};
    ~CsvWriter() {};

    // open a file `fname` for writing. the columns to be written 
    // will be the same and in the order as those given in `colnames` 
    void open(const std::string &fname, 
              const std::vector<std::string> &colnames); 

    // close the file
    void close();

    // set column `colname` to the value `val`
    void set(const std::string &colname, const std::string &val);
    
    // write a line to the file using the current values that were
    // `set` since the last commit. 
    void commit();

  private:
    std::ofstream fout_;

    std::unordered_map<std::string, size_t> colname_idx_;
    std::vector<std::string> cache_;
};

#endif
