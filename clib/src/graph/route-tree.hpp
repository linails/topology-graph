/*
 * Progarm Name: route-tree.hpp
 * Created Time: 2016-10-20 11:31:13
 * Last modified: 2016-10-20 16:41:45
 */

#ifndef _ROUTE_TREE_HPP_
#define _ROUTE_TREE_HPP_

#include <string>
#include <vector>

using std::string;

/* 
 *               root
 *       /        |        \
 *     A          E          G
 *  /  |  \       |         / \
 * B   C   D      F       H     I
 *                              |
 *                              J
 *
 * firstchild | data | rtag(0/1)
 * ----------------------------------------------
 *  fc   : B   F   H   ^   ^   ^   ^   ^   J   ^
 *  data : A   E   G   B   C   D   F   H   I   J
 *  rtag : 0   0   1   0   0   1   1   0   1   1
 * */

class RouteTree{
public:
    RouteTree(string ns);
    ~RouteTree();
private:
    int     m_root;     // root nwk
    string  m_ns;
};

#endif //_ROUTE_TREE_HPP_

