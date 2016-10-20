#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-11 14:40:13
# Last modified: 2016-10-19 16:57:37
# 

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation
from pprint import pprint
import time
import threading

__metaclass__ = type
class Draw:

    def __init__(self, mutex, vertex_edges):

        self.mtx  = mutex
        self.ves  = vertex_edges
        self.quit = False   # Note: draw quit state

        self.xlim = [-3.0, 3.0]
        self.ylim = [-3.0, 3.0]
        self.zlim = [-3.0, 3.0]

        # Attaching 3D axis to the figure
        self.fig  = plt.figure()
        self.ax   = p3.Axes3D(self.fig)

        self.ax_set_para(self.ax)

        # Note: cache for draw vertexs & edges
        self.draw_data    = [[], []] # [[(points, tags, )] [edges, ]]

        self.threads      = []

        self.threads.append(threading.Thread(target=self.update_local_data, args=(self.mtx, self.ves, )))

        for tds in self.threads:
            tds.start()

        self.mutex_updating     = threading.Lock()
        #----------------------------------------------------
        # For Test
        # Note:      ((x, y, z),       nwk  , [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07], 'C'),
        #vertexpos =  [
        #             ((0, 0, 0),      0x0000, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07], 'C'),
        #             ((0.7, 2.2, 1),  0x0001, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08], 'R'),
        #             ((0, 1.8, 3),    0x0002, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x09], 'R'),
        #             ((1.6, 2.3, -1), 0x0003, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0a], 'E'),
        #             ((2, 0.8, 3),    0x0004, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0b], 'E'),
        #             ((-0.6, -0.6, 2),0x0005, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0c], 'E'),
        #             ((-1.3, 0.8, 2), 0x0006, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0d], 'R'),
        #             ((-1.5, -1, 0.3),0x0007, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0e], 'E'),
        #             ((0.5, -1.5, 2), 0x0008, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0f], 'R'),
        #             ((1.7, -0.8, 1), 0x0009, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x10], 'E'),
        #             ((1.5, -2.3, 0), 0x000a, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x11], 'E')
        #             ]

        #edgespos = [
        #            ((vertexpos[0][0], vertexpos[1][0]), 'R'),
        #            ((vertexpos[0][0], vertexpos[2][0]), 'R'),
        #            ((vertexpos[0][0], vertexpos[3][0]), 'E'),
        #            ((vertexpos[1][0], vertexpos[4][0]), 'E'),
        #            ((vertexpos[1][0], vertexpos[5][0]), 'E'),
        #            ((vertexpos[2][0], vertexpos[6][0]), 'R'),
        #            ((vertexpos[2][0], vertexpos[7][0]), 'E'),
        #            ((vertexpos[6][0], vertexpos[8][0]), 'R'),
        #            ((vertexpos[8][0], vertexpos[9][0]), 'E'),
        #            ((vertexpos[8][0], vertexpos[10][0]),'E')
        #           ]

        #self.draw_data[0].append((vertexpos[0][0], ['0', '0x0000'], vertexpos[0][3]))
        #self.draw_data[0].append((vertexpos[1][0], ['1', '0x0001'], vertexpos[1][3]))
        #self.draw_data[0].append((vertexpos[2][0], ['2', '0x0002'], vertexpos[2][3]))
        #self.draw_data[0].append((vertexpos[3][0], ['3', '0x0003'], vertexpos[3][3]))
        #self.draw_data[0].append((vertexpos[4][0], ['4', '0x0004'], vertexpos[4][3]))
        #self.draw_data[0].append((vertexpos[5][0], ['5', '0x0005'], vertexpos[5][3]))
        #self.draw_data[0].append((vertexpos[6][0], ['6', '0x0006'], vertexpos[6][3]))
        #self.draw_data[0].append((vertexpos[7][0], ['7', '0x0007'], vertexpos[7][3]))
        #self.draw_data[0].append((vertexpos[8][0], ['8', '0x0008'], vertexpos[8][3]))
        #self.draw_data[0].append((vertexpos[9][0], ['9', '0x0009'], vertexpos[9][3]))
        #self.draw_data[0].append((vertexpos[10][0],['10','0x0010'], vertexpos[10][3]))

        #self.draw_data[1].append((edgespos[0][0][0], edgespos[0][0][1], edgespos[0][1]))
        #self.draw_data[1].append((edgespos[1][0][0], edgespos[1][0][1], edgespos[1][1]))
        #self.draw_data[1].append((edgespos[2][0][0], edgespos[2][0][1], edgespos[2][1]))
        #self.draw_data[1].append((edgespos[3][0][0], edgespos[3][0][1], edgespos[3][1]))
        #self.draw_data[1].append((edgespos[4][0][0], edgespos[4][0][1], edgespos[4][1]))
        #self.draw_data[1].append((edgespos[5][0][0], edgespos[5][0][1], edgespos[5][1]))
        #self.draw_data[1].append((edgespos[6][0][0], edgespos[6][0][1], edgespos[6][1]))
        #self.draw_data[1].append((edgespos[7][0][0], edgespos[7][0][1], edgespos[7][1]))
        #self.draw_data[1].append((edgespos[8][0][0], edgespos[8][0][1], edgespos[8][1]))
        #self.draw_data[1].append((edgespos[9][0][0], edgespos[9][0][1], edgespos[9][1]))
        #----------------------------------------------------


    def update_local_data(self, mtx, ves):
        while self.quit == False:
            time.sleep(0.5)
            if mtx.acquire(1): #True
                if ves[0][0] == True:
                    # [[(points, tags, )] [edges, ]]
                    if self.mutex_updating.acquire(1): #True
                        print "updating ves[0][0]"
                        pprint(ves[0][1])
                        self.draw_data[0] = []
                        # Note: ((x, y, z), nwk, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07], 'C'),
                        # ((vertexpos[0][0], ['0', '0x0000'], vertexpos[0][3]))
                        [self.draw_data[0].append((u[0], [u[1], u[2]], u[3])) for u in ves[0][1]]
                        self.mutex_updating.release()
                if ves[1][0] == True:
                    if self.mutex_updating.acquire(1): #True
                        print "updating ves[1][0]"
                        pprint(ves[1][1])
                        self.draw_data[1] = []
                        #((vertexpos[0][0], vertexpos[1][0]), 'R'),
                        [self.draw_data[1].append((u[0][0], u[0][1], u[1])) for u in ves[1][1]]
                        self.mutex_updating.release()

                ves[0][0] = False
                ves[1][0] = False
                mtx.release()


    def update_graph(self, loop, data, ax):
        self.axis_clear(ax)
        if self.mutex_updating.acquire(1): #True
            print "update_graph..."
            # [[(points, tags, )] [edges, ]]
            [self.draw_edge(edge[0], edge[1], edge[2]) for edge in data[1]]
            [self.tag_info(p[0], p[1]) for p in data[0]]
            [self.draw_point(p[0], p[2]) for p in data[0]]
            self.mutex_updating.release()


    def show(self):
        # Note: Creating the Animation object
        ani = animation.FuncAnimation(
                self.fig,
                self.update_graph,
                10,
                fargs=(self.draw_data, self.ax),
                interval=1 * 1000,
                blit=False)

        plt.show()

        self.quit = True

        for tds in self.threads:
            tds.join()
            print ""
            print "show - tds :", tds
            print ""


    def ax_set_para(self, iax):
        # Note: Setting the axes properties
        iax.set_title('Topological Graph of Zigbee')
        iax.set_xlim3d(self.xlim)
        iax.set_ylim3d(self.ylim)
        iax.set_zlim3d(self.zlim)
        iax.set_xlabel('X')
        iax.set_ylabel('Y')
        iax.set_zlabel('Z')


    def axis_clear(self, ax):
        self.xlim = ax.get_xlim3d()
        self.ylim = ax.get_ylim3d()
        self.zlim = ax.get_zlim3d()
        ax.clear()
        ax.cla()
        self.ax_set_para(ax)


    def draw_point(self, point, ptype='E'):
        if ptype == 'C':
            self.ax.scatter(point[0], point[1], point[2], zdir = 'z', s=150, c='k') # Note: point color black
        elif ptype == 'R' :
            self.ax.scatter(point[0], point[1], point[2], zdir = 'z', s=80, c='r') # Note: point color read
        else :
            self.ax.scatter(point[0], point[1], point[2], zdir = 'z', s=20, c='b') # Note: point color blue


    def draw_edge(self, p1, p2, etype='E'):
        if etype == 'R':
            self.ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'r-', linewidth=3) # Note: 'bo-' / 'b-'
        else :
            self.ax.plot([p1[0], p2[0]], [p1[1], p2[1]], [p1[2], p2[2]], 'b-', linewidth=2)


    def tag_info(self, point, s):
        self.ax.text(point[0], point[1], point[2], '\n'.join(s), fontsize=8)


