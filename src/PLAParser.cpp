#include "PLAParser.hpp"

#include <cstdlib>
#include <sstream>
#include <string>

#define CHAR_TO_NUM(c) ((c) - '0')

using namespace std;

void PLAParser::parse(istream &in) {
  for (string line; getline(in, line);) {
    stringstream ss(line);

    string command;
    ss >> command;
    if (command == ".i") {
      // eg. `.i 3`
      ss >> this->input_num;
    } else if (command == ".o") {
      // eg. `.o 1`
      ss >> this->output_num;
    } else if (command == ".ilb") {
      // eg. `.ilb a b c`
      this->input_vars.clear();
      for (size_t i = 0; i < this->input_num; ++i) {
        char var;
        ss >> var;
        this->input_vars.push_back(var);
      }
    } else if (command == ".ob") {
      // eg. `.ob f`
      this->output_vars.clear();
      for (size_t i = 0; i < this->output_num; ++i) {
        char var;
        ss >> var;
        this->output_vars.push_back(var);
      }
    } else if (command == ".p") {
      // eg.
      // `.p 2
      // 1-1 1
      // -11 1`
      int n;
      ss >> n;
      this->product_terms.clear();
      size_t i = 0;
      for (string p_line; i < n && getline(in, p_line) && !in.eof(); ++i) {
        stringstream p_ss(p_line);

        string product_terms;
        p_ss >> product_terms;

        char sum;
        p_ss >> sum;

        bool sum_bool = (CHAR_TO_NUM(sum) > 0 ? true : false);

        this->product_terms.push_back(
            pair<string, bool>(product_terms, sum_bool));
      }
    } else if (command == ".e") {
      // eg. `.e`
      this->end = true;
    } else {
      throw std::runtime_error("Unknown command");
    }
  }
}