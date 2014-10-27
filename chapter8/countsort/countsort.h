/*
 * =====================================================================================
 *
 *       Filename:  countsort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/27/14 17:45:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */

// count sort;
// only can be used for int type

#include <assert.h>
void countsort(int data_array[], int sorted_array[], int ele_num) {
    // assert data in range(0, 9999) negative value could be used countsort after position move;
    int max = 0; 
    int min = 9999;
    int count_size;
    int* count_array;
    for(auto i = 0; i < ele_num; i ++) {
        // in fact here is O(n);
        assert(data_array[i] < 9999 && data_array[i] > -9999);
        if(data_array[i] > max)
            max = data_array[i];
	if(data_array[i] < min)
            min = data_array[i];
	// init the array;
	count_size = max - min + 1;
        count_array = new int[count_size];
    }
    // init count_array;
    for(auto i = 0; i < count_size; i ++)
        count_array[i] = 0;
    // count the data
    for(auto i = 0; i < ele_num; i ++)
        count_array[data_array[i] - min] += 1;
    for(auto i = 1; i < count_size; i ++)
        count_array[i] = count_array[i] + count_array[i - 1];  // count_array[i] += count[i - 1];
    for(auto i = 0; i < ele_num; i ++) {
        sorted_array[count_array[data_array[i] - min]] = data_array[i];
        // for the same value;
        count_array[data_array[i]] -= 1;
    }
    delete count_array;
    return;
}
