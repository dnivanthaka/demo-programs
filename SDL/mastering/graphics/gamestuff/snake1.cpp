// HEADER FILES ------------------------------------------------------------
// g++ snake1.cpp  -lSDL -lSDL_image
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

const int INIT_NUM_BLOCKS = 30;

//const int FPMS = FPS / 1000;

/*******************************
http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range-c
http://stackoverflow.com/questions/2665909/random-numbers-from-10-to-10-in-c
http://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-entire-range
*******************************/

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
    dim_t dim;
    vel_t vel;
    bool is_Visible;
    Uint32 color;
};

SDL_Surface *screen = NULL;
//SDL_Surface *object = NULL;

std::vector<thing *> snake_blocks;
std::vector<thing> point_blocks;

//struct thing enemy;

SDL_Event event;
bool gameRunning = true;

bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;


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
void place_point_blocks( int count = 1 );
void check_point_collisions();

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

    SDL_WM_SetCaption( "The Snake", NULL );

    //object = loadImage( "Tux_sm.png" );

    //if( alien != NULL ){

        init_game();


        while( gameRunning ){
            
            loop = 0;
            update_state();

            SDL_Flip( screen );

            if( point_blocks.size() == 0 )
                place_point_blocks();
        //}
        //SDL_Delay(20);
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
               //player.vel.x = 10;
               break;
               case SDLK_LEFT:
               left_pressed = true;
               //creature.x_dir = LEFT;
               //player.vel.x = -10;
               break;
               case SDLK_UP:
               up_pressed = true;
               //creature.y_dir = UP;
               //player.vel.y = -10; 
               break;
               case SDLK_DOWN:
               down_pressed = true;
               //creature.y_dir = DOWN;
               //player.vel.y = +10;
               break;
           }
       }else if(event.type == SDL_KEYUP){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               right_pressed = false;
               //player.vel.x = 0;
               break;
               case SDLK_LEFT:
               left_pressed = false;
               //player.vel.x = 0;
               break;
               case SDLK_UP:
               up_pressed = false;
               //player.vel.y = 0;
               break;
               case SDLK_DOWN:
               down_pressed = false;
               //player.vel.y = 0;
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
    SDL_Rect tmp;

    //printf("alpha = %f\n", alpha);

    // clearing old positions
    SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
    
            printf("sdsdsd\n");
        fflush(stdout);
    // make sure he is visible

        //printf("alpha = %f\n", alpha);
        for(int i=0;i<snake_blocks.size();i++){

            if( !snake_blocks[i]->is_Visible )
                continue;

            tmp.w = snake_blocks[i]->dim.w;
            tmp.h = snake_blocks[i]->dim.h;
            tmp.x = (int)snake_blocks[i]->pos.x;
            tmp.y = (int)snake_blocks[i]->pos.y;
            //tmp.x = (int)(critters[i].pos.x * alpha ) + ((critters[i].pos.x - critters[i].vel.x) * (1 - alpha));
            //tmp.y = (int)(critters[i].pos.y * alpha ) + ((critters[i].pos.y - critters[i].vel.y) * (1 - alpha));
            //printf("x = %d\n", tmp.x);
            //printf("y = %d\n", tmp.y);

            if((int)tmp.y >= SCREEN_HEIGHT) {
                //tmp.y = 0;
                //flakes[ i ].pos.y = 0;
                //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
            }

            if((int)tmp.x >= SCREEN_WIDTH) {
                //tmp.x = 0;
                //flakes[ i ].pos.y = 0;
                //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
            }
           // SDL_BlitSurface( object, NULL, screen, &tmp );
            SDL_FillRect( screen, &tmp, snake_blocks[i]->color );
        }

        for(int i=0;i<point_blocks.size();i++){

            tmp.w = point_blocks[i].dim.w;
            tmp.h = point_blocks[i].dim.h;
            tmp.x = (int)point_blocks[i].pos.x;
            tmp.y = (int)point_blocks[i].pos.y;
            //tmp.x = (int)(critters[i].pos.x * alpha ) + ((critters[i].pos.x - critters[i].vel.x) * (1 - alpha));
            //tmp.y = (int)(critters[i].pos.y * alpha ) + ((critters[i].pos.y - critters[i].vel.y) * (1 - alpha));
            //printf("x = %d\n", tmp.x);
            //printf("y = %d\n", tmp.y);

            if((int)tmp.y >= SCREEN_HEIGHT) {
                //tmp.y = 0;
                //flakes[ i ].pos.y = 0;
                //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
            }

            if((int)tmp.x >= SCREEN_WIDTH) {
                //tmp.x = 0;
                //flakes[ i ].pos.y = 0;
                //flakes[ i ].pos.x = rand() % SCREEN_WIDTH;
            }
           // SDL_BlitSurface( object, NULL, screen, &tmp );
            SDL_FillRect( screen, &tmp, point_blocks[i].color );
        }

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
                printf("sdsdsd\n");
        fflush(stdout);
        move_objects();
                printf("sdsdsd\n");
        fflush(stdout);
        check_point_collisions();

        //if( point_blocks.size() == 0 )
            //place_point_blocks();

       // start_tick += 1000 / PHYSICS_FPS;
        start_tick += SKIP_TICKS;
        loops++;
    }

    //float interpolation = float(SDL_GetTicks() + SKIP_TICKS - start_tick) / float(SKIP_TICKS);
    float interpolation = float(SDL_GetTicks() + SKIP_TICKS - start_tick) / float(SKIP_TICKS);
    render( interpolation );
}

void
check_point_collisions()
{
    int mid_x = snake_blocks[0]->pos.x + (snake_blocks[0]->dim.w / 2);
    int mid_y = snake_blocks[0]->pos.y + (snake_blocks[0]->dim.h / 2);
    

    for(int i=0;i<point_blocks.size();i++){
        int pt_mid_x = point_blocks[i].pos.x + (point_blocks[i].dim.w / 2);
        int pt_mid_y = point_blocks[i].pos.y + (point_blocks[i].dim.h / 2);
        int distance = (int)sqrt( (pt_mid_x - mid_x) * (pt_mid_x - mid_x) + (pt_mid_y - mid_y) * (pt_mid_y - mid_y) );

        
        if( distance < (snake_blocks[0]->dim.w / 2) + (point_blocks[i].dim.w / 2) ){
            struct thing *tmp;
            tmp = new struct thing();

            tmp->dim.w = point_blocks[i].dim.w;
            tmp->dim.h = point_blocks[i].dim.h;
            //tmp.vel.x = 0;
            //tmp.vel.y = 0;
            //tmp.pos.x = 0;
            //tmp.pos.y = 0;
            //tmp.vel.x = point_blocks[i].vel.x;
            //tmp.vel.y = point_blocks[i].vel.y;
            tmp->vel.x = snake_blocks[ snake_blocks.size() - 1 ]->vel.x;
            tmp->vel.y = snake_blocks[ snake_blocks.size() - 1 ]->vel.y;
            //tmp.pos.x = point_blocks[i].pos.x;
            //tmp.pos.y = point_blocks[i].pos.y;
            tmp->pos.x = snake_blocks[ snake_blocks.size() - 1 ]->pos.x;
            tmp->pos.y = snake_blocks[ snake_blocks.size() - 1 ]->pos.y;
            tmp->is_Visible = false;
            tmp->color = point_blocks[i].color;
            printf("Collision\n");
            printf("Size = %d\n", (int)snake_blocks.size());
            snake_blocks.push_back( tmp );

            // removing the point block
            point_blocks.erase( point_blocks.begin() + i );
            printf("Done\n");
            fflush(stdout);
        }
    }

}


void
move_objects( )
{
    int next_x = 0, next_y = 0;
    struct thing *tmp;
 
    for(int i = snake_blocks.size() - 1; i >= 0 ;i--){
        tmp = snake_blocks[i];
        snake_blocks[i + 1])->vel.x = snake_blocks[i]->vel.x;
        snake_blocks[i + 1]->vel.y = snake_blocks[i]->vel.y;
           printf("sdsdsd %d\n", snake_blocks.size());
    fflush(stdout);

        if( !snake_blocks[i + 1]->is_Visible ){
            snake_blocks[i + 1]->pos.x = snake_blocks[i]->pos.x;
            snake_blocks[i + 1]->pos.y = snake_blocks[i]->pos.y;
            snake_blocks[i + 1]->is_Visible = true;
            continue;               
        }

        next_x = snake_blocks[i + 1]->pos.x + snake_blocks[i + 1]->vel.x;
        next_y = snake_blocks[i + 1]->pos.y + snake_blocks[i + 1]->vel.y;

        next_x = next_x % SCREEN_WIDTH;
        next_y = next_y % SCREEN_HEIGHT;

        if( next_x < 0 )
            next_x = SCREEN_WIDTH;

        if( next_y < 0 )
            next_y = SCREEN_HEIGHT;

        snake_blocks[i + 1]->pos.x = next_x;
        snake_blocks[i + 1]->pos.y = next_y;

        
    }

    /*
    snake_blocks[i + 1].vel.x = snake_blocks[i].vel.x;
    snake_blocks[i + 1].vel.y = snake_blocks[i].vel.y;

    next_x = snake_blocks[i + 1].pos.x + snake_blocks[i + 1].vel.x;
    next_y = snake_blocks[i + 1].pos.y + snake_blocks[i + 1].vel.y;

    next_x = next_x % SCREEN_WIDTH;
    next_y = next_y % SCREEN_HEIGHT;

    snake_blocks[i + 1].pos.x = next_x;
    snake_blocks[i + 1].pos.y = next_y;

    i++;

    if( i >= snake_blocks.size() - 1 )
        i = 0;

    */

    next_x = 0; next_y = 0;

    if( up_pressed ){
        snake_blocks[0]->vel.x = 0;
        snake_blocks[0]->vel.y = -10;
    }else if( down_pressed ){
        snake_blocks[0]->vel.x = 0;
        snake_blocks[0]->vel.y = 10;
    }else if( right_pressed ){
        snake_blocks[0]->vel.x = 10;
        snake_blocks[0]->vel.y = 0;
    }else if( left_pressed ){
        snake_blocks[0]->vel.x = -10;
        snake_blocks[0]->vel.y = 0;
    }
        
    // head node
    next_x = snake_blocks[0]->pos.x + snake_blocks[0]->vel.x;
    next_y = snake_blocks[0]->pos.y + snake_blocks[0]->vel.y;

    next_x = next_x % SCREEN_WIDTH;
    next_y = next_y % SCREEN_HEIGHT;

    if( next_x < 0 )
        next_x = SCREEN_WIDTH;

    if( next_y < 0 )
        next_y = SCREEN_HEIGHT;

    snake_blocks[0]->pos.x = next_x;
    snake_blocks[0]->pos.y = next_y;
}



void
place_point_blocks( int count ){
    for(int i=0;i<count;i++){
        struct thing tmp;

        tmp.dim.w = 10;
        tmp.dim.h = 10;
        tmp.vel.x = -10;
        tmp.vel.y = 0;
        tmp.pos.x = rand() % (SCREEN_WIDTH - tmp.dim.w);
        tmp.pos.y = rand() % (SCREEN_HEIGHT - tmp.dim.h);
        tmp.is_Visible = true;
        tmp.color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );

        point_blocks.push_back( tmp );
    }
}


void
init_game()
{
    struct thing *head;
    struct thing *tmp;

    head = new struct thing();

    head->dim.w = 10;
    head->dim.h = 10;
    head->vel.x = -10;
    head->vel.y = 0;
    head->pos.x = (SCREEN_WIDTH / 2) - (head->dim.w / 2);
    head->pos.y = (SCREEN_HEIGHT / 2) - (head->dim.w / 2);
    head->is_Visible = true;
    head->color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );

    snake_blocks.push_back( head );

    for(int i=0;i<INIT_NUM_BLOCKS - 1;i++){
        
        tmp = new struct thing();

        tmp->dim.w = 10;
        tmp->dim.h = 10;
        tmp->vel.x = -10;
        tmp->vel.y = 0;
        tmp->pos.x = ((SCREEN_WIDTH / 2) - (head->dim.w / 2)) + (i + 1) * tmp->dim.w;
        tmp->pos.y = (SCREEN_HEIGHT / 2) - (tmp->dim.h / 2);
        tmp->is_Visible = true;
        tmp->color = SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF );

        snake_blocks.push_back( tmp );
    }

    place_point_blocks();
}


