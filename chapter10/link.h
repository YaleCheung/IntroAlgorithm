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
template<typename T>
class Link {
public:
    Link();
    ~Link();

    Link(const Link&) = delete;
    Link& operator-(const Link&) = delete;
    
    Link& Insert(const T& val, const int& i);
    Link& Delete(T* value, const int& k);
    bool Find(const T& val);
    //int search(const T& val);
    int Length() const;
private:
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
Link<T>::Init_() {
    p_head_ = new Node;
    p_head_->p_next = NULL;
}

template<typename T>
Link<T>::Insert(const T& val, const int& k) {
    // insert a val after kth val;
    // the first pos is 0;
    assert(k <= length_ && k > 0);
    int i = 0;
    pNode p = p_head_;
    pNode pp = NULL;
    while(i < k) {
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
    length_ ++;
    return *this;
}

template<typename T>
bool Link<T>::Find(const T& val) {
     pNode p = p_head_;
     while(p) {
         if(p->data == val)
             return true;
         p = p->p_next;
     }
     if(p == NULL)
         return false;
}

template<typename T>
Link<T>& Link<T>::Delete(T* val, const int& k) {
    assert(k <= length_);
    pNode p = p_head_;
    pNode pp = p;
    // find the pp
    while(int i = 0; i < k; i ++) {
        p = p->p_next;
        i ++;
    }
    pp = p;
    // delete
    p = p->p_next;
    pp->p_next = p->p_next;
    length --;
    return *this;
}

template<typename T>
int Length() const {
    return length_;
}

#endif // LINK_H
