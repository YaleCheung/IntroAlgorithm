/*
 * =====================================================================================
 *
 *       Filename:  open_address.h
 *
 *    Description:  the method of hash open address
 *
 *        Version:  1.0
 *        Created:  11/12/14 22:31:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef OPEN_ADDRESS_HASH_H
#define OPEN_ADDRESS_HASH_H
#include "../lib/nocopyable.h"
#include <stdio.h>

// can only used for int now; should design for all 
template<typename T>
class Hash : NoCopyable<T> {
public:
    Hash(const int&);
    ~Hash();
    Hash& Insert(const T& val);
    int Search(const T& val);
    int Size() const;
    int HashFunc(const T& val) const;
private:
    bool IsEmpty_(const int& pos);
    void Init_();
    int size_;
    T* array_;
    bool* full_flag_;
};

template<typename T>
Hash<T>::Hash(const int & size) :
    size_(size), array_(NULL), full_flag_(NULL) {
    Init_();
}

template<typename T>
Hash<T>::~Hash() {
    if(array_ != NULL)
        delete [] array_;
    if(full_flag_ != NULL)
        delete [] full_flag_;
    array_ = NULL;
    full_flag_ = NULL;
}

template<typename T>
void Hash<T>::Init_() {
    array_ = new T[size_];
    full_flag_ = new bool[size_];
    for(int i = 0; i < size_; i ++)
        full_flag_[i] = false;
}

template<typename T>
Hash<T>& Hash<T>::Insert(const T& val) {
    int pos = HashFunc(val);
    if(IsEmpty_(pos)) {// the pos is empty
        array_[pos] = val;
        full_flag_[pos] = true;
        return *this;
    }
    int cur = (pos + 1) % size_;
    while(! IsEmpty_(cur) && (cur != pos)) {
        cur = (cur + 1) % size_;
    }
    if(cur == pos) {
        fprintf(stderr, "full\n");
    } else {
        array_[pos] = val;
        full_flag_[pos] = true;
    }
    return *this;
}

template<typename T>
int Hash<T>::Search(const T& val) {
    int pos = HashFunc(val);
    if(array_[pos] == val)
        return pos;
    int cur = pos + 1;
    while(array_[cur] != val && cur != pos) 
        cur = (cur + 1) % size_;
    if(cur == pos)
        return -1;
    else
        return cur;
}
template<typename T>
int Hash<T>::Size() const {
    return size_;
}

template<typename T>
bool Hash<T>::IsEmpty_(const int& pos) {
    return !full_flag_[pos];
}

// assume the emement are ints
template<typename T>
int Hash<T>::HashFunc(const T& val) const {
    return val % size_;
}
#endif // open addressed hash
