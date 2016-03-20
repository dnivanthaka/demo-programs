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
    int w, h;
    int x, y;
    int prev_x, prev_y;
    int vel_x, vel_y;
    int acc_x, acc_y;
    bool isMoving;
};

// -------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES -----------------------------------------------------------------
int init_graphics( std::string caption );
void clean_up();
void init_events();
void init_entities();
int key_pressed();
int key_released();
bool key_held(int key);
void update_game( float dt );
void render( float in );
void reset_ball();
void  handle_events();
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface* load_image( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0xFF, int b = 0xFF );
// -------------------------------------------------------------------------------------

struct entity ball, paddle_l, paddle_r;

unsigned short points_l, points_r;


int
main(int argc, char *argv[])
{
    int next_tick, loops;
    float interpolation;
    init_graphics("Pong Clone");
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

            if( key_pressed() == SDLK_UP ){
                paddle_r.vel_y = -5;
                if( !paddle_r.isMoving ){
                    paddle_r.acc_y = -20;
                    paddle_r.isMoving = true;
                }
            }else if( key_pressed() == SDLK_DOWN ){
                paddle_r.vel_y = 5;
                if( !paddle_r.isMoving ){
                    paddle_r.acc_y = 20;
                    paddle_r.isMoving = true;
                }
            }

            if( key_released() == SDLK_UP ){
                paddle_r.vel_y = 0;
            }else if( key_released() == SDLK_DOWN ){
                paddle_r.vel_y = 0;
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

    //screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF );
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );


    //SDL_ShowCursor( SDL_DISABLE );

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
    points_l = 0;
    points_r = 0;

    ball.w = 10;
    ball.h = 10;
    ball.x = SCREEN_WIDTH / 2  - ball.w / 2;
    ball.y = SCREEN_HEIGHT / 2 - ball.h / 2;
    ball.prev_x = ball.x;
    ball.prev_y = ball.y;
    ball.vel_x = 4;
    ball.vel_y = 4;
    ball.acc_x = 0;
    ball.acc_y = 0;

    paddle_r.w = 5;
    paddle_r.h = 50;
    paddle_r.x = SCREEN_WIDTH - (paddle_r.w + 5);
    paddle_r.y = SCREEN_HEIGHT / 2 - paddle_r.h / 2;
    paddle_r.vel_x = 0;
    paddle_r.vel_y = 0;
    paddle_r.acc_x = 0;
    paddle_r.acc_y = 0;
    paddle_r.isMoving = false;
}

void
reset_ball(){
    ball.x = SCREEN_WIDTH / 2  - ball.w / 2;
    ball.y = SCREEN_HEIGHT / 2 - ball.h / 2;
    ball.prev_x = ball.x;
    ball.prev_y = ball.y;
    ball.vel_x = 4;
    ball.vel_y = 4;
    ball.acc_x = 0;
    ball.acc_y = 0;
}

void
update_game( float dt )
{
     SDL_Rect r_ball;

     fprintf(stdout, "acc_y = %d\n", paddle_r.acc_y);

     if( paddle_r.vel_y == 0 ){
         paddle_r.isMoving = false;
     }

     //ball.vel_x = ball.vel_x * dt;
     //ball.vel_y = ball.vel_y * dt;
     ball.vel_x += ball.acc_x;
     ball.vel_y += ball.acc_y;
     paddle_r.vel_y += paddle_r.acc_y;

     if( paddle_r.acc_y > 0 ){
         paddle_r.acc_y--;
     }else if( paddle_r.acc_y < 0 ){
         paddle_r.acc_y++;
     }
    
     if( ball.acc_x > 0 ){
        ball.acc_x--;
     }else if( ball.acc_x < 0 ){
        ball.acc_x++;
     }

     // Checking for wall collisions
     // Left Wall
     if( ball.x <= 0 && ball.vel_x < 0 ){
         //ball.vel_x = -1 * ball.vel_x;
         //ball.acc_x = -1 * ball.acc_x;
         reset_ball();
     }
     // Right Wall
     if( ball.x + ball.w >= SCREEN_WIDTH && ball.vel_x > 0){
         //ball.vel_x = -1 * ball.vel_x;
         //ball.acc_x = -1 * ball.acc_x;
         reset_ball();
     }
     // Top Wall
     if( ball.y <= 0 && ball.vel_y < 0 ){
         ball.vel_y = -1 * ball.vel_y;
         //ball.acc_y = -1 * ball.acc_y;
     }
     // Bottom Wall
     if( ball.y + ball.h >= SCREEN_HEIGHT && ball.vel_y > 0 ){
         ball.vel_y = -1 * ball.vel_y;
         //ball.acc_y = -1 * ball.acc_y;
     }

    ball.x += ball.vel_x;
    ball.y += ball.vel_y;


    if( paddle_r.y <= 0 && paddle_r.vel_y < 0 ){
        paddle_r.vel_y = 0;
    }

    if( paddle_r.y + paddle_r.h >= SCREEN_HEIGHT && paddle_r.vel_y > 0 ){
        paddle_r.vel_y = 0;
    }

    paddle_r.x += paddle_r.vel_x;
    paddle_r.y += paddle_r.vel_y;

    //Paddle collisions
    if( (ball.x + ball.w) >= paddle_r.x && ball.y >= paddle_r.y && ball.y + ball.h <= paddle_r.y + paddle_r.h ){
        //ball.vel_x = -1 * ball.vel_x;
        ball.acc_x = -5;
        //ball.vel_x = -1 * ball.vel_x + paddle_r.acc;
    }
}

void render( float in )
{
    SDL_Rect r_ball, r_paddle_r;
    int prev_x, prev_y;
    
    r_ball.w = ball.w;
    r_ball.h = ball.h;
    r_ball.x = ball.x * in + (ball.prev_x * (1 - in));
    r_ball.y = ball.y * in + (ball.prev_y * (1 - in));

    //SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    SDL_BlitSurface( ball_img, NULL, screen, &r_ball );

    r_paddle_r.w = paddle_r.w;
    r_paddle_r.h = paddle_r.h;
    r_paddle_r.x = paddle_r.x * in + (paddle_r.prev_x * (1 - in));
    r_paddle_r.y = paddle_r.y * in + (paddle_r.prev_y * (1 - in));

    SDL_FillRect( screen, &r_paddle_r,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
    SDL_Flip(screen);

    ball.prev_x = ball.x;
    ball.prev_y = ball.y;

    paddle_r.prev_x = paddle_r.x;
    paddle_r.prev_y = paddle_r.y;

    // Removing the already drawn object ** This works
    SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0, 0, 0 ) );
    SDL_FillRect( screen, &r_paddle_r,SDL_MapRGB( screen->format, 0, 0, 0 ) );
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

int
key_released()
{
    if( event.type == SDL_KEYUP ){
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
