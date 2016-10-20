#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-10 16:36:16
# Last modified: 2016-10-20 14:56:18
# 

"""
setup.py for czigbee.c
"""

from distutils.core import setup, Extension

czigbee_module = Extension('_czigbee',
                        sources=['czigbee_wrap.c',
                                 './src/czigbee.c', 
                                 './src/graph/calc_points.c',
                                 './src/graph/cube.cpp',
                                 './src/graph/sphere.cpp',
                                 './src/graph/route-tree.cpp',
                                 './src/io/serial.cpp',
                                 './src/test/test.c',
                                 ],
                       )

setup(
        name = 'czigbee-clib',
        version = '0.1',
        author = 'minphone ; email: linails@foxmail.com',
        description = """czigbee for python""",
        ext_modules = [czigbee_module],
        py_modules = ["czigbee"],
        )


