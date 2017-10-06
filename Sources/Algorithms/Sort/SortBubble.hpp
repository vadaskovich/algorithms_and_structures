//
//  SortBubble.hpp
//  SortBubble
//
//  Created by Bro on 10/4/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef SortBubble_hpp
#define SortBubble_hpp

#include <vector>

namespace Sort {
  template <typename __DataType>
  void Bubble(std::vector<__DataType>& data) {
    // will be decreased each iteration for optimization
    size_t maxSortedIndex = data.size() - 1;
    
    bool needYetAnotherIteration = true;
    while (needYetAnotherIteration) {
      bool hasTheSortingBeenTakenPlace = false;
      
      for (size_t i = 0; i < maxSortedIndex; ++i) {
        __DataType& firstValue  = data[i];
        __DataType& secondValue = data[i + 1];
        
        if (firstValue > secondValue) {
          std::swap(firstValue, secondValue);
          hasTheSortingBeenTakenPlace = true;
        }
      } // for..
      
      // --
      needYetAnotherIteration = hasTheSortingBeenTakenPlace;
      
      // Decrease the index, because at the end of the array we already have
      // the highest value
      if (maxSortedIndex > 1) {
        --maxSortedIndex;
      } else {
        needYetAnotherIteration = false;
      }
    }
    
  }
}

#endif /* SortBubble_hpp */
