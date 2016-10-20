#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-11 14:25:02
# Last modified: 2016-10-12 16:27:58
# 

from pprint import pprint
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation
import time
import threading
import czigbee
import zigbee
import draw_graph

__metaclass__ = type
class ZigbeeDraw:

    def __init__(self):
        print ""
        print "init() ..."
        print ""

        self.g_draw_state = True

        self.threads      = []
        self.vertex_edges = []

        self.mutex_end_draw     = threading.Lock()
        self.mutex_update_data  = threading.Lock()

        vertexs = [True, []] # Note: 'True' indicates renew data
        edges   = [True, []] # Note: 'True' indicates renew data

        self.vertex_edges.append(vertexs);
        self.vertex_edges.append(edges)

        print "vertex_edge set - init() :", self.vertex_edges

        self.zig = zigbee.Zigbee(self.mutex_update_data, self.vertex_edges)

        self.threads.append(threading.Thread(target=self.worker_draw, args=(self.vertex_edges, )))
        self.threads.append(threading.Thread(target=self.worker_update_ves))

        for tds in self.threads:
            tds.start()


    def worker_draw(self, vertex_edges):
        print "vertex_edge set - worker_draw : " , vertex_edges

        self.draw = draw_graph.Draw(self.mutex_update_data, vertex_edges)
        self.draw.show()

        print ""
        print "self.mutex_update_data :", self.mutex_update_data
        print ""

        if self.mutex_end_draw.acquire(1):

            print ""
            print "worker_draw : self.g_draw_state = False"
            print ""
            self.g_draw_state = False

            self.mutex_end_draw.release()
        print "exit while - worker_draw"


    def worker_update_ves(self):

        draw_state = True

        while draw_state:

            self.zig.update_data()

            time.sleep(0.5)
            if self.mutex_end_draw.acquire(1): #True
                draw_state = self.g_draw_state
                self.mutex_end_draw.release()

        print "exit while - worker_update_ves"


    def uninit(self):
        for tds in self.threads:
            tds.join()
            print ""
            print "tds :", tds
            print ""
        print ""
        print "uninit() ..."
        print ""


if __name__ == '__main__':

    zigbee_draw = ZigbeeDraw();

    zigbee_draw.uninit()

