/*
 * Progarm Name: test.h
 * Created Time: 2016-10-19 14:14:37
 * Last modified: 2016-10-20 10:29:12
 */

#ifndef _TEST_H_
#define _TEST_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "../czigbee.h"

extern int test_get_vertexs_cnt(void);

extern int test_get_edges_cnt(void);

extern int test_node_cluster_load(struct ZNodeCluster *nc);

#ifdef __cplusplus
}
#endif
#endif //_TEST_H_

