#pragma once

#include <cstddef>

class BDDNode {
public:
  char var;
  int elseEdge;
  int thenEdge;

public:
  BDDNode() {}
  BDDNode(char var, int elseEdge, int thenEdge)
      : var(var), elseEdge(elseEdge), thenEdge(thenEdge) {}
};