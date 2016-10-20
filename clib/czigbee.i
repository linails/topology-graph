%module czigbee

%{
#include "./src/czigbee.h"
%}

void czigbee_main(void);

int  node_cluster_update(struct ZNodeCluster *nc);

%inline %{

struct ZNodeCluster *new_node_cluster(void);

struct ZNodeCluster *new_node_cluster(void)
{
    struct ZNodeCluster * nc = (struct ZNodeCluster *)malloc(sizeof(struct ZNodeCluster));

    nc->node_cnt  = 0;
    nc->edge_cnt  = 0;
    nc->node_list = NULL;
    nc->edge_list = NULL;

    return nc;
}

void free_node_cluster(struct ZNodeCluster *nc)
{
    int i = 0;

    for(i = 0; i < nc->node_cnt; i++) free(nc->node_list[i]);
    for(i = 0; i < nc->edge_cnt; i++) free(nc->edge_list[i]);

    free(nc->node_list);
    free(nc->edge_list);
    free(nc);
}

int node_cluster_get_node_cnt(struct ZNodeCluster *nc)
{
    return nc->node_cnt;
}

int node_cluster_get_edge_cnt(struct ZNodeCluster *nc)
{
    return nc->edge_cnt;
}

struct ZNodeInfo_ *node_cluster_get_node_idx(struct ZNodeCluster *nc, int idx)
{
    return nc->node_list[idx];
}

int znode_get_nwk(struct ZNodeInfo_ *zni)
{
    return zni->nwk;
}

int znode_get_ntype(struct ZNodeInfo_ *zni)
{
    return zni->nodetype;
}

int znode_get_mac_idx(struct ZNodeInfo_ *zni, int idx)
{
    return zni->mac[idx];
}

double znode_get_pos_x(struct ZNodeInfo_ *zni)
{
    return zni->pos.x;
}

double znode_get_pos_y(struct ZNodeInfo_ *zni)
{
    return zni->pos.y;
}

double znode_get_pos_z(struct ZNodeInfo_ *zni)
{
    return zni->pos.z;
}

struct Edge_ *node_cluster_get_edge_idx(struct ZNodeCluster *nc, int idx)
{
    return nc->edge_list[idx];
}

double zedge_get_spos_x(struct Edge_ *edge)
{
    return edge->spos.x;
}

double zedge_get_spos_y(struct Edge_ *edge)
{
    return edge->spos.y;
}

double zedge_get_spos_z(struct Edge_ *edge)
{
    return edge->spos.z;
}

double zedge_get_epos_x(struct Edge_ *edge)
{
    return edge->epos.x;
}

double zedge_get_epos_y(struct Edge_ *edge)
{
    return edge->epos.y;
}

double zedge_get_epos_z(struct Edge_ *edge)
{
    return edge->epos.z;
}

%}

