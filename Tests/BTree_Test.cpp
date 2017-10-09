//
//  BTree_Test.cpp
//  BTree_Test
//
//  Created by Bro on 10/6/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <iostream>

#include "Structures/BTree/BTree.hpp"

void FillTestData(std::vector<int>& data);

int main(int argc, const char* argv[]) {
  std::vector<int> dataForTree;
  FillTestData(dataForTree);
  
  BTree<int> tree(3);
  for (int value : dataForTree) {
    tree.add(value);
  }
  
  std::vector<int> valuesSorted;
  tree.traverseInfix([&valuesSorted](const int& value) {
    valuesSorted.push_back(value);
  });

  assert(std::is_sorted(valuesSorted.begin(), valuesSorted.end()));
  
  return 0;
}

void FillTestData(std::vector<int>& data) {
  // fill by some known and edge values
  data = {0, 10, -999, 256, 123123, 0, 0, 1, 1, 5, 1, 5, 1, 5, 1, 65, INT_MAX, INT_MIN};
  const size_t random_values_count = 30000;
  
  // also fill with random data
  srandom((int)time(NULL));
  
  data.reserve(data.size() + random_values_count);
  for (size_t i = 0; i < random_values_count; ++i) {
    int value = rand();
    data.push_back(value);
  }
}
