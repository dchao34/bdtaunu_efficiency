#include "CsvWriter.h"

void CsvWriter::open(
    const std::string &fname, 
    const std::vector<std::string> &colnames) {

  // check if another file is already open.
  if (fout_.is_open()) {
    throw std::runtime_error(
        "CsvWriter<>::open() : another file is already open. " 
        "run close() before running another open(). "
    );
  }
  assert(colname_idx_.empty());
  assert(cache_.empty());

  // initialize data structures
  std::string header;
  for (size_t i = 0; i < colnames.size(); ++i) {
    colname_idx_[colnames[i]] = i;
    header += colnames[i] + ",";
  }
  header.pop_back();
  cache_ = std::vector<std::string>(colnames.size());

  // open the file and write header
  fout_.open(fname);
  fout_ << header << std::endl;

}

void CsvWriter::set(const std::string &colname, const std::string &val) {
  cache_[colname_idx_.at(colname)] = val;
}

void CsvWriter::commit() {
  std::string line;
  for (size_t i = 0; i < cache_.size(); ++i) {
    line += cache_[i] + ",";
    cache_[i] = "";
  }
  line.pop_back();
  fout_ << line << std::endl;
}

void CsvWriter::close() {
  fout_.close();
  colname_idx_.clear();
  cache_.clear();
}
