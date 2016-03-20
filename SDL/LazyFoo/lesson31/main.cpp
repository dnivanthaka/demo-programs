/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Surface Flipping in SDL
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

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *pat_image  = NULL;
SDL_Surface *screen       = NULL;

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

    SDL_WM_SetCaption( "Flipping TryOut", NULL );


    return true;
}

bool
load_files()
{
    pat_image = load_image( "corner.png" );
    //dots        = load_image( "dots.png" );

    //state_image = load_image( "button.png" );

    if( pat_image == NULL )
        return false;


    return true;
}

void
clean_up()
{    
    SDL_FreeSurface( pat_image );
    //SDL_FreeSurface( state_image );

    
    //TTF_CloseFont( font );

    //TTF_Quit();

    //TTF_Quit();

    SDL_Quit();
}

bool
handle_events()
{
    while( SDL_PollEvent( &event ) ){
        //if( message != NULL ){
        if( event.type == SDL_KEYDOWN ){

        }
        if( event.type == SDL_QUIT ){
            return true;
            break;
        }
    }
}

void
put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;

    pixels[ surface->w * y + x ] = pixel;
}

Uint32
get_pixel(SDL_Surface *surface, int x, int y)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;

    return pixels[ surface->w * y + x ];
}

SDL_Surface *
flip_surface( SDL_Surface *surface )
{
    SDL_Surface *flipped = NULL;
    
    if( surface->flags & SDL_SRCCOLORKEY ){
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, 
    surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }else{
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, 
    surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    if( SDL_MUSTLOCK( surface ) )
        SDL_LockSurface( surface );

    for( int x, rx = flipped->w; x < flipped->w; x++, rx--  ){
        for(int y = 0, ry = flipped->y - 1; y < flipped->h; y++, ry-- ){
             //Get pixel 
            Uint32 pixel = get_pixel32( surface, x, y ); 
            //Copy pixel 
            if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) ) { 
            put_pixel32( flipped, rx, ry, pixel ); 
            } else if( flags & FLIP_HORIZONTAL ) { 
                put_pixel32( flipped, rx, y, pixel ); 
            } else if( flags & FLIP_VERTICAL ) { 
               put_pixel32( flipped, x, ry, pixel ); 
            }
        }
    }

    if( SDL_MUSTLOCK( surface ) )
        SDL_UnlockSurface( surface );
}

int
main ( int argc, char *argv[] )
{
    bool quit = false;

    if( init() == false )
        return EXIT_FAILURE;
    if( load_files() == false )
        return EXIT_FAILURE;

    apply_surface( 0, 0, background, screen );

    while( quit == false ){
        quit = handle_events();
    }

    //SDL_Delay(5000);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
