/*
 * =====================================================================================
 *
 *       Filename:  linked_hash.h
 *
 *    Description:  implementation of hash. Collion solved by link 
 *
 *        Version:  1.0
 *        Created:  11/06/14 13:03:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef LINKED_HASH_H
#define LINKED_HASH_H
#include "link.h"
#include "hash.h"
#include "../lib/nocopyable.h"

template<typename T>
class LinkHash : public Hash<T>, public NoCopyable<T> {
public:
    // 
    LinkHash();
    Hash& Insert(const T&);
    Hash& Delete(const T&);
    bool Find() const;
    
private:
    Link* array_; //  an array to store the head of link;
}
#endif // linked hash
