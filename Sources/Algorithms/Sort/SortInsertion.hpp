//
//  SortInsertion.hpp
//  Sort_Tests
//
//  Created by Bro on 10/5/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef SortInsertion_hpp
#define SortInsertion_hpp

#include <limits>
#include <vector>

namespace Sort {
  template <typename __DataType>
  void Insertion(std::vector<__DataType>& data) {
    size_t currentLengthSorted = 1;
    
    for (size_t i_common = 1; i_common < data.size(); ++i_common) {
      __DataType valueToSort = data[i_common];
      
      if (valueToSort < data[0]) {
        // here we process the case, in which the value is less then minimum sorted value, so
        // all we need is (love) put that value to the start
        memcpy(&data[1], &data[0], i_common * sizeof(__DataType));
        data[0] = valueToSort;
      } else if (valueToSort > data[i_common - 1]) {
        // nothing to do, because the value already is in the right place (greater than the greatest sorted element)
      } else {
        // find the place to put the element to in the sorted section
        for (size_t i_sorted = 0; i_sorted < currentLengthSorted; ++i_sorted) {
          __DataType& valueSortedLeft  = data[i_sorted];
          __DataType& valueSortedRight = data[i_sorted + 1];
          
          // if the value is between two already sorted elements, put that element to that place
          if (valueToSort >= valueSortedLeft && valueToSort <= valueSortedRight) {
            size_t dataSizeToShift = i_common - i_sorted - 1;
            memcpy(&data[i_sorted + 2], &data[i_sorted + 1],
                   dataSizeToShift * sizeof(__DataType));
            data[i_sorted + 1] = valueToSort;
            break;
          }
        }
      }
      
      // we will search a place to put element until that index
      // because this is the max sorted element index
      currentLengthSorted = i_common;
      
    }
  }
}

#endif /* SortInsertion_hpp */
