// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS = 60;
const int MAX_LOOPS = 4;
const int TICKS_PER_SEC = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SEC;
const float timestep = 1.0f/120.0f;
const int PHYSICS_FPS = 100;

const int BALL_VEL_X = 200;
const int BALL_VEL_Y = 200;

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

typedef struct {
    pos_t pos;
    pos_t prev_pos;
    dim_t dim;
    vel_t vel;
} paddle_t;

struct ball {
    pos_t pos;
    pos_t prev_pos;
    dir_t x_dir;
    dir_t y_dir;
    dim_t dim;
    vel_t vel;
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

struct ball bouncing_ball;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_events();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void handle_input(Uint32 dt);
void move_ball( Uint32 dt );
void render(float);
void init_game();
void update_state();
void handle_ball_collisions();

int 
main(int argc, char *argv[])
{
    SDL_Rect tux;
    SDL_Rect char_rect;
    Uint32 next_game_tick;
    int loop;
    SDL_Rect tmp;
    float accumulator;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "Cloned Pong", NULL );

    //blit_1 = loadImage( "mario3.png" );

    //if( blit_1 != NULL ){
        tmp.w = 10;
        tmp.h = 10;
        tmp.x = (SCREEN_WIDTH / 2) - ( tmp.w / 2 );
        tmp.y = (SCREEN_HEIGHT / 2) - ( tmp.h / 2 );

        short i = 0;
        int mv_amt_x = 1;
        int mv_amt_y = 1;
        int frameToDraw = 0;
        Uint32 dt;
        Uint32 numTicks = 0;
        //start_time = SDL_GetTicks();
       // anim_time = start_time;

        init_game();        
        //draw_court();

        //next_game_tick = SDL_GetTicks();
        //accumulator = SDL_GetTicks();
        //dt = SDL_GetTicks();

        while( gameRunning ){
            
            // handle input
            //handle_input();
            // logic
                        
            // rendering
 
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
            render( 1 );

            SDL_Flip( screen );

            //accumulator = SDL_GetTicks();
            //dt = SDL_GetTicks();
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
            
            //if( SDL_GetTicks() - start_time < 1000 / FPS ){
            //if( SDL_GetTicks() - start_time < FPMS ){
                //SDL_Delay( (1000 / FPS) - (SDL_GetTicks() - start_time) );
            //}
            //start_time = SDL_GetTicks();
            //numTicks++;
        //}
        //SDL_Delay(2000);
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
handle_input( Uint32 dt )
{
    while( SDL_PollEvent( &event ) ){
         if( event.type == SDL_KEYDOWN ){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               //right_pressed = true;
               bouncing_ball.x_dir = RIGHT;
               bouncing_ball.vel.x = 400;
               break;
               case SDLK_LEFT:
               //left_pressed = true;
               bouncing_ball.x_dir = LEFT;
               bouncing_ball.vel.x = -400;
               break;
               case SDLK_UP:
               //up_pressed = true;
               bouncing_ball.y_dir = UP;
               bouncing_ball.vel.y = -400; 
               break;
               case SDLK_DOWN:
               //down_pressed = true;
               bouncing_ball.y_dir = DOWN;
               bouncing_ball.vel.y = +400;
               break;
           }
       }else if(event.type == SDL_KEYUP){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               //right_pressed = false;
               bouncing_ball.vel.x = 0;
               break;
               case SDLK_LEFT:
               //left_pressed = false;
               bouncing_ball.vel.x = 0;
               break;
               case SDLK_UP:
               //up_pressed = false;
               bouncing_ball.vel.y = 0;
               break;
               case SDLK_DOWN:
               //down_pressed = false;
               bouncing_ball.vel.y = 0;
               break;
            }
        }else if( event.type == SDL_QUIT ){
            gameRunning = false;
        }
    }
    //bouncing_ball.vel.x = BALL_VEL_X * (dt / 1000.f);
    //bouncing_ball.vel.y = BALL_VEL_Y * (dt / 1000.f);
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
    SDL_Rect tmp;

    //printf("alpha = %f\n", alpha);
    

    //bouncing_ball.prev_pos.x = bouncing_ball.prev_pos.x * alpha;
    //bouncing_ball.prev_pos.y = bouncing_ball.prev_pos.y * alpha;
    // Deleting the previous state, ball
    tmp.w = bouncing_ball.dim.w;
    tmp.h = bouncing_ball.dim.h;
    tmp.x = bouncing_ball.prev_pos.x;
    tmp.y = bouncing_ball.prev_pos.y;
    SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0, 0, 0) );
    //SDL_BlitSurface( court, &tmp, screen, &tmp );
    // Drawing the new state, ball
    //bouncing_ball.pos.x += bouncing_ball.vel.x;
    //bouncing_ball.pos.y += bouncing_ball.vel.y;
    //bouncing_ball.pos.x += bouncing_ball.vel.x * (alpha);
    //bouncing_ball.pos.y += bouncing_ball.vel.y * (alpha);
    tmp.w = bouncing_ball.dim.w;
    tmp.h = bouncing_ball.dim.h;
    tmp.x = (int)bouncing_ball.pos.x;
    tmp.y = (int)bouncing_ball.pos.y;
    SDL_FillRect( screen, &tmp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );

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
        handle_input( SDL_GetTicks() - start_tick );
        //handle_paddle_collisions( &paddles[0] );
        handle_ball_collisions();
        //move_paddle( &paddles[0] );
        move_ball( SDL_GetTicks() - start_tick );

        start_tick += 1000 / PHYSICS_FPS;
        loops++;
    }
}

void
handle_ball_collisions(){
    if( bouncing_ball.pos.y <= 0 ||  bouncing_ball.pos.y + bouncing_ball.dim.h >= (SCREEN_HEIGHT)){
        printf("XXX");
        //bouncing_ball.vel.y = 1 * (dt / 1000);
        //bouncing_ball.vel.y = BALL_VEL_Y * (dt / 1000.f);
        //bouncing_ball.vel.y = bouncing_ball.vel.y;
        //bouncing_ball.vel.y = -1 * bouncing_ball.vel.y;
        bouncing_ball.vel.y = -1 * bouncing_ball.vel.y;
        //if( bouncing_ball.vel.y < 0 )
            //bouncing_ball.vel.y = -1 * bouncing_ball.vel.y;
        //else
            //bouncing_ball.vel.y = -1 * bouncing_ball.vel.y;
    }

    if( bouncing_ball.pos.x <= 0 || bouncing_ball.pos.x  >= (SCREEN_WIDTH)){
        printf("YYY");
        //bouncing_ball.vel.x = 1 * (dt / 1000);
        //bouncing_ball.vel.x = BALL_VEL_X * (dt / 1000.f);
        //bouncing_ball.vel.x = bouncing_ball.vel.x;
        //bouncing_ball.vel.x = -1 * bouncing_ball.vel.x;
        bouncing_ball.vel.x = -1 * bouncing_ball.vel.x;
        //if( bouncing_ball.vel.x < 0 )
            //bouncing_ball.vel.x = 200;
        //else
            //bouncing_ball.vel.x = -200;
    }
}

void
move_ball( Uint32 dt )
{
    //b->vel.x = 1;
    //int paddle_mid_y;
    //int mv_x = 200, my_y = 200;
    
    // Collision Detection
    // Wall
    //bouncing_ball.vel.y = 1 * (dt / 1000);
    //bouncing_ball.vel.x = 1 * (dt / 1000);

    //printf("ball_x = %d\n", dt);    
    //printf("ball_x = %f\n", 200 * (dt / 1000.f));
    //printf("ball_x = %d\n", (int)(200 * (dt / 1000.f)));

    //bouncing_ball.vel.x = 200;
    //bouncing_ball.vel.y = 200;

    //bouncing_ball.vel.y = 1.f;
    //bouncing_ball.vel.x = bouncing_ball.vel.x * (dt / 1000.f);
    //bouncing_ball.vel.y = bouncing_ball.vel.y * (dt / 1000.f);
    bouncing_ball.prev_pos.x = bouncing_ball.pos.x;
    bouncing_ball.prev_pos.y = bouncing_ball.pos.y;

    bouncing_ball.pos.x += bouncing_ball.vel.x * (dt / 1000.f);
    bouncing_ball.pos.y += bouncing_ball.vel.y * (dt / 1000.f);


    //if( bouncing_ball.pos.y + bouncing_ball.vel.y <= 0 ){
        //bouncing_ball.vel.y = 1 * (dt / 1000);
        //bouncing_ball.vel.y = BALL_VEL_Y * (dt / 1000.f);
        //bouncing_ball.vel.y = 1 * (dt / 1000);
    //}else if(bouncing_ball.pos.y + bouncing_ball.vel.y >= (SCREEN_HEIGHT - bouncing_ball.dim.h)){
        //bouncing_ball.vel.y = -1 * (dt / 1000);
        //bouncing_ball.vel.y = -BALL_VEL_Y * (dt / 1000.f);
        //bouncing_ball.vel.y = -1 * (dt / 1000);
    //}

    //if( bouncing_ball.pos.x + bouncing_ball.vel.x <= 0 ){
        //bouncing_ball.vel.x = 1 * (dt / 1000);
        //bouncing_ball.vel.x = BALL_VEL_X * (dt / 1000.f);
        //bouncing_ball.vel.x = 1 * (dt / 1000);
    //}else if(bouncing_ball.pos.x + bouncing_ball.vel.x >= (SCREEN_WIDTH - bouncing_ball.dim.w)){
        //bouncing_ball.vel.x = -1 * (dt / 1000);
        //bouncing_ball.vel.x = -BALL_VEL_X * (dt / 1000.f);
        //bouncing_ball.vel.x = -1 * (dt / 1000);
    //}

    printf("ball_x = %f\n", bouncing_ball.pos.y + bouncing_ball.vel.y);

    //bouncing_ball.prev_pos.x = bouncing_ball.pos.x;
    //bouncing_ball.prev_pos.y = bouncing_ball.pos.y;



    //tmp.x += mv_amt_x;
    //tmp.y += mv_amt_y;
    // Paddle Collision
    // Left
    /*
    if( bouncing_ball.pos.y <= (paddles[0].pos.y + paddles[0].dim.h)  && bouncing_ball.pos.y >= paddles[0].pos.y + paddles[0].vel.y ){
        if((bouncing_ball.pos.x) <= (paddles[0].pos.x + paddles[0].dim.w)
    && (bouncing_ball.pos.x) >= paddles[0].pos.x){
            bouncing_ball.vel.x = 1;        
            bouncing_ball.vel.y = 1;
        }
    }
    */

    /*
    paddle_mid_y = paddles[0].dim.h / 2;

    if( bouncing_ball.pos.x <= paddles[0].pos.x + paddles[0].dim.w && bouncing_ball.pos.x >= paddles[0].pos.x ){
        // Top hit
        //if(bouncing_ball.pos.y <= paddles[0].pos.y + paddles[0].dim.h  && bouncing_ball.pos.y >= paddles[0].pos.y){
        if( bouncing_ball.pos.y + bouncing_ball.dim.h <= (paddles[0].pos.y + paddle_mid_y)  && bouncing_ball.pos.y + bouncing_ball.dim.h >= paddles[0].pos.y ){
            bouncing_ball.vel.x = 1;        
            bouncing_ball.vel.y = -1;
            //printf("Top Hit\n");
        // Bottom Hit
        }else if( bouncing_ball.pos.y >= (paddles[0].pos.y + paddle_mid_y) && bouncing_ball.pos.y <= paddles[0].pos.y + paddles[0].dim.h ){
            bouncing_ball.vel.x = 1;        
            bouncing_ball.vel.y = 1;
            //printf("Bottom Hit\n");  
        }
    }
    */

    /*
    && (bouncing_ball.pos.x + bouncing_ball.vel.x) <= (paddles[0].pos.x + paddles[0].dim.w) + paddles[0].vel.x
    && (bouncing_ball.pos.x + bouncing_ball.vel.x) >= paddles[0].pos.x + paddles[0].vel.x
    */
    // Applying the new velocities
    //bouncing_ball.pos.x += bouncing_ball.vel.x;
    //bouncing_ball.pos.y += bouncing_ball.vel.y;
}

void
init_game()
{

    // Ball Coordinates and others
    bouncing_ball.dim.w = 10;
    bouncing_ball.dim.h = 10;
    bouncing_ball.vel.x = 0;
    bouncing_ball.vel.y = 0;
    bouncing_ball.pos.x = (SCREEN_WIDTH / 2)  - (bouncing_ball.dim.w / 2);
    bouncing_ball.pos.y = (SCREEN_HEIGHT / 2) - (bouncing_ball.dim.h / 2);
}


