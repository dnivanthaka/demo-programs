/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Tryout 01
 *
 *        Version:  1.0
 *        Created:  04/27/2013 09:13:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "globals.h"
#include "video.h"
#include "input.h"


//extern const int SCREEN_WIDTH;
//extern const int SCREEN_HEIGHT;
//extern const int SCREEN_BPP;
//extern const int GAME_FRAME_RATE_HZ;
//const int SCREEN_HEIGHT       = 320;
//const int SCREEN_BPP          = 32;
//const int GAME_FRAME_RATE_HZ  = 30;

SDL_Surface *screen       = NULL;
SDL_Surface *background   = NULL;
SDL_Surface *sprite_sheet = NULL;

//SDL_Event event;

bool gameIsRunning = true;
//extern SDL_Event event;

//extern bool gameIsRunning;
//extern bool keyevents[];

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
    Uint32 last_frame_update;
    SDL_Rect *frames;
    SDL_Surface *background;
    bool is_visible;
    bool first_time;
};

bool
load_resources()
{
    sprite_sheet = load_image( "assets/bouncing.bmp" );

    if( sprite_sheet == NULL )
        return false;

    background = load_image( "assets/back1.jpg" );

    if( background == NULL )
        return false;
    return true;
}

void
clean_up()
{
    SDL_FreeSurface( sprite_sheet );
    SDL_FreeSurface( background );
    SDL_FreeSurface( screen );

    SDL_Quit();
}


int
main( int argc, char *argv[] )
{
    Uint32 last_updated;

    if( init( &screen ) == false ){
        fprintf(stderr, "Unable to create window.\n%s", SDL_GetError());
        return -1;
    }

    if( load_resources() == false ){
        fprintf(stderr, "Unable to load resource(s).\n%s", SDL_GetError());
        return -1;
    }

    for( int i = 0; i < 323; i++ )
    {
        keyevents[i] = false;
    }


    // creating the main character -----------------------------
    struct entity penguin;
    penguin.x                 = 0;
    penguin.y                 = 0;
    penguin.vel_x             = 0;
    penguin.vel_y             = 0;
    penguin.width             = 32;
    penguin.height            = 32;
    penguin.max_frames        = 8;
    penguin.current_frame     = 0;
    penguin.animation_fps     = 16;
    penguin.last_frame_update = 0;
    penguin.is_visible        = true;
    penguin.first_time        = true;
    penguin.frames = new SDL_Rect[8];
    for(int i=0;i<8;i++){
        penguin.frames[i].x = i * penguin.width;
        //penguin.frames[i].x = 32;
        penguin.frames[i].y = 0;
        penguin.frames[i].w = penguin.width;
        penguin.frames[i].h = penguin.height;
    }
    penguin.background = SDL_CreateRGBSurface(SDL_SWSURFACE, penguin.width, 
            penguin.height, SCREEN_BPP, screen->format->Rmask, 
            screen->format->Gmask, screen->format->Bmask, 
            screen->format->Amask );
    //----------------------------------------------------------


    last_updated = SDL_GetTicks();
    int i = 0;
    int j = 0;

    SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
    //apply_surface( 0, 0, background, screen );
    // Putting the penguin in mid screen
    penguin.x = SCREEN_WIDTH / 2  - penguin.width / 2;
    penguin.y = SCREEN_HEIGHT / 2 - penguin.height / 2;
    SDL_Rect tmp;
    
    while( gameIsRunning ){
        static int last_tick = SDL_GetTicks();
        int this_tick = SDL_GetTicks();
        //SDL_Delay(1000);

        if( last_tick == this_tick ){
            SDL_Delay(1);
            continue;
        }

        while( last_tick < this_tick ){

            handle_events();

            if( keyevents[ SDLK_LEFT ] ){
                penguin.vel_x = -1;
            }else{
                if( penguin.vel_x < 0 )
                    penguin.vel_x = 0;
            }

            if( keyevents[ SDLK_RIGHT ] ){
                penguin.vel_x = 1;
            }else{
                if( penguin.vel_x > 0 )
                    penguin.vel_x = 0;
            }


            if( penguin.vel_x > 0 && penguin.x >= (SCREEN_WIDTH / 2  - penguin.width / 2) ){
                //penguin.x += penguin.vel_x;
                j += penguin.vel_x;
                //penguin.x = (SCREEN_WIDTH / 2  - penguin.width / 2);
            }else{
                //j += penguin.vel_x;
                penguin.x += penguin.vel_x;
            }
            penguin.y += penguin.vel_y;

            // handle collisions

            last_tick += 1000 / GAME_PHYSICS_HZ;

        }

        // ------------------------------------------------------
        i = i % 8;
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //apply_surface( 100, 100, , screen, &penguin.frames[i] );

        int rem_time = last_tick - this_tick;


        //while( rem_time > 0 ){
        // Drawing the background
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //SDL_Rect tmp;
        tmp.w = background->w - j;
        //fprintf(stdout, "%d\n", tmp.w);
        tmp.h = background->h;
        tmp.x = j;
        tmp.y = 0;
        apply_surface( 0, 0, background, screen, &tmp );
        tmp.w = j;
        //fprintf(stdout, "%d\n", tmp.w);
        tmp.h = background->h;
        tmp.x = 0;
        tmp.y = 0;
        apply_surface( screen->w - j, 0, background, screen, &tmp );
        //j++; 
        /*
        if( j >= screen->w ){
            j = 0;
        }
        */

        j = j % screen->w;
        // Restoring previous background
        /*
        if( !penguin.first_time ){
            //apply_surface( penguin.x, penguin.y, penguin.background, screen );
        }else{
            penguin.first_time = false;
        }*/
        // Saving new background --------------------------------
        //SDL_Rect tmp;
        tmp.w = penguin.width;
        tmp.h = penguin.height;
        tmp.x = penguin.x;
        tmp.y = penguin.y;
        apply_surface( 0, 0, screen, penguin.background, &tmp );
        //apply_surface( 0, 0, background, penguin.background, &tmp );
        //-------------------------------------------------------

        // Animation
        if( (SDL_GetTicks() - penguin.last_frame_update) >= (1000.f / penguin.animation_fps) ){
            penguin.current_frame = (penguin.current_frame + 1) % penguin.max_frames;
            penguin.last_frame_update = SDL_GetTicks();
            //printf("XXXX\n");
        }
        //else{
            //penguin.last_frame_update = SDL_GetTicks();
            //printf("YYYY\n");
        //}


        //apply_surface( 100, 100, sprite_sheet, screen, &penguin.frames[i] );
        //apply_surface( penguin.x, penguin.y, sprite_sheet, screen, &penguin.frames[i] );
        apply_surface( penguin.x, penguin.y, sprite_sheet, screen, &penguin.frames[ penguin.current_frame ] );
        //apply_surface( 0, 0, penguin.background, screen );
        SDL_Flip( screen );

        // Deleting the penguin
        //apply_surface( penguin.x, penguin.y, background, screen, &tmp );
        apply_surface( penguin.x, penguin.y, penguin.background, screen );
        //SDL_Rect tmp;
        //tmp.w = penguin.width;
        //tmp.h = penguin.height;
        //tmp.x = penguin.x;
        //tmp.y = penguin.y;
        //apply_surface( penguin.x, penguin.y, background, screen, &tmp );

        // Frame rate capping
        //SDL_Delay(30);
        i++;

        //rem_time -= 1000 / GAME_FRAME_RATE_HZ;
        //}
    }

    clean_up();

    return 0;
}
