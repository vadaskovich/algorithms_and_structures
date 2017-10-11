//
//  Graph.hpp
//  Graph_Test
//
//  Created by Bro on 10/9/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <memory> // need for shared_ptr and weak_ptr
#include <set> // for keeping list of node's neighbors


// A graph is supposed to be a very complicated thing, but all we have to have is graph nodes and links between them
template <typename __DataType>
class GraphNodeImpl {
public:
  typedef GraphNodeImpl<__DataType> __GrapeNodeConcrete;
  typedef std::shared_ptr<__GrapeNodeConcrete> ptr;
  typedef std::weak_ptr<__GrapeNodeConcrete> ptr_weak;
  
  template <typename ...Args>
  static __GrapeNodeConcrete::ptr Create(Args&& ... args) {
    return std::make_shared<__GrapeNodeConcrete>(std::forward<Args>(args)...);
  }
  GraphNodeImpl() {}
  ~GraphNodeImpl() {}
  
  std::set<__GrapeNodeConcrete::ptr_weak> neighborList;
  __DataType data;
};

#endif /* Graph_hpp */
