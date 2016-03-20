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
==============================
w = 16
h = 16
screen x = 336
screen y = 464
type = 1
==============================


 */

#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <sstream>
#include <iostream>
#include <math.h>

#include "gtypedef.h"
#include "player.h"
#include "events.h"
#include "entities.h"
#include "level.h"
#include "graphics.h"


#define mag(x): return (x < 0) ? (-1 * x) : x

// Screen attributes
//const int SCREEN_WIDTH  = 640;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP    = 32;
/*const int frame_delay = 25; // milli's*/

int sm_sprite_w = 16;
int sm_sprite_h = 16;

int player_anim_fps = 2;

SDL_Surface *background   = NULL;
SDL_Surface *object_sheet = NULL;
SDL_Surface *state_image  = NULL;
SDL_Surface *screen       = NULL;

SDL_Event event;

bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;

//extern player_t d;
player_t d;
/*
enum direction {
    LEFT, RIGHT, JUMP, CROUCH
};

typedef struct frame {
    int x;
    int y;
} frame;
*/

//TTF_Font *font = NULL;

//SDL_Color textColor = { 255, 255, 255 };

//SDL_Rect clip[ 4 ];
/*
struct player {
    int w;
    int h;
    int screen_x;
    int screen_y;
    direction c_d;
    int c_sp_offset;
    int vel_x;
    int vel_y;
    frame l_frames[4];
    frame r_frames[4];
    frame j_frames[2];
    frame c_frames[2];
    SDL_Rect current_bg;
};
*/
/*
struct game_object {
    int w;
    int h;
    int screen_x;
    int screen_y;
    int o_type;
    struct game_object *next;
};
*/

int level1[24][40] = {
{01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
{01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01},
};

/*
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
*/

/*
void
apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}
*/

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
    background   = load_image( "background.png" );
    state_image  = load_image( "mario3.png" );
    object_sheet = load_image( "object_tiles.jpg" );
    //object_sheet = load_image( "SMB-Tiles.gif" );
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
    SDL_FreeSurface( object_sheet );
    
    //TTF_CloseFont( font );

    //TTF_Quit();

    //TTF_Quit();

    SDL_Quit();
}

void
load_level()
{
    int i, j;
    /*
    for( i=0;i<24;i++ ){
        for(j=0;j<40;j++){
            if( level1[ i ][ j ] == 01 ){
                //printf("01 ");
                SDL_Rect tmp;
                tmp.w = 16;
                tmp.h = 16;
                tmp.x = 17 * 0;
                tmp.y = 0;
                apply_surface( j * tmp.w % SCREEN_WIDTH, i * tmp.h, object_sheet, screen, &tmp );
             }
        }
    }
    */
    for( i=0;i < (SCREEN_HEIGHT / 16);i++ ){
        for( j=0;j<(SCREEN_WIDTH / 16);j++ ){
            SDL_Rect tmp;
            tmp.w = 16;
            tmp.h = 16;
            tmp.x = 17 * 0;
            tmp.y = 0;
            if( i == 0 || i == (SCREEN_HEIGHT / 16) - 1 ){
                apply_surface( j * tmp.w % SCREEN_WIDTH, i * tmp.h, object_sheet, screen, &tmp );
            }else if (j == 0 || j == (SCREEN_WIDTH / 16) - 1){
                apply_surface( j * tmp.w % SCREEN_WIDTH, i * tmp.h, object_sheet, screen, &tmp );
            }

            
        }
    }
}

void
draw_level( SDL_Surface *screen, level *lvl, struct ga_object *go )
{
    int i, j, c = 0;

    for( i=0; i<lvl->height; i++ ){
        for( j=0; j<((lvl->width - 1) / 2); j++ ){
            SDL_Rect tmp;
            tmp.w = 16;
            tmp.h = 16;
            tmp.x = 17 * 0;
            tmp.y = 0;
            if( get_obj_type( lvl, j, i ) == 01 ){
                apply_surface( j * tmp.w, i * tmp.h, object_sheet, screen, &tmp );
                //printf("***\n");
                //c++;
                //printf("%d ", j * tmp.w);
                add_object( go, tmp.w, tmp.h, j * tmp.w, i * tmp.h, 01 );
            }
        }
    }

    //printf(" c = %d\n", c);
}





bool
handle_events()
{
    event_t key_ev;

    while( SDL_PollEvent( &event ) ){
           //if( message != NULL ){
       if( event.type == SDL_KEYDOWN ){

           key_ev.type = ev_keydown;

           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               key_ev.sym.sym = SDLK_RIGHT;
               enqueue_event( &key_ev );
               //right_pressed = true;
               //mario->put( background, screen, sprite_sheet, 1 );
               break;
               case SDLK_LEFT:
               key_ev.sym.sym = SDLK_LEFT;
               enqueue_event( &key_ev );
               //left_pressed = true;
               //mario->put( background, screen, sprite_sheet, 0 );
               break;
               case SDLK_UP:
               key_ev.sym.sym = SDLK_UP;
               enqueue_event( &key_ev );
               //up_pressed = true;
               break;
               case SDLK_DOWN:
               key_ev.sym.sym = SDLK_DOWN;
               enqueue_event( &key_ev );
               //down_pressed = true;
               break;
           }
       }else if(event.type == SDL_KEYUP){

           key_ev.type = ev_keyup;

           switch( event.key.keysym.sym ){
               case SDLK_RIGHT:
               key_ev.sym.sym = SDLK_RIGHT;
               enqueue_event( &key_ev );
               //right_pressed = false;
               break;
               case SDLK_LEFT:
               key_ev.sym.sym = SDLK_LEFT;
               enqueue_event( &key_ev );
               //left_pressed = false;
               break;
               case SDLK_UP:
               key_ev.sym.sym = SDLK_UP;
               enqueue_event( &key_ev );
               //up_pressed = false;
               break;
               case SDLK_DOWN:
               key_ev.sym.sym = SDLK_DOWN;
               enqueue_event( &key_ev );
               //down_pressed = false;
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
    //player_t d;  
  
    bool quit = false;
    int player_x  = 0;
    int player_y  = 0;
    SDL_Rect tmp;
    SDL_Rect old_bak;
    bool is_jumping = false;
    int initial_jmp_vel = 100;
    int accel = 1;
    level lvl;

    float start_tick = 0;
    float tick_diff = 0;

    int tmp_offset = 15;

    if( init() == false )
        return EXIT_FAILURE;
    if( load_files() == false )
        return EXIT_FAILURE;
    
    d.bg_ptr = background;
    d.sprites = state_image;
    
    d.w = sm_sprite_w;
    d.h = sm_sprite_h;
    d.direction = RIGHT;
    //tmp_offset = 7;
    d.vel_x = 4;
    d.vel_y = 4;

    d.r_frames[0].x = sm_sprite_w * tmp_offset;
    d.r_frames[0].y = sm_sprite_h * 0;

    d.r_frames[1].x = sm_sprite_w * (tmp_offset + 2);
    d.r_frames[1].y = sm_sprite_h * 0;

    d.r_frames[2].x = sm_sprite_w * (tmp_offset + 4);
    d.r_frames[2].y = sm_sprite_h * 0;

    d.r_frames[3].x = sm_sprite_w * (tmp_offset + 6);
    d.r_frames[3].y = sm_sprite_h * 0;
    
    d.l_frames[0].x = sm_sprite_w * (tmp_offset - 2);
    d.l_frames[0].y = sm_sprite_h * 0;

    d.l_frames[1].x = sm_sprite_w * (tmp_offset - 4);
    d.l_frames[1].y = sm_sprite_h * 0;

    d.l_frames[2].x = sm_sprite_w * (tmp_offset - 6);
    d.l_frames[2].y = sm_sprite_h * 0;

    d.l_frames[3].x = sm_sprite_w * (tmp_offset - 8);
    d.l_frames[3].y = sm_sprite_h * 0;

    d.j_frames[0].x = sm_sprite_w * (tmp_offset + 10);
    d.j_frames[0].y = sm_sprite_h * 0;

    d.j_frames[1].x = sm_sprite_w * (tmp_offset - 12);
    d.j_frames[1].y = sm_sprite_h * 0;

    
    //-------------- Remove this --------------------------
    //struct solid_object ob;
    struct ga_object *go;
    //go = NULL;
    go = ( struct ga_object * )malloc( sizeof(struct ga_object) );
    go->next = NULL;
    go->w = 0;
    go->h = 0;
    go->screen_x = 0;
    go->screen_y = 0;
    //SDL_Rect brick;

    //brick.w = 17;
    //brick.h = 17;
    //brick.x = 17 * 5;
    //brick.y = 0;
    
    //ob.w = 16 * 3;
    //ob.h = 16;
    //ob.screen_x = 100 + brick.w;
    //ob.screen_y = 340;
    //ob.w = 16;
    //ob.h = 16;
    //ob.image.w = 16;
    //ob.image.h = 16;
    //ob.image.x = 17 * 5;
    //ob.image.y = 0;

    // Applying the background
    SDL_FillRect( background, NULL, SDL_MapRGB( screen->format, 0, 0, 0 ) );
    apply_surface( 0, 0, background, screen );
    
    // Applying the object sheet
    //apply_surface( 100, 100, object_sheet, screen, &brick );
    //apply_surface( 100 + brick.w, 340, object_sheet, screen, &brick );
    //draw_solid_object( &ob, object_sheet, screen );

    player_x  = (screen->w / 2) - (d.w / 2);
    player_y  = (screen->h / 2) - (d.h / 2);
    //player_x  = lvl.start_pos.x;
    //player_y  = 100;

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

    //load_level();
    char t[3];
    int nValue = 5;
    void *pVoid = &nValue;
 
    // can not dereference pVoid because it is a void pointer
 
    
    //int *d_ptr = (int *)lvl.data;
    load_level_map( "level1.map", &lvl );
    printf("level width %d\n", lvl.width);
    printf("level height %d\n", lvl.height);
    printf("%d\n", get_obj_type( &lvl, 1, 13 ));
    //memcpy( (char *)lvl.data, t, 2 );
    //t[3] = '\0';
    //int *pInt = static_cast<int*>( d_ptr ); 
    //printf( "%p\n", lvl.data + 1 );
    //printf("%d\n", atoi(lvl.data) );
    //printf("%s\n", &c_ptr[1] );
    //printf("%d\n", *pInt );
    //printf("%d\n", *d_ptr );
    //printf("x%c\n", c_ptr[3] == );
      //printf("%d\n", get_level_val( &lvl, 2 ));  
      //printf("%c\n", *(&lvl.data[0]));
      /*
        if( c_ptr[0] == '1' ){
            printf("its 0\n");        
        }
      */
    //printf("S = %d\n", lvl.start_pos.x);
    //printf("S = %d\n", lvl.start_pos.y);
    d.screen_x = lvl.start_pos.x * 16;
    d.screen_y = lvl.start_pos.y * 16;

    apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
    draw_level( screen, &lvl, go);
    print_ga_objects( go );

    //printf("block x = %d\n", ob.screen_x);
    //printf("block y = %d\n", ob.screen_y);

    if( SDL_Flip( screen ) == -1 ){
        return EXIT_FAILURE;
    }

    init_event_queue();

    event_t *ev;

    int prev_x, prev_y, reg_x_off, reg_y_off, next_x, next_y;
    bool ascending = false;
    while( quit == false ){
    

        start_tick = SDL_GetTicks();

        quit = handle_events();

        //tick_diff = SDL_GetTicks() - last_tick;
        //last_tick = SDL_GetTicks();
        /*
        ev = dequeue_event();
        if( ev != NULL ){
            if(ev->type == ev_keydown){
                if( ev->sym.sym == SDLK_RIGHT ){
                    right_pressed = true;
                }
                if( ev->sym.sym == SDLK_LEFT ){
                    left_pressed = true;
                }
            }
            if( ev->type == ev_keyup ){
                printf("Im here");
                if( ev->sym.sym == SDLK_RIGHT ){
                    right_pressed = false;
                }
                if( ev->sym.sym == SDLK_LEFT ){
                    left_pressed = false;
                }
            }
        }
        */
        process_events();

        if( right_pressed && !is_jumping ){
            //animate( SDL_Surface *frames, int start_frame );
            if( d.direction != RIGHT ){
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

                d.direction = RIGHT;

                apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
            }
            //animate_player( &d, RIGHT, 0 );
            draw( &d, go, screen,  0 );
        }

        if( left_pressed && !is_jumping ){
            //animate( SDL_Surface *frames, int start_frame );
            if( d.direction != LEFT ){
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

                d.direction = LEFT;

                apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );
            }
            //animate_player( &d, LEFT, 0 );
            //d.screen_x = d.screen_x + d.vel_x;
            //d.screen_x -= d.vel_x;
            
            //move_player( &d );
            draw( &d, go, screen,  0 );
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
            if( is_jumping == false ){
                //initial_jmp_vel = player_can_jump( &d, &ob, 20 );
                initial_jmp_vel = 18;
                //printf( "jmp %d\n", initial_jmp_vel );
                prev_x = d.screen_x; 
                prev_y = d.screen_y;
                
            }

            is_jumping = true;
            ascending = true;
            //d.direction = JUMP;
            
            //accel = 6;
            //f_vel[Y] += GRAVITY * f_ticksDiff;

		    //i_pos[X] += (int)(f_vel[X] * f_ticksDiff);
		    //i_pos[Y] += (int)(f_vel[Y] * f_ticksDiff);
            

        }
        if( is_jumping ){
            //-----------------------------------------------------
        
            apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

            d.current_bg.x = d.screen_x;
            d.current_bg.y = d.screen_y;
            d.current_bg.w = d.w;
            d.current_bg.h = d.h;

            if( d.direction == RIGHT ){
                tmp.x = d.j_frames[0].x;
                tmp.y = d.j_frames[0].y;
            }else if( d.direction == LEFT ){
                tmp.x = d.j_frames[1].x;
                tmp.y = d.j_frames[1].y;
            }
            tmp.w = d.w;
            tmp.h = d.h;
            
            //-----------------------------------------------------
        
            next_y = d.screen_y;
            next_x = d.screen_x;

            initial_jmp_vel = initial_jmp_vel - accel;
            next_y = next_y - initial_jmp_vel;

            // Horizontal Movements -------------------------------
            if( left_pressed ){
                next_x = d.screen_x - (d.vel_x - 2);
               // d.screen_x -= (d.vel_x - 2);
                //d.direction = LEFT;
            }
            if( right_pressed ){
                next_x = (d.screen_x + (d.vel_x - 2));
                //d.screen_x = (d.screen_x + (d.vel_x - 2));
                //d.direction = RIGHT;
            }
            //-----------------------------------------------------
 
            if( initial_jmp_vel <= 0 ){
                ascending = false;
            }      

            //if( next_y <= (SCREEN_HEIGHT - 16) ){
                
            //}else{
                //is_jumping = false;
            //} 
            printf("dave x = %d\n", d.screen_x);
            printf("dave y = %d\n", d.screen_y);
            
            collision_info *t;
            if( (t = get_object(go, d.screen_x, d.screen_y, d.w, d.h )) != NULL ){
                printf("collision\n");
                if( t->hit == TOP_HIT ){
                    printf("TOP_HIT");
                    //if(is_jumping == true)
                    is_jumping = false;
                }else if( t->hit == BOTTOM_HIT ){
                    printf("BOTTOM_HIT");
                    //is_jumping = false;
                    //initial_jmp_vel = -20;
                }
            }else{
                d.screen_y = next_y;
                d.screen_x = next_x;
            }
            
            //d.screen_y = next_y;
            //d.screen_x = next_x;

            /*
            struct ga_object *t;
            if( (t = get_object(go, d.screen_x + d.w, d.screen_y + d.h, d.screen_x + d.w + d.w, d.screen_y + d.h + d.h )) != NULL ){
                printf("collision\n");
                printf("w = %d\n", t->w);
                printf("h = %d\n", t->h);
                printf("screen x = %d\n", t->screen_x);
                printf("screen y = %d\n", t->screen_y);
                printf("type = %d\n", t->o_type);
            }
            */

            apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );

            //SDL_Delay(20);
        }
         collision_info *t;
            /*
         if( (t = get_object(go, d.screen_x, d.screen_y, d.w, d.h )) != NULL ){
                //printf("collision\n");
                if( t->screen_y == 336 ){
                    printf("************************");
                    printf("w = %d\n", t->w);
                    printf("h = %d\n", t->h);
                    printf("screen x = %d\n", t->screen_x);
                    printf("screen y = %d\n", t->screen_y);
                    printf("type = %d\n", t->o_type);
                    printf("************************");
                }
        }
        */
        
        if( (t = get_object(go, d.screen_x, d.screen_y, d.w, d.h )) != NULL ){
                //printf("collision\n");
                if( t->hit == TOP_HIT ){
                    printf("========= Top Hit =============");
                }
                if( is_jumping == true)
                    is_jumping = false;
        }else{
             is_jumping = true;
             //initial_jmp_vel = -20;
             //d.screen_y -= d.vel_y;
        }
       /*
       if( d.screen_x >= ob.screen_x && d.screen_x <= (ob.screen_x + ob.w) ){
                printf("under %d\n", ob.screen_y + ob.h);
                if( d.screen_y >= (ob.screen_y + ob.h) ){
                    // dave is under and is close
                    printf("under and close\n");
                    //next_y = d.screen_y;
                }else if( (d.screen_y + d.h) <= ob.screen_y ){
                    // dave is above
                    printf("above\n");
                }
       }
        */
        /*
        if( ob.screen_x <= d.screen_x && (ob.screen_x + ob.w) >= d.screen_x && ob.screen_y <= d.screen_y && (ob.screen_y + ob.h) >= d.screen_y ){
            printf("collision\n");

            if( d.screen_y >= (ob.screen_y + ob.h) ){
                d.screen_y = ob.screen_y + ob.h;
            }else{
                d.screen_y = ob.screen_y - d.h;
            }

            //is_jumping = false;
        }
        */

        
        if( d.screen_y >= (SCREEN_HEIGHT - (16 + 16)) && is_jumping ){
            apply_surface( d.screen_x, d.screen_y, background, screen, &d.current_bg );

            d.current_bg.x = d.screen_x;
            d.current_bg.y = d.screen_y;
            d.current_bg.w = d.w;
            d.current_bg.h = d.h;

            if( d.direction == RIGHT ){
                tmp.x = d.r_frames[0].x;
                tmp.y = d.r_frames[0].y;
            }else{
                tmp.x = d.l_frames[0].x;
                tmp.y = d.l_frames[0].y;
            }
            tmp.w = d.w;
            tmp.h = d.h;

            d.screen_y = (SCREEN_HEIGHT - (16 + 16));

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
    clean_up();
    //if( lvl.data != NULL )
        free( lvl.data );
    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
