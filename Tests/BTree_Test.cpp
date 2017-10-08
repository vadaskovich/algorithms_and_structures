//
//  BTree_Test.cpp
//  BTree_Test
//
//  Created by Bro on 10/6/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include "Structures/BTree/BTree.hpp"

int main(int argc, const char* argv[]) {
  BTree<int> tree(3);
  tree.add(1);
  tree.add(2);
  tree.add(3);
  tree.add(4);
  tree.add(5);
  tree.add(6);
  tree.add(7);
  
  return 0;
}
