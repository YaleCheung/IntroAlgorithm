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

#include<assert.h>
//#define NULL 0

template<typename T>
class Stack {
public:
    Stack() : length_(0), p_head_(NULL) {Init_();};
    // forbid copy;
    Stack(const Stack<T>&) = delete;
    void operator=(const Stack<T>&) = delete;
    // push
    int Length() {
        return length_;
    }

    void Push(const T& data) {
        pNode p = new Node;
        p->pNext = NULL; 
        p->data = data;
        // add a node into *head 
        pNode p_next = (*p_head_) -> pNext;
        p -> pNext = p_next;
        *p_head_ = p;
        length_ ++;
    }
    T Pop() {
        assert(length_ > 0);
        T val = (*p_head_) -> data;
        *p_head_ = (*p_head_) -> pNext;
    }
    
    ~Stack() {
        if(NULL != (*p_head_)) {
            pNode tmp = *p_head_;
            while(tmp != NULL) {
                pNode next = tmp -> pNext;
                delete tmp;
            }
        }
        delete p_head_;
    }
private:
    // only be called by Stack();
    void Init_() {
        p_head_ = new pNode;
        *p_head_ = NULL;
    }
    // node definition;
    typedef struct Node {
        T data;
        Node* pNext;
    } Node, *pNode;
    int length_;
    pNode* p_head_; // with empty head thus the p_head_ is permanent
};
#endif
