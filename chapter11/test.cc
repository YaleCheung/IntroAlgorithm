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
#include <stdio.h>
#include <iostream>

#include "open_address.h"
using namespace std;
int main(int argc, char* argv[]) {
    Hash<int> hash(2);
    for(int i = 0; i < 5; i ++)
        hash.Insert(i);
    return 0;
}

