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

#include "queue.h"
#include <iostream>
using std::endl;
using std::cout;
int main(int argc, char* argv[]) {
    // init test
    Queue<int> test;
    // test EnQueue;
    for(auto i = 0; i < 90; i ++) {
        test.EnQueue(i);   
    }
    test.Print();
    for(auto i = 5; i < 10; i++) {
        cout << test.DeQueue() << endl;
    }
    test.Print();
    return 0;
}
