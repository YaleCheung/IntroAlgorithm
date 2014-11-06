/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/05/14 13:38:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "direct_address_array.h"
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
    
    Array<int> a;
    for(int i = 1; i < 100; i ++)
        a[i] = i;
    for(int i = 1; i < 100;) {
        cout << a.Delete(i) << endl;
    }
    return 0;
}

