// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <math.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS  = 90;
const int FPMS = FPS / 1000;

SDL_Surface *screen = NULL;
SDL_Surface *blit_1 = NULL;
SDL_Surface *stage_objects;
SDL_Event event;
bool gameRunning = true;

#define PI 3.142

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_events();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void handle_input();
void draw_circle();

int 
main(int argc, char *argv[])
{
    SDL_Rect tux;
    SDL_Rect char_rect;
    Uint32 start_time;
    SDL_Rect tmp;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "SDL Examples", NULL );

    blit_1 = loadImage( "mario3.png" );

    if( blit_1 != NULL ){
        tmp.w = 10;
        tmp.h = 10;
        tmp.x = (SCREEN_WIDTH / 2) - ( tmp.w / 2 );
        tmp.y = (SCREEN_HEIGHT / 2) - ( tmp.h / 2 );

        short i = 0;
        int mv_amt_x = 1;
        int mv_amt_y = 1;
        int frameToDraw = 0;
        Uint32 anim_time;
        Uint32 numTicks = 0;
        start_time = SDL_GetTicks();
        anim_time = start_time;

        //draw_circle();
        //SDL_Flip( screen );

        while( gameRunning ){
            
            // handle input
            handle_input();
            // logic
                        
            // rendering
 
            //SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
            //SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
            draw_circle();
            //SDL_BlitSurface( blit_1, NULL, screen, NULL );
            SDL_Flip( screen );

            /*            
            if( tmp.y <= 0 ){
                mv_amt_y = 1;
            }else if(tmp.y >= (SCREEN_HEIGHT - tmp.h)){
                mv_amt_y = -1;
            }

            if( tmp.x <= 0 ){
                mv_amt_x = 1;
            }else if(tmp.x >= (SCREEN_WIDTH - tmp.w)){
                mv_amt_x = -1;
            }

            tmp.x += mv_amt_x;
            tmp.y += mv_amt_y;
            */
            
            
            if( SDL_GetTicks() - start_time < 1000 / FPS ){
            //if( SDL_GetTicks() - start_time < FPMS ){
                SDL_Delay( (1000 / FPS) - (SDL_GetTicks() - start_time) );
            }
            start_time = SDL_GetTicks();
            numTicks++;
        }
        //SDL_Delay(2000);
    }

    SDL_FreeSurface( blit_1 );
    SDL_FreeSurface( screen );

    return 0;
}

// -------------------------------------------------------------------------
// loadImage
//
// Creates a [screen] type optimized surface from given image file, doesnot handle alpha chanels. Supports color keying
//
// -------------------------------------------------------------------------
SDL_Surface* 
loadImage( std::string file, bool setColorKey, int r, int g, int b )
{
    SDL_Surface *src_img = NULL;
    SDL_Surface *dst_img = NULL;

    src_img = IMG_Load( file.c_str() );

    if( src_img != NULL ){
        if( setColorKey )
        SDL_SetColorKey( src_img, SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, r, g, b) );

        dst_img = SDL_DisplayFormat( src_img );
        SDL_FreeSurface( src_img );

        return dst_img;
        
    }else{
        return NULL;
    }
}

// -------------------------------------------------------------------------
// handle_events
//
// Handles inputs
//
// -------------------------------------------------------------------------
void
handle_input()
{
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_QUIT ){
            gameRunning = false;
        }
    }
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
draw_circle()
{
    int x, y;
    int length = 50;

    float angle = 0.0;
    float angle_stepsize = 0.1;

    while( angle < 2 * PI ){
        x = length * cos( angle );
        y = length * sin( angle );

        printf("%d\n", x);

        putpixel( screen, x + SCREEN_WIDTH / 2, y + SCREEN_HEIGHT / 2, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );

        angle += angle_stepsize;
    }
}

