/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main launcher
 *
 *        Version:  1.0
 *        Created:  09/16/2014 10:08:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <iostream>

#include "SDL/SDL.h"
#include "config.h" 
#include "types.h"
#include "video.h"
#include "layout.h"
#include "thing.h"

//-------------------------------------------------------------------------------------
void init();
void load_resources();
SDL_Surface *load_image( char *filename );
void handle_events();
void handle_events2();
void move_objects();
void handle_collisions();
void update_screen();
void remove_objects();
void cleanup();
//-------------------------------------------------------------------------------------

bool gameIsRunning = true;
SDL_Event event;
struct thing player;
SDL_Surface *box1;

int main(int argc, char *argv[])
{
    init(); 
    load_resources();
    //init_objects();
    //std::cout << box1_x << std::endl;

    while( gameIsRunning ){
        handle_events();
        handle_collisions();
        move_objects();
        update_screen();

        SDL_Flip( screen );

        remove_objects();

        SDL_Delay(10);
    }

    cleanup();

    return 0;
}

void init()
{
    init_screen();
    init_layout();
    init_thing(&player, true);

    set_pos_thing( &player, 32, SCREEN_HEIGHT - 64 );
}

void load_resources()
{
    //box1 = load_image( "right_gr1.bmp" );
    /*
    box2 = load_image( "right_gr1.bmp" );
    if( box2 == NULL ){
        std::cerr << "Error loading resource. " << std::endl;
        exit(1);
    }

    //Setting initial coords, this should be done in a seperate function

    box1_x = (SCREEN_WIDTH / 2) - (32 / 2);
    box1_y = (SCREEN_HEIGHT / 2) - (32 / 2);
    box2_x = (SCREEN_WIDTH / 2) - (32 / 2) + 32;
    box2_y = (SCREEN_HEIGHT / 2) - (32 / 2);

    box1_back = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, SCREEN_BPP, screen->format->Rmask, screen->format->Gmask, 
            screen->format->Bmask, screen->format->Amask);
*/
    player.sprites = load_image( "right_gr1.bmp" );
    player.back    = SDL_CreateRGBSurface(SDL_SWSURFACE, TILE_SIZE, TILE_SIZE, SCREEN_BPP, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
    draw_layout(screen);
}

void handle_events()
{
    while( SDL_PollEvent(&event) ){
        switch( event.type ){
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE ){
                    gameIsRunning = false; 
                }
                handle_events_thing(&player, &event);
                break;
            case SDL_KEYUP:
                handle_events_thing(&player, &event);
                break;

            default:
                //std::cerr << "Not implemented event." << std::endl;
            ;
        }
    }
}


void handle_events2()
{
    while( SDL_PollEvent(&event) ){
        switch( event.type ){
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE ){
                    gameIsRunning = false; 
                }
                if( event.key.keysym.sym == SDLK_RIGHT ){
                    /*
                    if( box1_jumping ){
                        box1_xvel = 2;
                    }else{
                        box1_xvel = 1; 
                    }
                    */
                }
                if( event.key.keysym.sym == SDLK_LEFT ){
                    /*
                    if( box1_jumping ){
                        box1_xvel = -2;
                    }else{
                        box1_xvel = -1;
                    }
                    */
                }
                if( event.key.keysym.sym == SDLK_UP ){
                    /*
                    if( !box1_jumping ){
                        box1_yvel   = -16;
                        box1_yaccel = 1;

                        box1_jumping = true;
                        std::cout << box1_yaccel << std::endl;
                    }
                    */
                }
                break;
            case SDL_KEYUP:
                if( event.key.keysym.sym == SDLK_RIGHT ){
                    //box1_xvel = 0;
                }
                if( event.key.keysym.sym == SDLK_LEFT ){
                    //box1_xvel = 0;
                }
                break;

            default:
                //std::cerr << "Not implemented event." << std::endl;
            ;
        }
    }
}

void handle_collisions()
{
    handle_collisions_thing(&player);

    update_state_thing(&player);
}

void move_objects()
{
    /*
    box1_xvel += box1_xaccel;
    box1_yvel += box1_yaccel;

    box1_x += box1_xvel;
    box1_y += box1_yvel;

    box2_x += box2_xvel;
    box2_y += box2_yvel;
    */
    //set_vel_thing(&player, 1, 0);
}

void remove_objects()
{
    /*
    SDL_Rect tmp;

    tmp.x = box1_x;
    tmp.y = box1_y;
    tmp.w = 32;
    tmp.h = 32;

    // Blitting object
    SDL_BlitSurface(box1_back, NULL, screen, &tmp);
    */
    erase_thing( &player, screen );
}

void update_screen()
{
    /*
    SDL_Rect tmp;

    tmp.x = box1_x;
    tmp.y = box1_y;
    tmp.w = 32;
    tmp.h = 32;

    // Saving background
    SDL_BlitSurface(screen, &tmp, box1_back, NULL);
    // Blitting object
    SDL_BlitSurface(box1, NULL, screen, &tmp);
    //tmp.x = tmp.x + 32;
    tmp.x = box2_x;
    tmp.y = box2_y;
    //tmp.y = tmp.y + 32;
    SDL_BlitSurface(box2, NULL, screen, &tmp);
    */
    //draw_layout(screen);
    //SDL_BlitSurface(box1, NULL, screen, NULL);
    //SDL_BlitSurface(player.sprites, NULL, screen, NULL);
    draw_thing(&player, screen);
}

void cleanup()
{
    /*
    SDL_FreeSurface(screen);
    SDL_FreeSurface(box1);
    SDL_FreeSurface(box2);
    SDL_FreeSurface(box1_back);
    */
    cleanup_screen();
    cleanup_layout();
    cleanup_thing( &player );

    SDL_Quit();
}
