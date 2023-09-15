#include "BDDManager.hpp"
#include "BDDNode.hpp"

#define POW_OF_TWO(n) ((n >= 0) ? (1 << (n)) : 0) // 2 ^ i
#define ASCII_TO_NUM(c) ((c) - '0')

using namespace std;

void BDDManager::buildTable() {
  this->table.clear();
  this->table.push_back(BDDNode('0', -1, -1));
  this->table.push_back(BDDNode('1', -1, -1));

  const size_t vars_num = this->vars.size();
  size_t index = 2; // skip 2 rows for constsnt 0 and 1

  for (size_t i = 0; i < vars_num; i++) {
    index += POW_OF_TWO(i);

    for (size_t j = 0; j < POW_OF_TWO(i); j++) {
      BDDNode node;

      node.var = this->vars[i];
      if (i == (vars_num - 1)) {
        // shift left 1 bit to move to next layer
        node.elseEdge = this->getPathResult(j << 1);
        node.thenEdge = this->getPathResult((j << 1) | 1);
      } else {
        node.elseEdge = index + (2 * j);
        node.thenEdge = index + (2 * j) + 1;
      }

      this->table.push_back(node);
    }
  }
}

bool BDDManager::getPathResult(int path) {
  for (const string &p : this->product_terms) {
    const size_t vars_num = this->vars.size();
    bool result = true;

    for (int j = 0; j < vars_num; j++) {
      // if the term is '-', then the result can be true
      // or the terms all equal to the path, then the result should be true
      result &= (p[j] == '-') ||
                (ASCII_TO_NUM(p[j]) == ((path >> (vars_num - 1 - j)) & 1));
    }

    // if we find a terms fully equal to the path,
    // then we don't need to judge anymore
    if (result)
      return true;
  }

  return false;
}

BDDManager BDDManager::toROBDD() const {
  BDDManager robdd = *this;
  const size_t vars_num = robdd.vars.size();
  size_t index = POW_OF_TWO(vars_num) - 1 + 2; // last index

  for (int i = vars_num - 1; i >= 0; i--) {
    index -= POW_OF_TWO(i); // move back one block

    for (int j = 0; j < POW_OF_TWO(i); j++) {
      const size_t parent_index = index - POW_OF_TWO(i - 1) + (j / 2);
      const size_t current_index = index + j;

      if (robdd.table[current_index].thenEdge ==
          robdd.table[current_index].elseEdge) {
        // if the elseEdge and the thenEdge are the same

        // connect the parent's edge to the child's edge
        // if j is odd number, it means that the elseEdge
        // otherwise it's the thenEdge
        if (j % 2 == 0)
          robdd.table[parent_index].elseEdge =
              robdd.table[current_index].elseEdge;
        else
          robdd.table[parent_index].thenEdge =
              robdd.table[current_index].thenEdge;

        // throwing out the old node
        robdd.table[current_index].thenEdge = -1;
        robdd.table[current_index].elseEdge = -1;

      } else if (j != 0) {
        // if the node is not the only one in the layer

        for (int k = 0; k < j; k++) {
          const size_t next_index = index + k;

          if ((robdd.table[current_index].thenEdge ==
               robdd.table[next_index].thenEdge) &&
              (robdd.table[current_index].elseEdge ==
               robdd.table[next_index].elseEdge)) {
            // if the node ends up connecting to the same place.

            // connect the parent's edge to the child's edge
            if (j % 2 == 0)
              robdd.table[parent_index].elseEdge = next_index;
            else
              robdd.table[parent_index].thenEdge = next_index;

            // throwing out the old node
            robdd.table[current_index].thenEdge = -1;
            robdd.table[current_index].elseEdge = -1;

            break;
          }
        }
      }
    }
  }

  return robdd;
}

void BDDManager::toDOT(ostream &out) const {
  const size_t vars_num = this->vars.size();
  size_t index = 2; // skip 2 rows for constsnt 0 and 1

  out << "digraph ROBDD{" << endl;

  for (int i = 0; i < vars_num; i++) {
    index += POW_OF_TWO(i - 1);
    out << "{rank=same";
    for (int j = 0; j < POW_OF_TWO(i); j++) {
      if (this->table[index + j].thenEdge != -1)
        out << ' ' << index + j;
    }
    out << "}" << endl;
  }
  out << endl;

  out << "0[label=0 ,shape=box]" << endl << "1[label=1 ,shape=box]" << endl;
  for (int i = 0; i < this->table.size(); i++) {
    if (this->table[i].thenEdge != -1)
      out << i << "[label=\"" << this->table[i].var << "\"]" << endl;
  }
  out << endl;

  for (int i = 0; i < this->table.size(); i++) {
    if (this->table[i].thenEdge != -1)
      out << i << "->" << this->table[i].thenEdge << "[label=\"1\",style=solid]"
          << endl
          << i << "->" << this->table[i].elseEdge
          << "[label=\"0\",style=dotted]" << endl;
  }
  out << "}" << endl;
}

void BDDManager::printTable(std::ostream &out) const {
  out << "= Table ============================" << endl;
  out << "#\tvar\telse\tthen" << endl;
  size_t i = 0;
  for (const auto &node : this->table) {
    out << i << '\t' << node.var << '\t' << node.elseEdge << '\t'
        << node.thenEdge << endl;
    i += 1;
  }
}
