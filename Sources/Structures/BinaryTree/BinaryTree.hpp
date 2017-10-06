//
//  BinaryTree.hpp
//  BinaryTree_Test
//
//  Created by Bro on 10/6/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <functional>

template <typename __DataType>
class BinaryTreeNode {
public:
  typedef std::function<void(const __DataType& item)> __ItemAccessCallback;
  
  BinaryTreeNode(const __DataType& itemInit) {
    m_item = itemInit;
  }
  ~BinaryTreeNode() {
    delete m_leftChildNode;
    delete m_rightChildNode;
  }
  void add(const __DataType& itemToAdd) {
    if (itemToAdd < m_item) {
      if (m_leftChildNode) {
        m_leftChildNode->add(itemToAdd);
      } else {
        BinaryTreeNode* child = new BinaryTreeNode(itemToAdd);
        child->m_parentNode = this;
        m_leftChildNode = child;
      }
    } else {
      if (m_rightChildNode) {
        m_rightChildNode->add(itemToAdd);
      } else {
        BinaryTreeNode* child = new BinaryTreeNode(itemToAdd);
        child->m_parentNode = this;
        m_rightChildNode = child;
      }
    }
  }
  
  void traverseInfix(const __ItemAccessCallback& callback) const {
    if (m_leftChildNode) {
      m_leftChildNode->traverseInfix(callback);
    }
    callback(m_item);
    if (m_rightChildNode) {
      m_rightChildNode->traverseInfix(callback);
    }
  }
  
private:
  __DataType m_item;
  BinaryTreeNode* m_parentNode     = nullptr;
  BinaryTreeNode* m_leftChildNode  = nullptr;
  BinaryTreeNode* m_rightChildNode = nullptr;
};

template <typename __DataType>
class BinaryTree {
public:
  typedef BinaryTreeNode<__DataType> __Node;
  typedef __Node* __NodePtr;
  typedef std::function<void(const __DataType& item)> __ItemAccessCallback;
  
  void add(const __DataType& item) {
    if (m_rootNode) {
      m_rootNode->add(item);
    } else {
      __NodePtr rootNode = new __Node(item);
      m_rootNode = rootNode;
    }
  }
  
  void traverseInfix(const __ItemAccessCallback& callback) {
    if (m_rootNode) {
      m_rootNode->traverseInfix(callback);
    }
  }
  
  ~BinaryTree() {
    delete m_rootNode;
  }
  
private:
  __NodePtr m_rootNode = nullptr;
};

#endif /* BinaryTree_hpp */
