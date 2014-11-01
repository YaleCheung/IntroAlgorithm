/*
 * =====================================================================================
 *
 *       Filename:  link.h
 *
 *    Description:  simple one way link
 *
 *        Version:  1.0
 *        Created:  11/01/14 21:12:12
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  zhangyi
 *   Organization:  
 *
 * =====================================================================================
 */

template<typename T>
class Link {
public:
    Link();
    ~Link();

    Link(const Link&) = delete;
    Link& operator-(const Link&) = delete;

private:
    typedef Node{
        T data;
	Node* p_next;
    } Node, *pNode;
};
