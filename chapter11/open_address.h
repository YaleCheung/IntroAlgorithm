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
#include "../lib/nocopyable"

// can only used for int now; should design for all 
template<typename T>
class Hash : NoCopyable<T> {
public:
    Hash(const int&);
    ~Hash();
    Hash& Insert(const T& val);
    int Search(const T& val);
    int Size() const;
    int HashFunc() const;
private:
    void IsEmpty_(const int& pos);
    void Init_();
    int size_;
    T* array_;
    bool* empty_flag_;
};

template<typename T>
Hash<T>::Hash(const int & size) :
    size_(size), array_(NULL) {
    Init_();
}

template<typename T>
Hash<T>::~Hash() {
    if(array_ != NULL)
        delete [] array_;
    if(empty_flag_ != NULL)
        delete [] empty_flag_;
    array_ = NULL;
    empty_flag_ = NULL;
}

template<typename T>
void Init_() {
    array_ = new T[size_];
    empty_flag_ = new T[size_];
    for(int i = 0; i < empty_flag_; i ++)
        empty_flat_[i] = false;
}

template<typename T>
Hash<T>& Hash<T>::Insert(const T val) {
    int pos = HashFunc(val);
    if(IsEmpty(pos)) // the pos is empty
        array_[pos] = val;
        return *this;
    int cur = (pos + 1) % size_;
    while(! IsEmpty(cur) && (cur != pos)) {
        cur = (cur + 1) % size_;
    }
    if(cur == pos) {
        cout << "full" << endl;
    } else {
        array_[pos] = val;
        empty_flags_[pos] = true;
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
#endif

