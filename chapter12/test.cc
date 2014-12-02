/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/24/14 18:30:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "binarysearchtree.h"
#include <time.h>
#include <math.h>

int main() {
    BinarySearchTree<int> tree;
    srand(time(NULL));
    for(int i = 0; i < 10; i ++) {
        int data = rand() % 100;
        tree.Insert(data);
    }
    printf("InOrder Traverse\n");
    tree.InOrderR();
    printf("Level Order Traverse\n");
    tree.LevelOrder();
    printf("PreOrder Traverse\n");
    tree.PreOrderR();
    printf("PostOrder Traverse\n");
    tree.PostOrderR();
    printf("InOrder Iterator func\n");
    tree.InOrderI();
    printf("PreOrder Iterator func\n");
    tree.PreOrderI();
    printf("PostOrder Iterator func\n");
    tree.PostOrderI();
    return 0;
}
