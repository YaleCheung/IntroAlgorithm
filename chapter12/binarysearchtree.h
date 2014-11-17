/*
 * =====================================================================================
 *
 *       Filename:  binary_tree.h
 *
 *    Description:  The implementation of Binary Search Tree 
 *
 *        Version:  1.0
 *        Created:  11/15/14 23:04:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangyi
 *   Organization:  com.zhangyi.org
 *
 * =====================================================================================
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../lib/nocopyable.h"

#ifndef NULL
#define NULL 0
#endif

template<typename T>
class BinarySearchTree;

template<typename T>
class Node {
public:
    friend BinarySearchTree<T>; 
    Node();
    Node(const T& val, Node* left, Node* right);
    ~Node();
private:
    T data_;
    Node* left_;
    Node* right_;
};

template<typename T>
Node<T>::Node() :
    left_(NULL), right_(NULL) { 
}

template<typename T>
Node<T>::Node(const T& val, Node* left, Node* right) :
    data_(val), left_(left), right_(right) {}

template<typename T>
class BinarySearchTree : NoCopyable<T> {
public:
    typedef void (*Func)(Node<T>*);
    BinarySearchTree();
    BinarySearchTree(const T val, const BinarySearchTree& l, const BinarySearchTree& r);
    BinarySearchTree& Insert(const T& val);
    BinarySearchTree& Delete(const T& val);

    bool Find(const T& val);
    void InOrderR(Func func);
    void LastOrderR(Func func);
    void FirstOrderR(Func func);
    void InOrderI(Func func);
    void LastOrderI(Func func);
    void FirstOrderI(Func func);
private:
    void Init_();
    Node<T>* root_;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
    root_(NULL) {
   Init_();
};

template<typename T>
void BinarySearchTree<T>::
#endif //BINARY_SEARCH_TREE_H
