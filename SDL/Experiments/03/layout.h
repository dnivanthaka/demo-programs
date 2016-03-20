#ifndef __LAYOUT_H__
#define __LAYOUT_H__

/*
 * Tile types { 0 = empty, 1 = brick 1 }
 * */

extern Uint8 layout[SCREEN_HEIGHT / TILE_SIZE][SCREEN_WIDTH / TILE_SIZE];
void init_layout();
void draw_layout(SDL_Surface *screen);
Uint8 get_tile_type(coord *p);
coord *get_nearest_tile(coord *p);
void cleanup_layout();

#endif
