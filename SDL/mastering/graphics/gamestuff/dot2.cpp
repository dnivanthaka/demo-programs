// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS = 100;
const int MAX_LOOPS = 4;
const int TICKS_PER_SEC = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SEC;
const float timestep = 1.0f/120.0f;
#define FIXED_DT 0.017f
#define MAX_DT 2.0f
//const int FPMS = FPS / 1000;

typedef struct {
    int x;
    int y;
} vel_t;

typedef struct {
    int x;
    int y;
} pos_t;

typedef struct {
    int w;
    int h;
} dim_t;

struct dot_t {
    pos_t pos;
    pos_t prev_pos;
    dim_t dim;
    vel_t vel;
    vel_t prev_vel;
};

SDL_Surface *screen = NULL;
SDL_Surface *court = NULL;
//SDL_Surface *stage_objects;
SDL_Event event;
bool gameRunning = true;

bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;

struct dot_t dot;

float remainder = 0.0f;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_events();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void handle_input();
void update();
void render();
void handle_wall_collisions();

int 
main(int argc, char *argv[])
{
    SDL_Rect tmp;

    dot.dim.w      = 10;
    dot.dim.h      = 10;
    dot.pos.x      = (SCREEN_WIDTH / 2) - (dot.dim.w / 2);
    dot.pos.y      = (SCREEN_HEIGHT / 2) - (dot.dim.h / 2);
    dot.prev_pos.x = (SCREEN_WIDTH / 2) - (dot.dim.w / 2);
    dot.prev_pos.y = (SCREEN_HEIGHT / 2) - (dot.dim.h / 2);
    dot.vel.x      = 0;
    dot.vel.y      = 0;
    dot.prev_vel.x = 0;
    dot.prev_vel.y = 0;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "Move the Dot", NULL );

        tmp.w = 10;
        tmp.h = 10;
        tmp.x = (SCREEN_WIDTH / 2) - ( tmp.w / 2 );
        tmp.y = (SCREEN_HEIGHT / 2) - ( tmp.h / 2 );

        while( gameRunning ){
            
            // handle input
            handle_input();
            // logic
                        
            // rendering
            update();
            handle_wall_collisions();
            render();

            SDL_Flip( screen );
    }

    SDL_FreeSurface( court );
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
         if( event.type == SDL_KEYDOWN ){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               dot.vel.x = 1;
               //right_pressed = true;
               break;
               case SDLK_LEFT:
               dot.vel.x = -1;
               //left_pressed = true;
               break;
               case SDLK_UP:
               dot.vel.y = -1;
               //up_pressed = true;
               break;
               case SDLK_DOWN:
               dot.vel.y = 1;
               //down_pressed = true;
               break;
           }
       }else if(event.type == SDL_KEYUP){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               if( dot.vel.x > 0 )
                   dot.vel.x = 0;
               //right_pressed = false;
               break;
               case SDLK_LEFT:
               if( dot.vel.x < 0 )
                   dot.vel.x = 0;
               //left_pressed = false;
               break;
               case SDLK_UP:
               if( dot.vel.y < 0 )
                   dot.vel.y = 0;
               //up_pressed = false;
               break;
               case SDLK_DOWN:
               if( dot.vel.y > 0 )
                   dot.vel.y = 0;
               //down_pressed = false;
               break;
            }
        }else if( event.type == SDL_QUIT ){
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
update(){
    static int last_tick = SDL_GetTicks();
    int this_tick = SDL_GetTicks();
    int loops = 0;

    if( this_tick <= last_tick ){
        SDL_Delay(1);
        return;
    }

    dot.prev_pos.x = dot.pos.x;
    dot.prev_pos.y = dot.pos.y;

    while( this_tick > last_tick && loops < 4 ){
        //printf("XXX");

        //dot.prev_vel.x = dot.vel.x;
        //dot.prev_vel.y = dot.vel.y;

        //dot.vel.x = 1;
        dot.pos.y += dot.vel.y;
        dot.pos.x += dot.vel.x;

        last_tick += 1000 / FPS;
        loops++;
    }
}

void
handle_wall_collisions()
{
    if( dot.pos.x < 0 ){
        dot.dim.w -= 1;
        dot.pos.x = 0;
        if( dot.dim.w <= 5 ) dot.dim.w = 5;
    }else if( dot.pos.x + dot.dim.w > SCREEN_WIDTH ){
         dot.pos.x = SCREEN_WIDTH - dot.dim.w;
         dot.dim.w -= 1;
         if( dot.dim.w <= 5 ) dot.dim.w = 5;
    }else if( dot.pos.x + dot.dim.w < SCREEN_WIDTH  ){
         dot.dim.w += 1;
         if( dot.dim.w >= 10 ) dot.dim.w = 10;
    }

    if( dot.pos.y < 0 ){
        dot.pos.y = 0;
    }else if( dot.pos.y + dot.dim.h > SCREEN_HEIGHT ){
        dot.pos.y = SCREEN_HEIGHT - dot.dim.h;
    }
}

void
render()
{
    SDL_Rect tmp;

    //float ratio = remainder / FIXED_DT;

    SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
    
    tmp.w = dot.dim.w;
    tmp.h = dot.dim.h;
    tmp.x = dot.prev_pos.x;
    tmp.y = dot.prev_pos.y;
    SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0, 0, 0) );
    //dot.pos.x = dot.pos.x * ratio + dot.prev_pos.x * (1 - ratio);
    // Drawing the new state, Left Paddle
    //paddles[0].pos.y += paddles[0].vel.y;
    //dot.pos.x += dot.vel.x;
    tmp.w = dot.dim.w;
    tmp.h = dot.dim.h;
    tmp.x = dot.pos.x;
    tmp.y = dot.pos.y;
    SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );

}
