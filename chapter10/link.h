/*
 * =====================================================================================
 *
 *       Filename:  link.h
 *
 *    Description:  simple one way link
 *
 *        Version:  1.0
 *        Created:  11/01/14 21:12:12
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LINK_H
#define LINK_H

#define INT_DEBUG_
#ifdef INT_DEBUG_
#include <stdio.h>
#endif

#include <assert.h>
//#define NULL 0
template<typename T>
class Link {
public:
    Link();
    ~Link();

    Link(const Link&) = delete;
    Link& operator-(const Link&) = delete;
    
    Link& Insert(const T& val, const int& i);
    Link& Delete(const int& k, T* value);
    bool Find(const T& val);
    int Search(const T& val) const; // if val exists, return the pos else return -1, which means not existed;
    int Length() const;
#ifdef INT_DEBUG_
    void Print() const;
#endif
private:
    void Init_();
    typedef struct Node {
        T data;
	Node* p_next;
    } Node, *pNode;
    pNode p_head_; // link with an empty node;
    int length_;
};

template<typename T>
Link<T>::Link() :
    length_(0) {
    Init_();
}

template<typename T>
void Link<T>::Init_() {
    p_head_ = new Node;
    p_head_->p_next = NULL;
}

template<typename T>
Link<T>& Link<T>::Insert(const T& val, const int& k) {
    // insert a val as kth val;
    // the first pos is 0;
    assert(k <= length_ && k >= 0);
    int i = 1;
    pNode p = p_head_;
    pNode pp = NULL;
    while(i <= k) {
        p = p->p_next;
        i += 1;
    }
    // the k-1 th ele is pp;
    pp = p; 
    p = p->p_next;
    // alloc a new node with value val;
    pNode p_insert = new Node;
    p_insert->data = val;
    p_insert->p_next = NULL;
    pp->p_next = p_insert;
    p_insert->p_next = p;
    length_ += 1;
    return *this;
}

template<typename T>
int Link<T>::Search(const T& val) const {
    assert(length_ > 1);
    int pos = 0;
    pNode p = p_head_->p_next;
    while(p) {
        pos ++;
        if(p->data == val)
            return pos;
        p = p->p_next;
    }
    return -1;
}

template<typename T>
bool Link<T>::Find(const T& val) {
    assert(length_ > 0);
    pNode p = p_head_->p_next;
    while(p) {
        if(p->data == val)
            return true;
        p = p->p_next;
    }
    if(p == NULL)
        return false;
}


template<typename T>
Link<T>& Link<T>::Delete(const int& k, T* val) {
    assert(k <= length_);
    pNode p = p_head_;
    pNode pp = p;
    // find the pp
    for(int i = 1; i < k; i ++) 
        p = p->p_next;
    pp = p;
    // delete
    p = p->p_next;
    *val = p->data;
    pp->p_next = p->p_next;
    length_ --;
    return *this;
}

template<typename T>
int Link<T>::Length() const {
    return length_;
}

template<typename T>
Link<T>::~Link() {
    pNode p = p_head_;
    while(p) {
        pNode p_tmp = p;
        p = p->p_next;
        delete p_tmp;
    }
}

#ifdef INT_DEBUG_
template<typename T>
void Link<T>::Print() const {
    pNode p = p_head_->p_next;
    while(p) {
        printf("%d\n", p->data);
        p = p->p_next;
    }
}
#endif
#endif // LINK_H
