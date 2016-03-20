// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS = 60;
const int MAX_LOOPS = 4;
const int TICKS_PER_SEC = 30;
const int SKIP_TICKS = 1000 / TICKS_PER_SEC;
const float timestep = 1.0f/120.0f;
const int PHYSICS_FPS = 60;

const int NUM_FLAKES = 100;

const int BALL_VEL_X = 200;
const int BALL_VEL_Y = 200;

const int NUM_CRITTERS = 200;

//const int FPMS = FPS / 1000;

typedef struct {
    float x;
    float y;
} vel_t;

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN
} dir_t;

typedef struct {
    float x;
    float y;
} pos_t;

typedef struct {
    int w;
    int h;
} dim_t;

struct thing {
    pos_t pos;
    pos_t prev_pos;
    dir_t x_dir;
    dir_t y_dir;
    dim_t dim;
    vel_t vel;
    SDL_Rect clip_rect;
    bool is_Visible;
};



SDL_Surface *screen = NULL;
//SDL_Surface *object = NULL;

struct thing player, enemy;
//struct thing enemy;

SDL_Event event;
bool gameRunning = true;

bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;

bool chasing = false;


SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_events();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void handle_input();
void move_objects();
void render(float);
void init_game();
void update_state();
void handle_ball_collisions();
void draw_walls();
void handle_clipping();
void determine_position();

int 
main(int argc, char *argv[])
{
    SDL_Rect tux;
    SDL_Rect char_rect;
    Uint32 next_game_tick;
    int loop;
    float accumulator;

    srand( time(NULL) );

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "Random Motion", NULL );

    //object = loadImage( "Tux_sm.png" );

    //if( alien != NULL ){

        init_game();

        while( gameRunning ){
            
            loop = 0;
            update_state();

            SDL_Flip( screen );
        //}
        //SDL_Delay(2000);
        }
    //}

    //SDL_FreeSurface( alien );
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
handle_input( )
{
    while( SDL_PollEvent( &event ) ){
         if( event.type == SDL_KEYDOWN ){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               //right_pressed = true;
               //creature.x_dir = RIGHT;
               player.vel.x = 10;
               break;
               case SDLK_LEFT:
               //left_pressed = true;
               //creature.x_dir = LEFT;
               player.vel.x = -10;
               break;
               case SDLK_UP:
               //up_pressed = true;
               //creature.y_dir = UP;
               player.vel.y = -10; 
               break;
               case SDLK_DOWN:
               //down_pressed = true;
               //creature.y_dir = DOWN;
               player.vel.y = +10;
               break;
           }
       }else if(event.type == SDL_KEYUP){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               //right_pressed = false;
               player.vel.x = 0;
               break;
               case SDLK_LEFT:
               //left_pressed = false;
               player.vel.x = 0;
               break;
               case SDLK_UP:
               //up_pressed = false;
               player.vel.y = 0;
               break;
               case SDLK_DOWN:
               //down_pressed = false;
               player.vel.y = 0;
               break;
            }
        }else if( event.type == SDL_QUIT ){
            gameRunning = false;
        }
    }
    //creature.vel.x = BALL_VEL_X * (dt / 1000.f);
    //creature.vel.y = BALL_VEL_Y * (dt / 1000.f);
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
render( float alpha )
{
    SDL_Rect tmp, tmp2;

    //printf("alpha = %f\n", alpha);

    // clearing old positions
    SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
    
    
    // make sure he is visible

        printf("alpha = %f\n", alpha);
        //tmp.w = flakes[ i ].dim.w;
        //tmp.h = flakes[ i ].dim.h;
        //tmp.x = (int)(flakes[ i ].pos.x + (flakes[ i ].vel.x * alpha ));
        //tmp.y = (int)(flakes[ i ].pos.y + (flakes[ i ].vel.y * alpha ));
        //tmp.y = (int)(creature.pos.y * alpha ) + (creature.prev_pos.y * (1 - alpha));
        tmp.w = enemy.dim.w;
        tmp.h = enemy.dim.h;
        tmp.x = (int)enemy.pos.x;
        tmp.y = (int)enemy.pos.y;
        //tmp.x = (int)(critters[i].pos.x * alpha ) + ((critters[i].pos.x - critters[i].vel.x) * (1 - alpha));
        //tmp.y = (int)(critters[i].pos.y * alpha ) + ((critters[i].pos.y - critters[i].vel.y) * (1 - alpha));
        printf("x = %d\n", tmp.x);
        printf("y = %d\n", tmp.y);

        if((int)tmp.y >= SCREEN_HEIGHT) {
            tmp.y = 0;
            //flakes[ i ].pos.y = 0;
            //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
        }

        if((int)tmp.x >= SCREEN_WIDTH) {
            tmp.x = 0;
            //flakes[ i ].pos.y = 0;
            //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
        }
       // SDL_BlitSurface( object, NULL, screen, &tmp );
        SDL_FillRect( screen, &tmp, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        // blitting the player
        tmp.w = player.dim.w;
        tmp.h = player.dim.h;
        tmp.x = (int)player.pos.x;
        tmp.y = (int)player.pos.y;
        //tmp.x = (int)(player.pos.x * alpha ) + ((player.pos.x - player.vel.x) * (1 - alpha));
        //tmp.y = (int)(player.pos.y * alpha ) + ((player.pos.y - player.vel.y) * (1 - alpha));
        printf("x = %d\n", tmp.x);
        printf("y = %d\n", tmp.y);

        if((int)tmp.y >= SCREEN_HEIGHT) {
            tmp.y = 0;
            //flakes[ i ].pos.y = 0;
            //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
        }

        if((int)tmp.x >= SCREEN_WIDTH) {
            tmp.x = 0;
            //flakes[ i ].pos.y = 0;
            //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
        }
       // SDL_BlitSurface( object, NULL, screen, &tmp );
        SDL_FillRect( screen, &tmp, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        
        //putpixel( screen, tmp.x, tmp.y, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
}

void
update_state()
{
    int loops;
    static int start_tick = SDL_GetTicks();
    int this_tick = SDL_GetTicks();

    if( this_tick == start_tick ){
        SDL_Delay(1);
        return;
    }

    loops = 0;
    while( this_tick > start_tick && loops < 4 ){
        handle_input();
        move_objects();

       // start_tick += 1000 / PHYSICS_FPS;
        start_tick += SKIP_TICKS;
        loops++;
    }

    //float interpolation = float(SDL_GetTicks() + SKIP_TICKS - start_tick) / float(SKIP_TICKS);
    float interpolation = float(SDL_GetTicks() + SKIP_TICKS - start_tick) / float(SKIP_TICKS);
    render( interpolation );
}


void
move_objects( )
{
    int next_x = 0, next_y = 0;
    enemy.vel.x = 0;
    enemy.vel.y = 0;

    if( chasing ){
        // determine motion
        if( enemy.pos.x > player.pos.x ){
            enemy.vel.x = -3;
        }else if( enemy.pos.x < player.pos.x ){
            enemy.vel.x = 3;
        }else if( enemy.pos.x == player.pos.x ){
            enemy.vel.x = 0;    
        }

        if( enemy.pos.y > player.pos.y ){
            enemy.vel.y = -3;
        }else if( enemy.pos.y < player.pos.y ){
            enemy.vel.y = 3;
        }else if( enemy.pos.y == player.pos.y ){
            enemy.vel.y = 0;
        }
    }else{
        // determine motion
        /*
        if( enemy.pos.x - (player.pos.x + player.dim.w) < 10 ){
            enemy.vel.x = 3;
        }else if( enemy.pos.x - player.pos.x < -10 ){
            enemy.vel.x = -3;
        }else{
            enemy.vel.x = 0;
        }

        if( enemy.pos.y - (player.pos.y + player.dim.h) < 10 ){
            enemy.vel.y = 3;
        }else if( enemy.pos.y - player.pos.y < -10 ){
            enemy.vel.y = -3;
        }else{
            enemy.vel.y = 0;
        }
        */
        if( enemy.pos.x > player.pos.x ){
            enemy.vel.x = 3;
        }else if( enemy.pos.x < player.pos.x ){
            enemy.vel.x = -3;
        }else if( enemy.pos.x == player.pos.x ){
            enemy.vel.x = 0;    
        }

        if( enemy.pos.y > player.pos.y ){
            enemy.vel.y = 3;
        }else if( enemy.pos.y < player.pos.y ){
            enemy.vel.y = -3;
        }else if( enemy.pos.y == player.pos.y ){
            enemy.vel.y = 0;
        }
        
    }

    next_x = enemy.pos.x + enemy.vel.x;
    next_y = enemy.pos.y + enemy.vel.y;

    next_x = next_x % SCREEN_WIDTH;
    next_y = next_y % SCREEN_HEIGHT;

    if( next_x < 0 )
        next_x = SCREEN_WIDTH - next_x;

    if( next_y < 0 )
        next_y = SCREEN_HEIGHT - next_y;

    enemy.pos.x = next_x;
    enemy.pos.y = next_y;

    next_x = 0, next_y = 0;

    next_x = player.pos.x + player.vel.x;
    next_y = player.pos.y + player.vel.y;

    next_x = next_x % SCREEN_WIDTH;
    next_y = next_y % SCREEN_HEIGHT;

    if( next_x < 0 )
        next_x = SCREEN_WIDTH - next_x;

    if( next_y < 0 )
        next_y = SCREEN_HEIGHT - next_y;

    player.pos.x = next_x;
    player.pos.y = next_y;
}


void
init_game()
{

    player.dim.w = 10;
    player.dim.h = 10;
    player.vel.x = 0;
    player.vel.y = 0;
    player.pos.x = (SCREEN_WIDTH / 2) - (player.dim.w / 2);
    player.pos.y = (SCREEN_HEIGHT / 2) - (player.dim.h / 2);
    player.is_Visible = true;

    enemy.dim.w = 10;
    enemy.dim.h = 10;
    enemy.vel.x = 0;
    enemy.vel.y = 0;
    enemy.pos.x = rand() % SCREEN_WIDTH;
    enemy.pos.y = rand() % SCREEN_HEIGHT;
    enemy.is_Visible = true;
}


