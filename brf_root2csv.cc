#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <boost/program_options.hpp>

#include <TFile.h>
#include <TTree.h>

#include <CsvWriter.h>
#include <pgstring_utils.h>

#include "BrfReweightCode.h"
#include "BrfCorrectionTable.h"

namespace po = boost::program_options;
namespace pu = pgstring_utils;

void evaluate(const po::variables_map &vm);

int main(int argc, char **argv) {

  try {

    // define program options
    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration options");
    config.add_options()
        ("cernroot_fname", po::value<std::string>(), 
             "name of the ROOT file containing the inputs. ")
        ("cernroot_trname", po::value<std::string>(), 
             "name of the TTree containing the inputs. ")
        ("output_fname", po::value<std::string>(), 
             "output csv file name. ")
        ("brf_correction_table_fname", po::value<std::string>(), 
             "file containing branching fraction weights. ")
    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("config_file", po::value<std::string>(), 
             "name of a configuration file. ")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config);

    po::options_description visible;
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("config_file", -1);

    // parse program options and configuration file
    po::variables_map vm;
    store(po::command_line_parser(argc, argv).
          options(cmdline_options).positional(p).run(), vm);
    notify(vm);

    if (vm.count("help") || !vm.count("config_file")) {
      std::cout << std::endl;
      std::cout << "Usage: ./brf_root2csv ";
      std::cout << "[options] config_fname" << std::endl;
      std::cout << visible << "\n";
      return 0;
    }

    std::ifstream fin(vm["config_file"].as<std::string>());
    if (!fin) {
      std::cout << "cannot open config file: ";
      std::cout << vm["config_file"].as<std::string>() << std::endl;
      return 0;
    }

    store(parse_config_file(fin, config_file_options), vm);
    notify(vm);

    // main routine
    evaluate(vm);

  } catch(std::exception& e) {

    std::cerr << "error: " << e.what() << "\n";
    return 1;

  } catch(...) {

    std::cerr << "Exception of unknown type!\n";
    return 1;
  }

  return 0;
}

void evaluate(const po::variables_map &vm) {

  // read in branching fraction correction table
  std::string brf_correction_table_fname = vm["brf_correction_table_fname"].as<std::string>();
  BrfCorrectionTable brf_correction_table(brf_correction_table_fname);

  // open output csv file
  std::string output_fname = vm["output_fname"].as<std::string>();
  CsvWriter csv;
  csv.open(output_fname, {
      "eventlabel", "b1_brf_mode", "b2_brf_mode", "brf_correction_weight"
  });

  // open input root file and ttree
  std::string cernroot_fname = vm["cernroot_fname"].as<std::string>();
  std::string cernroot_trname = vm["cernroot_trname"].as<std::string>();
  TFile *root_file = new TFile(cernroot_fname.c_str());
  TTree *root_tree = (TTree*) root_file->Get(cernroot_trname.c_str());

  int eventlabel, b1_brf_int, b2_brf_int;
  root_tree->SetBranchAddress("EventLabel", &eventlabel);
  root_tree->SetBranchAddress("B1ModeType", &b1_brf_int);
  root_tree->SetBranchAddress("B2ModeType", &b2_brf_int);

  // loop and process every record
  int n_entries = root_tree->GetEntries();
  for (int i = 0; i < n_entries; ++i) {

    root_tree->GetEntry(i);

    // deduce mode code
    BrfReweightCode b1_brf_mode = int2BrfReweightCode(b1_brf_int);
    BrfReweightCode b2_brf_mode = int2BrfReweightCode(b2_brf_int);

    // compute correction weight
    double brf_correction_weight = 1.0;

    if (brf_correction_table.is_valid_entry(b1_brf_mode)) {
      brf_correction_weight *= brf_correction_table.brf(b1_brf_mode);
    }

    if (brf_correction_table.is_valid_entry(b2_brf_mode)) {
      brf_correction_weight *= brf_correction_table.brf(b2_brf_mode);
    }

    // write to csv
    csv.set("eventlabel", pu::type2string(eventlabel));
    csv.set("b1_brf_mode", brfcode2string(b1_brf_mode));
    csv.set("b2_brf_mode", brfcode2string(b2_brf_mode));
    csv.set("brf_correction_weight", pu::type2string(brf_correction_weight));
    csv.commit();

  }

  // clean up
  root_file->Close();
  delete root_file;

  csv.close();

}

