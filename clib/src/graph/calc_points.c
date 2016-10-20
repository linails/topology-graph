/*
 * Progarm Name: calc_points.c
 * Created Time: 2016-10-11 23:40:15
 * Last modified: 2016-10-20 14:59:30
 */

#include <stdio.h>
#include <math.h>

#include "calc_points.h"
#include "cube.h"
#include "sphere.h"
#include "route-tree.h"

void calc_points(void)
{
    printf(".......calc_points.......\n");

    void * rt_instance = NULL;

    rt_instance = new_rtree_instance();

    if(0 == release_rtree_instance( &rt_instance )){
        printf("rt_instance : %d\n", rt_instance);
    }
}

/*
 * points calc flow
 * */
void calc_flow(void)
{
    /* step :  */
    /* step :  */
}

