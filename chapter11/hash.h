/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  interface of hash
 *
 *        Version:  1.0
 *        Created:  11/06/14 13:20:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef HASH_H
#define HASH_H
template<typename T>
class Hash {
public:
    virtual Hash& Insert(const T&) = 0;
    virtual Hash& Delete(const T&) = 0;
    virtual bool Find(const T&) const = 0;
};
#endif // Hash
