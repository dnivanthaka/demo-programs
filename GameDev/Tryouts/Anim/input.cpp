/*
 * =====================================================================================
 *
 *       Filename:  input.cpp
 *
 *    Description:  Input Handling
 *
 *        Version:  1.0
 *        Created:  05/05/2013 06:36:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include "SDL/SDL.h"

#include "input.h"
#include "globals.h"

SDL_Event event;
bool keyevents[323];

void
handle_events()
{

while( SDL_PollEvent(&event) ){
    switch( event.type ){
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
                    //penguin.vel_x = -1;
                    keyevents[ SDLK_LEFT ] = true;
                    break;
                case SDLK_RIGHT:
                    //penguin.vel_x = 1;
                    keyevents[ SDLK_RIGHT ] = true;
                    break;
                case SDLK_UP:
                    //penguin.vel_y = -1;
                    keyevents[ SDLK_UP ] = true;
                    break;
                case SDLK_DOWN:
                    //penguin.vel_y = 1;
                    keyevents[ SDLK_DOWN ] = true;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
                    //if( penguin.vel_x < 0 )
                        //penguin.vel_x = 0;
                    keyevents[ SDLK_LEFT ] = false;
                    break;
                case SDLK_RIGHT:
                    //if( penguin.vel_x > 0 )
                        //penguin.vel_x = 0;
                    keyevents[ SDLK_RIGHT ] = false;
                    break;
                case SDLK_UP:
                    //if(penguin.vel_y < 0){
                        //penguin.vel_y = 0;
                    //}
                    keyevents[ SDLK_UP ] = false;
                    break;
                case SDLK_DOWN:
                    //if(penguin.vel_y > 0){
                        //penguin.vel_y = 0;
                    //}
                    keyevents[ SDLK_DOWN ] = false;
                    break;
                case SDLK_ESCAPE:
                    gameIsRunning = false;
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            gameIsRunning = false;
            break;
        default:
            break;
    }

}

}
