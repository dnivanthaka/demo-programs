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
#include "SDL/SDL.h"

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

SDL_Surface 
*load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL;

    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void
apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool
init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
        return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
        return false;

    SDL_WM_SetCaption( "Event Test", NULL );

    return true;
}

bool
load_files()
{
    image = load_image( "" );

    if( image == NULL )
        return false;

    return true;
}

void
clean_up()
{
    SDL_FreeSurface( image );

    SDL_Quit();
}

int
main ( int argc, char *argv[] )
{
    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
