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
#include <queue>
#include <stack>

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
Node<T>::~Node(){}


template<typename T>
class BinarySearchTree : NoCopyable<T> {
public:
    typedef void (BinarySearchTree::*Func)(Node<T>* node);
    BinarySearchTree();
    BinarySearchTree(const T& val, const BinarySearchTree& l, const BinarySearchTree& r);
    BinarySearchTree& Insert(const T& val);
    ~BinarySearchTree();
    //BinarySearchTree& Delete(const T& val);

    bool Find(const T& val);
    void InOrderR();
    void PreOrderR();
    void PostOrderR();
    void LevelOrder();
    void InOrderI();
    void PreOrderI();
    void PostOrderI();
private:
    void Print_(Node<T>* node) {
        std::cout << node->data_ << std::endl;
    }

    void Free_(Node<T>* node) {
        if(node != NULL) {
            delete  node;
            node = NULL;
        }
    }
    void InOrderR_(Node<T>* node);
    void PreOrderR_(Node<T>* node);
    void PostOrderR_(Node<T>* node);

    void LevelOrder_(Node<T>* node);
    void InOrderI_(Node<T>* node);
    void PreOrderI_(Node<T>* node);
    void PostOrderI_(Node<T>* node);
    Func func_;
    Node<T>* root_;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
    root_(NULL) {
    func_ = &BinarySearchTree<T>::Print_;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const T& val, const BinarySearchTree& l, const BinarySearchTree& r) {
    root_ = new Node<T>();
    root_ -> data_ = val; 
    root_ -> left = l->root;
    root_ -> right = r->root;
    func_ = &BinarySearchTree<T>::Print_;
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::Insert(const T& val) {
    Node<T>* node_insert = new Node<T>(val, NULL, NULL);
    if(NULL == root_) {
        root_ = node_insert;
        return *this;
    }
    // find a pos to insert the node_insert
    Node<T>* p = root_;
    Node<T>* pp;
    while(p != NULL) {
        if(val > p->data_) {
            pp = p;
            p = p->right_;
        } else if(val < p->data_)  {
                pp = p;
                p = p->left_;
        }
    }
    // p is a NULL pointer;
    p = node_insert;
    if (val > pp->data_) 
        pp-> right_ = p;
    else if (val < pp->data_)
        pp-> left_ = p;
    return *this;
}

/*template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::Delete(const T& val) {
    // need to consider multiple condition
    // if the deletion node has right node, then the min right side is under consideration
    // else if the deletion node has left node, then the max left side is under consideration
    // find the node to be deleted and its parents
    Node<T>* p = root_;
    Node<T>* pp = NULL;
    while(p != NULL && p->data_ != val) {
        if(p->data_ > val) {
            pp = p;
            p = p->left_;
        }
        else if(p->data_ < val) {
            pp = p;
            p = p->right_;
        }
    } 
    // if  pp == NULL, then pp is the root
    if(p != NULL) { // find
        if(pp == NULL) // delete the root node;
            
        Node<T>* node_cur = p;
        if(p->right_ != NULL) {
            p = p->right_;
            while(p->left_ != NULL) {
                pp = p;
                p = p->left_;
            }
            // p is the node to replace the delete node;
            // exchange the val only, do not delete the node node_delete
            node_cur->data_ = p->data_;
            pp->left_ = NULL;
            delete p;
            // need to judge whether the node is the left nor the right  successor llof pp
        } else {
            // has left side only
            // delete p not hte node_delete;
            if(pp -> left_ == p)
                pp -> left_ = p->left_;
            else
                pp->right_ = p->left_;
            delete p;
            p = NULL;
        }
    } 
    return *this;
}
*/

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
    InOrderR_(root_);
}

template<typename T>
void BinarySearchTree<T>::InOrderR_(Node<T>* node) {
    if(node == NULL)
        return;
    Node<T>* p = node;
    if(p->left_ != NULL) InOrderR_(p->left_);
    (this->*func_)(p);
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
    (this->*func_)(node);
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
    if(node->right_) PostOrderR_(node->right_);
    (this->*func_)(node);
}

template<typename T>
void BinarySearchTree<T>::LevelOrder() {
    LevelOrder_(root_);
}

template<typename T>
void BinarySearchTree<T>::LevelOrder_(Node<T>* node) {
    std::queue<Node<T>*> q;
    q.push(node);
    while(q.size()) {
        Node<T>* p = q.front();
        (this->*func_)(p);
        if (p->left_) 
            q.push(p->left_);
        if (p->right_) 
            q.push(p->right_);
        q.pop();
    }
}

template<typename T>
void BinarySearchTree<T>::InOrderI() {
    InOrderI_(root_);
}

template<typename T>
void BinarySearchTree<T>::InOrderI_(Node<T>* node) {
    std::stack<Node<T>*> stack;
    while(node || stack.size()) {
        while(node) {
            stack.push(node);
            node = node->left_;
        }
        if(! stack.empty()) {
            node = stack.top();
            (this->*func_)(node);
            stack.pop();
            node = node->right_;
        }
    }
}

template<typename T>
void BinarySearchTree<T>::PreOrderI() {
    BinarySearchTree<T>::PreOrderI_(root_);
}

template<typename T>
void BinarySearchTree<T>::PreOrderI_(Node<T>* node) {
   std::stack<Node<T>*> stack;    
    while(node || stack.size()) {
        while(node) {
            this->*func_(node);
            stack.push(node);
            node = node->left_;
        }
        if(! stack.empty()) {
            node = stack.top();
            node = node->right_;
            stack.pop();
        }
    }
}

template<typename T>
void BinarySearchTree<T>::PostOrderI() {
    PostOrderI_(root_);
}

template<typename T>
void BinarySearchTree<T>::PostOrderI_(Node<T>* node) {
    std::stack<Node<T>*> stack;
    while(node || stack.size()) {
        while(node) {
            stack.push(node);
            node = node->left_;
        }
        if(! stack.empty()) {
            
        }
    }
}
template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
   func_ = &BinarySearchTree<T>::Free_; 
   PostOrderR_(root_);
}

#endif //BINARY_SEARCH_TREE_H
