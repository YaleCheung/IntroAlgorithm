/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/23/14 23:14:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "heap.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "basic test" ;
    MaxHeap<int> heap(100);
    cout << " size and length test;" << endl;
    cout << heap.Size() << " " << heap.Length() << endl;
    
    //cout << "add an element for mInsert and test the size and length" << endl;

    for(auto i = 0; i < 10; i ++) {
        heap.Insert(i);
        cout << heap.Size() << " " << heap.Length() << endl;
    }
    heap.Print();
    cout << "insert test complete" << " now, test init with array" << endl;
    
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    MaxHeap<int> heap2;
    heap2.Init(a, 10, 100);
    heap2.Print();
    
    
    cout << "Init complete" << endl;
    
    cout << "test max" << " delete max" << endl;
    
    int* p_data = new int;
    int value = heap2.Max();
    cout << value << endl;
    
    heap2.DeleteMax(p_data);
    cout << *p_data << endl;
    cout << heap2.Size() << " " << heap2.Length() << endl;
    for(int i = 9; i > 0; i --) {
        heap2.DeleteMax(p_data);
        cout << *p_data << endl;
    }
    delete p_data;
    return 0;
}

