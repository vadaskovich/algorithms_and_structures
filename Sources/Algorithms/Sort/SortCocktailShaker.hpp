//
//  SortCocktailShaker.hpp
//  SortCocktailShaker
//
//  Created by Bro on 10/4/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef SortCocktailShaker_hpp
#define SortCocktailShaker_hpp

#include <vector>

namespace Sort {
  template <typename __DataType>
  void CocktailShaker(std::vector<__DataType>& data) {
    // edge indices which will be changed, narrowing range of iterations
    size_t leftIndex = 0;
    size_t rightIndex = data.size() - 1;
    
    bool needYetAnotherIteration = true;
    while (needYetAnotherIteration) {
      bool hasTheSortingBeenTakenPlace = false;
      
      // iterate from left to right
      for (size_t i = leftIndex; i < rightIndex; ++i) {
        __DataType& leftValue  = data[i];
        __DataType& rightValue = data[i + 1];
        
        if (leftValue > rightValue) {
          std::swap(leftValue, rightValue);
          hasTheSortingBeenTakenPlace = true;
        }
      }
      
      if (rightIndex > 1) {
        --rightIndex;
      }
      // --
      
      // iterate from right to left
      for (size_t i = rightIndex; i > leftIndex; --i) {
        __DataType& leftValue = data[i - 1];
        __DataType& rightValue = data[i];
        
        if (leftValue > rightValue) {
          std::swap(leftValue, rightValue);
          hasTheSortingBeenTakenPlace = true;
        }
      }
      
      if (leftIndex < data.size() - 1) {
        ++leftIndex;
      }
      // --
      
      bool leftAndRightMetEachOther = (rightIndex - leftIndex) <= 0;
      
      if (hasTheSortingBeenTakenPlace && !leftAndRightMetEachOther) {
        needYetAnotherIteration = true;
      } else {
        needYetAnotherIteration = false;
      }
    }
  }
}

#endif /* SortCocktailShaker_hpp */
