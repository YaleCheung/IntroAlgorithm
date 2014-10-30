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

#include <assert.h>

template<typename T>
class Queue {
public:
    Queue(const int& size);
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    // put a data into queue
    Queue& EnQueue(const T& val);
    // del a data in the queue
    T DeQueue();
    int Length() const;
    int Size() const;
private:
    void Init_(const int& size);
    int first_;
    int tail_
    int size_;
    T p_data_[];
};

template<typename T>
Queue<T>::Queue(const int size):
    first_(0), tail_(0), size_(size), p_data_(NULL) {
    Init_(size);
}

template<typename T>
void Queue<T>::Init_(const int& size) {
    if(p_data != NULL)
        delete [] p_data_;
    p_data_ = new T[size];
}

template<typename T>
Queue<T>& Queue<T>::EnQueue(const T& val) {
    if((tail_ == (size_ - 1)) && first_ > 0) {
        p_data_[tail_] = val;
        tail_ = 0;
    } else if(tail_ < first_ || 
            ((tail_ < size_) && tail_ > first_))
        p_data_[tail_ ++] = val;
    return *this;
}

template<typename T>
T Queue<T>::DeQueue() {
    if((first_ < size_) && (first_ < size_) {
        
    }
}
#endif
