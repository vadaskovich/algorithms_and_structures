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

#include "Common/Counter.hpp"
#include "Common/throw_assert.hpp"
#include "Algorithms/Graph/GraphTraversal.hpp"
#include "Structures/Graph/Graph.hpp"

#include "Common/BMP.hpp"
#include "Algorithms/Graph/BMPToGraph.hpp"

void ReportAlgorithmFinish(const std::string& algorithmName, Counter& counter) {
  float secondsElapsed = counter.secondsElapsed();
  std::cout << ">> " << algorithmName << ": " << secondsElapsed << " s" << std::endl;
}

int MazeTest() {
  // try to read bmp into maze structure, considering white pixels as nodes
  BMP maze;
  
  const char* mazeFilePath = "../../../Tests/Resources/maze_1.bmp";
  bool mazeFileReadResult = maze.read(mazeFilePath);
  throw_assert_explain(mazeFileReadResult, "can not read the file at path: %s", mazeFilePath);
  
  std::cout << "Labyrinth test started" << std::endl;
  
  Counter counter;
  
  // Build graph
  std::map<NodeCoordinate, Node::ptr> nodeTable;
  BuildGraphForMaze(maze, nodeTable);
  ReportAlgorithmFinish("Building graph", counter);
  // --
  
  // Visit all nodes and paint them
  BMP mazeAllTraversed = maze;
  NodeCoordinate coordinateStartFrom(0, 0);
  Node::ptr startNode = nodeTable[coordinateStartFrom];
  throw_assert_explain(startNode, "there is no such node for coordinate: [%d, %d]", coordinateStartFrom.x, coordinateStartFrom.y);
  
  RGBColor trackColor(255, 0, 0);
  counter.tick();
  GraphTraversal<NodeCoordinate>::TraverseAllGraph
  (startNode, [&mazeAllTraversed, &trackColor](Node::ptr node) {
    if (!node) return;
    
    NodeCoordinate coordinate = node->data;
    mazeAllTraversed.setColor(coordinate.x, coordinate.y, trackColor);
  });
  ReportAlgorithmFinish("Traversing all graph", counter);
  mazeAllTraversed.save("../../../Tests/Resources/maze_1_all.bmp");
  
  // Try to find a shortest way between points in the given maze
  std::vector<Node::ptr> shortestWay;
  
  NodeCoordinate coordinateAtStart(0, 0);
  NodeCoordinate coordinateAtEnd(maze.width() - 1, maze.height() - 1);
  Node::ptr nodeStartFrom = nodeTable[coordinateAtStart];
  Node::ptr nodeGoTo      = nodeTable[coordinateAtEnd];
  
  throw_assert_explain(nodeStartFrom, "there is no such node for start point: [%d, %d]", coordinateAtStart.x, coordinateAtStart.y);
  throw_assert_explain(nodeGoTo, "there is no such node for end point: [%d, %d]", coordinateAtEnd.x, coordinateAtEnd.y);
  
  counter.tick();
  GraphTraversal<NodeCoordinate>::FindAWay(nodeStartFrom, nodeGoTo, shortestWay);
  ReportAlgorithmFinish("Finding a shortest way", counter);
  
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
