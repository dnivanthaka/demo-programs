/*
 * =====================================================================================
 *
 *       Filename:  layout.h
 *
 *    Description:  Layout handling functions
 *
 *        Version:  1.0
 *        Created:  09/18/2014 11:33:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#ifndef __LAYOUT_H__
#define __LAYOUT_H__ 1

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int TILE_WIDTH = 32;

extern SDL_Surface *smap;

extern Uint8 layout[SCREEN_HEIGHT / TILE_WIDTH][SCREEN_WIDTH / TILE_WIDTH]; 

void layout_draw(SDL_Surface *screen);
Uint8 layout_gettiletype(int x, int y);
void layout_init();
SDL_Surface *load_layout(char *filename);

#endif
