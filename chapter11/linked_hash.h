/*
 * =====================================================================================
 *
 *       Filename:  linked_hash.h
 *
 *    Description:  implementation of hash. Collion solved by link 
 *
 *        Version:  1.0
 *        Created:  11/06/14 13:03:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef LINKED_HASH_H
#define LINKED_HASH_H

#ifndef NULL
#define NULL 0
#endif
#include "../chapter10/link.h"
#include "hash.h"
#include "../lib/nocopyable.h"


template<typename T>
class LinkHash : public Hash<T>, public NoCopyable<T> {
public:
    // 
    LinkHash(const int& size = 100);
    LinkHash& Insert(const T&);
    LinkHash& Delete(T* val);
    int Hash_Func(const T&) const;
    bool Find(const T& val) const;
    int Size() {return size_;}
    
private:
    int size_;
    void Init_();
    Link<T>* array_; //  an array to store the head of link;
};

template<typename T>
LinkHash<T>::LinkHash(const int& size) :
    size_(size), array_(NULL) {
    Init_();
}

template<typename T>
void LinkHash<T>::Init_() {
    array_ = new Link<T>[size_];
}

template<typename T>
LinkHash<T>& LinkHash<T>::Insert(const T& val) {
    int pos = Hash_Func(val);
    assert(pos < size_);
    array_[pos].Insert(val, 1);
}

template<typename T>
LinkHash<T>& LinkHash<T>::Delete(T* val) {
    int pos = Hash_Func(val);
    assert(pos < size_);
    int size = array_[pos].Length();
    if(size > 0) {
        int val_pos = array_[pos].Search(val);
        assert(val_pos > 0);
        array_[pos].Delete(val_pos, val);
    }
    return *this;
}

template<typename T>
bool LinkHash<T>::Find(const T& val) const {
    int pos = Hash_Func(val);
    assert(pos < size_);
    return array_[pos].Find(val);
}

#endif // linked hash
