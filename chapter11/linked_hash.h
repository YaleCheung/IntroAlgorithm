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
    LinkHash& Delete(const T& val);
    int IntHashFunc(const T&);
    bool Find(const T& val);
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
    array_ = new Link<T>[size_]();
}

template<typename T>
LinkHash<T>& LinkHash<T>::Insert(const T& val) {
    int pos = IntHashFunc(val);
    assert(pos < size_);
    array_[pos].Insert(val, 0);
}

template<typename T>
LinkHash<T>& LinkHash<T>::Delete(const T& val) {
    int pos = IntHashFunc(val);
    T* tmp;
    assert(pos < size_);
    int size = array_[pos].Length();
    if(size > 0) {
        int val_pos = array_[pos].Search(val);
        assert(val_pos > 0);
        array_[pos].Delete(val_pos, tmp);
    }
    return *this;
}

template<typename T>
bool LinkHash<T>::Find(const T& val) {
    int pos = IntHashFunc(val);
    assert(pos < size_);
    return array_[pos].Find(val);
}

template<typename T>
int LinkHash<T>::IntHashFunc(const T& val){
    return val % size_;
}
#endif // linked hash
