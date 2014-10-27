/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  10/25/14 22:29:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "quicksort.h"
#include <iostream>
int main() {
    int a[] = {5,4,3,2,1};
    QuickSort(a, 0, 4);
    for(auto i = 0; i < 4; i ++)
        std::cout << a[i] << std::endl;
    return 0;
} 
