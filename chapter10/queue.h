/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  implement a generic queue
 *
 *        Version:  1.0
 *        Created:  10/29/14 13:20:47
 *       Revision:  none
 *       Compiler:  g+=
 *
 *         Author:  zhangyi
 *   Organization:  org.zhangyi.com
 *
 * =====================================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>

template<typename T>
class Queue {
public:
    Queue();
    Queue(const Queue&) = delete;
    Queue operator(const Queue&) = delete;

private:
    int size_;
    int length_;
    T p_data_[];
};
#endif
