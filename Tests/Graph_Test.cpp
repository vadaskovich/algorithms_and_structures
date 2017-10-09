//
//  Graph_Test.cpp
//  Graph_Test
//
//  Created by Bro on 10/9/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <map>

#include "Structures/Graph/Graph.hpp"

#include "Common/BMP.hpp"

struct NodeCoordinate {
  NodeCoordinate() {}
  NodeCoordinate(int x_, int y_)
  : x(x_),
    y(y_)
  { }
  int x = 0;
  int y = 0;
};

bool operator<(const NodeCoordinate& c1, const NodeCoordinate& c2) {
  return c1.x < c2.x || c1.y < c2.y;
}

typedef GraphNode<NodeCoordinate> Node;
bool operator<(const Node::ptr_weak& n1, const Node::ptr_weak& n2);

void ExploreGraph();

int main(int argc, const char* argv[]) {
  BMP maze;
  maze.read("../../../Tests/Resources/maze_1.bmp");
  
  
  std::map<NodeCoordinate, Node::ptr> nodeTable;
  
  // Create list of existing nodes (white dots of the maze)
  for (size_t x = 0; x < maze.width(); ++x) {
    for (size_t y = 0; y < maze.height(); ++y) {
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
    
    NodeCoordinate upCellCoordinate = NodeCoordinate(coordinate.x, coordinate.y + 1);
    if (nodeTable.count(upCellCoordinate)) {
      node->neighborList.insert(nodeTable[upCellCoordinate]);
    }
    
    NodeCoordinate bottomCellCoordinate = NodeCoordinate(coordinate.x, coordinate.y - 1);
    if (nodeTable.count(bottomCellCoordinate)) {
      node->neighborList.insert(nodeTable[bottomCellCoordinate]);
    }
  }

  
  // --
  {
    int const maxStepsCount = 100;
    
    std::set<NodeCoordinate> visitedPoints;
    
    int stepNumber = 0;
    Node::ptr traverseNode = nodeTable[NodeCoordinate(0, 0)];
    while (traverseNode) {
      NodeCoordinate coordinate = traverseNode->data;
      maze.setColor(coordinate.x, coordinate.y, RGBColor(255, 0, 0));
      
      Node::ptr nextNotVisitedNode = nullptr;
      for (Node::ptr_weak nodeWeak : traverseNode->neighborList) {
        Node::ptr node = nodeWeak.lock();
        if (!visitedPoints.count(node->data)) {
          nextNotVisitedNode = node;
          break;
        }
      }
      
      traverseNode = nextNotVisitedNode;
      
      visitedPoints.insert(coordinate);
      
      ++stepNumber;
      if (stepNumber == maxStepsCount) {
        break;
      }
    }
  }

  maze.save("../../../Tests/Resources/maze_1_out.bmp");
  
  return 0;
}


typedef GraphNode<NodeCoordinate> Node;
bool operator<(const Node::ptr_weak& n1, const Node::ptr_weak& n2) {
  Node::ptr node1Strong = n1.lock();
  Node::ptr node2Strong = n2.lock();
  
  if (node1Strong && node2Strong) {
    return node1Strong->data < node2Strong->data;
  } else {
    return false;
  }
}

