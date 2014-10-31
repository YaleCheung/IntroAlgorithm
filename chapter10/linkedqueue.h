/*
 * =====================================================================================
 *
 *       Filename:  linkedqueue.h
 *
 *    Description:  link queue
 *
 *        Version:  1.0
 *        Created:  10/31/14 22:59:10
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

template<typename T>
class Queue {
public:
    Queue();
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& EnQueue(const Queue)
private:
    void init_();
    typedef struct Node {
        T data;
	Node* p_next;
    } Node, *pNode;

    pNode* p_head_;
};
#endif
