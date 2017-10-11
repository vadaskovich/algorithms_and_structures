//
//  Graph_Test.cpp
//  Graph_Test
//
//  Created by Bro on 10/9/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <map>
#include <functional>
#include <iostream>
#include <queue>

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

typedef GraphNode<NodeCoordinate> Node;

bool operator<(const NodeCoordinate& c1, const NodeCoordinate& c2);

typedef GraphNode<NodeCoordinate> Node;
bool operator<(const Node::ptr_weak& n1, const Node::ptr_weak& n2);

typedef std::function<void(Node::ptr node)> NodeCallback;

void TraverseAllGraph(const Node::ptr startNode, const NodeCallback& nodeCallback);

int main(int argc, const char* argv[]) {
  BMP maze;
  maze.read("../../../Tests/Resources/maze_1.bmp");
  
  std::queue<int> q;
  
  std::map<NodeCoordinate, Node::ptr> nodeTable;
  
  // Create list of existing nodes (white dots of the maze)
  for (size_t x = 0; x < maze.width(); ++x) {
    for (size_t y = 0; y < maze.height(); ++y) {
      RGBColor cellColor = maze.getColor(x, y);
      if (cellColor.r == 255 && cellColor.g == 255 && cellColor.b == 255) {
        
        // (y, x) because pixels are stored so
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
    
    NodeCoordinate upCellCoordinate = NodeCoordinate(coordinate.x, coordinate.y - 1);
    if (nodeTable.count(upCellCoordinate)) {
      node->neighborList.insert(nodeTable[upCellCoordinate]);
    }
    
    NodeCoordinate bottomCellCoordinate = NodeCoordinate(coordinate.x, coordinate.y + 1);
    if (nodeTable.count(bottomCellCoordinate)) {
      node->neighborList.insert(nodeTable[bottomCellCoordinate]);
    }
  }
  
  // Traverse all nodes
  BMP mazeAllTraversed = maze;
  Node::ptr startNode = nodeTable[NodeCoordinate(0, 0)];
  RGBColor trackColor(255, 0, 0);
  TraverseAllGraph(startNode, [&mazeAllTraversed, &trackColor](Node::ptr node) {
    NodeCoordinate coordinate = node->data;
    mazeAllTraversed.setColor(coordinate.x, coordinate.y, trackColor);
    
    trackColor.b += 2;
    trackColor.g += 2;
  });
  mazeAllTraversed.save("../../../Tests/Resources/maze_1_all.bmp");
  
  return 0;
}

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

void __TraverseAllGraph(const Node::ptr node_in, const NodeCallback& nodeCallback, std::set<NodeCoordinate>& visited) {
  if (visited.count(node_in->data)) {
    return;
  }
  
  // visit input node
  nodeCallback(node_in);
  visited.insert(node_in->data);
  
  //
  Node::ptr nextNotVisitedNode = nullptr;
  for (Node::ptr_weak nodeWeak : node_in->neighborList) {
    Node::ptr node = nodeWeak.lock();
    __TraverseAllGraph(node, nodeCallback, visited);
  }
}

void TraverseAllGraph(const Node::ptr node, const NodeCallback& nodeCallback) {
  std::set<NodeCoordinate> visited;
  __TraverseAllGraph(node, nodeCallback, visited);
}

