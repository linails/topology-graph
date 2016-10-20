/*
 * Progarm Name: route-tree.h
 * Created Time: 2016-10-20 11:30:54
 * Last modified: 2016-10-20 14:25:15
 */

#ifndef _ROUTE_TREE_H_
#define _ROUTE_TREE_H_
#ifdef __cplusplus
extern "C" {
#endif

    /* new route-tree instance */
    extern void *new_rtree_instance(void);

    /* release route-tree instance */
    extern int  release_rtree_instance(void **pinstance);

    extern int  add_rtree_node(void *instance, int nwk);

    extern int  del_rtree_node(void *instance, int nwk);

    /* update route-tree node-rela | pnwk - parent nwk */
    extern int  update_rtree_noderela(void *instance, int pnwk, int cnwk);

#ifdef __cplusplus
}
#endif
#endif //_ROUTE_TREE_H_

