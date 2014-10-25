/*
 * =====================================================================================
 *
 *       Filename:  cheap.h
 *
 *    Description:  The h file of heap
 *
 *        Version:  1.0
 *        Created:  10/23/2014 13:19:32
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi 
 *   Organization:  Org.zhangyi.com
 *
 * =====================================================================================
 */


// basic data structure
#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include <assert.h>
#include <iostream>

template<typename T>
class MaxHeap {
public:
    MaxHeap(const int& size = 100);
    void Init(T* data, const int& array_size, const int& heap_size);
    // empty or not
    bool IsEmpty() const;
    // full or not
    bool IsFull() const;
    // length 
    int Length() const;
    // curent size
    int Size() const;
    // Insert an element with T type;
    MaxHeap<T>& Insert(const T& ele);
    // Delete an element;
    MaxHeap<T>& DeleteMax(T* ele);
    // max
    T Max() const;
    ~MaxHeap();
    // by google code style, do not override << operator
    void Print();
private:
    void MakeHeap_();
    // return the index of left node in tree formed heap
    inline int Left_(const int& i) const;
    // return the index of right node in tree formed heap
    inline int Right_(const int& i) const;
    inline int Parent_(const int& i) const;
    MaxHeap(const MaxHeap<T>&) = delete;
    MaxHeap<T>& operator=(const MaxHeap<T>&) = delete;
    T* p_data_;
    int size_;
    int length_;

};

// constructor
template<typename T>
MaxHeap<T>::MaxHeap(const int& size) :
    size_(size) , length_(0) {
    assert(size > 0);
    p_data_ = new T[size_];
}

template<typename T>
void MaxHeap<T>::Init(T* data, const int& array_size, const int& heap_size) {
    length_ = array_size;
    size_ = heap_size;
    assert((data != NULL) && (length_ >= 0) && (size_ >= length_));
    p_data_ = new T[size_];
    // data copy;
    for(auto i = 0; i < length_; i ++)
        p_data_[i] = data[i];
    // make to heap
    MakeHeap_();
}

template<typename T>
int MaxHeap<T>::Left_(const int& i) const {
    assert(i >= 0);
    return 2 * i + 1;
}

template<typename T>
int MaxHeap<T>::Right_(const int& i) const {
    assert(i >= 0);
    return 2 * i + 2;
}

template<typename T>
int MaxHeap<T>::Parent_(const int& i) const {
    assert(i >= 0);
    if( i >= 1)
        return (i - 1) / 2;
    else
        return -1;
}

template<typename T>
T MaxHeap<T>::Max() const {
    assert(length_ > 0);
    return p_data_[0];
}

template<typename T>
void MaxHeap<T>::MakeHeap_() {
    for(int i = length_ / 2 - 1; i >= 0; i --) {
        // i becomes an empty node
        T value = p_data_[i];
        int left = Left_(i);
        int empty_pos = i;

        // make the sub tree to a heap
        while(left <= length_) {
            int right = left + 1;
            // max records the bigger num between the position left and right;
            int max = left;
            // right may not be existed, so examine it;
            // exist! then make the max point the right position;
            if((right <= length_) && (p_data_[left] < p_data_[right]))
                max ++;
            int parent = Parent_(max);
            // right not existed or left is bigger, exchange the parent to a bigger one;
            if(value < p_data_[max]) {
                p_data_[parent] = p_data_[max];
                empty_pos = max;
                left = Left_(max);
            } else
                break;
            // max becomes an empty node
        }
        p_data_[empty_pos] = value;
    }
}

template<typename T>
bool MaxHeap<T>::IsEmpty() const {
    return length_ ? false : true;    
}

template<typename T>
bool MaxHeap<T>::IsFull() const {
    return (length_ == size_) ? true : false;
}

template<typename T>
int MaxHeap<T>::Length() const {
    return length_;
}

template<typename T>
int MaxHeap<T>::Size() const{
    return size_;
}

template<typename T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& ele) {
    // insert an element to the heap
    // boundary check
    assert(length_ < size_);

    int empty_pos = length_;

    // find a place to insert the node
    int parent = Parent_(empty_pos);
    while((parent >= 0) && (p_data_[parent] < ele)) {
        p_data_[empty_pos] = p_data_[parent];
        empty_pos = parent;
        parent = Parent_(empty_pos);
    }
    p_data_[empty_pos] = ele;
    length_ ++;
    return *this;
}

template<typename T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T* ele) {
    // not empty
    assert(length_ > 0);
    *ele = p_data_[0];
    
    // put the end to front
    T value = p_data_[0] = p_data_[length_ - 1];
    // delete the max;
    length_ --;

    // because sub trees are max heap, only find a pos to place the first data;
    int empty_pos = 0;
    int left = Left_(empty_pos);
    // find a place
    while(left < length_) {
        int right = left + 1;
        int max = left;
        if((right < length_) && (p_data_[left] < p_data_[right]))
            max ++;
        if(value > p_data_[max])
            break;
        // move the max element up
        p_data_[empty_pos] = p_data_[max];
        empty_pos = max;
        left = Left_(max);
    }
    p_data_[empty_pos] = value;

    return *this;
}

template<typename T>
MaxHeap<T>::~MaxHeap() {
    if(p_data_ != NULL) {
        delete [] p_data_;
        p_data_ = NULL;
    }
}

template<typename T>
void MaxHeap<T>::Print() {
   for(auto i = 0; i < length_; i ++)
       std::cout <<  p_data_[i] << std::endl;
}
#endif //MaxHeap
