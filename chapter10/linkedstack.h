/*
 * =====================================================================================
 *
 *       Filename:  linkedstack.h
 *
 *    Description:  Linked stack
 *
 *        Version:  1.0
 *        Created:  10/28/14 13:32:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef STACKLINK_H
#define STACKLINK_H

template<typename T>
class Stack {
public:
    Stack() : length_(0), p_node_(NULL) {Init_()};
    // forbid copy;
    Stack(const Stack<T>&) = delete;
    void operator=(const Stack<T>&) = delete;
    // push
    void Push(const T& data) {
        pNode p = new Node;
        

    }
private:
    // only be called by Stack();
    void Init_() {
        p_node_ = new Node<T>;
	pNext = NULL;
    }
    // node definition;
    template<typename T>
    typedef struct Node {
        T data;
        T* pNext;
    } Node, *pNode;
    int length_;
    pNode<T> p_node_;
};
#endif


