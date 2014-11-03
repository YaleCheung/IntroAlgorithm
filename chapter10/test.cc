/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
<<<<<<< HEAD
 *        Created:  10/28/14 12:51:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "linkedqueue.h"
=======
 *        Created:  11/02/14 17:50:21
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi
 *   Organization:  org.zhangyi.com
 *
 * =====================================================================================
 */
#include "link.h"
#include <stdlib.h>
>>>>>>> develop
#include <iostream>
using std::endl;
using std::cout;
int main(int argc, char* argv[]) {
<<<<<<< HEAD
    // init test
    Queue<int> test;
    // test EnQueue;
    for(auto i = 0; i < 10; i ++) {
        test.EnQueue(i);   
    }

    for(auto i = 0; i < 10; i ++) {
        cout << test.DeQueue() << endl;;   
=======
    // test constructor;
    Link<int> test;
    // for insert
    for(int i = 0; i < 10; i ++) {
        test.Insert(i, i);
    }
    test.Print();
    cout << "length" << test.Length() << endl;
    int p = 0;
    for(int i = 10; i > 0 ; i ++) {
        test.Delete(i, &p);
        cout << p << endl;
>>>>>>> develop
    }
    return 0;
}
