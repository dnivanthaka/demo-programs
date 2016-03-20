/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Event Driven programming in SDL
 *
 *        Version:  1.0
 *        Created:  12/21/2011 10:19:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *background   = NULL;
SDL_Surface *state_image  = NULL;
SDL_Surface *screen       = NULL;

//SDL_Surface *message      = NULL;
//SDL_Surface *upMessage    = NULL;
//SDL_Surface *downMessage  = NULL;
//SDL_Surface *leftMessage  = NULL;
//SDL_Surface *rightMessage = NULL;

SDL_Event event;

//TTF_Font *font = NULL;

//SDL_Color textColor = { 255, 255, 255 };

SDL_Rect clip[ 4 ];

SDL_Surface 
*load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL;

    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        if( optimizedImage != NULL ){
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void
apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool
init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
        return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
        return false;

    SDL_WM_SetCaption( "Mouse States TryOut", NULL );

    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = 640 / 2;
    clip[0].h = 480 / 2;

    clip[1].x = 640 / 2;
    clip[1].y = 0;
    clip[1].w = 640 / 2;
    clip[1].h = 480 / 2;

    clip[2].x = 0;
    clip[2].y = 480 / 2;
    clip[2].w = 640 / 2;
    clip[2].h = 480 / 2;

    clip[3].x = 640 / 2;
    clip[3].y = 480 / 2;
    clip[3].w = 640 / 2;
    clip[3].h = 480 / 2;    

    return true;
}

bool
load_files()
{
    background = load_image( "background.png" );
    //dots        = load_image( "dots.png" );

    state_image = load_image( "button.png" );

    if( background == NULL )
        return false;

    if( state_image == NULL )
        return false;

    return true;
}

void
clean_up()
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( state_image );
    //SDL_FreeSurface( dots );
    
    //TTF_CloseFont( font );

    //TTF_Quit();

    SDL_Quit();
}

int
main ( int argc, char *argv[] )
{
    bool quit = false;

    if( init() == false )
        return EXIT_FAILURE;
    if( load_files() == false )
        return EXIT_FAILURE;

    //upMessage    = TTF_RenderText_Solid( font, "Up was pressed.", textColor );
    //downMessage  = TTF_RenderText_Solid( font, "Down was pressed.", textColor );
    //leftMessage  = TTF_RenderText_Solid( font, "Left was pressed.", textColor );
    //rightMessage = TTF_RenderText_Solid( font, "Right was pressed.", textColor );

    apply_surface( 0, 0, background, screen );

    while( quit == false ){
        if( SDL_PollEvent( &event ) ){
                //if( message != NULL ){
                if( event.type == SDL_MOUSEMOTION ){
                    int x = 0, y = 0;

                    x = event.motion.x;
                    y = event.motion.y;

                    if( (x > 0) && (x < 640) && (y > 0) && (y < 480) ){
                        apply_surface( ( (SCREEN_WIDTH / 2) - (state_image->w / 4) ), ( (SCREEN_HEIGHT / 2) - (state_image->h / 4) ), state_image, screen, &clip[0] );
                    }else{
                        apply_surface( ( (SCREEN_WIDTH / 2) - (state_image->w / 4) ), ( (SCREEN_HEIGHT / 2) - (state_image->h / 4) ), state_image, screen, &clip[1] );
                    }
                }
                //apply_surface( ( SCREEN_WIDTH - state_image->w ) / 2, ( SCREEN_HEIGHT - state_image->h ) / 2, state_image, screen );
                //} 
                if( SDL_Flip( screen ) == -1 )
                {
                    return EXIT_FAILURE;
                }
            if( event.type == SDL_QUIT ){
                quit = true;
            }
        }
    }
    


    //SDL_Delay(5000);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
