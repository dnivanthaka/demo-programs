#include <stdlib.h>
#include "SDL/SDL.h"

#include "gtypedef.h"
#include "entities.h"

/*
int
get_collision_ob( struct player *pla, level *lvl )
{
    if( lvl->data != NULL ){
        if( *(&lvl->data[ (lvl->width * pla->screen_x) + pla->screen_y ]) == 01 ){
            return 01;
        }
    }
}
*/
/*
int w;
int h;
int screen_x;
int screen_y;
int o_type;
*/

void
add_object( struct ga_object *go, int w, int h, int s_x, int s_y, int ty )
{
    struct ga_object *tmp, *ptr;

    ptr = go;

    tmp = ( struct ga_object * )malloc( sizeof(struct ga_object) );
    tmp->w = w;
    tmp->h = h;
    tmp->screen_x = s_x;
    tmp->screen_y = s_y;
    tmp->o_type = ty;
    tmp->next = NULL;

    if( ptr != NULL ){    
        while( ptr->next != NULL )
            ptr = ptr->next;

        ptr->next = tmp;
    }else{    
        ptr = tmp;
    }
}

collision_info *
get_object( struct ga_object *go, int st_x, int st_y, int w, int h )
{
    collision_info *c_info = NULL;
    int mid_st_y =  st_y + (h / 2);
    //struct ga_object *tmp;
    //tmp = NULL;
   

    while( go != NULL ){
        //if( go->screen_y == 0 && go->screen_y == 464 && go->screen_x == 0 )
            //continue;
    //printf("mid_st_y = %d\n", mid_st_y);
    //printf("go->screen_y = %d\n", go->screen_y);
        
        if( go->screen_y != 0 && go->screen_y != 464 && go->screen_y <= mid_st_y &&  (go->screen_y + go->h) >= mid_st_y && go->screen_x <= (st_x + w) && (go->screen_x + go->w) >= (st_x + w) && st_y >= go->screen_y && (go->screen_y + go->h) >= st_y ){
        //if( go->screen_y != 464 && go->screen_x <= (st_x + w) && (go->screen_x + go->w) >= (st_x + w) && (go->screen_y + go->h) >= st_y && go->screen_y <= st_y ){
            //if( go->screen_y == 336 ){
                    //go->screen_x <= (st_x + w)  && (go->screen_x + go->w) >= (st_x + w) && (go->screen_y + go->h) >= st_y && go->screen_y <= st_y
                    printf("********** Left Side Hit **************\n");
                    printf("w = %d\n", go->w);
                    printf("h = %d\n", go->h);
                    printf("screen x = %d\n", go->screen_x);
                    printf("screen y = %d\n", go->screen_y);
                    printf("type = %d\n", go->o_type);
                    printf("************************\n");
            //}
            c_info = (collision_info *)malloc( sizeof(collision_info) );
            c_info->hit = LEFT_HIT;
            c_info->ob = go;
            break;

        }else if( go->screen_y != 0 && go->screen_y != 464 && go->screen_y <= mid_st_y && (go->screen_x + go->w) >= st_x  && go->screen_x <= st_x && go->screen_y <= st_y && (go->screen_y + go->h) >= st_y ){
            //if( go->screen_y == 336 ){
                    printf("********** Right Side Hit**************\n");
                    printf("w = %d\n", go->w);
                    printf("h = %d\n", go->h);
                    printf("screen x = %d\n", go->screen_x);
                    printf("screen y = %d\n", go->screen_y);
                    printf("type = %d\n", go->o_type);
                    printf("************************\n");
            //}
            //tmp = go;
            c_info = (collision_info *)malloc( sizeof(collision_info) );
            c_info->hit = RIGHT_HIT;
            c_info->ob = go;
            break;
        }else if( go->screen_y != 0 && go->screen_y != 464 && go->screen_x <= (st_x + w)  && (go->screen_x + go->w) >= (st_x + w) && go->screen_y <= (st_y + h) && (go->screen_y + go->h) >= (st_y + h) ){
            //
            // dave is above
            //if( go->screen_y == 336 ){
                    printf("********** Up **************\n");
                    printf("w = %d\n", go->w);
                    printf("h = %d\n", go->h);
                    printf("screen x = %d\n", go->screen_x);
                    printf("screen y = %d\n", go->screen_y);
                    printf("type = %d\n", go->o_type);
                    printf("************************\n");
            //}
            c_info = (collision_info *)malloc( sizeof(collision_info) );
            c_info->hit = TOP_HIT;
            c_info->ob = go;
            break;
        }else if( go->screen_y != 0 && go->screen_y != 464 && go->screen_x <= st_x  && (go->screen_x + go->w) >= st_x && (go->screen_y + go->h) >= st_y && go->screen_y <= st_y ){
            // dave is under
            //&& (go->screen_x + go->w) >= st_x
            //&& go->screen_y <= st_y && (go->screen_y + go->h) >= end_y
            //if( go->screen_y == 336 ){
                    printf("********** Down **************\n");
                    printf("w = %d\n", go->w);
                    printf("h = %d\n", go->h);
                    printf("screen x = %d\n", go->screen_x);
                    printf("screen y = %d\n", go->screen_y);
                    printf("type = %d\n", go->o_type);
                    printf("************************\n");
            //}

            c_info = (collision_info *)malloc( sizeof(collision_info) );
            c_info->hit = BOTTOM_HIT;
            c_info->ob = go;
            //tmp = go;

            break;
        }
        

        go = go->next;
    }

    return c_info;
}

void
print_ga_objects( struct ga_object *go )
{
    while( go != NULL ){
        if( go->screen_y == 336 ){
        printf("w = %d\n", go->w);
        printf("h = %d\n", go->h);
        printf("screen x = %d\n", go->screen_x);
        printf("screen y = %d\n", go->screen_y);
        printf("type = %d\n", go->o_type);
        printf("==============================\n");
        }
        go = go->next;
    }
}
