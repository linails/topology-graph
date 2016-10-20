/*
 * Progarm Name: test.c
 * Created Time: 2016-10-19 14:14:31
 * Last modified: 2016-10-20 10:29:08
 */

#include "test.h"
#include <stdio.h>
#include "../czigbee.h"

/* 
 # Data For Test
 # Note:      ((x, y, z),       nwk  , [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07], 'C'),
 vertexpos =  [
              ((0, 0, 0),      0x0000, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07], 'C'),
              ((0.7, 2.2, 1),  0x0001, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08], 'R'),
              ((0, 1.8, 3),    0x0002, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x09], 'R'),
              ((1.6, 2.3, -1), 0x0003, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0a], 'E'),
              ((2, 0.8, 3),    0x0004, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0b], 'E'),
              ((-0.6, -0.6, 2),0x0005, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0c], 'E'),
              ((-1.3, 0.8, 2), 0x0006, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0d], 'R'),
              ((-1.5, -1, 0.3),0x0007, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0e], 'E'),
              ((0.5, -1.5, 2), 0x0008, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0f], 'R'),
              ((1.7, -0.8, 1), 0x0009, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x10], 'E'),
              ((1.5, -2.3, 0), 0x000a, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x11], 'E')
              ]
 
 edgespos = [
             ((vertexpos[0][0], vertexpos[1][0]), 'R'),
             ((vertexpos[0][0], vertexpos[2][0]), 'R'),
             ((vertexpos[0][0], vertexpos[3][0]), 'E'),
             ((vertexpos[1][0], vertexpos[4][0]), 'E'),
             ((vertexpos[1][0], vertexpos[5][0]), 'E'),
             ((vertexpos[2][0], vertexpos[6][0]), 'R'),
             ((vertexpos[2][0], vertexpos[7][0]), 'E'),
             ((vertexpos[6][0], vertexpos[8][0]), 'R'),
             ((vertexpos[8][0], vertexpos[9][0]), 'E'),
             ((vertexpos[8][0], vertexpos[10][0]),'E')
            ]
 * */

typedef struct {
    double posx;
    double posy;
    double posz;
    int    nwk;
    int    mac[8];
    int    nodetype;    /* [0:'C', 1:'R', 2:'E'] */
}TestDataVes_t;

typedef struct {
    double sposx;
    double sposy;
    double sposz;
    double eposx;
    double eposy;
    double eposz;
}TestDataEdg_t;

static TestDataVes_t tdv[] = {
    {0, 0, 0,      0x0000, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, 0},
    {0.7, 2.2, 1,  0x0001, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08}, 1},
    {0, 1.8, 3,    0x0002, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x09}, 1},
    {1.6, 2.3, -1, 0x0003, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0a}, 2},
    {2, 0.8, 3,    0x0004, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0b}, 2},
    {-0.6, -0.6, 2,0x0005, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0c}, 2},
    {-1.3, 0.8, 2, 0x0006, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0d}, 1},
    {-1.5, -1, 0.3,0x0007, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0e}, 2},
    {0.5, -1.5, 2, 0x0008, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0f}, 1},
    {1.7, -0.8, 1, 0x0009, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x10}, 2},
    {1.5, -2.3, 0, 0x000a, {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x11}, 2}
};

static TestDataEdg_t tde[] = {
    {0, 0, 0, 0.7, 2.2, 1},
    {0, 0, 0, 0, 1.8, 3},
    {0, 0, 0, 1.6, 2.3, -1},
    {0.7, 2.2, 1, 2, 0.8, 3},
    {0.7, 2.2, 1, -0.6, -0.6, 2},
    {0, 1.8, 3, -1.3, 0.8, 2},
    {0, 1.8, 3, -1.5, -1, 0.3},
    {-1.3, 0.8, 2, 0.5, -1.5, 2},
    {0.5, -1.5, 2, 1.7, -0.8, 1},
    {0.5, -1.5, 2, 1.5, -2.3, 0}
};

int test_get_vertexs_cnt(void)
{
    return sizeof(tdv)/sizeof(TestDataVes_t);
}

int test_get_edges_cnt(void)
{
    return sizeof(tde)/sizeof(TestDataEdg_t);
}

int test_node_cluster_load(struct ZNodeCluster *nc)
{
    int i = 0;
    int j = 0;

    printf("nc->node_cnt : %d\n", nc->node_cnt);
    printf("nc->edge_cnt : %d\n", nc->edge_cnt);

    for(i=0; i<nc->node_cnt; i++){
        nc->node_list[i]->nwk   = tdv[i].nwk;
        nc->node_list[i]->pos.x = tdv[i].posx;
        nc->node_list[i]->pos.y = tdv[i].posy;
        nc->node_list[i]->pos.z = tdv[i].posz;
        for(j=0; j<8; j++) nc->node_list[i]->mac[j] = tdv[i].mac[j];
        nc->node_list[i]->nodetype = tdv[i].nodetype;
    }

    for(i=0; i<nc->edge_cnt; i++){
        nc->edge_list[i]->spos.x = tde[i].sposx;
        nc->edge_list[i]->spos.y = tde[i].sposy;
        nc->edge_list[i]->spos.z = tde[i].sposz;
        nc->edge_list[i]->epos.x = tde[i].eposx;
        nc->edge_list[i]->epos.y = tde[i].eposy;
        nc->edge_list[i]->epos.z = tde[i].eposz;
    }
    return 0;
}

