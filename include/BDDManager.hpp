#pragma once

#include "BDDNode.hpp"

#include <ostream>
#include <string>
#include <vector>

class BDDManager {
public:
  std::vector<char> vars;
  std::vector<BDDNode> table;
  std::vector<std::string> product_terms;

public:
  BDDManager() {}

public:
  void buildTable();
  bool getPathResult(int);
  BDDManager toROBDD() const;
  void toDOT(std::ostream &) const;
  void printTable(std::ostream &) const;
};