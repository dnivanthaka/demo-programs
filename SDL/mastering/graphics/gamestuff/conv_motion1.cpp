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

struct thing critters[ NUM_CRITTERS ];

SDL_Event event;
bool gameRunning = true;

bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;

float centroid_x, centroid_y;


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

    float dx, dy, speed, length;
        //start_time = SDL_GetTicks();
       // anim_time = start_time;
        centroid_x = 0;
        centroid_y = 0;

        init_game();

        for( int i=0;i<NUM_CRITTERS;i++ ){
            centroid_x += critters[ i ].pos.x;
            centroid_y += critters[ i ].pos.y;
        }        
        //draw_court();

        centroid_x /= (float) NUM_CRITTERS;
        centroid_y /= (float) NUM_CRITTERS;

        //next_game_tick = SDL_GetTicks();
        //accumulator = SDL_GetTicks();
        //dt = SDL_GetTicks();

        //creature.vel.x = 0;
        //creature.vel.y = 2;

        for( int i=0;i<NUM_CRITTERS;i++ ){
            dx = centroid_x - critters[i].pos.x;
            dy = centroid_y - critters[i].pos.y;

            length = sqrt( dx * dx + dy * dy );
            dx = dx/length;
            dy = dy/length;

            speed = 2 + rand() % 3;

            critters[i].vel.x = dx * speed;
            critters[i].vel.y = dy * speed;
        }

        while( gameRunning ){
            
            // handle input
            //handle_input();
            // logic
                        
            // rendering

            // Drawing the walls
            //draw_walls();
            //SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
            //SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
            //SDL_BlitSurface( blit_1, NULL, screen, NULL );
            // This order should be maintained since we need 
            // the final paddle velocities for collision detection
            //accumulator = SDL_GetTicks() - dt;
            loop = 0;
            update_state();
            //while( SDL_GetTicks() - next_game_tick > 20 ){ 
                //handle_input();
                //handle_paddle_collisions( &paddles[0] );
                //move_paddle( &paddles[0] );
                //move_ball( );

                //next_game_tick += SKIP_TICKS;
                //next_game_tick += 20;
                //loop++;
            //}

            //render( (SDL_GetTicks() + SKIP_TICKS - next_game_tick) / SKIP_TICKS );
            //float interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
            //render( interpolation );

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
               right_pressed = true;
               //creature.x_dir = RIGHT;
               //creature.vel.x = 1;
               break;
               case SDLK_LEFT:
               left_pressed = true;
               //creature.x_dir = LEFT;
               //creature.vel.x = -1;
               break;
               case SDLK_UP:
               up_pressed = true;
               //creature.y_dir = UP;
               //creature.vel.y = -400; 
               break;
               case SDLK_DOWN:
               down_pressed = true;
               //creature.y_dir = DOWN;
               //creature.vel.y = +400;
               break;
           }
       }else if(event.type == SDL_KEYUP){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               right_pressed = false;
               //creature.vel.x = 0;
               break;
               case SDLK_LEFT:
               left_pressed = false;
               //creature.vel.x = 0;
               break;
               case SDLK_UP:
               up_pressed = false;
               //creature.vel.y = 0;
               break;
               case SDLK_DOWN:
               down_pressed = false;
               //creature.vel.y = 0;
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

    
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }
    
    
    // make sure he is visible

        printf("alpha = %f\n", alpha);
        for(int i=0;i<NUM_CRITTERS;i++){
        //tmp.w = flakes[ i ].dim.w;
        //tmp.h = flakes[ i ].dim.h;
        //tmp.x = (int)(flakes[ i ].pos.x + (flakes[ i ].vel.x * alpha ));
        //tmp.y = (int)(flakes[ i ].pos.y + (flakes[ i ].vel.y * alpha ));
        //tmp.y = (int)(creature.pos.y * alpha ) + (creature.prev_pos.y * (1 - alpha));
        tmp.w = critters[i].dim.w;
        tmp.h = critters[i].dim.h;
        tmp.x = (int)critters[i].pos.x;
        tmp.y = (int)critters[i].pos.y;
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
        
            putpixel( screen, tmp.x, tmp.y, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        }
    
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
    
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
        handle_input( );
        move_objects( );

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
    int next_x, next_y;

    //determine_position();

    for(int i=0;i<NUM_CRITTERS;i++){
        if( (abs(critters[i].pos.x - centroid_x)) + (abs(critters[i].pos.y - centroid_y)) > 20 ){
            critters[i].pos.x += critters[i].vel.x;
            critters[i].pos.y += critters[i].vel.y;
        }
    }
}



void
init_game()
{
    int i;

    for(i=0;i<NUM_CRITTERS;i++){
        critters[i].dim.w           = 1;
        critters[i].dim.h           = 1;
        critters[i].vel.x           = 0;
        critters[i].vel.y           = 0;
        critters[i].pos.x           = rand() % SCREEN_WIDTH;
        critters[i].pos.y           = rand() % SCREEN_HEIGHT;
        critters[i].is_Visible      = true;
    }
}


