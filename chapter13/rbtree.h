/*
 * =====================================================================================
 *
 *       Filename:  rbtree.h
 *
 *       Description:  the implementation of red black tree, using double linked method
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

enum Color {black = 0, red = 1};

template<typename T>
class Node {
public:
    friend RBTree<T>; 
    Node();
    Node(const T& val, Node* left, Node* right, Node* parent, Color color = red);
    // only  for nil node
    Node(Node* left, Node* right, Node* parent, Color color = black);
    ~Node();
private:
    T data_;
    Node* left_;
    Node* right_;
    Node* parent_;
    Color color_;
};

template<typename T>
Node<T>::Node() :
    left_(NULL), right_(NULL), parent_(NULL) { 
}

template<typename T>
Node<T>::Node(const T& val, Node<T>* left, Node<T>* right, Node<T>* parent, Color color) :
    data_(val), left_(left), right_(right),  parent_(parent), color_(color){}

template<typename T>
Node<T>::Node(Node<T>* left, Node<T>* right, Node<T>* parent, Color color) :
    left_(left), right_(right), parent_(parent), color_(color) {}

template<typename T>
Node<T>::~Node(){}

// the node has parent_ attribute, so I don't want to inherit the binarysearchtree
// only implement the insert and delete method, for RBTree is a binarysearchtree essentially
template<typename T>
class RBTree : NoCopyable<T> {
public:
    RBTree();
    RBTree& Insert(const T& val);
    RBTree& Delete(const T& val);
private:
    void Fix_(Node<T>*);
    Node<T>* root_;
    Node<T>* nil_;
};

template<typename T>
RBTree<T>::RBTree() {
    nil_ = new Node<T>(NULL, NULL, NULL, black);
    root_ = NULL;
}

template<typename T>
RBTree<T>& RBTree<T>::Insert(const T& val) {
    Node<T>* p_cur = root_;
    Node<T>* node_insert = new Node<T>(val, nil_, nil_, NULL, red);
    Node<T>* p_pre = NULL;
    while(p_cur) {
        if(val > p_cur->data_) {
            p_pre = p_cur;
            p_cur = p_cur->right_;
        } else {
            p_pre = p_cur; 
            p_cur = p_cur->left_;
        }
    }
    if (p_pre == NULL)  {// root node
        root_ = node_insert;
        root_->color_ = black; // the color of root must be black
    } else {
        if(val > p_pre->data_) p_pre->right_ = node_insert;
        else p_pre->left_ = node_insert;
        node_insert->parent_ = p_pre;
    }
    Fix_(node_insert);
}

template<typename T>
RBTree<T>& RBTree<T>::Delete(const T& val) {
}
#endif
