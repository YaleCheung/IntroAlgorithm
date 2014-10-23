/*
 * =====================================================================================
 *
 *       Filename:  CHeap.cpp
 *
 *    Description:  the implement of heap
 *
 *        Version:  1.0
 *        Created:  10/23/2014 13:19:32
 *       Revision:  none
 *       Compiler:  g++ // c11
 *
 *         Author:  zhangyi
 *   Organization:  org.zhangyi.com
 *
 * =====================================================================================
 */

#include "CHeap.h"
#include <assert.h>
// memory full exception
class MemoryFullExp;

// constructor
template<typename T>
CHeap<T>::CHeap(size_t size = 100) :
    _m_nSize(size) , _m_nLength(0) {
    assert(size > 0);
    _m_pData = new T[_m_nSize];
}

template<typename T>
CHeap<T>::CHeap(T* data, int array_size, int heap_size) :
    _m_nLength(array_size), _m_nSize(heap_size) {
    assert((data != NULL) && (_m_nLength >= 0) && (_m_nSize >= _m_nLength));
    _m_pData = new T[_m_nSize];
    // data copy;
    for(auto i = 0; i < _m_nSize, i ++)
        _m_pData[i] = data[i];
    // make to heap
    _mMakeHeap();
}

template<typename T>
size_t CHeap<T>::_mLeft(cosnt size_t& i) const {
    assert(i >= 0);
    return 2 * i + 1;
}

template<typename T>
size_t CHeap<T>::_mRight(const size_t& i) const {
    assert(i >= 0);
    return 2 * i + 2;
}

template<typename T>
size_t _mParent(const size_t& i) const {
    assert(i > 0);
    return (i - 1) / 2;
}

template<typename T>
void CHeap<T>::_mMakeHeap() {
    for(auto i = _m_nLength / 2 - 1; i >= 0; i --) {
        // i becomes an empty node
        T value = _m_pData[i];
        size_t left = _mLeft(i);
        size_t empty_pos = i;

        // make the sub tree to a heap
        while(left < _m_nLength) {
            int right = _mRight(i);
            // max records the bigger num between the position left and right;
            int max = left;
            // right may not be existed, so examine it;
            // exist! then make the max point the right position;
            if((right < _m_nLength) && (_m_pData[left] < _m_pData[right]))
                max ++;
            // right not existed or left is bigger, exchange the parent to a bigger one;
            if(value < _m_pData[max]) {
                _m_pData[empty_pos] = _m_pData[max];
                empty_pos = max;
            }
            // max becomes an empty node
            left = _mLeft(max);
        }
        _m_pData[empty_pos] = value;
    }
}

template<typename T>
bool CHeap<T>::mIsEmpty() const {
    return _m_nLength ? false : true;    
}

template<typename T>
bool CHeap<T>::mIsFull() const {
    return (_m_nLength == _m_nSize) ? true : false;
}

template<typename T>
CHeap<T>& CHeap<T>::mInsert(const T& ele) {
    // insert an element to the heap
    // boundary check
    if(_m_nLength == _m_nSize)
        throw(MemoryFullExp);
    size_t empty_pos = _m_nLength - 1;

    // find a place to insert the node
    size_t parent = _mParent(empty_pos);
    while((parent > 0) && 
    _m_nLength ++;


}
