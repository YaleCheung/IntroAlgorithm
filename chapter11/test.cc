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

#include "linked_hash.h"
using namespace std;
int main(int argc, char* argv[]) {
    LinkHash<int> hash;
    hash.Insert(1);
    for(int i = 0; i < 100; i ++)
        hash.Insert(i);
    for(int i = 0; i < 100; i++) 
        hash.Delete(i);
    return 0;
}

