/*
 * =====================================================================================
 *
 *       Filename:  rbtree.h
 *
 *       Description:  the implementation of RED BLACK tree, using double linked method
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

enum Color {BLACK = 0, RED = 1};

template<typename T>
class Node {
public:
    friend RBTree<T>; 
    Node();
    Node(const T& val, Node* left, Node* right, Node* parent, Color color = RED);
    // only  for nil node
    Node(Node* left, Node* right, Node* parent, Color color = BLACK);
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

// some thing is not right, for the link between child and parent is not constructed
template<typename T>
Node<T>::Node(const T& val, Node<T>* left, Node<T>* right, Node<T>* parent, Color color) :
    data_(val), left_(left), right_(right),  parent_(parent), color_(color){
}

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
    Node<T>* Left_(Node<T>* node);
    Node<T>* Right_(Node<T>* node);
    Node<T>* Parent_(Node<T>* node);
    Node<T>* Nil_();
    Node<T>* root_;
    Node<T>* nil_;
};

template<typename T>
RBTree<T>::RBTree() {
    nil_ = new Node<T>(NULL, NULL, NULL, BLACK);
    root_ = NULL;
}

template<typename T>
RBTree<T>& RBTree<T>::Insert(const T& val) {
    Node<T>* p_cur = root_;
    Node<T>* node_insert = new Node<T>(val, nil_, nil_, NULL, RED);
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
    if(NULL == p_pre)  {// root node
        root_ = node_insert;
        root_->color_ = BLACK; // the color of root must be BLACK
        return *this;
    } else {
        if(val > p_pre->data_) p_pre->right_ = node_insert;
        else p_pre->left_ = node_insert;
        node_insert->parent_ = p_pre;
    }
    Fix_(node_insert);
    return *this;
}

template<typename T>
Node<T>* RBTree<T>::Left_(Node<T>* node) {
    if (node != nil_ && node != NULL && node->left_ != nil_ && node->left_ != NULL) 
        return node->left_;
    return NULL;
}

template<typename T>
Node<T>* RBTree<T>::Right_(Node<T>* node) {
    if (node != nil_ && node != NULL && node->right_ != nil_ && node->right_ != NULL) 
        return node->right_;
    return NULL;
}

template<typename T>
Node<T>* RBTree<T>::Parent_(Node<T>* node) {
}

template<typename T>
void RBTree<T>::Fix_(Node<T>* insert_node) {
    // insert_node is not the root_, because the return is before Fix_(node);
    // case 1: the node is the root;
    if(BLACK == insert_node->parent_->color_) // case 2: His parent is Black, then do nothing; because a red node cannot change the bh(tree);
        return;
    else if(RED == insert_node->parent_->color_) { 
        // case 3: the father is RED, but his uncle is Black, which means the father has had a child already. and the parent must possess a Black parent_ gp;
        if(BLACK == insert_node->parent_->parent_->color_) {
             
        }

    }
}

template<typename T>
RBTree<T>& RBTree<T>::Delete(const T& val) {

}
#endif
