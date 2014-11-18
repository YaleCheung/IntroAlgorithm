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
    BinarySearchTree(const T& val, const BinarySearchTree& l, const BinarySearchTree& r);
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
    void InOrderR_(Node<T>* node);
    void LastOrderR(Node<T>* node);
    void FirstOrderR(Node<T>* node);
    void InOrderI(Node<T>* node);
    void LastOrderI(Node<T>* node);
    void FirstOrderI(Node<T>* node);

    Node<T>* root_;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
    root_(NULL) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const T& val, const BinarySearchTree& l, const BinarySearchTree& r) {
    root_ = new Node<T>();
    root_ -> data_ = val; 
    root_ -> left = l->root;
    root_ -> right = r->root;
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
void BinarySearchTree<T>::InOrderR(Func func) {
    InOrderR(root_, Func func);
}
template<typename T>
void BinarySearchTree<T>::InOrderR_(Node<T>* node, Func func) {
    if(node == NULL)
        return;
    Node<T>* p = node;
    if(p->left_ != NULL) InOrderR_(p->left_);
    func(p);
    if(p->right_ != NULL) InOrderR_(p->right_);
}

template<typename T>
void BinarySearchTree<T>::
#endif //BINARY_SEARCH_TREE_H
