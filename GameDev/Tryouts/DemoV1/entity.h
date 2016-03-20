/*
 * =====================================================================================
 *
 *       Filename:  entity.h
 *
 *    Description:  Entity Actions
 *
 *        Version:  1.0
 *        Created:  05/18/2013 03:50:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "globals.h"

struct entity{
    unsigned int x;
    unsigned int y;
    int vel_x;
    int vel_y;
    unsigned short width;
    unsigned short height;
    unsigned short max_frames;
    unsigned short current_frame;
    unsigned short animation_fps;
    unsigned short frame_row;
    Uint32 last_frame_update;
    SDL_Rect **frames;
    SDL_Surface *background;
    bool is_visible;
    bool first_time;
    state_t action;
    bool is_jumping;
    bool is_player;
};

void init_entity( struct entity *obj, bool is_player = false );
void animate_entity( struct entity *obj );
#endif
