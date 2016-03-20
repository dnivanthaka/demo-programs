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

SDL_Surface *background = NULL;
SDL_Surface *screen     = NULL;

SDL_Surface *message      = NULL;
SDL_Surface *upMessage    = NULL;
SDL_Surface *downMessage  = NULL;
SDL_Surface *leftMessage  = NULL;
SDL_Surface *rightMessage = NULL;

SDL_Event event;

TTF_Font *font = NULL;

SDL_Color textColor = { 255, 255, 255 };

//SDL_Rect clip[ 4 ];

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

    if( TTF_Init() == -1 ){
        fprintf(stderr, "Error loading ttf\n");
        return false;
    }

    SDL_WM_SetCaption( "TTF Test", NULL );

    return true;
}

bool
load_files()
{
    background = load_image( "background.png" );
    //dots        = load_image( "dots.png" );

    font = TTF_OpenFont( "lazy.ttf", 28 );

    if( background == NULL )
        return false;

    if( font == NULL )
        return false;

    return true;
}

void
clean_up()
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );
    //SDL_FreeSurface( dots );
    
    TTF_CloseFont( font );

    TTF_Quit();

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

    upMessage    = TTF_RenderText_Solid( font, "Up was pressed.", textColor );
    downMessage  = TTF_RenderText_Solid( font, "Down was pressed.", textColor );
    leftMessage  = TTF_RenderText_Solid( font, "Left was pressed.", textColor );
    rightMessage = TTF_RenderText_Solid( font, "Right was pressed.", textColor );

    while( quit == false ){
    if( SDL_PollEvent( &event ) ){
        if( event.type == SDL_KEYDOWN ){
            switch( event.key.keysym.sym ){
                case SDLK_UP : message = upMessage; break;
                case SDLK_DOWN: message = downMessage; break;
                case SDLK_LEFT: message = leftMessage; break;
                case SDLK_RIGHT: message = rightMessage; break;
            }

            if( message != NULL ){
                apply_surface( 0, 0, background, screen );
                apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
            } 
            if( SDL_Flip( screen ) == -1 )
            {
                return EXIT_FAILURE;
            }
        }else if( event.type == SDL_QUIT ){
            quit = true;
        }
    }
    }
    


    //SDL_Delay(5000);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
