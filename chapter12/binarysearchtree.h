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
template<typename T>
class BinarySearchTree : NoCopyable<T> {
public:
    BinarySearchTree();
    BinarySearchTree& Insert(const T& val);
    BinarySearchTree& Delete(const T& val);
    bool Find(const T& val);
private:
    void Init_();
    
    typedef struct Node {
        T data;
        Node* p_left;
        Node* p_right;
    } Node, *pNode;
    pNode p_root_;
};
