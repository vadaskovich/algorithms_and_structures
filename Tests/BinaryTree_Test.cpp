//
//  BinaryTree_Test.cpp
//  BinaryTree_Test
//
//  Created by Bro on 10/6/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <vector>
#include <iostream>

#include "Structures/BinaryTree/BinaryTree.hpp"

int main(int argc, const char* argv[]) {
  
  std::vector<int> test_data =
  {0, -1, -999, 0, 0, 1, 2, 3, 4, INT_MAX, INT_MIN};
  
  // --
  {
    BinaryTree<int> tree;
    for (size_t i = 0; i < test_data.size(); ++i) {
      tree.add(test_data[i]);
    }
        
    tree.traverseInfix([](const int& value) {
      std::cout << value << " ";
    });
  }
  return 0;
}
