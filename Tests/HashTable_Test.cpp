//
//  main.cpp
//  HashTable
//
//  Created by Bro on 9/28/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <string>
#include <iostream>
#include <assert.h>

#include "Structures/HashTable/HashTable.hpp"
#include "Structures/HashTable/HashTableBucket.hpp"

void testHashTable() {
  // --
  {
    FixedHashTable table(3);
    table["1"] = "one";
    table["2"] = "two";
    
    table["3"] = "three false";
    table["3"] = "three";
    
    table["4"] = "four";
    table["4"] = "four";
    table["4"] = "four";
    
    assert(HashTableBucket::s_allocations_count == 4);
    
    std::string three_value = table["3"];
    assert(three_value == "three");
    
    table.remove("2");
  }
  
  // --
  assert(HashTableBucket::s_allocations_count == 0);
}

int main(int argc, const char * argv[]) {
  try {
    testHashTable();
  } catch (std::exception& exc) {
    std::cout << "Caught an exception: "<< exc.what() << std::endl;
  }
  
  return 0;
}
