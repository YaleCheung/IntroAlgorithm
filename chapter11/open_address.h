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
    void Init_();
    int size_;
    T* array_;
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
    array_ = NULL;
}

template<typename T>
void Init_() {
    array_ = new T[size_];
}

template<typename T>
Hash<T>& Hash<T>::Insert(const T val) {
    int
}
#endif

