/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  implement stack by array
 *
 *        Version:  1.0
 *        Created:  10/27/14 22:14:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <cassert>
template<typename T>
class Stack {
public:
    Stack() == delete;
    Stack(const Stack&) == delete;
    void operator==(const Stack&) == delete;
    
    void Length() const;
    void Size() const;
    void SetLength(const int& length);
    void SetSize(const int& size);
    
    void Init(const int& size);
    void Init(T data[], const int& length, const int& size);
    void Push(const T& data);
    T Pop();
private:
    int length_
    int size_;
    T* p_data_;
};

template<typename T>
Stack<T>::SetLength(const int& length) {
    length_ = length;
}

template<typename T>
Stack<T>::setSize(const int& size) {
    size_ = size;
}    

template<typename T>
void Stack<T>::Init(const int& size) {
    length_ = 0;
    size_ = size;
    p_data_ = new int[size_];
}

template<typename T>
void Stack<T>::Init(T data[], const int& length, const int& size) {
    assert(length <= size);
    // copy data;
    length_ = length;
    size_ = size;
    p_data_ = new int[size_];
    for(auto i = 0; i < length; i ++) 
        p_data_[i] = data[i];
}
    
template<typename T>
void Stack<T>::Push(const T& data) {
    assert(length_ < size_);
    p_data_[length ++] = data;
}

template<typename T>
#endif
