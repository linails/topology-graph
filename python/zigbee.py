#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-11 14:50:09
# Last modified: 2016-10-19 17:31:33
# 

from pprint import pprint
import threading
import czigbee
import time

__metaclass__ = type
class Zigbee:

    def __init__(self, mutex, vertex_edges):
        czigbee.czigbee_main()
        self.mtx = mutex
        self.ves = vertex_edges
        self.nc  = czigbee.new_node_cluster()
        self.nodec = [[], [], {}] # Note :[[nodes], [edges], {node:type}]


    def update_data(self):
        if 0 == czigbee.node_cluster_update(self.nc):
            print "...... renew"
            # Note: update self.ves
            if self.get_node_cluster() > 0:
                self.update_ves()
        else:
            print "...... ******"


    def update_ves(self):
        if self.mtx.acquire(1):

            # Note: [nodes]
            if len(self.nodec[0]):
                print "self.ves[0][0] = True"
                self.ves[0][0] = True
                self.ves[0][1] = self.nodec[0]

            # Note: [edges]
            if len(self.nodec[1]):
                print "self.ves[1][0] = True"
                self.ves[1][0] = True
                self.ves[1][1] = self.nodec[1]

            self.mtx.release()


    def get_node_cluster(self):
        self.nodec[0] = self.znode_get_nodes()
        self.nodec[1] = self.zedge_get_edges()
        return len(self.nodec[0]) + len(self.nodec[1])


    #----------------------------------------------------
    # Note: get zigbee-node-info from czigbee.c
    def znode_get_nodes(self):
        nodes = []
        cnt = czigbee.node_cluster_get_node_cnt(self.nc)
        print "cnt-znode_get_nodes :", cnt
        for idx in range(cnt):
            # Note: node [(pos), nwk, mac, ptype]
            # Note: node ((x, y, z),       nwk  , [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07], 'C'),
            node = []

            zni = czigbee.node_cluster_get_node_idx(self.nc, idx)
            # Note: append (x, y, z)
            node.append((
                czigbee.znode_get_pos_x(zni),
                czigbee.znode_get_pos_y(zni),
                czigbee.znode_get_pos_z(zni)))
            # Note: append nwk addr
            node.append("nwk:" + self.short2hex(czigbee.znode_get_nwk(zni)))
            # Note: append mac addr
            #node.append('mac:' + self.mac2hex([czigbee.znode_get_mac_idx(zni, idx) for idx in range(8)]))
            node.append('mac[2]:' + self.mac2hex([czigbee.znode_get_mac_idx(zni, idx) for idx in range(8)])[12:16])
            if czigbee.znode_get_ntype(zni) == 0: node.append('C')
            elif czigbee.znode_get_ntype(zni) == 1: node.append('R')
            else : node.append('E')
            nodes.append(tuple(node))
            self.nodec[2][node[0]] = node[3] # Note: add / update {node(pos) : type}
        return nodes


    def zedge_get_edges(self):
        edges = []
        cnt = czigbee.node_cluster_get_edge_cnt(self.nc)
        print "cnt-zedge_get_edges :", cnt
        for idx in range(cnt):
            nce = czigbee.node_cluster_get_edge_idx(self.nc, idx)
            # Note: (((sx, sy, sz), (ex, ey, ez)), 'R/E') = ((spos, epos), 'R/E')
            spos = ( czigbee.zedge_get_spos_x(nce),
                     czigbee.zedge_get_spos_y(nce),
                     czigbee.zedge_get_spos_z(nce) )
            epos = ( czigbee.zedge_get_epos_x(nce),
                     czigbee.zedge_get_epos_y(nce),
                     czigbee.zedge_get_epos_z(nce) )
            et = 'R'
            if self.nodec[2][spos] == 'E' or self.nodec[2][epos] == 'E': et = 'E'
            edges.append(((spos, epos), et))
        return edges
    #----------------------------------------------------


    def byte2hex(self, num):
        """
        # Note: {2 -> 0x02 | 10 -> 0x0A}
        """
        base = [str(x) for x in range(10)] + [chr(x) for x in range(ord('A'), ord('A')+6)]
        mid = []
        if num > 0xff:
            num = 0xff
            print "out of range"
        while True:
            if num == 0: break
            num ,rem = divmod(num, 16)
            mid.append(base[rem])
        while len(mid) < 2: mid.append('0')
        return ''.join([str(x) for x in mid[::-1]]) # Note:


    def mac2hex(self, mac):
        """
        # Note: {0x[01 02 03 04 05 06 07 08] -> str:0102030405060708}
        """
        return ''.join([self.byte2hex(u) for u in mac])


    def short2hex(self, num):
        """
        # Note: {0x0102 -> str(0x0102)}
        """
        base = [str(x) for x in range(10)] + [chr(x) for x in range(ord('A'), ord('A')+6)]
        mid = []
        if num > 0xffff:
            num = 0xffff
            print "out of range"
        while True:
            if num == 0: break
            num ,rem = divmod(num, 16)
            mid.append(base[rem])
        while len(mid) < 4: mid.append('0')
        return ''.join([str(x) for x in mid[::-1]]) # Note:


    def test(self):
        #----------------------------------------------------
        # For Test

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



