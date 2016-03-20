/*
 * =====================================================================================
 *
 *       Filename:  player.cpp
 *
 *    Description:  Player Actions
 *
 *        Version:  1.0
 *        Created:  05/18/2013 03:47:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include "SDL/SDL.h"

#include "entity.h"

void
init_entity( struct entity *obj, bool is_player )
{

    obj->x                 = 0;
    obj->y                 = 0;
    obj->vel_x             = 0;
    obj->vel_y             = 0;
    obj->width             = 16;
    obj->height            = 16;
    obj->max_frames        = 4;
    obj->current_frame     = 0;
    obj->frame_row         = 0;
    obj->animation_fps     = 16;
    obj->last_frame_update = 0;
    obj->is_visible        = true;
    obj->first_time        = true;
    obj->is_jumping        = false;
    obj->is_player         = is_player;
}

void
animate_entity( struct entity *obj )
{
    if( !obj->is_jumping && obj->vel_x != 0 ){
        if( (SDL_GetTicks() - obj->last_frame_update) >= (1000.f / obj->animation_fps) ){
            obj->current_frame = (obj->current_frame + 1) % obj->max_frames;
            obj->last_frame_update = SDL_GetTicks();
        }
    }else{
        obj->current_frame = 0;
    }
}
