/*
 * =====================================================================================
 *
 *       Filename:  rbtree.h
 *
 *       Description:  the implementation of red black tree
 *
 *       Version:  1.0
 *       Created:  12/01/14 13:41:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *       Author:  zhangyi
 *       Organization:  org.zhangyi.com
 *
 * =====================================================================================
 */

#ifndef RBTree_H 
#define RBTree_H 

#include <iostream>
#include "../lib/nocopyable.h"

#ifndef NULL
#define NULL 0
#endif

template<typename T>
class RBTree;

template<typename T>
class Node {
public:
    friend RBTree<T>; 
    Node();
    Node(const T& val, Node* left, Node* right, Node* parent);
    ~Node();
private:
    T data_;
    Node* left_;
    Node* right_;
    Node* parent_;
};

template<typename T>
Node<T>::Node() :
    left_(NULL), right_(NULL), parent_ { 
}

template<typename T>
Node<T>::Node(const T& val, Node* left, Node* right) :
    data_(val), left_(left), right_(right) {}
template<typename T>
Node<T>::~Node(){}


template<typename T>
class RBTree {
    
};
#endif
