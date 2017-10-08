//
//  HashTableBucket.hpp
//  HashTable
//
//  Created by Bro on 10/4/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef HashTableBucket_hpp
#define HashTableBucket_hpp

#include <string>

class HashTableBucket {
public:
  std::string key;
  std::string value;
  
  HashTableBucket* next = nullptr;
  
#ifdef DEBUG
  HashTableBucket() {
    ++s_allocations_count;
  }
  ~HashTableBucket() {
    --s_allocations_count;
  }
  static long s_allocations_count;
#endif
};

#endif /* HashTableBucket_hpp */
