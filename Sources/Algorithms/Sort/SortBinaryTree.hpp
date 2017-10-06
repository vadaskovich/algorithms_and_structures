//
//  SortBinaryTree.hpp
//  Sort_Tests
//
//  Created by Bro on 10/6/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef SortBinaryTree_hpp
#define SortBinaryTree_hpp

#include <vector>

#include "Structures/BinaryTree/BinaryTree.hpp"

namespace Sort {
  template <typename __DataType>
  void BinaryTreeSort(std::vector<__DataType>& data) {
    // Make the binary tree
    BinaryTree<__DataType> tree;
    for (const auto& value : data) {
      tree.add(value);
    }
    
    // Traverse in order leftChildNode-currentNode-rightChildNode
    size_t addIndex = 0;
    tree.traverseInfix([&data, &addIndex](const __DataType& value) {
      data[addIndex] = value;
      
      ++addIndex;
    });
  }
}

#endif /* SortBinaryTree_hpp */
