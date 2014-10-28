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

#include "stack.h"
#include <iostream>
using std::endl;
using std::cout;
int main(int argc, char* argv[]) {
    // init test
    Stack<int> stack;

    for(auto i = 0; i < 10; i ++)
        stack.Push(i);
    cout << stack.Size();
    for(auto i = 0; i < 10; i ++)
       cout << "delete " << stack.Pop() << endl;
    return 0;
}
