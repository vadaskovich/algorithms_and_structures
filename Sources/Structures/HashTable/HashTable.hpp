//
//  HashTable.hpp
//  HashTable
//
//  Created by Bro on 9/29/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <string>
#include <cstdlib>

// Used as a data type for hash table.
class HashTableBucket;

class FixedHashTable {
public:
  FixedHashTable(size_t size);
  ~FixedHashTable();
  
  /* Need to use setter and getter syntax
   
      To set:
        table["key"] = "value";
   
      To Get:
        std::string var = table["key];
  */
  class GetSetHelper {
  public:
    std::string key;
    FixedHashTable* table = nullptr;
    void operator=(const std::string& value);
    operator std::string();
  };
  
  GetSetHelper operator[](const std::string& key);
  // --
  
  // removal
  void remove(const std::string& key);
  
  size_t count() { return m_objects_count; }
  
  // getter
  std::string get(const std::string& key) const;
  
  // setter
  void set(const std::string& key, const std::string& value);
  
private:
  size_t m_objects_count = 0;
  size_t m_table_size    = 0;
  
  HashTableBucket** m_data;
};

#endif /* HashTable_hpp */
