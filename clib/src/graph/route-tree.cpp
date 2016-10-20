/*
 * Progarm Name: route-tree.cpp
 * Created Time: 2016-10-20 11:30:34
 * Last modified: 2016-10-20 17:38:30
 */

#include "route-tree.h"
#include "route-tree.hpp"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

RouteTree::RouteTree(string ns)
    :m_ns(ns)
{
    cout << "RouteTree constructor : " << ns << endl;
}

RouteTree::~RouteTree()
{
    cout << "RouteTree destructor ... : " << this->m_ns << endl;
}

/* new route-tree instance */
void *new_rtree_instance(void)
{
    //shared_ptr<RouteTree> p(new RouteTree("shared_ptr"));

    RouteTree *rt = new RouteTree("rt");
    return (void *)rt;
}

/* release route-tree instance */
int  release_rtree_instance(void **pinstance)
{
    if(NULL != *pinstance){
        delete (RouteTree *)*pinstance;
        *pinstance = NULL;
        return 0;
    }else{
        cout << "[Error] : release_rtree_instance() : pinstance = NULL !!!" << endl;
        return 1;
    }
}

int  add_rtree_node(void *instance, int nwk)
{
}

int  del_rtree_node(void *instance, int nwk)
{
}

/* update route-tree node-rela | pnwk - parent nwk */
int  update_rtree_noderela(void *instance, int pnwk, int cnwk)
{
}

