#include "BDDManager.hpp"
#include "PLAParser.hpp"

#include <fstream>
#include <iostream>

using namespace std;

void printUsage() { cout << "Usage: robdd [input] [output]" << endl; }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printUsage();
    return 1;
  }

  const char *input_file = argv[1];
  const char *output_file = argv[2];

  ifstream ifs;
  ifs.open(input_file);
  if (!ifs.is_open()) {
    cout << "Error: Could not open input file " << input_file << endl;
    return 1;
  }

  ofstream ofs;
  ofs.open(output_file);
  if (!ofs.is_open()) {
    cout << "Error: Could not open output file " << output_file << endl;
    return 1;
  }

  PLAParser parser;
  parser.parse(ifs);
  if (!parser.end) {
    cout << "Error: Could not parse input file " << input_file << endl;
    return 1;
  }

  BDDManager bdd;
  bdd.vars = parser.input_vars;
  for (const auto &p : parser.product_terms) {
    if (p.second != '1') {
      // eg. `11- 0` <- we don't support the terms that sum is zero or dont't
      // care
      cout << "Error: Find unsupported product terms sum" << endl;
      return 1;
    }

    bdd.product_terms.push_back(p.first);
  }

  // Build BDD Table
  bdd.buildTable();
  cout << "= BDD ==============================" << endl;
  bdd.printTable(cout);

  // To ROBDD
  BDDManager robdd = bdd.toROBDD();
  cout << "= ROBDD ============================" << endl;
  robdd.printTable(cout);

  cout << "== DOT =============================" << endl;
  robdd.toDOT(cout);
  robdd.toDOT(ofs);

  return 0;
}