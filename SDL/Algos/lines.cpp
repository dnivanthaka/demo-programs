#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include <sstream>

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

SDL_Surface *screen     = NULL;

SDL_Event event;

bool
init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
        return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
        return false;

    SDL_WM_SetCaption( "Blitting", NULL );

    return true;
}

bool
handle_events()
{
    bool quit = false;
    
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
       }
       if( event.type == SDL_QUIT ){
           quit = true;
       }
    }

    return quit;
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 
getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void 
putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void
clean_up()
{    
    SDL_FreeSurface( screen );
    SDL_Quit();
}

void 
put_pixel_ex()
{
/* Code to set a yellow pixel at the center of the screen */

    int x, y;
    Uint32 yellow;

    /* Map the color yellow to this display (R=0xff, G=0xFF, B=0x00)
       Note:  If the display is palettized, you must set the palette first.
    */
    yellow = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00);

    x = screen->w / 2;
    y = screen->h / 2;

    /* Lock the screen for direct access to the pixels */
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

    putpixel(screen, x, y, yellow);

    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
    /* Update just the part of the display that we've changed */
    SDL_UpdateRect(screen, x, y, 1, 1);

    return;
}

void
draw_line( SDL_Surface *surface, Uint32 color, int x1, int y1, int x2, int y2 )
{
    int dx, dy, inc_e, inc_ne, d, slope, x, y;

    if( x1 > x2 ){
        draw_line( surface, color, x2,  y2, x1, y1 );
        return;    
    }

    dx = x2 - x1;
    dy = y2 - y1;

    if( dy < 0 ){
        slope = -1;
        dy = -dy;
    }else{
        slope = 1;
    }
    

    inc_e  = 2 * dy;
    inc_ne = 2 * dy - 2 * dx;
    d      = 2 * dy - dx;
    y      = y1;

    for( x = x1; x <= x2; x++ ){
        putpixel( screen, x, y, color );

        if(d <= 0){
            d += inc_e;
        }else{
            d += inc_ne;
            y += slope;
        }
    }
}

int
main ( int argc, char *argv[] )
{
    bool quit = false;
    Uint32 color;

    if( init() == false )
        return 1;

    color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );

    while( quit != true ){
        quit = handle_events();
        draw_line( screen, color, 1, 1, 100, 100 );
        SDL_Flip( screen );
    }


    return 0;
}
