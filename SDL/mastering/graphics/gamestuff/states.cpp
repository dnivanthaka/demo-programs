// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <fstream>
#include <string>
#include <stack>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS           = 60;
const int FPMS          = FPS / 1000;
const int TILE_WIDTH    = 16;
const int TILE_HEIGHT   = 16;
const int NUM_TILES_X   = SCREEN_WIDTH / TILE_WIDTH;
const int NUM_TILES_Y   = SCREEN_HEIGHT / TILE_HEIGHT;

SDL_Surface *screen = NULL;
SDL_Surface *image1 = NULL;
SDL_Surface *image2 = NULL;
SDL_Event event;
bool gameRunning = true;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_input();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void mainSplash();
void mainMenu();
//void (*state_ptr)();

struct state_t {
    void (*state_ptr)();
};

std::stack<state_t> g_gameStates;

SDL_Rect dot;

int 
main(int argc, char *argv[])
{
    int i, j;
    Uint32 start_time = 0, numTicks = 0;
    SDL_Rect src, dest;
    state_t menu;
    
    dot.x = 0;
    dot.y = 0;

    //star_t stars[ num_stars ];
    //frame_t container;

    // seeding the rand generator
    srand( (unsigned)time( NULL ) );

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "SDL Examples", NULL );

    //image1 = loadImage( "pic1.png" );
    image1 = loadImage( "Tux.png" );
    

    i = 0;

    menu.state_ptr = mainSplash;
    g_gameStates.push( menu );

    while( !g_gameStates.empty() ){
        
        //handle_input();

        //SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
        //SDL_BlitSurface( image1, (player.spr.f_ptr + player.spr.frame_idx), screen, &tux );


        //SDL_Flip( screen );

        g_gameStates.top().state_ptr();

        SDL_Flip( screen );

        start_time = SDL_GetTicks();
        numTicks++;
    }
    SDL_FreeSurface( screen );
    SDL_FreeSurface( image1 );

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
mainSplash()
{
    //while( gameRunning ){

        while( SDL_PollEvent( &event ) ){
            if( event.type == SDL_KEYDOWN ){
                switch( event.key.keysym.sym ){
                    case SDLK_ESCAPE:
                    state_t menu;
                    menu.state_ptr = mainMenu;
                    g_gameStates.push( menu );
                    break;
                };
            }else if( event.type == SDL_QUIT ){
                gameRunning = false;
                g_gameStates.pop();
            }
        }

        SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
        //SDL_BlitSurface( image1, NULL, screen, NULL );

        
    //}

    //g_gameStates.pop();
}

void
mainMenu()
{
    SDL_Rect tmp;
    //while( gameRunning ){
        //handle_input();

        //SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
        //SDL_BlitSurface( image1, NULL, screen, NULL );

        //SDL_Flip( screen );
    //}

    //g_gameStates.pop();
     tmp.w = 250;
     tmp.h = 150;
     tmp.x = (SCREEN_WIDTH / 2) - ( tmp.w / 2 );
     tmp.y = (SCREEN_HEIGHT / 2) - ( tmp.h / 2 );

     dot.w = 10;
     dot.h = 10;
     if( dot.x == 0 ){
        dot.x = tmp.x + 10;
        dot.y = tmp.y + 10;
     }
     while( SDL_PollEvent( &event ) ){
            if( event.type == SDL_KEYDOWN ){
                switch( event.key.keysym.sym ){
                    case SDLK_ESCAPE:
                    //state_t menu;
                    //menu.state_ptr = mainMenu;
                    //g_gameStates.push( menu );
                    //if( menuOn ){ 
                        //menuOn = false;
                        g_gameStates.pop();
                    //}else{ 
                        //menuOn = true;
                    //}
                    break;
                    case SDLK_UP:
                    dot.y -= dot.h;
                    break;
                    case SDLK_DOWN:
                    dot.y += dot.h;
                    break;
                };
            }else if( event.type == SDL_QUIT ){
                //gameRunning = false;
                g_gameStates.pop();
                g_gameStates.pop();
            }
     }

    //if( !menuOn ){
        SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0, 0, 0xFF) );
        SDL_FillRect( screen, &dot, SDL_MapRGB(screen->format, 0, 0, 0) );
        //menuOn = true;
    //}else{
        //SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
    //}
}
