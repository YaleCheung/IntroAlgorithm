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

#include <iostream>
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
    typedef void (BinarySearchTree::*Func)(Node<T>* node);
    BinarySearchTree();
    BinarySearchTree(const T& val, const BinarySearchTree& l, const BinarySearchTree& r);
    BinarySearchTree& Insert(const T& val);
    BinarySearchTree& Delete(const T& val);

    bool Find(const T& val);
    void SetFunc(Func func);
    void InOrderR();
    void PreOrderR();
    void PostOrderR();
    //void InOrderI(Func func);
    //void PreOrderI(Func func);
    //void PostOrderI(Func func);
private:
    void Print_(Node<T>* node) {
        std::cout << node -> data_ << std::endl;
    }
    void InOrderR_(Node<T>* node);
    void PreOrderR_(Node<T>* node);
    void PostOrderR_(Node<T>* node);
    //void InOrderI_(Node<T>* node);
    //void PreOrderI_(Node<T>* node);
    //void PostOrderI_(Node<T>* node, Func func);

    Node<T>* root_;
    typename BinarySearchTree::Func func_;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
    root_(NULL) {
    func_ = Print_;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const T& val, const BinarySearchTree& l, const BinarySearchTree& r) {
    root_ = new Node<T>();
    root_ -> data_ = val; 
    root_ -> left = l->root;
    root_ -> right = r->root;
    func_ = Print_;
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::Insert(const T& val) {
    Node<T> node_insert = new Node<T>(val, NULL, NULL);
    // find a pos to insert the node_insert
    Node<T> p = root_;
    while(p != NULL) {
        if(val > p->data_) p = p->right_;
        if(val < p->data_) p = p->left_;
    }
    // p is a NULL pointer;
    p = node_insert;
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::Delete(const T& val) {
    // need to consider multiple condition
    // if the deletion node has right node, then the min right side is under consideration
    // else if the deletion node has left node, then the max left side is under consideration
    // find the node to be deleted and its parents
    Node<T>* p = root_;
    while(p != NULL && p->data_ != val) {
        if(p->data_ < val) 
            p = p->left_;
        else if(p->data > val) 
            p = p->right_;
    } 
    if(p != NULL) { // find
        Node<T>* node_cur = p;
        if(p->right_ != NULL) {
            p = p->right;
            while(p -> left_ != NULL)
                p = p->left_;
            // p is the node to replace the delete node;
            // exchange the val only, do not delete the node node_delete
            node_cur->data_ = val;
            delete p;
        } else {
            // has left side only
            p = p->left_;
            node_cur-> data_ = p->data_;
            // delete p not hte node_delete;
            node_cur->left_ = p->left_;
            node_cur->right = p->right_;
            delete p;
        }
    } 
    return *this;
}

template<typename T>
bool BinarySearchTree<T>::Find(const T& val) {
    Node<T>* p = root_;
    while(p != NULL && p->data_ != val) {
        if(p->data_ < val) p = p->left_;
        else if(p->data_ > val) p = p->right_;
    }
    return (p != NULL) ? true : false;
}

template<typename T>
void BinarySearchTree<T>::InOrderR() {
    InOrderR(root_);
}
template<typename T>
void BinarySearchTree<T>::InOrderR_(Node<T>* node) {
    if(node == NULL)
        return;
    Node<T>* p = node;
    if(p->left_ != NULL) InOrderR_(p->left_);
    func_(p);
    if(p->right_ != NULL) InOrderR_(p->right_);
}

template<typename T>
void BinarySearchTree<T>::PreOrderR() {
    PreOrderR_(root_);
}

template<typename T>
void BinarySearchTree<T>::PreOrderR_(Node<T>* node) {
    if(node == NULL) 
        return;
    func_(node);
    if(node->left_) PreOrderR_(node->left_);
    if(node->right_) PreOrderR_(node->right_);
}

template<typename T>
void BinarySearchTree<T>::PostOrderR() {
    PostOrderR_(root_);
}

template<typename T>
void BinarySearchTree<T>::PostOrderR_(Node<T>* node) {
    if(node == NULL)
        return;
    if(node->left_) PostOrderR_(node->left_);
    if(node->rigth_) PostOrderR_(node->right_);
    func_(node);
}

template<typename T>
void 
#endif //BINARY_SEARCH_TREE_H
