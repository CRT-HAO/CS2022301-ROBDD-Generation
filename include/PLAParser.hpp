#pragma once

#include <istream>
#include <string>
#include <vector>

class PLAParser {
public:
  int input_num{0};
  int output_num{0};
  std::vector<char> input_vars;
  std::vector<char> output_vars;
  int product_terms_num{0};
  std::vector<std::pair<std::string, char>> product_terms;
  bool end{false};

public:
  PLAParser() {}

public:
  void parse(std::istream &);
};