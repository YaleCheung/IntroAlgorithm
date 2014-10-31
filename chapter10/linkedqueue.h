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
    ~Queue();
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& EnQueue(const Queue);
    T DeQueue();
private:
    void Init_();
    typedef struct Node {
        T data;
	Node* p_next;
    } Node;

    Node* p_head_;
    Node* p_tail_
};
#endif

template<typename T>
Queue<T>::Queue() {
    p_tail_ = p_head_ = NULL;
    init_();
}

template<typename T>
void Queue<T>::Init_() {
    p_head_ = new Node;
    p_head_->p_next = NULL;
    p_tail_ = p_head_;
}

template<typename T>
Queue<T>& Queue<T>::EnQueue(const T& val) {
    Node p = new Node;
    p->data = val;    
    p->p_next = NULL;
    p_tail_->p_next = p;
    p_tail_ = p;
}

template<typename T>
T Queue<T>::DeQueue() {
    assert(p_tail_ != NULL);    
    T val = p_head_->p_next->data;
    Node* tmp = p_head_->p_next;
    p_head_->p_next = tmp->p_next;
    delete tmp;
}

template<typename T>
Queue<T>::~Queue() {
    while(p_head_) {
        Node* tmp = p_head_;
        p_head_ = p_head_->p_next;
        delete tmp;
    }
}
