/*
 * =====================================================================================
 *
 *       Filename:  nocopyable.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/06/14 13:16:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef NOCOPYABLE_H
#define NOCOPYABLE_H
template<typename T>
class NoCopyable {
public:
    NoCopyable() {}
    NoCopyable(const NoCopyable&) = delete;
    NoCopyable& operator=(const NoCopyable&) = delete; 
};
#endif

