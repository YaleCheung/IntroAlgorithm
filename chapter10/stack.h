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
    Stack() : p_data_(NULL), length_(0), size_(0) {Init_(100);};
    ~Stack() {if(NULL != p_data_) delete [] p_data_;}
    Stack(const Stack<T>&) = delete;
    Stack operator=(const Stack<T>&) = delete;
    
    int Length() const;
    int Size() const;
    void SetLength(const int& length);
    void SetSize(const int& size);
    
    void Init(T data[], const int& length, const int& size);
    void Push(const T& data);
    T Pop();
   
private:
    void Init_(const int& size);
    int length_;
    int size_;
    T* p_data_;
};

template<typename T>
int Stack<T>::Length() const {
    return length_;
}

template<typename T>
int Stack<T>::Size() const {
    return size_;
}

template<typename T>
void Stack<T>::SetLength(const int& length) {
    length_ = length;
}

template<typename T>
void Stack<T>::SetSize(const int& size) {
    size_ = size;
}    

template<typename T>
void Stack<T>::Init_(const int& size) {
    if(NULL == p_data_)
        delete [] p_data_;
    length_ = 0;
    size_ = size;
    p_data_ = new int[size_];
}

template<typename T>
void Stack<T>::Init(T data[], const int& length, const int& size) {
    assert(length <= size);
    if(NULL == p_data_)
        delete [] p_data_;
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
    p_data_[length_ ++] = data;
}

template<typename T>
T Stack<T>::Pop() {
    assert(length_ > 0);
    length_ --;
    return p_data_[length_];
};

#endif
