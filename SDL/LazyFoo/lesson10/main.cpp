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
#include "SDL/SDL_mixer.h"

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *background   = NULL;
SDL_Surface *state_image  = NULL;
SDL_Surface *screen       = NULL;

Mix_Music *music   = NULL;

Mix_Chunk *scratch = NULL;
Mix_Chunk *high    = NULL;
Mix_Chunk *med     = NULL;
Mix_Chunk *low     = NULL;

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

    SDL_WM_SetCaption( "Audio TryOut", NULL );

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }    

    return true;
}

bool
load_files()
{
    background = load_image( "background.png" );
    //dots        = load_image( "dots.png" );

    //state_image = load_image( "button.png" );

    if( background == NULL )
        return false;

    music = Mix_LoadMUS( "beat.wav" );

    if( music == NULL )
        return false;

    scratch = Mix_LoadWAV( "scratch.wav" );
    high    = Mix_LoadWAV( "high.wav" );
    med     = Mix_LoadWAV( "medium.wav" );
    low     = Mix_LoadWAV( "low.wav" );

    if( scratch == NULL || high == NULL || med == NULL || low == NULL ){
        return false;    
    }


    return true;
}

void
clean_up()
{    
    SDL_FreeSurface( background );
    //SDL_FreeSurface( state_image );

    Mix_FreeChunk( scratch );
    Mix_FreeChunk( high );
    Mix_FreeChunk( med );
    Mix_FreeChunk( low );
    //SDL_FreeSurface( dots );

    Mix_FreeMusic( music );
    
    //TTF_CloseFont( font );

    //TTF_Quit();

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

    apply_surface( 0, 0, background, screen );

    while( quit == false ){
        if( SDL_PollEvent( &event ) ){
                //if( message != NULL ){
            if( event.type == SDL_KEYDOWN ){

                if( event.key.keysym.sym == SDLK_1 ){
                    Mix_PlayChannel( -1, scratch, 0 );
                }else if( event.key.keysym.sym == SDLK_2 ){
                    Mix_PlayChannel( -1, high, 0 );
                }else if( event.key.keysym.sym == SDLK_3 ){
                    Mix_PlayChannel( -1, med, 0 );
                }else if( event.key.keysym.sym == SDLK_0 ){
                    Mix_HaltMusic();
                }else{
                    //
                }

                if( SDL_Flip( screen ) == -1 )
                {
                    return EXIT_FAILURE;
                }
            }
            if( event.type == SDL_QUIT ){
                quit = true;
            }
        }
    }

    //SDL_Delay(5000);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
