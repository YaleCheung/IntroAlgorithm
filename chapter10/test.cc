/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/28/14 12:51:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "linkedstack.h"
#include <iostream>
using std::endl;
using std::cout;
int main(int argc, char* argv[]) {
    // init test
    Stack<int> ss;
    for(int i = 0; i < 10; i ++) {
        ss.Push(i);
        cout << ss.Length() << endl;
    }
    return 0;
}
