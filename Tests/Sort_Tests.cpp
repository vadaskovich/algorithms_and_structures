//
//  main.cpp
//  Sort
//
//  Created by Bro on 10/4/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <random>
#include <vector>
#include <iostream>
#include <assert.h>

#include "Common/Counter.hpp"

#include "Algorithms/Sort/SortBubble.hpp"
#include "Algorithms/Sort/SortCocktailShaker.hpp"
#include "Algorithms/Sort/SortInsertion.hpp"
#include "Algorithms/Sort/SortMerge.hpp"
#include "Algorithms/Sort/SortBinaryTree.hpp"
#include "Algorithms/Sort/SortBtree.hpp"

void ReportAlgorithmFinish(const std::string& algorithm_name, Counter& counter, const std::vector<int>& result_sorted, const std::vector<int>& data_for_comparison);
void FillTestData(std::vector<int>& data);
bool CompareInteger(const int& i1, const int& i2);

int main(int argc, const char * argv[]) {
  std::vector<int> data;
  FillTestData(data);
  
  // will compare our implementations with that to be sure
  std::vector<int> dataSortedPattern = data;
  std::sort(dataSortedPattern.begin(), dataSortedPattern.end(), &CompareInteger);
  // --
  
  std::cout << "Sorting tests." << std::endl;
  std::cout << "Elements count: " << data.size() << std::endl;
  
  Counter counter;
  
  
  // Bubble
  {
    std::vector<int> bubbleData = data;
    
    counter.tick();
    Sort::Bubble(bubbleData);
    ReportAlgorithmFinish("Bubble", counter, bubbleData, dataSortedPattern);
  }
  
  // Cocktail Shaker
  {
    std::vector<int> cocktailShakerData = data;
    counter.tick();
    Sort::CocktailShaker(cocktailShakerData);
    ReportAlgorithmFinish("Cocktail Shaker", counter, cocktailShakerData, dataSortedPattern);
  }
  
  // Insertion
  {
    std::vector<int> insertionData = data;
    counter.tick();
    Sort::Insertion(insertionData);
    ReportAlgorithmFinish("Insertion", counter, insertionData, dataSortedPattern);
  }
  
  // Merge
  {
    std::vector<int> sortMergeData = data;
    counter.tick();
    Sort::MergeSort(sortMergeData);
    ReportAlgorithmFinish("Merge", counter, sortMergeData, dataSortedPattern);
  }
  
  // Binary Tree (without balancing)
  {
    std::vector<int> sortBinaryTreeData = data;
    counter.tick();
    Sort::BinaryTreeSort(sortBinaryTreeData);
    ReportAlgorithmFinish("Binary Tree (Unbalancing)", counter, sortBinaryTreeData, dataSortedPattern);
  }
  
  // BTree
  {
    std::vector<int> sortBTreeData = data;
    counter.tick();
    Sort::BTreeSort(sortBTreeData);
    ReportAlgorithmFinish("B-Tree", counter, sortBTreeData, dataSortedPattern);
  }
  return 0;
}

bool CompareInteger(const int& i1, const int& i2) {
  return i1 < i2;
}

void ReportAlgorithmFinish
(const std::string& algorithmName, Counter& counter,
 const std::vector<int>& resultSorted, const std::vector<int>& dataForComparison)
{
  float secondsElapsed = counter.secondsElapsed();
  std::cout << ">> " << algorithmName << ": " << secondsElapsed << " s" << std::endl;
  
  bool sizesAreEqual = resultSorted.size() == dataForComparison.size();
  assert(sizesAreEqual);
  
  bool sortingIsSame = memcmp(&resultSorted[0], &dataForComparison[0], dataForComparison.size() * sizeof(int)) == 0;
  assert(sortingIsSame);
}

void FillTestData(std::vector<int>& data) {
  // fill by some known and edge values
  data =
  //{0, 5, 10, 9, 0, 4, 5};
  {0, 10, -999, 256, 123123, 0, 0, 1, 1, 5, 1, 5, 1, 5, 1, 65, INT_MAX, INT_MIN};
  //{0, 10, 0, 10, 0, 0, 1, 1, 1, 5, 1, 5, 1, 5, 65, -999};
  const size_t random_values_count =
  //0;
  30000;
  
  // also fill with random data
  srandom((int)time(NULL));
  
  data.reserve(data.size() + random_values_count);
  for (size_t i = 0; i < random_values_count; ++i) {
    int value = rand();
    data.push_back(value);
  }
}
