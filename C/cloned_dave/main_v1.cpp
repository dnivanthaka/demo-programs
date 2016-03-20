/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Dave/Mario Clone, Compile with g++ main.cpp -o dave -lSDL -lSDL_image
 *
 *        Version:  1.0
 *        Created:  12/21/2011 10:19:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <sstream>

#define mag(x): return (x < 0) ? (-1 * x) : x

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int frame_delay = 25; // milli's

int sm_sprite_w = 30;
int sm_sprite_h = 30;

int player_anim_fps = 2;

SDL_Surface *background   = NULL;
SDL_Surface *state_image  = NULL;
SDL_Surface *screen       = NULL;

SDL_Event event;

bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;

enum dir {
    LEFT, RIGHT, JUMP, CROUCH
};

typedef struct frame {
    int x;
    int y;
} frame;

//TTF_Font *font = NULL;

//SDL_Color textColor = { 255, 255, 255 };

//SDL_Rect clip[ 4 ];

struct player {
    int w;
    int h;
    int screen_x;
    int screen_y;
    dir c_d;
    int c_sp_offset;
    int c_vel_x;
    int c_vel_y;
    frame l_frames[4];
    frame r_frames[4];
    frame j_frames[2];
    frame c_frames[2];
    SDL_Rect current_bg;
};

SDL_Surface 
*load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL, *optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        if( optimizedImage != NULL ){
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void
apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool
init()
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
        return false;

    SDL_WM_SetCaption( "Cloned Mario", NULL );    

    return true;
}

bool
load_files()
{
    background = load_image( "background.png" );
    state_image = load_image( "mario-brothers.png" );
    //dots        = load_image( "dots.png" );

    //state_image = load_image( "button.png" );

    if( state_image == NULL )
        return false;

    return true;
}

void
clean_up()
{    
    SDL_FreeSurface( background );
    SDL_FreeSurface( state_image );
    
    //TTF_CloseFont( font );

    //TTF_Quit();

    //TTF_Quit();

    SDL_Quit();
}

void
check_screen_bounds( struct frame *fr )
{
    
}

void
animate_player( struct player *p, dir d, int start_frame )
{
    int i;
    SDL_Rect tmp;
    unsigned int start_time, end_time;
    int mv_val= 0;
    int frame_count = 0;

    frame *f_ptr;
    //f_ptr = &test[0];

    if( d == RIGHT ){
        f_ptr = &p->r_frames[0];
        mv_val = p->c_vel_x;
        frame_count = 4;
    }else if( d == LEFT ){
        f_ptr = &p->l_frames[0];
        mv_val = -1 * (p->c_vel_x);
        frame_count = 4;
    }else if( d == JUMP ){
        f_ptr = &p->j_frames[0];
        mv_val = -4;
        frame_count = 1;
    }
       
    

    if( d == RIGHT || d == LEFT ){
        for( i=0;i<frame_count;i++ ){
            start_time = SDL_GetTicks();
            // Apply previous background
            //apply_surface( p->screen_x, p->screen_y, background, screen, &p->current_bg );
            
            p->current_bg.x = p->screen_x;
            p->current_bg.y = p->screen_y;
            p->current_bg.w = p->w;
            p->current_bg.h = p->h;

            apply_surface( p->screen_x, p->screen_y, background, screen, &p->current_bg );

            //tmp.x = p->r_frames[i].x;
            tmp.x = (f_ptr + i)->x;
            //tmp.y = p->r_frames[i].y;
            tmp.y = (f_ptr + i)->y;
            tmp.w = p->w;
            tmp.h = p->h;

            // Im limiting the movement here
            //p->screen_x = (p->screen_x + mv_val) % SCREEN_WIDTH;
            p->screen_x = p->screen_x + mv_val;
            p->screen_x = (p->screen_x <= 0) ? 0 : (p->screen_x >= 620) ? 620 : p->screen_x;
            //printf("pitch = %d\n", screen->pitch);
            //printf("width = %d\n", screen->w);
            apply_surface( p->screen_x, p->screen_y, state_image, screen, &tmp );

            if( SDL_Flip( screen ) == -1 )
            {
                return;
            }

            end_time = SDL_GetTicks();
            /*
            if((end_time - start_time) < (player_anim_fps * 100)){
                SDL_Delay( (player_anim_fps * 100) - (end_time - start_time) );
            }
            */
            if( (SDL_GetTicks() -  start_time) <= (frame_delay + 25) ){
                SDL_Delay( (frame_delay + 25) -  (SDL_GetTicks() -  start_time) );
            }
            //SDL_Delay(50);
        }
        // Resetting to initial position
        apply_surface( p->screen_x, p->screen_y, background, screen, &p->current_bg );

        tmp.x = (f_ptr + start_frame)->x;
        tmp.y = (f_ptr + start_frame)->y;
        tmp.w = p->w;
        tmp.h = p->h;

        p->current_bg.x = p->screen_x;
        p->current_bg.y = p->screen_y;
        p->current_bg.w = p->w;
        p->current_bg.h = p->h;

        apply_surface( p->screen_x, p->screen_y, state_image, screen, &tmp );

        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }
    }else if( d == JUMP ){

    }
}

bool
handle_events()
{
    while( SDL_PollEvent( &event ) ){
           //if( message != NULL ){
       if( event.type == SDL_KEYDOWN ){

           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               right_pressed = true;
               //mario->put( background, screen, sprite_sheet, 1 );
               break;
               case SDLK_LEFT:
               left_pressed = true;
               //mario->put( background, screen, sprite_sheet, 0 );
               break;
               case SDLK_UP:
               up_pressed = true;
               break;
               case SDLK_DOWN:
               down_pressed = true;
               break;
           }
       }else if(event.type == SDL_KEYUP){
           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               right_pressed = false;
               break;
               case SDLK_LEFT:
               left_pressed = false;
               break;
               case SDLK_UP:
               up_pressed = false;
               break;
               case SDLK_DOWN:
               down_pressed = false;
               break;
           }
       }else if( event.type == SDL_QUIT ){
           return true;
       }
    }
}

int
main ( int argc, char *argv[] )
{
    struct player d;    
    bool quit = false;
    int player_x  = 0;
    int player_y  = 0;
    SDL_Rect tmp;
    SDL_Rect old_bak;
    bool is_jumping = false;
    int initial_jmp_vel = 100;
    int accel = 1;

    float start_tick = 0;
    float tick_diff = 0;

    if( init() == false )
        return EXIT_FAILURE;
    if( load_files() == false )
        return EXIT_FAILURE;
    
    d.w = sm_sprite_w;
    d.h = sm_sprite_h;
    d.c_d = RIGHT;
    d.c_sp_offset = 7;
    d.c_vel_x = 6;
    d.c_vel_y = 6;

    d.r_frames[0].x = sm_sprite_w * d.c_sp_offset;
    d.r_frames[0].y = sm_sprite_h * 0;

    d.r_frames[1].x = sm_sprite_w * (d.c_sp_offset + 1);
    d.r_frames[1].y = sm_sprite_h * 0;

    d.r_frames[2].x = sm_sprite_w * (d.c_sp_offset + 2);
    d.r_frames[2].y = sm_sprite_h * 0;

    d.r_frames[3].x = sm_sprite_w * (d.c_sp_offset + 3);
    d.r_frames[3].y = sm_sprite_h * 0;
    
    d.l_frames[0].x = sm_sprite_w * (d.c_sp_offset - 1);
    d.l_frames[0].y = sm_sprite_h * 0;

    d.l_frames[1].x = sm_sprite_w * (d.c_sp_offset - 2);
    d.l_frames[1].y = sm_sprite_h * 0;

    d.l_frames[2].x = sm_sprite_w * (d.c_sp_offset - 3);
    d.l_frames[2].y = sm_sprite_h * 0;

    d.l_frames[3].x = sm_sprite_w * (d.c_sp_offset - 4);
    d.l_frames[3].y = sm_sprite_h * 0;

    d.j_frames[0].x = sm_sprite_w * (d.c_sp_offset + 5);
    d.j_frames[0].y = sm_sprite_h * 0;

    d.j_frames[1].x = sm_sprite_w * (d.c_sp_offset - 6);
    d.j_frames[1].y = sm_sprite_h * 0;;

    // Applying the background
    apply_surface( 0, 0, background, screen );

    player_x  = (screen->w / 2) - (d.w / 2);
    player_y  = (screen->h / 2) - (d.h / 2);

    // setting player screen coordinates

    d.screen_x = player_x;
    d.screen_y = player_y;

    d.current_bg.x = d.screen_x;
    d.current_bg.y = d.screen_y;
    d.current_bg.w = d.w;
    d.current_bg.h = d.h;

    tmp.x = d.r_frames[0].x;
    tmp.y = d.r_frames[0].y;
    tmp.w = d.w;
    tmp.h = d.h;

    apply_surface( player_x, player_y, state_image, screen, &tmp );

    if( SDL_Flip( screen ) == -1 ){
        return EXIT_FAILURE;
    }

    while( quit == false ){

        start_tick = SDL_GetTicks();

        quit = handle_events();

        //tick_diff = SDL_GetTicks() - last_tick;
        //last_tick = SDL_GetTicks();
        

        if( right_pressed && !is_jumping ){
            //animate( SDL_Surface *frames, int start_frame );
            if( d.c_d != RIGHT ){
                //tmp.x = d.r_frames[0].x;
                //tmp.y = d.r_frames[0].y;
                //tmp.w = d.w;
                //tmp.h = d.h;
                //apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

                d.current_bg.x = d.screen_x;
                d.current_bg.y = d.screen_y;
                d.current_bg.w = d.w;
                d.current_bg.h = d.h;

                apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

                tmp.x = d.r_frames[0].x;
                tmp.y = d.r_frames[0].y;
                tmp.w = d.w;
                tmp.h = d.h;

                d.c_d = RIGHT;

                apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
            }
            animate_player( &d, RIGHT, 0 );
        }

        if( left_pressed && !is_jumping ){
            //animate( SDL_Surface *frames, int start_frame );
            if( d.c_d != LEFT ){
                //tmp.x = d.r_frames[0].x;
                //tmp.y = d.r_frames[0].y;
                //tmp.w = d.w;
                //tmp.h = d.h;
                //apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

                d.current_bg.x = d.screen_x;
                d.current_bg.y = d.screen_y;
                d.current_bg.w = d.w;
                d.current_bg.h = d.h;
                
                apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

                tmp.x = d.l_frames[0].x;
                tmp.y = d.l_frames[0].y;
                tmp.w = d.w;
                tmp.h = d.h;

                d.c_d = LEFT;

                apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
            }
            animate_player( &d, LEFT, 0 );
        }

        if( up_pressed ){
                /*
                apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

                d.current_bg.x = d.screen_x;
                d.current_bg.y = d.screen_y;
                d.current_bg.w = d.w;
                d.current_bg.h = d.h;

                tmp.x = d.j_frames[0].x;
                tmp.y = d.j_frames[0].y;
                tmp.w = d.w;
                tmp.h = d.h;

                d.screen_y -= 1;

                apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
                SDL_Delay(10);
            */
            //animate_player( &d, JUMP, 0 );
            //initial_jmp_vel = 10;
            if( is_jumping == false )
                initial_jmp_vel = 20;

            is_jumping = true;
            //accel = 6;
            //f_vel[Y] += GRAVITY * f_ticksDiff;

		    //i_pos[X] += (int)(f_vel[X] * f_ticksDiff);
		    //i_pos[Y] += (int)(f_vel[Y] * f_ticksDiff);
            

        }
        if( is_jumping ){
           //apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

            d.current_bg.x = d.screen_x;
            d.current_bg.y = d.screen_y;
            d.current_bg.w = d.w;
            d.current_bg.h = d.h;

           apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

            if( d.c_d == RIGHT ){
                tmp.x = d.j_frames[0].x;
                tmp.y = d.j_frames[0].y;
            }else{
                tmp.x = d.j_frames[1].x;
                tmp.y = d.j_frames[1].y;
            }
            tmp.w = d.w;
            tmp.h = d.h;

            initial_jmp_vel = initial_jmp_vel - accel;
            d.screen_y = d.screen_y - initial_jmp_vel;

            if( left_pressed )
                d.screen_x -= (d.c_vel_x - 2);
            if( right_pressed )
                d.screen_x = (d.screen_x + (d.c_vel_x - 2)) % SCREEN_WIDTH;

            d.screen_x = (d.screen_x <= 0) ? 0 : (d.screen_x >= 620) ? 620 : d.screen_x;

            //printf("%d\n", d.screen_y);

            apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
            //SDL_Delay(20);
        }
        /*
        if( !up_pressed && is_jumping ){
                apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

                d.current_bg.x = d.screen_x;
                d.current_bg.y = d.screen_y;
                d.current_bg.w = d.w;
                d.current_bg.h = d.h;

                if( d.c_d == RIGHT ){
                    tmp.x = d.r_frames[0].x;
                    tmp.y = d.r_frames[0].y;
                }else{
                    tmp.x = d.l_frames[0].x;
                    tmp.y = d.l_frames[0].y;
                }
                tmp.w = d.w;
                tmp.h = d.h;

                //initial_jmp_vel = initial_jmp_vel - accel;                
                //d.screen_y = d.screen_y - initial_jmp_vel;
                //initial_jmp_vel = (int)(initial_jmp_vel + 1) * tick_diff;
                //d.screen_y = d.screen_y + (int)(initial_jmp_vel * tick_diff);
                //d.screen_y -= (4 - accel);
                //accel -= 2;
                //initial_jmp_vel = initial_jmp_vel - accel;
                //d.screen_y -= initial_jmp_vel;
                //accel--;
                //d.screen_y = (accel-- > 0 ) ? (d.screen_y - accel) : (d.screen_y + accel);
                //initial_jmp_vel = initial_jmp_vel - accel;
                //d.screen_y = d.screen_y + initial_jmp_vel;
                //d.screen_y -= accel--;
                //accel = (accel <= 0) ? accel++: accel--;
                //accel = ( accel < 0 ) ? (accel + 1) : accel;
                d.screen_y = d.screen_y + initial_jmp_vel;
                initial_jmp_vel = initial_jmp_vel + accel;
                //d.screen_y += 1;
                //printf("%d\n", accel);

                apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
                SDL_Delay(20);
        }
        */
        
        if( d.screen_y >= player_y && is_jumping ){
            apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

            d.current_bg.x = d.screen_x;
            d.current_bg.y = d.screen_y;
            d.current_bg.w = d.w;
            d.current_bg.h = d.h;

            if( d.c_d == RIGHT ){
                tmp.x = d.r_frames[0].x;
                tmp.y = d.r_frames[0].y;
            }else{
                tmp.x = d.l_frames[0].x;
                tmp.y = d.l_frames[0].y;
            }
            tmp.w = d.w;
            tmp.h = d.h;

            apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );            
        
            is_jumping = false;
            initial_jmp_vel = 20;
            //accel = 10;
        }

        if( SDL_Flip( screen ) == -1 )
        {
            return EXIT_FAILURE;
        }

        if( SDL_GetTicks() - start_tick <= frame_delay ){
            //printf("xxx");
            SDL_Delay( frame_delay - (SDL_GetTicks() - start_tick) );
        }
    }

    //SDL_Delay(5000);

    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
