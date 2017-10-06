//
//  HashTable.cpp
//  HashTable
//
//  Created by Bro on 9/29/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include "HashTableBucket.hpp"

#include "HashTable.hpp"

FixedHashTable::FixedHashTable(size_t size) {
  m_table_size = size;
  m_data = (HashTableBucket**)calloc(size, sizeof(*m_data));
}

FixedHashTable::GetSetHelper
FixedHashTable::operator[](const std::string& key) {
  GetSetHelper helper;
  helper.key = key;
  helper.table = this;
  return helper;
}

std::string FixedHashTable::get(const std::string& key) const {
  std::string result;
  
  // Calculate hash for the needed key
  size_t hash = std::hash<std::string>()(key);
  
  // --
  size_t table_index = hash % m_table_size;
  
  // --
  HashTableBucket* bucket = m_data[table_index];
  while(bucket) {
    if (bucket->key == key) {
      result = bucket->value;
      break;
    } else {
      bucket = bucket->next;
    }
  }
  return result;
}

void FixedHashTable::set(const std::string& key, const std::string& value) {
  // --
  HashTableBucket* new_bucket = new HashTableBucket();
  new_bucket->key   = key;
  new_bucket->value = value;
  
  // --
  remove(key);
  
  // --
  size_t hash = std::hash<std::string>()(key);
  size_t table_index = hash % m_table_size;
  
  // --
  new_bucket->next = m_data[table_index];
  m_data[table_index] = new_bucket;
  
  ++m_objects_count;
}

FixedHashTable::~FixedHashTable() {
  for (size_t i = 0; i < m_table_size; ++i) {
    HashTableBucket* bucket = m_data[i];
    if (bucket) {
      HashTableBucket* next_bucket = bucket->next;
      while(next_bucket) {
        HashTableBucket* next_to_delete = next_bucket;
        next_bucket = next_bucket->next;
        delete next_to_delete;
      }
      delete bucket;
    }
  }
  delete[] m_data;
}

void FixedHashTable::remove(const std::string& key) {
  // Calculate hash for the key
  size_t hash = std::hash<std::string>()(key);
  
  // --
  size_t table_index = hash % m_table_size;
  
  // --
  HashTableBucket* bucket = m_data[table_index];
  HashTableBucket* previous_bucket = nullptr; // will be used for joining it to the next, if needed
  
  while (bucket) {
    if (bucket->key == key) {
      HashTableBucket* next_bucket = bucket->next;
      
      delete bucket; // actual deletion
      bucket = nullptr; // to break the while loop
      
      // Reconstruct the table, keep it integral
      if (previous_bucket) {
        // Join the next and previous by pointers to each other, if needed
        previous_bucket->next = next_bucket;
        
        // make the previous as the first for the key
        m_data[table_index] = previous_bucket;
      } else if (next_bucket) {
        // make the next as the first
        m_data[table_index] = next_bucket;
      } else {
        // .. if not, the place for the key will be empty
        m_data[table_index] = nullptr;
      }
      // --
      
      // Only decrement if the deletion has been taken place
      --m_objects_count;
      
      // no need to go further if the one has been deleted
      break;
    }
    
    // save it for future use
    previous_bucket = bucket;
    
    // move along
    if (bucket) {
      bucket = bucket->next;
    }
  }
}

FixedHashTable::GetSetHelper::operator std::string() {
  if (table) {
    return table->get(this->key);
  } else {
    return "";
  }
}

void FixedHashTable::GetSetHelper::operator=(const std::string& value) {
  if (table) {
    table->set(this->key, value);
  }
}
