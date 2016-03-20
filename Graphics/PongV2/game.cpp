/*
 * =====================================================================================
 *
 *       Filename:  game.cpp
 *
 *    Description:  Main game loop
 *
 *        Version:  1.0
 *        Created:  08/05/2012 05:05:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include "SDL/SDL.h"

#include "globals.h"
#include "paddle.h"
#include "ball.h"

SDL_Surface *screen = NULL;
SDL_Event event;
Paddle *left, *right;
Ball *ball;

bool keys_held[323];
bool game_is_running = true;

int init_graphics( int w, int h, int b, std::string caption );
void draw_objects();
void update_objects(float);
void cleanup();

// Event handling --------------------------------------------
void init_events();
void handle_events();
int key_pressed();
int key_released();
bool key_held( int );
//------------------------------------------------------------

int main( int argc, char *argv[] )
{
    unsigned int this_tick, last_tick;

    init_graphics( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, "Pong V2" );

    //Paddle *p;
    left  = new Paddle( 100, 100, 10, 50, 0, 0  );
    right = new Paddle( 500, 100, 10, 50, 0, 0  );
    //ball  = new Ball( 100, 100, 10, 50, 0, 0 );

    last_tick = SDL_GetTicks();

    while( game_is_running ){
        handle_events();

        this_tick = SDL_GetTicks();

        update_objects( (this_tick - last_tick) );
        last_tick = SDL_GetTicks();

        last_tick = this_tick;
        draw_objects();
        SDL_Flip( screen );
        right->erase( screen );
    }

    cleanup();

    return 0;
}

void cleanup()
{
    SDL_FreeSurface( screen );

    SDL_Quit();
}

int init_graphics( int w, int h, int b, std::string caption )
{
   if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER  ) < 0 ){
        std::cerr << "Failed to initialize SDL : " << __FILE__ << __LINE__ << std::endl;
        return -1;
   } 

   screen = SDL_SetVideoMode( w, h, b, SDL_SWSURFACE );

   if( screen == NULL ){
        std::cerr << "Failed to create Surface : " << __FILE__ << __LINE__ << std::endl;
        return -1;
   }

   SDL_WM_SetCaption( caption.c_str(), NULL );

   return 0;
}

void init_events()
{
    for(int i=0;i<323;i++){
        keys_held[i] = false;
    }
}

int key_pressed(){
    if( event.type == SDL_KEYDOWN ){
        return event.key.keysym.sym; 
    }

    return -1;
}

int key_released(){
    if( event.type == SDL_KEYUP ){
        return event.key.keysym.sym; 
    }

    return -1;
}

void handle_events()
{
    while( SDL_PollEvent(&event) ){
        if( event.type == SDL_KEYDOWN ){
            keys_held[ event.key.keysym.sym ] = true; 
        }else if( event.type == SDL_KEYUP ){
            keys_held[ event.key.keysym.sym ] = false; 
        }else if( event.type == SDL_QUIT ){
            game_is_running = false;
        }
    }
}

void update_objects(float dt)
{
    if( key_pressed() == SDLK_UP  ){
       right->setVelY( -dt ); 
    }else if( key_released() == SDLK_UP ){
       right->setVelY( dt ); 
    }

    right->setY( right->getY() + right->getVelY() ); 
}

void draw_objects()
{
   //left->draw( screen );
   right->draw( screen );
}
