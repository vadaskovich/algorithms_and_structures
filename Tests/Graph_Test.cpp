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
#include <deque>
#include <queue>
#include <assert.h>

#include "Common/throw_assert.hpp"
#include "Algorithms/Graph/GraphTraversal.hpp"
#include "Structures/Graph/Graph.hpp"

#include "Common/BMP.hpp"
#include "Algorithms/Graph/BMPToGraph.hpp"


int MazeTest() {
  // try to read bmp into maze structure, considering white pixels as nodes
  BMP maze;
  
  const char* mazeFilePath = "../../../Tests/Resources/maze_1.bmp";
  bool mazeFileReadResult = maze.read(mazeFilePath);
  throw_assert_explain(mazeFileReadResult, "can not read the file at path: %s", mazeFilePath);
  
  // --
  std::map<NodeCoordinate, Node::ptr> nodeTable;
  BuildGraphForMaze(maze, nodeTable);
  
  // Visit all nodes and paint them
  BMP mazeAllTraversed = maze;
  NodeCoordinate coordinateStartFrom(0, 0);
  Node::ptr startNode = nodeTable[coordinateStartFrom];
  throw_assert_explain(startNode, "there is no such node for coordinate: [%d, %d]", coordinateStartFrom.x, coordinateStartFrom.y);
  
  RGBColor trackColor(255, 0, 0);
  GraphTraversal<NodeCoordinate>::TraverseAllGraph
  (startNode, [&mazeAllTraversed, &trackColor](Node::ptr node) {
    if (!node) return;
    
    NodeCoordinate coordinate = node->data;
    mazeAllTraversed.setColor(coordinate.x, coordinate.y, trackColor);
  });
  mazeAllTraversed.save("../../../Tests/Resources/maze_1_all.bmp");
  
  // Try to find a shortest way between points in the given maze
  std::vector<Node::ptr> shortestWay;
  
  NodeCoordinate coordinateAtStart(0, 1);
  NodeCoordinate coordinateAtEnd(maze.width() - 1, maze.height() - 1);
  Node::ptr nodeStartFrom = nodeTable[coordinateAtStart];
  Node::ptr nodeGoTo      = nodeTable[coordinateAtEnd];
  
  throw_assert_explain(nodeStartFrom, "there is no such node for start point: [%d, %d]", coordinateAtStart.x, coordinateAtStart.y);
  throw_assert_explain(nodeGoTo, "there is no such node for end point: [%d, %d]", coordinateAtEnd.x, coordinateAtEnd.y);
  
  GraphTraversal<NodeCoordinate>::FindAWay(nodeStartFrom, nodeGoTo, shortestWay);
  
  BMP mazePath = maze;
  for (Node::ptr node : shortestWay) {
    mazePath.setColor(node->data.x, node->data.y, RGBColor(255, 0, 0));
  }
  mazePath.save("../../../Tests/Resources/maze_1_path.bmp");
  // --
  
  return 0;
}

int main(int argc, const char* argv[]) {
  try {
    MazeTest();
  } catch (std::exception& e) {
    std::cout << "Error with MazeTest: " << e.what() << std::endl;
  }
  return 0;
}
