//
//  SortBtree.hpp
//  Sort_Tests
//
//  Created by Bro on 10/8/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef SortBtree_hpp
#define SortBtree_hpp

#include <vector>

#include "Structures/BTree/BTree.hpp"

namespace Sort {
  template <typename __DataType>
  void BTreeSort(std::vector<__DataType>& data) {
    // Make the binary tree
    BTree<__DataType> tree(25); // the number has been chosen without any reason, just not too small
    for (size_t i = 0; i < data.size(); ++i) {
      __DataType& valueToAdd = data[i];
      tree.add(valueToAdd);
    }
    
    // Traverse in order leftChildNode-currentElement-rightChildNode to get the data sorted
    size_t addIndex = 0;
    tree.traverseInfix([&data, &addIndex](const __DataType& value) {
      data[addIndex] = value;
      
      ++addIndex;
    });
  }
}

#endif /* SortBtree_hpp */
