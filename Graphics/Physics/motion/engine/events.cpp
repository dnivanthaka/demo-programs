/*
 * =====================================================================================
 *
 *       Filename:  events.cpp
 *
 *    Description:  Handles the events
 *
 *        Version:  1.0
 *        Created:  07/23/2012 09:55:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
include "globals.h"
include "events.h"

void
init_events()
{
    for(int i = 0; i < 323; i++){
        keys_held[i] = false;
    }
}

void
handle_events()
{
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_KEYDOWN ){
            keys_held[ event.key.keysym.sym ] = true;
        }else if( event.type == SDL_KEYUP ){
            keys_held[ event.key.keysym.sym ] = false;
        }else if( event.type == SDL_QUIT ){
            gameIsRunning = false;
        }
    }
}

int
key_pressed()
{
    if( event.type == SDL_KEYDOWN ){
        return event.key.keysym.sym;
    }

    return -1;
}

bool
key_held(int key)
{
    return keys_held[ key ];
}

