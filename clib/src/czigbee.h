/*
 * Progarm Name: czigbee.h
 * Created Time: 2016-10-11 14:27:58
 * Last modified: 2016-10-19 17:46:06
 */

#ifndef _CZIGBEE_H_
#define _CZIGBEE_H_
#ifdef __cplusplus
extern "C" {
#endif

    /* define vertex */
    struct Vertex_{
        double x;
        double y;
        double z;
    };

    struct Edge_{
        struct Vertex_ spos;
        struct Vertex_ epos;
    };

    struct ZNodeInfo_{
        int    nwk;
        int    mac[8];
        int    nodetype;    /* [0:'C', 1:'R', 2:'E'] */
        struct Vertex_ pos;
    };

    struct ZNodeCluster{
        int         node_cnt;
        int         edge_cnt;
        struct ZNodeInfo_  **node_list;
        struct Edge_       **edge_list;
    };

    extern void czigbee_main(void);

    extern int  node_cluster_update(struct ZNodeCluster *nc);

#ifdef __cplusplus
}
#endif
#endif //_CZIGBEE_H_

