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

include "globals.h"
// -------------------------------------------------------------------------------------
// PUBLIC DATA -------------------------------------------------------------------------

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
void update_game();
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
            update_game();

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


void
init_entities()
{
    ball.w = 10;
    ball.h = 10;
    ball.x = SCREEN_WIDTH / 2  - ball.w / 2;
    ball.y = SCREEN_HEIGHT / 2 - ball.h / 2;
    ball.prev_x = ball.x;
    ball.prev_y = ball.y;
    ball.vel_x = 5;
    ball.vel_y = 5;
    ball.acc_x = 0;
    ball.acc_y = 0;
}

void
update_game()
{
    SDL_Rect r_ball;
     // Checking for wall collisions
     // Left Wall
     if( ball.x + ball.vel_x <= 0 ){
         ball.vel_x = -1 * ball.vel_x;
     }
     // Right Wall
     if( ball.x + ball.vel_x + ball.w >= SCREEN_WIDTH ){
         ball.vel_x = -1 * ball.vel_x;
     }
     // Top Wall
     if( ball.y + ball.vel_y <= 0 ){
         ball.vel_y = -1 * ball.vel_y;
     }
     // Bottom Wall
     if( ball.y + ball.vel_y + ball.h >= SCREEN_HEIGHT ){
         ball.vel_y = -1 * ball.vel_y;
     }

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


    printf("intr = %d\n", (int)in);

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

    printf("ball_x = %d\n", (int)r_ball.x);
    printf("ball_y = %d\n", (int)r_ball.y);

    SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

    SDL_Flip(screen);

    ball.prev_x = ball.x;
    ball.prev_y = ball.y;

    // Removing the already drawn object ** This works
    //SDL_FillRect( screen, &r_ball,SDL_MapRGB( screen->format, 0, 0, 0 ) );
    SDL_FillRect( screen, NULL,SDL_MapRGB( screen->format, 0, 0, 0 ) );
}

void
clean_up()
{
    SDL_FreeSurface( screen );

    TTF_CloseFont( font_basic );
    TTF_Quit();
    SDL_Quit();
}

