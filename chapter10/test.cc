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
    cout << test.Length() << endl;
    return 0;
}
