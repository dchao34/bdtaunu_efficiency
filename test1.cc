#include <iostream>
#include <TFile.h>
#include <TTree.h>

#include <CsvWriter.h>
#include <pgstring_utils.h>

#include "BrfReweightCode.h"
#include "BrfCorrectionTable.h"

namespace pu = pgstring_utils;

int main() {

  BrfCorrectionTable brf_correction_table("brf_corrections.dat");

  TFile *root_file = new TFile("BtoDtaunu.root");
  TTree *root_tree = (TTree*) root_file->Get("ntp1");

  int eventlabel, b1_brf_int, b2_brf_int;
  root_tree->SetBranchAddress("EventLabel", &eventlabel);
  root_tree->SetBranchAddress("B1ModeType", &b1_brf_int);
  root_tree->SetBranchAddress("B2ModeType", &b2_brf_int);

  CsvWriter csv;
  csv.open("br_mode.csv", {
      "eventlabel", "b1_brf_mode", "b2_brf_mode", "brf_correction_weight"
  });

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

  root_file->Close();
  delete root_file;

  csv.close();
  
  return 0;
}
