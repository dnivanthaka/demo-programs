/*
 * =====================================================================================
 *
 *       Filename:  graphics.cpp
 *
 *    Description:  Handling of graphics routines
 *
 *        Version:  1.0
 *        Created:  07/15/2012 10:19:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
// HEADER FILES ------------------------------------------------------------------------
#include <string>
#include <stack>
#include <cstdlib>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
// -------------------------------------------------------------------------------------
// PUBLIC DATA -------------------------------------------------------------------------
SDL_Surface *screen     = NULL;
SDL_Surface *ball_img   = NULL;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

const int GAME_SPEED_HZ  = 60;
const int MAX_FRAME_SKIP = 30;

// -------------------------------------------------------------------------------------
// PRIVATE DATA ------------------------------------------------------------------------
bool gameIsRunning = true;
SDL_Event event;
TTF_Font *font_basic = NULL;
bool keys_held[323];
SDL_Color text_color = { 0, 0, 0 };

struct entity {
    int w;
    int h;
    int x;
    int y;
    int prev_x;
    int prev_y;
    int vel_x;
    int vel_y;
    int acc_x;
    int acc_y;
};

// -------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES -----------------------------------------------------------------
int init_graphics( std::string caption );
void clean_up();
void init_events();
void init_entities();
int key_pressed();
bool key_held(int key);
void update_game( float dt );
void render( float in );
void  handle_events();
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface* load_image( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0xFF, int b = 0xFF );
// -------------------------------------------------------------------------------------

struct entity ball;


int
main(int argc, char *argv[])
{
    int next_tick, loops;
    float interpolation;
    init_graphics("Graphics Demo");
    init_events();
    init_entities();


    next_tick = SDL_GetTicks();

    while( gameIsRunning ){
        loops = 0;
        /*
        if( SDL_GetTicks() == next_tick ){
            printf("Im here\n");
            SDL_Delay(10);
            continue;
        }
        */

        while( SDL_GetTicks() > next_tick && loops++ < MAX_FRAME_SKIP ){
            handle_events();
        
            // Important to put this, otherwise you cannot exit from fullscreen.
            if( key_pressed() == SDLK_ESCAPE ){
                gameIsRunning = false;
            }

            update_game( 1000 / GAME_SPEED_HZ );

            next_tick += 1000 / GAME_SPEED_HZ;
        }

    
        interpolation = float(SDL_GetTicks() + (1000 / GAME_SPEED_HZ) - next_tick) / float(1000 / GAME_SPEED_HZ);
        render( interpolation );

        //putpixel( screen, 100, 100, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );


        //SDL_Flip(screen);
    }

    //SDL_FreeSurface( screen );
    clean_up();
}

int
init_graphics( std::string caption )
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 ){
        return -1;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF );
    //screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );


    SDL_ShowCursor( SDL_DISABLE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create Screen surface in %d - %s\n", __LINE__, __FILE__ );
        return -1;
    }

    SDL_WM_SetCaption(caption.c_str(), NULL);

    if( TTF_Init() == -1 ){
        fprintf( stderr, "Unable to initialize Font Subsystem in %d - %s\n", __LINE__, __FILE__ );
        return -1;
    }

    //font_basic = TTF_OpenFont( "VeraSe.ttf", 18 );
    //
    ball_img = load_image( "ball_10.png", true, 0xFF, 0, 0xFF  );

}

void
init_entities()
{
    ball.w = 10;
    ball.h = 10;
    ball.x = SCREEN_WIDTH / 2  - ball.w / 2;
    ball.y = SCREEN_HEIGHT / 2 - ball.h / 2;
    ball.prev_x = ball.x;
    ball.prev_y = ball.y;
    ball.vel_x = 4;
    ball.vel_y = 4;
    ball.acc_x = 0;
    ball.acc_y = 1;
}

void
update_game( float dt )
{
    SDL_Rect r_ball;

    //fprintf(stdout, "dt = %f\n", dt);

    //ball.vel_x = ball.vel_x * dt;
    //ball.vel_y = ball.vel_y * dt;
    ball.vel_x += ball.acc_x;
    ball.vel_y += ball.acc_y;

     // Checking for wall collisions
     // Left Wall
     if( ball.x + ball.vel_x <= 0 && ball.vel_x < 0 ){
         ball.vel_x = -1 * ball.vel_x;
         //ball.acc_x = -1 * ball.acc_x;
         //ball.acc_x = 0;
         //ball.acc_x--;
     }
     // Right Wall
     if( ball.x + ball.vel_x + ball.w >= SCREEN_WIDTH && ball.vel_x > 0){
         ball.vel_x = -1 * ball.vel_x;
         //ball.acc_x = -1 * ball.acc_x;
         //ball.acc_x = 0;
         //ball.acc_x--;
     }
     // Top Wall
     if( ball.y + ball.vel_y <= 0 && ball.vel_y < 0 ){
         ball.vel_y = -1 * ball.vel_y;
         //ball.acc_y = -1 * ball.acc_y;
         //ball.acc_y = 0;
         //ball.acc_y--;
     }
     // Bottom Wall
     if( ball.y + ball.vel_y + ball.h >= SCREEN_HEIGHT && ball.vel_y > 0 ){
         ball.vel_y = -1 * ball.vel_y;
         //ball.acc_y = -1 * ball.acc_y;
         //ball.acc_y = 0;
         //ball.acc_y--;
     }
    fprintf(stdout, "vel_x = %d\n", ball.vel_x);
    fprintf(stdout, "vel_y = %d\n", ball.vel_y);
    fprintf(stdout, "acc_x = %d\n", ball.acc_x);
    fprintf(stdout, "acc_y = %d\n", ball.acc_y);

    ball.x += ball.vel_x;
    ball.y += ball.vel_y;
     
}

void render( float in )
{
    SDL_Rect r_ball;
    int prev_x, prev_y;
    
    // Removing the previous ball drawing
    //r_ball.w = ball.w;
    //r_ball.h = ball.h;
    //r_ball.x = ball.x;
    //r_ball.y = ball.y;
    //r_ball.x = ball.prev_x;
    //r_ball.y = ball.prev_y;

    //SDL_FillRect( screen, NULL,SDL_MapRGB( screen->format, 0, 0, 0 ) );
    //SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0xFF, 0, 0 ) );
    //SDL_FillRect( screen, NULL,SDL_MapRGB( screen->format, 0, 0, 0 ) );


    //printf("intr = %d\n", (int)in);

    // Drawing the new ball
    //ball.x += ball.vel_x;
    //ball.y += ball.vel_y;
    //ball.x += (ball.vel_x * in);
    //ball.y += (ball.vel_y * in);
    //ball.x = ((ball.x + ball.vel_x) * in + ball.x * (1.0 - in));
    //ball.y = ((ball.y + ball.vel_y) * in + ball.y * (1.0 - in));
    //printf("1ball_x = %d\n", (int)r_ball.x);
    //printf("1ball_y = %d\n", (int)r_ball.y);

    r_ball.w = ball.w;
    r_ball.h = ball.h;
    //r_ball.x = ball.x * in + r_ball.x * (1.0 - in);
    r_ball.x = ball.x * in + (ball.prev_x * (1 - in));
    //r_ball.x = ball.prev_x * in;
    //r_ball.y = ball.y * in + r_ball.y * (1.0 - in);
    r_ball.y = ball.y * in + (ball.prev_y * (1 - in));
    //r_ball.y = ball.prev_y * in;

    //printf("ball_x = %d\n", (int)r_ball.x);
    //printf("ball_y = %d\n", (int)r_ball.y);

    //SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    SDL_BlitSurface( ball_img, NULL, screen, &r_ball );

    SDL_Flip(screen);

    ball.prev_x = ball.x;
    ball.prev_y = ball.y;

    // Removing the already drawn object ** This works
    SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0, 0, 0 ) );
    //SDL_FillRect( screen, NULL,SDL_MapRGB( screen->format, 0, 0, 0 ) );
}

void
clean_up()
{
    SDL_FreeSurface( screen );

    TTF_CloseFont( font_basic );
    TTF_Quit();
    SDL_Quit();
}

void
init_events()
{
    for(int i = 0; i < 323; i++){
        keys_held[i] = false;
    }
}

void
handle_events()
{
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_KEYDOWN ){
            keys_held[ event.key.keysym.sym ] = true;
        }else if( event.type == SDL_KEYUP ){
            keys_held[ event.key.keysym.sym ] = false;
        }else if( event.type == SDL_QUIT ){
            gameIsRunning = false;
        }
    }
}

int
key_pressed()
{
    if( event.type == SDL_KEYDOWN ){
        return event.key.keysym.sym;
    }

    return -1;
}

bool
key_held(int key)
{
    return keys_held[ key ];
}

SDL_Surface* 
load_image( std::string file, bool setColorKey, int r, int g, int b )
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
