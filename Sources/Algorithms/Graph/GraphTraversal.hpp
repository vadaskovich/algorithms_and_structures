//
//  GraphTraversal.hpp
//  Algorithms
//
//  Created by Bro on 10/11/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef GraphTraversal_hpp
#define GraphTraversal_hpp

#include <assert.h> // to break the program if something went wrong
#include <queue> // we will use it a lot of times
#include <map>   // we need multimap, to keep depth-node accordance

#include "Common/throw_assert.hpp"

#include "Graph.hpp"

template <typename __NodeDataType>
class GraphTraversal {
public:
  typedef GraphNodeImpl<__NodeDataType> __Node;
  typedef typename __Node::ptr __NodePtr;
  typedef typename __Node::ptr_weak __NodePtrWeak;
  typedef std::function<void(const __NodePtr node, int depth)> __NodeIndexCallback;
  typedef std::function<void(__NodePtr node)> NodeCallback;
  
  static void FindAWay(const __NodePtr nodeStart, const __NodePtr nodeEnd, std::vector<__NodePtr>& result) {
    assert(nodeStart);
    assert(nodeEnd);
    
    std::multimap<int, __NodePtr> nodeDepthAccordance;
    
    // Here we search breadth-first kind of search and get depths of each node
    // we keep that pair in external multimap structure to not touch the nodes
    BreadthSearchFirst
    (nodeStart, nodeEnd,
     [&nodeDepthAccordance, &result, &nodeEnd](const __NodePtr node, int depth)
     {
       nodeDepthAccordance.insert(std::make_pair(depth, node));
     });
    
    // Search for the end node. Here we answer the question: "Have we reached the desired node?"
    bool reachedTheEnd = false;
    int depthOfTheEnd = -1;
    // Find the endNode we want to reach
    for (auto& data : nodeDepthAccordance) {
      if (data.second == nodeEnd) {
        reachedTheEnd = true;
        depthOfTheEnd = data.first;
      }
      // std::cout << "[" << data.first << "] {" << data.second->data.x << ", " << data.second->data.y << "}" << std::endl;
    }
    
    // Construct the path
    if (reachedTheEnd) {
      std::vector<__NodePtr> reversePath;
      reversePath.reserve(depthOfTheEnd);
      
      typedef typename std::multimap<int, __NodePtr>::iterator MMAPIterator;
      
      assert(depthOfTheEnd != -1);
      reversePath.push_back(nodeEnd);
      
      // Here we walk in reverse order from the end node to the start node
      // by the path we reached the end node from the start
      __NodePtr current_node = nodeEnd;
      for (int depth_i = depthOfTheEnd - 1; depth_i >= 0; --depth_i) {
        std::pair<MMAPIterator, MMAPIterator> nodesNearby = nodeDepthAccordance.equal_range(depth_i);
        
        // Check for neighboring
        for (MMAPIterator it = nodesNearby.first; it != nodesNearby.second; ++it) {
          __NodePtr nodeNeighbor = it->second;
          if (current_node->neighborList.count(nodeNeighbor)) {
            reversePath.push_back(nodeNeighbor);
            current_node = nodeNeighbor;
          }
        }
      }
      
      result = reversePath;
      std::reverse(result.begin(), result.end());
    }
  }
  
  static void BreadthSearchFirst
  (const __NodePtr nodeStart,
   const __NodePtr nodeEnd,
   const __NodeIndexCallback& callback)
  {
    // Has been visited? Added hither then.
    std::set<__NodePtr> visited;
    
    // Depth is the shortest length to reach a certain node
    int depth = 0;
    
    //
    callback(nodeStart, depth);
    visited.insert(nodeStart);
    
    // Queues of queus – to allow you to be in a queue while you are in a queue
    // If seriously – each internal queue will contain nodes with equal depth
    std::queue<std::queue<__NodePtr>> depthQueues;
    
    // Initiate begin state
    std::queue<__NodePtr> startDepthNodes;
    startDepthNodes.push(nodeStart);
    depthQueues.push(startDepthNodes);
    // --
    
    // If we have nodes that need to be handled (added from internal loop), do it.
    while (depthQueues.size() > 0) {
      // Fetch nodes with equal depth from the queue of queues
      std::queue<__NodePtr> currentDepthNodes = depthQueues.front();
      depthQueues.pop();
      // --
      
      // Further we deal with greater depth
      ++depth;
      
      // here we will put nodes that are in the next depth level
      std::queue<__NodePtr> nextDepthNodes;
      
      // if there is some, handle it.
      while (currentDepthNodes.size() > 0) {
        __NodePtr node = currentDepthNodes.front();
        currentDepthNodes.pop(); // I'd like it to be classical, not pop :(
        
        // All not visited neighbors are to be added to the next depth level node list
        for (__NodePtrWeak neighborWeak : node->neighborList) {
          const __NodePtr neighbor = neighborWeak.lock();
          if (visited.count(neighbor)) {
            continue;
          }
          
          callback(neighbor, depth); // I'll call you back, I promise.
          visited.insert(neighbor);
          
          nextDepthNodes.push(neighbor);  // We'll come to this later
        }
      }
      
      // If there is some nodes, add them to the super queue of queues
      if (nextDepthNodes.size() > 0) {
        depthQueues.push(nextDepthNodes);
      }
    }
  }
  
  // Very simple algorithm via depth-first search
  static void TraverseAllGraph(const __NodePtr node, const NodeCallback& nodeCallback) {
    std::set<__NodePtr> visited;
    __TraverseAllGraph(node, nodeCallback, visited);
  }
  
private:
  static void __TraverseAllGraph(const __NodePtr node_in, const NodeCallback& nodeCallback, std::set<__NodePtr>& visited) {
    assert(node_in);
    
    if (visited.count(node_in)) {
      return;
    }
    
    // visit input node first
    nodeCallback(node_in);
    visited.insert(node_in);
    
    //
    __NodePtr nextNotVisitedNode = nullptr;
    for (__NodePtrWeak nodeWeak : node_in->neighborList) {
      __NodePtr node = nodeWeak.lock();
      assert(node);
      
      __TraverseAllGraph(node, nodeCallback, visited);
    }
  }
};

#endif /* GraphTraversal_hpp */
