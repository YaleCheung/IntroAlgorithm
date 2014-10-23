/*
 * =====================================================================================
 *
 *       Filename:  CMaxHeap.h
 *
 *    Description:  The cpp implement of Heap
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
#ifdef CHEAP_HHH
#define CHEAP_HHH

template<typename T>
class CMaxHeap {
public:
    CMaxHeap(int size);
    CMaxHeap(T* data, int array_size, int heap_size);
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

#endif
