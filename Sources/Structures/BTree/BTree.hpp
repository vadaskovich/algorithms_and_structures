//
//  BTree.hpp
//  BTree
//
//  Created by Bro on 10/6/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef BTree_hpp
#define BTree_hpp

#include <assert.h>
#include <vector>
#include <algorithm>
#include <functional>

#ifdef DEBUG
extern long s_BTreeNodeAllocationsCount;
#endif

template<typename __KeyType> class BTree;

template<typename __KeyType>
class BTreeNode {
public:
  friend class BTree<__KeyType>;
  
  typedef BTreeNode<__KeyType> __Node;
  typedef BTreeNode<__KeyType>* __NodePtr;
  
  typedef std::vector<__NodePtr> __NodelList;
  typedef std::vector<__KeyType> __KeyList;
  
  typedef std::function<void(const __KeyType& item)> __ItemAccessCallback;
  
  // Adds the key to the tree and return splitted node, if any
  __NodePtr add(const __KeyType& keyToAdd, int32_t order) {
    // First, if there are no children nodes, it is a leaf node then,
    // so simply add the key to the list
    if (m_childNodeList.empty()) {
      __addKeyToTheList(keyToAdd);
    }
    // If it is not a leaf node, add the key to a child node recursively
    else {
      __addKeyToChildNode(keyToAdd, order);
    }
    
    // Split if the key list contains more than it is allowed to
    if (m_keyList.size() >= order) {
      return __split();
    }
    return nullptr;
  }
  
  // Traverse to get keys in a sorted order
  void traverseInfix(const __ItemAccessCallback& callback) const {
    for (size_t i = 0; i < m_keyList.size(); ++i) {
      const __KeyType& key = m_keyList[i];
      
      if (!m_childNodeList.empty()) {
        const __NodePtr node = m_childNodeList[i];
        node->traverseInfix(callback);
      }
      callback(key);
      
      bool lastElement = (i == (m_keyList.size() - 1));
      if (lastElement && !m_childNodeList.empty()) {
        const __NodePtr lastChildNode = m_childNodeList.back();
        lastChildNode->traverseInfix(callback);
      }
    }
  }

private:
  int compare(const __KeyType& k1, const __KeyType& k2) {
    if (k1 == k2) {
      return 0;
    } else if (k1 < k2) {
      return -1;
    } else {
      return 1;
    }
  }
  // the method of binary division is used to find the place in logN
  int __findPositionForKeyToPut(const __KeyType& keyToFind) {
    int low = 0;
    int high = m_keyList.size();
    
    while (high != low) {
      int middle = (high + low) / 2;

      int compareResult = (middle < 0 || middle >= m_keyList.size())
      ? -1
      : compare(keyToFind, m_keyList[middle]);
      
      if (compareResult < 0) {
        high = middle;      // look in first half
      } else if (compareResult > 0) {
        low = middle + 1;    // look in second half
      } else {
        return middle; // found it
      }
    }
    return low;
  }
  
  void __addKeyToTheList(const __KeyType& keyToAdd) {
    // find proper position for the key to keep the list in order
    int foundResult = __findPositionForKeyToPut(keyToAdd);
    
    if (foundResult >= 0) {
      size_t indexToAdd = foundResult;
      m_keyList.insert(m_keyList.begin() + indexToAdd, keyToAdd);
    } else {
      m_keyList.push_back(keyToAdd);
    }
  }
  
  void __addKeyToChildNode(const __KeyType& keyToAdd, int order) {
    // Find the child node to add the key to
    __NodePtr childNodeToAdd = nullptr;
    size_t indexOfChildNodeToAdd = std::max((int)m_keyList.size(), 0);
    for (size_t i = 0; i < m_keyList.size(); ++i) {
      const __KeyType& key = m_keyList[i];
      if (keyToAdd < key) {
        indexOfChildNodeToAdd = i;
        break;
      }
    }
    assert(indexOfChildNodeToAdd < m_childNodeList.size());
    
    childNodeToAdd = m_childNodeList[indexOfChildNodeToAdd];
    assert(childNodeToAdd != this);
    
    if (childNodeToAdd) {
      __NodePtr nodeSplitted = childNodeToAdd->add(keyToAdd, order);
      
      if (nodeSplitted) {
        // A split of child node took place, so we need to
        // add a reference to that node and put the first key on the current level
        __KeyType firstKeyOfSplitted = nodeSplitted->m_keyList[0];
        nodeSplitted->m_keyList.erase(nodeSplitted->m_keyList.begin());
        
        m_keyList.insert(m_keyList.begin() + indexOfChildNodeToAdd, firstKeyOfSplitted);
        m_childNodeList.insert(m_childNodeList.begin() + indexOfChildNodeToAdd + 1, nodeSplitted);
      }
    }
  }
  
  __NodePtr __split() {
    // it will contain the second half of the node
    __NodePtr splittedNode = new __Node();
    
    // Get the second half keys and turn it to a splitted node
    size_t middleIndex = m_keyList.size() / 2;
    __KeyList keyListSplitted(m_keyList.begin() + middleIndex, m_keyList.end());
    splittedNode->m_keyList = keyListSplitted;
    m_keyList.erase(m_keyList.begin() + middleIndex, m_keyList.end());
    
    // Get proper child nodes to the splitted node, too, if there is
    if (!m_childNodeList.empty()) {
      __NodelList nodeListSplitted(m_childNodeList.begin() + middleIndex + 1, m_childNodeList.end());
      splittedNode->m_childNodeList = nodeListSplitted;
      m_childNodeList.erase(m_childNodeList.begin() + middleIndex + 1, m_childNodeList.end());
    }
    
    return splittedNode;
  }
  BTreeNode() {
#ifdef DEBUG
    ++s_BTreeNodeAllocationsCount;
#endif
  }
  ~BTreeNode() {
    if (!m_childNodeList.empty()) {
      for (__NodePtr node : m_childNodeList) {
        delete node;
      }
    }
#ifdef DEBUG
    --s_BTreeNodeAllocationsCount;
#endif
  }
  __NodelList m_childNodeList;
  __KeyList m_keyList;
};

template<typename __KeyType>
class BTree {
public:
  typedef BTreeNode<__KeyType> __Node;
  typedef BTreeNode<__KeyType>* __NodePtr;
  typedef std::function<void(const __KeyType& item)> __ItemAccessCallback;
  
  // Order is a maximum amount of child nodes
  explicit BTree(int32_t order)
  : m_order(std::max(order, 3))
  {
    m_rootNode = new __Node();
  }
  
  void add(const __KeyType& value) {
    // Do the addition
    __NodePtr nodeSplitted = m_rootNode->add(value, m_order);
    
    // If a node has been splitted on a lower level,
    // we need to set a new root node up
    // It will contain one key and two references to child nodes
    if (nodeSplitted) {
      __NodePtr newRoot = new __Node();
      
      __KeyType firstKeyOfSplitted = nodeSplitted->m_keyList[0];
      nodeSplitted->m_keyList.erase(nodeSplitted->m_keyList.begin());
      
      newRoot->m_keyList.push_back(firstKeyOfSplitted);
      newRoot->m_childNodeList.push_back(m_rootNode);
      newRoot->m_childNodeList.push_back(nodeSplitted);
      
      m_rootNode = newRoot;
      
      ++m_height;
    }
  }
  
  void traverseInfix(const __ItemAccessCallback& callback) {
    if (m_rootNode) {
      m_rootNode->traverseInfix(callback);
    }
  }

  ~BTree() {
    delete m_rootNode;
  }
private:
  __NodePtr m_rootNode = nullptr;
  
  // max amount of node children
  const int32_t m_order;
  int m_height = 1;
};

#endif /* BTree_hpp */
