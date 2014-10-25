/*
 * =====================================================================================
 *
 *       Filename:  quick_sort.h
 *
 *    Description:  quick sort
 *
 *        Version:  1.0
 *        Created:  10/25/14 21:35:46
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi
 *   Organization:  org.zhangyi.com
 *
 * =====================================================================================
 */

template<typename T>
int Partition(T*, int, int);

#include <assert.h>
template<typename T>
void QuickSort(T array[], int begin, int end) {
    // boundary judge;
    assert(array != NULL);
    if(begin >= end)
        return;
    int partition = Partition<T>(array, begin, end); // partition the array into two parts.
    QuickSort(array, begin, partition);
    QuickSort(array, partition + 1, end);

}

template<typename T>
int Partition(T array[], int begin, int end) {
    // array[end] as the num to place in the return value;
    int i = begin;
    int j = end;
    T value = array[begin]; // begin is empty
    while(i < j) {
        // find an element to place front
        while((j > i) && value < array[j]) // find a smaller one
            j --;
	if(i < j) {
            array[i] = array[j];
	    i ++;
	}
        // find  an element to place behind
	while((j > i) && value > array[i]) // find a bigger one
            i ++;
        // 
        if(i < j) { 
	    array[j] = array[i];
	    j --;
	}
    }
    array[i] = value;
    return i;
}
