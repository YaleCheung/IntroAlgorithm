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
    Node<T>* Nil_();
    Node<T>* Parent_(Node<T>* node);
    Node<T>* Uncle_(Node<T>* node);
    Node<T>* GrandParent_(Node<T>* node);
    Node<T>* root_;
    Node<T>* nil_;
};

template<typename T>
RBTree<T>::RBTree() {
    nil_ = new Node<T>(NULL, NULL, NULL, BLACK);
    root_ = NULL;
}

template<typename T>
Node<T>* RBTree<T>::Left_(Node<T>* node) {
    if (node != nil_)
        return node->left_;
    else
        return NULL;
}

template<typename T>
Node<T>* RBTree<T>::Right_(Node<T>* node) {
    if(node != nil_)
        return node->right_;
    else
        return NULL;
}

template<typename T>
Node<T>* RBTree<T>::Parent_(Node<T>* node) {
    if(node != nil_)
        return node->parent_;
    else
        return NULL;
}

template<typename T>
Node<T>* RBTree<T>::GrandParent_(Node<T>* node) {
    Node<T>* parent = Parent_(node);
    if (parent != NULL) {
        return Parent_(node);
    }
    return NULL;
}

template<typename T>
Node<T>* RBTree<T>::Uncle_(Node<T>* node) {
    if(node != nil_) {
        Node<T>* parent = Parent(node);
        if ((parent != nil_) && (node == Left_(node)))
            return Right_(node);
        else if (parent && (node == Right_(node)))
            return Left_(node);
    }
    // node == nil_ or parent == NULL;
    return NULL;
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
void RBTree<T>::Fix_(Node<T>* insert_node) {
    Node<T>* parent = Parent_(insert_node);
    if (NULL == parent) {
        insert_node->color_ = BLACK;
        return;
    }
    if (parent->color_ == BLACK)  // case1 & 2 : the parent is black. which means the current RBTree is right; 
        return;
    while(((parent = Parent(insert_node)) != NULL) && (RED == parent->color_)) { // if the father is RED, there must be a BLACK grand_father;
        Node<T>* grand_father = GrandFather_(insert_node);
        assert(BLACK == grand_father->color_);
        Node<T>* uncle = Uncle_(insert_node);
        if((uncle != NULL) && (RED == uncle->color_)) {
            parent->color_ = BLACK;
            uncle->color_ = BLACK;
            grand_father->color_ = RED;
            insert_node = grand_father;
        } else if ((NULL != uncle) && (BLACK == uncle->color_)) {
            if(insert_node == Left_(parent))
                 RightRotate(grand_father);
            
        }
    }
}

template<typename T>
RBTree<T>& RBTree<T>::Delete(const T& val) {
    
}
#endif
