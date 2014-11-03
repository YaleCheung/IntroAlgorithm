/*
 * =====================================================================================
 *
 *       Filename:  dlink.h
 *
 *    Description:  double link
 *
 *        Version:  1.0
 *        Created:  11/03/14 13:15:24
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef DLINK_H
#define DLINK_H

template<typename T>
class DLink {
public:
    DLink();
    // can not copy
    DLink(const DLink&) == delete;
    DLink& operate=(const DLink&) = delete;
    DLink& Insert(const T& data, const int& k); // insert as kth node;
    DLink& Delete(const int& k, T* output); // delete kth node, with output node 
    // bool Find(const T& data) const; // the same as single link
private:
    void Init_();
    typedef Node {
        T data;
	Node* p_next;
	Node* p_pre;
    } Node, pNode;
    pNode p_head_; // with an empty node;
    int length_;
};

template<typename T>
DLink<T>::DLink() :
    length_(0), p_head_(NULL) {
    Init_();
}

template<typename T>
void DLink<T>::Init_() {
    if(p_head_ != NULL)
        delete p_head_;
    p_head_ = new Node;
    p_head_->p_pre = p_head_->p_next = NULL;
}

template<typename T>
DLink<T>& DLink<T>::Insert(const T& val, const int& k) {
    assert((p_head_ != NULL) && ((k - 1) <= length_));
    pNode p = p_head_;
    // find the (k)th node
    int i = 1;
    // find the father;
    while(i < k) {
        p = p->p_next;
	i ++;
    }
    pNode pp = p->p_next;
    p = p->p_next;
    // create new node;
    pNode p_insert = new Node;
    // init the new node
    p_insert->p_data = val;
    p_insert->p_next = NULL;
    p_insert->p_pre = NULL;
    // inste the new node; 
    p_insert->p_pre = pp;
    p_insert->p_next = p;
    pp->p_next = p_insert;
    p_pre = p_insert;
    length_ ++;
    return *this;
}

template<typename T>
DLink<T>& DLink<T>::Delete(const int& k, T* val) {
    assert((p_head != NULL) && (k <= length_));
    pNode p = p_head_;
    int i = 1;
    while(1) {
        p = p->p_next;
	i += 1;
    }
    pNode pp = p->p_next;
    p = p->p_next;
    // p is the Node to be deleted
    pNode p_next = p->p_next;
    pp->p_next = p_next;
    p_next->p_pre = pp;
    delete p;
    return *this;
}
#endif // DLink
