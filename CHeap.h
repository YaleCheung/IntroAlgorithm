/*
 * =====================================================================================
 *
 *       Filename:  CHeap.h
 *
 *    Description:  The h file of Heap
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
#ifndef CHEAP_HHH
#define CHEAP_HHH

#include <assert.h>

template<typename T>
class CMaxHeap {
public:
    CMaxHeap(const size_t& size = 100);
    CMaxHeap(T* data, const size_t& array_size, const size_t& heap_size);
    // empty or not
    bool mIsEmpty() const;
    // full or not
    bool mIsFull() const;
    // length 
    size_t mLength() const;
    // curent size
    size_t mSize() const;
    
    // Insert an element with T type;
    CMaxHeap<T>& mInsert(const T& ele);
    // Delete an element;
    CMaxHeap<T>& mDeleteMax(T& ele);
    // max
    T mMax() const;
    ~CMaxHeap();
private:
    void _mMakeHeap();
    // return the index of left node in tree formed heap
    inline size_t _mLeft(const size_t& i) const;
    // return the index of right node in tree formed heap
    inline size_t _mRight(const size_t& i) const;
    inline size_t _mParent(const size_t& i) const;
    CMaxHeap(const CMaxHeap<T>&) = delete;
    CMaxHeap<T>& operator=(const CMaxHeap<T>&) = delete;
    T* _m_pData;
    size_t _m_nSize;
    size_t _m_nLength;

};


// constructor
template<typename T>
CMaxHeap<T>::CMaxHeap(const size_t& size) :
    _m_nSize(size) , _m_nLength(0) {
    assert(size > 0);
    _m_pData = new T[_m_nSize];
}

template<typename T>
CMaxHeap<T>::CMaxHeap(T* data, const size_t& array_size, const size_t& heap_size) :
    _m_nLength(array_size), _m_nSize(heap_size) {
    assert((data != NULL) && (_m_nLength >= 0) && (_m_nSize >= _m_nLength));
    _m_pData = new T[_m_nSize];
    // data copy;
    for(auto i = 0; i < _m_nSize; i ++)
        _m_pData[i] = data[i];
    // make to heap
    _mMakeHeap();
}

template<typename T>
size_t CMaxHeap<T>::_mLeft(const size_t& i) const {
    assert(i >= 0);
    return 2 * i + 1;
}

template<typename T>
size_t CMaxHeap<T>::_mRight(const size_t& i) const {
    assert(i >= 0);
    return 2 * i + 2;
}

template<typename T>
size_t CMaxHeap<T>::_mParent(const size_t& i) const {
    assert(i > 0);
    return (i - 1) / 2;
}

template<typename T>
T CMaxHeap<T>::mMax() const {
    assert(_m_nLength > 0);
    return _m_pData[0];
}

template<typename T>
void CMaxHeap<T>::_mMakeHeap() {
    for(auto i = _m_nLength / 2 - 1; i >= 0; i --) {
        // i becomes an empty node
        T value = _m_pData[i];
        size_t left = _mLeft(i);
        size_t empty_pos = i;

        // make the sub tree to a heap
        while(left <= _m_nLength) {
            int right = left + 1;
            // max records the bigger num between the position left and right;
            int max = left;
            // right may not be existed, so examine it;
            // exist! then make the max point the right position;
            if((right <= _m_nLength) && (_m_pData[left] < _m_pData[right]))
                max ++;
            size_t parent = _mParent(max);
            // right not existed or left is bigger, exchange the parent to a bigger one;
            if(value < _m_pData[max]) {
                _m_pData[parent] = _m_pData[max];
                empty_pos = max;
                left = _mLeft(max);
            } else
                break;
            // max becomes an empty node
        }
        _m_pData[empty_pos] = value;
    }
}

template<typename T>
bool CMaxHeap<T>::mIsEmpty() const {
    return _m_nLength ? false : true;    
}

template<typename T>
bool CMaxHeap<T>::mIsFull() const {
    return (_m_nLength == _m_nSize) ? true : false;
}

template<typename T>
size_t CMaxHeap<T>::mLength() const {
    return _m_nLength;
}

template<typename T>
size_t CMaxHeap<T>::mSize() const{
    return _m_nSize;
}

template<typename T>
CMaxHeap<T>& CMaxHeap<T>::mInsert(const T& ele) {
    // insert an element to the heap
    // boundary check
    assert(_m_nLength < _m_nSize);

    size_t empty_pos = _m_nLength - 1;

    // find a place to insert the node
    size_t parent = _mParent(empty_pos);
    while((parent >= 0) && (_m_pData[parent] < ele)) {
        _m_pData[empty_pos] = _m_pData[parent];
        empty_pos = parent;
        parent = _mParent(parent);
    }
    _m_pData[empty_pos] = ele;
    _m_nLength ++;
    return *this;
}

template<typename T>
CMaxHeap<T>& CMaxHeap<T>::mDeleteMax(T& ele) {
    // not empty
    assert(_m_nLength > 0);
    ele = _m_pData[0];
    
    // put the end to front
    T value = _m_pData[0] = _m_pData[_m_nLength - 1];
    // delete the max;
    _m_nLength --;

    // because sub trees are max heap, only find a pos to place the first data;
    size_t empty_pos = ele;
    size_t left = _mLeft(empty_pos);
    // find a place
    while(left < _m_nLength) {
        size_t right = left + 1;
        int max = left;
        if((right < _m_nLength) && (_m_pData[left] < _m_pData[right]))
            // right is bigger;
            max ++;
        if(value > _m_pData[max])
            break;
        
        // move the max element up
        _m_pData[max] = _m_pData[_mParent(max)];
        empty_pos = max;
        left = _mLeft(max);
    }
    _m_pData[empty_pos] = value;

    return *this;
}

template<typename T>
CMaxHeap<T>::~CMaxHeap() {
    if(_m_pData != NULL) {
        delete [] _m_pData;
        _m_pData = NULL;
    }
}
#endif
