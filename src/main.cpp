#include "BDDManager.hpp"

#include <iostream>

using namespace std;

int main() {
  BDDManager bdd;

  // // 11- 1
  // // --1 1
  // bdd.vars = {'a', 'b', 'c'};
  // bdd.product_terms.push_back("11-");
  // bdd.product_terms.push_back("--1");

  // -110 1
  // 01-- 1
  // -001 1
  // 1110 1
  // 0-00 1
  bdd.vars = {'a', 'b', 'c', 'd'};
  bdd.product_terms.push_back("-110");
  bdd.product_terms.push_back("01--");
  bdd.product_terms.push_back("-001");
  bdd.product_terms.push_back("1110");
  bdd.product_terms.push_back("0-00");

  bdd.buildTable();

  // bdd.toDOT(cout);

  bdd.printTable(cout);

  BDDManager robdd = bdd.toROBDD();

  cout << "= ROBDD ============================" << endl;
  robdd.toDOT(cout);
  // robdd.printTable(cout);

  return 0;
}