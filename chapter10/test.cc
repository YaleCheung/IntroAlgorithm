/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
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
#include <iostream>
using std::endl;
using std::cout;
int main(int argc, char* argv[]) {
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
    }
    return 0;
}
