/*
 * =====================================================================================
 *
 *       Filename:  layout.h
 *
 *    Description:  Layout Manager
 *
 *        Version:  1.0
 *        Created:  05/08/2013 10:33:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#ifndef __LAYOUT_H__
#define __LAYOUT_H__
#include "SDL/SDL.h"

int get_tile_type( int x, int y, int scr );
void draw_layout( SDL_Surface **src, SDL_Surface **dest, SDL_Rect *src_rect, int scr );
#endif
