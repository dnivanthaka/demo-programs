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

const int BOARD_PIECE_WIDTH  = 20;
const int BOARD_PIECE_HEIGHT = 20;
const int BOARD_PIECE_SPACE  = 1;
const int BOARD_LINE_WIDTH = 5;
const int BOARD_HEIGHT = 480;
//const int BOARD_HORIZONTAL_PIECE_COUNT = BOARD_WIDTH / (BOARD_PIECE_WIDTH + BOARD_PIECE_SPACE);
const int BOARD_HORIZONTAL_PIECE_COUNT = 10;
const int BOARD_VERTICAL_PIECE_COUNT   = BOARD_HEIGHT / (BOARD_PIECE_HEIGHT + BOARD_PIECE_SPACE);
//BOARD_HORIZONTAL_PIECE_COUNT

const int BOARD_WIDTH  = (BOARD_HORIZONTAL_PIECE_COUNT * (BOARD_PIECE_WIDTH + BOARD_PIECE_SPACE)) - (BOARD_PIECE_SPACE * 2);

char board_blocks[ BOARD_HORIZONTAL_PIECE_COUNT ][ BOARD_VERTICAL_PIECE_COUNT ];

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
void check_point_collisions();
void update_state();

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

    SDL_WM_SetCaption( "Tetris", NULL );

    //object = loadImage( "Tux_sm.png" );

    //if( alien != NULL ){

        init_game();


        while( gameRunning ){
            
            loop = 0;
            update_state();

            SDL_Flip( screen );

        //}
        //SDL_Delay(20);
        }
    //}

    // Cleaning-up
    //SDL_FreeSurface( alien );

    std::vector<thing *>::iterator it;
    for( it=snake_blocks.begin();it!=snake_blocks.end();it++ ){
        delete *it;
    }

    snake_blocks.clear();
    point_blocks.clear();
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
        move_objects();

        //if( point_blocks.size() == 0 )
            //place_point_blocks();

       // start_tick += 1000 / PHYSICS_FPS;
        start_tick += SKIP_TICKS;
        loops++;
    }

    //float interpolation = float(SDL_GetTicks() + SKIP_TICKS - start_tick) / float(SKIP_TICKS);
    float interpolation = float(SDL_GetTicks() + SKIP_TICKS - start_tick) / float(SKIP_TICKS);
    //render( interpolation );
}



void
move_objects( )
{
    

}


void
init_game()
{
    // drawing the two boundaries
    SDL_Rect tmp;
    int start_offset = 0;

    tmp.w = BOARD_LINE_WIDTH;
    tmp.h = BOARD_HEIGHT;
    //tmp.x = SCREEN_WIDTH / 2 - (BOARD_WIDTH + BOARD_LINE_WIDTH * 2) / 2;
    tmp.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2;
    tmp.y = SCREEN_HEIGHT - BOARD_HEIGHT;
    SDL_FillRect( screen, &tmp, SDL_MapRGB( screen->format, 0x0, 0x0, 0xFF ) );

    tmp.w = BOARD_LINE_WIDTH;
    tmp.h = BOARD_HEIGHT;
    //tmp.x = SCREEN_WIDTH / 2 + (BOARD_WIDTH + BOARD_LINE_WIDTH * 2) / 2;
    tmp.x = (SCREEN_WIDTH / 2 + BOARD_WIDTH / 2) + BOARD_LINE_WIDTH + 1;
    tmp.y = SCREEN_HEIGHT - BOARD_HEIGHT;
    SDL_FillRect( screen, &tmp, SDL_MapRGB( screen->format, 0x0, 0x0, 0xFF ) );

    printf("cnt x = %d\n", BOARD_WIDTH);

    start_offset = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + BOARD_LINE_WIDTH;

/*
    for( int i=0;i<BOARD_VERTICAL_PIECE_COUNT;i++ ){
        for( int j=0;j<BOARD_HORIZONTAL_PIECE_COUNT;j++ ){
            tmp.w = BOARD_PIECE_WIDTH;
            tmp.h = BOARD_PIECE_HEIGHT;
            tmp.x = start_offset;
            tmp.y = SCREEN_HEIGHT - (BOARD_PIECE_HEIGHT + BOARD_PIECE_SPACE) * (i + 1);
            SDL_FillRect( screen, &tmp, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
            start_offset += BOARD_PIECE_WIDTH + BOARD_PIECE_SPACE;
        }
        start_offset = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + BOARD_LINE_WIDTH;
    }
*/


}


