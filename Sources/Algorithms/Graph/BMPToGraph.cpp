//
//  BMPToGraph.cpp
//  Algorithms
//
//  Created by Bro on 10/11/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include "BMPToGraph.hpp"

bool operator<(const NodeCoordinate& c1, const NodeCoordinate& c2) {
  return c1.x < c2.x || (c1.x == c2.x && c1.y < c2.y);
}

bool operator<(const Node::ptr_weak& n1, const Node::ptr_weak& n2) {
  Node::ptr node1Strong = n1.lock();
  Node::ptr node2Strong = n2.lock();
  
  if (node1Strong && node2Strong) {
    return node1Strong->data < node2Strong->data;
  } else {
    return false;
  }
}

void BuildGraphForMaze(const BMP& maze, std::map<NodeCoordinate, Node::ptr>& nodeTable) {
  // Create list of existing nodes (white dots of the maze)
  for (int x = 0; x < maze.width(); ++x) {
    for (int y = 0; y < maze.height(); ++y) {
      RGBColor cellColor = maze.getColor(x, y);
      if (cellColor.r == 255 && cellColor.g == 255 && cellColor.b == 255) {
        NodeCoordinate coordinate(x, y);
        
        Node::ptr node = Node::Create();
        node->data = coordinate;
        nodeTable[coordinate] = node;
      }
    }
  }
  
  // Build graph (i.e. links between nodes)
  // We try to get neighbor pixels
  for (auto& nodePair : nodeTable) {
    const Node::ptr node = nodePair.second;
    const NodeCoordinate& coordinate = nodePair.first;
    
    // --
    NodeCoordinate leftCellCoordinate = NodeCoordinate(coordinate.x - 1, coordinate.y);
    if (nodeTable.count(leftCellCoordinate)) {
      node->neighborList.insert(nodeTable[leftCellCoordinate]);
    }
    
    NodeCoordinate rightCellCoordinate = NodeCoordinate(coordinate.x + 1, coordinate.y);
    if (nodeTable.count(rightCellCoordinate)) {
      node->neighborList.insert(nodeTable[rightCellCoordinate]);
    }
    
    NodeCoordinate upCellCoordinate = NodeCoordinate(coordinate.x, coordinate.y - 1);
    if (nodeTable.count(upCellCoordinate)) {
      node->neighborList.insert(nodeTable[upCellCoordinate]);
    }
    
    NodeCoordinate bottomCellCoordinate = NodeCoordinate(coordinate.x, coordinate.y + 1);
    if (nodeTable.count(bottomCellCoordinate)) {
      node->neighborList.insert(nodeTable[bottomCellCoordinate]);
    }
  }
}
