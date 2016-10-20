# readme.txt
# Created Time: 2016-10-11 14:55:48
# Last modified: 2016-10-20 15:46:38
#

[使用步骤]

    1. 执行工程根目录脚本，安装环境与编译获得so库：./build-so.sh

    2. 执行画图脚本：./python/main.py



[画图原理]
    
    1. 界面画图采用 python 的 matplot 库进行画图
        1> 画图时采用实时动态更新，一个线程更新数据，一个线程更新图形
        2> 画图主体启动后，调用 czigbee 中的 czigbee-main 函数，进行对 czigbee 中的必要初始化
        3> 更新数据线程，不断获取 czigbee 中的数据，有数据则更新，并将数据转换成图形可用数据
        ...

    2. 坐标计算 
        1> 将 zigbee 节点添加到 route-tree 中
        2> 将 zigbee 节点的父子关系添加到 route-tree 中进行调整 节点间的层次结构
        3> 在 cube 中对 route-tree 中按节点所在树的深度进行每一层均匀布点计算坐标
        ...

    3. 拓扑变化
        1> 节点直接的关系，为体现在图中的边
        2> 节点的空间坐标以第一次拓扑构成的 route-tree 为层次关系进行计算坐标
        3> 节点拓扑变化过程中，坐标不进行变化，只进行图中的边
        ...

    4. io 通信
        1> serial
        ...


[目录结构]

    1. 项目根目录有三个文件夹: clib / docs / python 
        1> clib : c/c++ 程序部分，会编译成so库共python调用
        2> docs : 包含一些工程文档
        3> python : python部分代码

    2. docs 文件夹中有一个 video 目录，是一些使用录制视频





