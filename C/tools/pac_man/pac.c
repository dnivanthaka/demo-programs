#include <stdio.h>

#include "pac.h"

#define MAX_PAC_DISTANCE 50
#define PAC_MOVE_DELAY 1

static int pac_pos_x, pac_pos_y;

void
move_pac(int key)
{
    int i = 0;

    //while(++i != MAX_PAC_DISTANCE){
        
    //}
}

void
set_pac_pos(int x, int y){
    /*
    if(x == 0){
        pac_pos_y = y;
    }else if(y == 0){
        pac_pos_x = x;
    }else{
        pac_pos_x = x;
        pac_pos_y = y;
    }
    */
    pac_pos_x = x;
    pac_pos_y = y;
}
