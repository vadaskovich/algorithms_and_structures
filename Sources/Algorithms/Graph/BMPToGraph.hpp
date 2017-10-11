//
//  BMPToGraph.hpp
//  Algorithms
//
//  Created by Bro on 10/11/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef BMPToGraph_hpp
#define BMPToGraph_hpp

#include <map>

#include "Common/BMP.hpp"
#include "Structures/Graph/Graph.hpp"

struct NodeCoordinate {
  NodeCoordinate() {}
  NodeCoordinate(int x_, int y_)
  : x(x_),
  y(y_)
  { }
  int x = 0;
  int y = 0;
};

typedef GraphNodeImpl<NodeCoordinate> Node;

// these functions are used for using in sorting containers as map or set
bool operator<(const NodeCoordinate& c1, const NodeCoordinate& c2);
bool operator<(const Node::ptr_weak& n1, const Node::ptr_weak& n2);

void BuildGraphForMaze(const BMP& maze, std::map<NodeCoordinate, Node::ptr>& nodeTable);

#endif /* BMPToGraph_hpp */
