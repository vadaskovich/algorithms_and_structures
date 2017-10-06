//
//  Merge.hpp
//  Sort_Tests
//
//  Created by Bro on 10/5/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef SortMerge_hpp
#define SortMerge_hpp

#include <vector>

namespace Sort {
  bool __CompareInteger(const int& i1, const int& i2);
  
  template <typename __DataType>
  void MergeSort(std::vector<__DataType>& data) {
    
    // we will multiply this by 2 each iteration, therefore, increasing block size twice
    size_t mergeBlockSize = 1;
    
    while (mergeBlockSize < data.size()) {
      // Here we go through block pairs
      for (size_t i = 0; i < data.size(); i += (mergeBlockSize * 2)) {
        size_t leftBlockStartIndex  = i;
        size_t rightBlockStartIndex = leftBlockStartIndex + mergeBlockSize;
        
        // Start merging...
        std::vector<__DataType> mergedResult;
        mergedResult.reserve(mergeBlockSize * 2);
        
        typedef typename std::vector<__DataType>::iterator _ContainerIterator;
        
        _ContainerIterator leftIterator  = leftBlockStartIndex < data.size() ? data.begin() + leftBlockStartIndex : data.end();
        _ContainerIterator rightIterator = rightBlockStartIndex < data.size() ? data.begin() + rightBlockStartIndex : data.end();
        
        _ContainerIterator leftBlockEndIterator = leftIterator + mergeBlockSize;
        _ContainerIterator rightBlockEndIterator = rightIterator + mergeBlockSize;
        
        while ((leftIterator  != leftBlockEndIterator  && leftIterator  != data.end()) &&
               (rightIterator != rightBlockEndIterator && rightIterator != data.end()))
        {
          __DataType& leftValue  = *leftIterator;
          __DataType& rightValue = *rightIterator;
          
          if (leftValue == rightValue) {
            mergedResult.push_back(leftValue);
            mergedResult.push_back(rightValue);
            ++leftIterator;
            ++rightIterator;
          } else if (leftValue < rightValue) {
            ++leftIterator;
            mergedResult.push_back(leftValue);
          } else {
            ++rightIterator;
            mergedResult.push_back(rightValue);
          }
        }
        
        while (leftIterator != leftBlockEndIterator && leftIterator != data.end()) {
          mergedResult.push_back(*leftIterator);
          ++leftIterator;
        }
        
        while (rightIterator != rightBlockEndIterator && rightIterator != data.end()) {
          mergedResult.push_back(*rightIterator);
          ++rightIterator;
        }
        // ... end merging
        
        // Apply the merging result
        memcpy(&data[leftBlockStartIndex], &mergedResult[0], mergedResult.size() * sizeof(__DataType));
      }
      
      mergeBlockSize *= 2;
    }
  }
}

#endif /* Merge_hpp */
