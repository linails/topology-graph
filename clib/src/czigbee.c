/*
 * Progarm Name: czigbee.c
 * Created Time: 2016-10-11 14:27:54
 * Last modified: 2016-10-20 10:22:55
 */

#include "czigbee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "graph/calc_points.h"
#include "test/test.h"

typedef void *(*FUNC)(void *arg);

static void *worker_get_zigbee_data(void *arg);
static void *worker_calc_points(void *arg);

static FUNC threads[] = {
    worker_get_zigbee_data,
    worker_calc_points
};

//---------------------------------------------------------------------

char msg[1024] = "hello czigbee";

void *thread_func(void *arg)
{
    int times = 0;
    while(1){
        printf("thread func is running , arg was : %s\n",(char *)arg);
        sleep(1);
        memset(arg, 0, 11);
        memcpy(arg, "zigbee tick ...", strlen("zigbee tick ..."));
        if(times++ > 10){
            break;
        }
        printf("thread ... , times : %d\n", times);
    }
    pthread_exit("thread exit");
}

void *worker_get_zigbee_data(void *arg)
{
    while(1){
        usleep(100);
    }
    pthread_exit("worker_get_zigbee_data exit");
}

void *worker_calc_points(void *arg)
{
    while(1){
        usleep(100);
    }
    pthread_exit("worker_calc_points exit");
}

/* return 0-renew  */
int node_cluster_update(struct ZNodeCluster *nc)
{
#if 0
    int i = 0;

    nc->node_cnt = 10;
    nc->edge_cnt = 3;

    if(NULL == nc->node_list){
        nc->node_list = (struct ZNodeInfo_ **)malloc( sizeof(struct ZNodeInfo_ *) * nc->node_cnt );
        nc->edge_list = (struct Edge_      **)malloc( sizeof(struct Edge_ *) * nc->edge_cnt );
        for(i=0; i<nc->node_cnt; i++)
            nc->node_list[i] = (struct ZNodeInfo_ *)malloc( sizeof(struct ZNodeInfo_) );
        for(i=0; i<nc->edge_cnt; i++)
            nc->edge_list[i] = (struct Edge_ *)malloc( sizeof(struct Edge_) );
    }

    printf("-- node_cluster_update --\n");

    /* !!! renew return 0 */
    return 0;
#else
    /* For Test */
    static int flag = 0;

    int ret = 1;
    int i = 0;

    if(0 == flag){

        nc->node_cnt = test_get_vertexs_cnt();
        nc->edge_cnt = test_get_edges_cnt();

        if(NULL == nc->node_list){
            nc->node_list = (struct ZNodeInfo_ **)malloc( sizeof(struct ZNodeInfo_ *) * nc->node_cnt );
            nc->edge_list = (struct Edge_      **)malloc( sizeof(struct Edge_ *) * nc->edge_cnt );
            for(i=0; i<nc->node_cnt; i++)
                nc->node_list[i] = (struct ZNodeInfo_ *)malloc( sizeof(struct ZNodeInfo_) );
            for(i=0; i<nc->edge_cnt; i++)
                nc->edge_list[i] = (struct Edge_ *)malloc( sizeof(struct Edge_) );
        }

        test_node_cluster_load(nc);

        flag = ~flag;
        ret = 0;
    }
    return ret;
#endif
}

void czigbee_main(void)
{
    int         i;
    pthread_t   thread_a[2];

    for(i=0; i<2; i++){
        if(0 != pthread_create(&thread_a[i], NULL, threads[i], (void *)msg)){
            perror("thread_a creation failed!");
            exit(EXIT_FAILURE);
        }
    }

    for(i=0; i<2; i++){
        if(0 != pthread_detach(thread_a[i])){
            perror("thread_a join failed!");
            exit(EXIT_FAILURE);
        }else{
            printf("success !\n");
        }
    }

    calc_points();
}

