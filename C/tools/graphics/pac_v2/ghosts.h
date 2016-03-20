#ifndef __GHOST_H__
#define __GHOST_H__

#define GHOST_CHAR '@'

struct ghost{
    int pos_x;
    int pos_y;
};

void draw_ghosts();
void reset_ghosts();
#endif //__GHOST_H__
