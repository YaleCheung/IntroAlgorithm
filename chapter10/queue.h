/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  implement a generic queue
 *
 *        Version:  1.0
 *        Created:  10/29/14 13:20:47
 *       Revision:  none
 *       Compiler:  g+=
 *
 *         Author:  zhangyi
 *   Organization:  org.zhangyi.com
 *
 * =====================================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <assert.h>

template<typename T>
class Queue {
public:
    Queue(const int& size = 10);
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    // put a data into queue
    Queue& EnQueue(const T& val);
    // del a data in the queue
    T DeQueue();
    int Size() const;

    void Print();
private:
    void Init_();
    int length_;
    int first_;
    int tail_;
    int size_;
    T* p_data_;
};

template<typename T>
Queue<T>::Queue(const int& size):
    length_(0), first_(0), tail_(0), size_(size), p_data_(NULL) {
    Init_();
}

template<typename T>
int Queue<T>::Size() const {
    return size_;
}

template<typename T>
void Queue<T>::Init_() {
    if(p_data_ != NULL)
        delete [] p_data_;
    p_data_ = new T[size_];
}

template<typename T>
Queue<T>& Queue<T>::EnQueue(const T& val) {
    assert(length_ < size_); // have position
    // tail_ < first;
    p_data_[tail_ ++] = val;
    if(tail_ == size_)
        tail_ = 0;
    length_ ++;
    return *this;
}

template<typename T>
T Queue<T>::DeQueue() {
    assert(length_ > 0);
    T val = p_data_[first_ ++];
    if(first_ == size_)
        first_ = 0;
    length_ --;
    return val;
}


template<typename T>
void Queue<T>::Print() {
    assert(length_ > 0);
    int order = 0;
    int indx = first_;
    while(order < length_) {
        printf("%d\n", p_data_[indx ++]);
        if(indx == size_)
            indx == 0;
        order ++;
    }
}
#endif
