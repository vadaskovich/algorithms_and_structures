//
//  Graph.hpp
//  Graph_Test
//
//  Created by Bro on 10/9/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <memory>
#include <vector>
#include <set>


template <typename __DataType>
class GraphNode {
public:
  typedef GraphNode<__DataType> __GrapeNodeConcrete;
  typedef std::shared_ptr<__GrapeNodeConcrete> ptr;
  typedef std::weak_ptr<__GrapeNodeConcrete> ptr_weak;
  
  template <typename ...Args>
  static __GrapeNodeConcrete::ptr Create(Args&& ... args) {
    return std::make_shared<__GrapeNodeConcrete>(std::forward<Args>(args)...);
  }
  GraphNode() {}
  ~GraphNode() {}
  
  std::set<__GrapeNodeConcrete::ptr_weak> neighborList;
  __DataType data;
};

#endif /* Graph_hpp */
