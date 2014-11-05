/*
 * =====================================================================================
 *
 *       Filename:  direct_address_array.h
 *
 *    Description:  the direct search method of array with dynamic size 
 *
 *        Version:  1.0
 *        Created:  11/05/14 12:56:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef DIRECT_ADDRESS_ARRAY_H
#define DIRECT_ADDRESS_ARRAY_H

template<typename T>
class Array {
public:
    Array() : array_(NULL), size_(0)  {Init_()};
    Array(const Array&) = delete;
    Array operator=(const Array&) = delete;
    // add a index at index;
    void Add(const int& index, const T& val);
    T Delete(const int& index);
    T Search(const int& index);
    T& operator[](const int& index);
    // find a value in the array
    bool Find(const T& val) const;
    // set the arraysize
    // return the size of array;
    int Size() const;
    
private:
    // init the array;
    void Init_();
    T* array_;
    int size_;
};

template<typename T>
void Array<T>::Init_() {
    if(array_ != NULL)
        delete [] array_;
    size_ = 100; // initial size;
    array_ = new T[size_]; // default constructor to init the array
}

template<typename T>
void Array<T>::Add(const int& index, const T& val) {
    assert((array_ != NULL) && (index > 0));
    if(index > size_) {// the array is full;
        T* new_array = new T[size_ * 2];
	// copy the element into new array
	for(int i = 0; i < size_; i ++)
            new_array[i] = array_[i];
	delete [] array_;
	array_ = new_array;
	size_ *= 2;
    }
    array_[index] = val;
}

template<typename T>
void Array<T>::Delete(const T& index) {
    assert(index <= size_ && index > 0);
    // copy the data after index;
    for(int i = index, i < size_; i ++)
        array_[i] = array_[i + 1];
}

template<typename T>
bool Array<T>::Find(const T& val) {
    for(int i = 0; i < size_; i ++) {
        if(val == array_[i])
            return true;
    }
    return false;
}

template<typename T>
T Array<T>::Search(const int& index) {
    assert((index < size_) && (index > 0));
    return array_[index - 1];
}

template<typename T>
T& Array<T>::operator[](const int& index) {
    return array_[index];
}

template<typename T>
int Array<T>::Size() const {
    return size_;
}

#endif
