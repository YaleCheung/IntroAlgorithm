/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/27/14 17:46:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */
#include "countsort.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char* argv[]) {
    int* input = new int[100];
    int* output = new int[100];
    srand(time(NULL));
    for(auto i = 0; i < 100; i ++) {
         int value = rand() % 50;
         input[i] = value;
    }
    countsort(input, output, 100);
    for(auto i = 0; i < 100; i ++)
        std::cout << input[i] << " " << output[i] << std::endl;
    return 0;
}
