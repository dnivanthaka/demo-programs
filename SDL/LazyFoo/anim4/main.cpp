/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Event Driven programming in SDL
 *    URL to Refer: http://www.libsdl.org/cgi/docwiki.cgi/Time_Examples
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
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <sstream>

#define TICK_INTERVAL 30

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *sprites    = NULL;
SDL_Surface *screen     = NULL;

SDL_Event event;

static Uint32 next_time;

TTF_Font *font = NULL;

SDL_Color textColor = { 255, 255, 255 };

SDL_Rect clip[ 4 ];

bool leftdown;
bool rightdown;
bool updown;

SDL_Surface 
*load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL;

    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        if( optimizedImage != NULL ){
            //Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
            //SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey );
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


    TTF_Init();

    SDL_WM_SetCaption( "Blitting", NULL );

    return true;
}

bool
load_files()
{
    sprites = load_image( "background.png" );

    if( sprites == NULL )
        return false;


    return true;
}

bool
handle_events( int *v )
{
    bool quit = false;
    static bool inc, dec;
    
   while( SDL_PollEvent( &event ) ){
           //if( message != NULL ){
       if( event.type == SDL_KEYDOWN ){

           /*
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
           */
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               //(*v)++;
               //fprintf( stderr, "Y" );
               //inc = true;
               rightdown = true;
               break;
               case SDLK_LEFT:
               //(*v)++;
               //fprintf( stderr, "X" );
               //dec = true;
               leftdown = true;
               break;
               case SDLK_UP:
               updown = true;
               break;
           }
       }

// Fix this -> read only SDLK_RIGHT
// Do not fix this :) Its ok to have this
       else if( event.type == SDL_KEYUP ){
           //inc = false;
           //fprintf( stderr, "Im here" );
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               //(*v)++;
               //inc = false;
               rightdown = false;
               break;
               case SDLK_LEFT:
               //(*v)++;
               //dec = false;
               leftdown = false;
               break;
               case SDLK_UP:
               updown = false;
               break;
           }
       }

       if( event.type == SDL_QUIT ){
           quit = true;
       }

       //fprintf( stderr, "I" );
    }
    /*
    if( inc == true )
       (*v)++;
    */

    /*
    if( dec == true && *v > 0 )
       (*v)--;
    */
    return quit;
}

Uint32
time_left( void )
{
    Uint32 now;

    now = SDL_GetTicks();

    if( next_time <= now )
        return 0;
    else
        return next_time - now;
}

void
clean_up()
{    
    SDL_FreeSurface( background );
    SDL_FreeSurface( sprite_image );
    SDL_FreeSurface( screen );

    //SDL_FreeSurface( dots );

    
    TTF_CloseFont( font );

    TTF_Quit();

    //TTF_Quit();

    SDL_Quit();
}

void
draw(){

    static int i = 210;

    SDL_Rect tmp2;

    tmp2.x = 210;

    if(i == (210 + 90))
        i = 210;

    if(i == (180 - 90))
        i = 180;

    if( rightdown ){
        tmp2.x = (i + 30);
        i = tmp2.x;
    }

    if( leftdown ){
        tmp2.x = (i - 30);
        i = tmp2.x;
    }

    if( updown )
        tmp2.x = 210 + 150;

    tmp2.y = 0;
    tmp2.w = 16;
    tmp2.h = 16;

    apply_surface( 100, 100, sprite_image2, screen, &tmp2 );
}

int
main ( int argc, char *argv[] )
{
    bool quit = false;
    int sprite_x = 0;
    int inc_val  = 0;
    char m[80];
    int u = 0;
    int bgX = 0;
    int bgY = 0;

    if( init() == false )
        return EXIT_FAILURE;
    if( load_files() == false )
        return EXIT_FAILURE;

    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = 32;
    clip[0].h = 32;

    //apply_surface( 0, 0, background, screen );
    apply_surface( 10, 10, sprite_image, screen, &clip[0] );
    //apply_surface( 10, 10, sprite_image, screen );
    if( SDL_Flip( screen ) == -1 )
    {
        return EXIT_FAILURE;
    }

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    while( quit == false ){

        SDL_Rect tmp;
        SDL_Rect tmp2;
        
        tmp.x = sprite_x;
        tmp.y = 0;
        tmp.w = 32;
        tmp.h = 32;

        quit = handle_events( &inc_val );

        tmp2.x = 210 + 150;
        tmp2.y = 0;
        tmp2.w = 16;
        tmp2.h = 16;

        if( rightdown )
            inc_val++;

        if( inc_val > 0 && leftdown )
            inc_val--;

        //rightdown = false;
        //leftdown = false;

        //
        //fprintf(stderr, "x = %d\n", sprite_x);

        sprintf( m, "%d", inc_val );

        message = TTF_RenderText_Solid( font, m, textColor );

        SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0, 0, 0 ) );
        //apply_surface( 10, 10, sprite_image, screen, &tmp );
        //apply_surface( 100, 100, sprite_image2, screen, &tmp2 );
        draw();

        bgX -= 2;

        if( bgX <= -background->w ){
            bgX = 0;
        }
        /*
        if( !updown && u != 50 ){
            u = 100;

        }
        */
        apply_surface( bgX, bgY, background, screen );
        apply_surface( bgX + background->w, bgY, background, screen );
        apply_surface( 50, 50, message, screen );
        //apply_surface( 10, 10, sprite_image, screen );
        if( SDL_Flip( screen ) == -1 )
        {
            return EXIT_FAILURE;
        }

        sprite_x = (sprite_x + 32) % 256;
        //SDL_Delay(30);
        SDL_Delay( time_left() );
        //SDL_free( tmp );
        next_time += TICK_INTERVAL;
    }

    //SDL_Delay(5000);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
