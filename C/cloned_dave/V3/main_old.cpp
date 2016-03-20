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
#include <iostream>

#include "gtypedef.h"
#include "level.h"
#include "graphics.h"
#include "player.h"

#define mag(x): return (x < 0) ? (-1 * x) : x

// Screen attributes
//const int SCREEN_WIDTH  = 640;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP    = 32;
/*const int frame_delay = 25; // milli's*/

int sm_sprite_w = 15;
int sm_sprite_h = 15;

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

struct solid_object {
    int w;
    int h;
    int screen_x;
    int screen_y;
    bool repeat;
    SDL_Rect image;
};

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
    state_image  = load_image( "mario-brothers.png" );
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
draw_level( SDL_Surface *screen, level *lvl )
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
            }
        }
    }

    //printf(" c = %d\n", c);
}


bool
detect_collision( struct solid_object *ob, struct player *d )
{
    bool ret = false;

    if( d->screen_x >= ob->screen_x && (ob->screen_x + ob->w) >= d->screen_x ){
            printf("collision\n");
            //&& (d->screen_x) >= d->screen_x
            //ob->screen_x <= d->screen_x && (ob->screen_x + ob->w) >= d->screen_x && (ob->screen_y + ob->h) >= d->screen_y
            //&& ob->screen_y >= (d->screen_y + ob->h)  
            /*
            if( d->screen_y >= (ob->screen_y + ob->h) ){
                d->screen_y = ob->screen_y + ob->h;
            }else{
                d->screen_y = ob->screen_y - d->h;
            }
            */

            //is_jumping = false;
            //ret = true;
            if( ob->screen_y + ob->h >= d->screen_y && ob->screen_y <= (d->screen_y + d->h) ){
                ret = true;
            }
    }
    /*
    else if( d->screen_x >= ob->screen_x && (ob->screen_x + ob->w) >= d->screen_x  && (ob->screen_y) <= (d->screen_y + d->h)) ){

    }
    */

    //if( ob->screen_y >= d->screen_y && (ob->screen_y + ob->h) <= d->screen_y && (d->screen_x + d->w) <= ob->screen_x ){
            //ret = true;
    //}
    //if(  ){}
        
    return ret;
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
    level lvl;

    float start_tick = 0;
    float tick_diff = 0;

    int tmp_offset = 7;

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
    d.vel_x = 6;
    d.vel_y = 6;

    d.r_frames[0].x = sm_sprite_w * 2 * tmp_offset;
    d.r_frames[0].y = sm_sprite_h * 0;

    d.r_frames[1].x = sm_sprite_w * 2 * (tmp_offset + 1);
    d.r_frames[1].y = sm_sprite_h * 0;

    d.r_frames[2].x = sm_sprite_w * 2 * (tmp_offset + 2);
    d.r_frames[2].y = sm_sprite_h * 0;

    d.r_frames[3].x = sm_sprite_w * 2 * (tmp_offset + 3);
    d.r_frames[3].y = sm_sprite_h * 0;
    
    d.l_frames[0].x = sm_sprite_w * 2 * (tmp_offset - 1);
    d.l_frames[0].y = sm_sprite_h * 0;

    d.l_frames[1].x = sm_sprite_w * 2 * (tmp_offset - 2);
    d.l_frames[1].y = sm_sprite_h * 0;

    d.l_frames[2].x = sm_sprite_w * 2 * (tmp_offset - 3);
    d.l_frames[2].y = sm_sprite_h * 0;

    d.l_frames[3].x = sm_sprite_w * 2 * (tmp_offset - 4);
    d.l_frames[3].y = sm_sprite_h * 0;

    d.j_frames[0].x = sm_sprite_w * 2 * (tmp_offset + 5);
    d.j_frames[0].y = sm_sprite_h * 0;

    d.j_frames[1].x = sm_sprite_w * 2 * (tmp_offset - 6);
    d.j_frames[1].y = sm_sprite_h * 0;

    
    //-------------- Remove this --------------------------
    struct solid_object ob;
    /*
    SDL_Rect brick;

    brick.w = 17;
    brick.h = 17;
    brick.x = 17 * 5;
    brick.y = 0;
    */
    ob.w = 16 * 3;
    ob.h = 16;
    ob.screen_x = 100;
    ob.screen_y = 100;
    ob.image.w = 16;
    ob.image.h = 16;
    ob.image.x = 17 * 5;
    ob.image.y = 0;

    // Applying the background
    SDL_FillRect( background, NULL, SDL_MapRGB( screen->format, 0, 0, 0 ) );
    apply_surface( 0, 0, background, screen );
    
    // Applying the object sheet
    //apply_surface( 100, 100, object_sheet, screen, &brick );
    //apply_surface( 100 + brick.w, 100, object_sheet, screen, &brick );
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
    draw_level( screen, &lvl );

    if( SDL_Flip( screen ) == -1 ){
        return EXIT_FAILURE;
    }
    int prev_x, prev_y, reg_x_off, reg_y_off;
    while( quit == false ){
    

        start_tick = SDL_GetTicks();

        quit = handle_events();

        //tick_diff = SDL_GetTicks() - last_tick;
        //last_tick = SDL_GetTicks();

        
        

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
            draw( &d, &lvl, screen,  0 );
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
            draw( &d, &lvl, screen,  0 );
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
            //d.direction = JUMP;
            
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

            if( d.direction == RIGHT ){
                tmp.x = d.j_frames[0].x;
                tmp.y = d.j_frames[0].y;
            }else if( d.direction == LEFT ){
                tmp.x = d.j_frames[1].x;
                tmp.y = d.j_frames[1].y;
            }
            tmp.w = d.w;
            tmp.h = d.h;

            prev_x = d.screen_x;
            prev_y = d.screen_y;

            initial_jmp_vel = initial_jmp_vel - accel;
            d.screen_y = d.screen_y - initial_jmp_vel;
        
            if( left_pressed ){
                d.screen_x -= (d.vel_x - 2);
                d.direction = LEFT;
            }
            if( right_pressed ){
                d.screen_x = (d.screen_x + (d.vel_x - 2)) % SCREEN_WIDTH;
                d.direction = RIGHT;
            }

            d.screen_x = (d.screen_x <= 0) ? 0 : (d.screen_x >= (SCREEN_WIDTH - d.w)) ? (SCREEN_WIDTH - d.w) : d.screen_x;
            /*
            if( d.direction == LEFT ){
                reg_x_off = d.screen_x;
                reg_y_off = d.screen_y + 16;
            }
            if( d.direction == RIGHT ){
                reg_x_off = d.screen_x + 16;
                reg_y_off = d.screen_y + 16;
            }
            if( d.direction == JUMP ){
                //reg_x_off = d.screen_x + 16;
                reg_y_off = d.screen_y + 16;
            }

            if( get_obj_type( &lvl, reg_x_off / 16, reg_y_off / 16 ) == 01 ){
                d.screen_x = prev_x;
                d.screen_y = prev_y;
            }
            */
            
            /*
            if( get_obj_type( &lvl, d.screen_x / 16, d.screen_y / 16 ) == 01 ){
                d.screen_x = prev_x;  
                d.screen_y = prev_y;              
                    
                is_jumping = false;
            }
            */

            /*
            if( detect_collision( &ob, &d ) ){
                if( d.screen_y >= (ob.screen_y + ob.h) ){
                    d.screen_y = ob.screen_y - ob.h;
                    
                }else{
                    //ob.screen_y
                    d.screen_y = ob.screen_y - d.h;
                    player_y = d.screen_y;
                    
                }
                //is_jumping = false;
                initial_jmp_vel = -10;
            }
            */
            /*
            if( ob.screen_x <= d.screen_x && (ob.screen_x + ob.w) >= (d.screen_x) ){
                printf("collision %d\n", d.screen_y + d.h);
                // player is on top
                if( (d.screen_y + d.h) <= ob.screen_y ){
                    //ret = true;
                    printf("xxxxx");
                    d.screen_y = ob.screen_y - d.h;
                    is_jumping = false;
                }else if( d.screen_y <= (ob.screen_y + ob.h) ){
                    // player is on the bottom
                    //ret = true;
                    printf("Im here");
                    d.screen_y = ob.screen_y + ob.h;
                    initial_jmp_vel = -1;
                }
                //initial_jmp_vel = -10;
            }
            */

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
        
        if( d.direction == LEFT ){
                reg_x_off = d.screen_x;
                reg_y_off = d.screen_y + 16;
        }
        if( d.direction == RIGHT ){
                reg_x_off = d.screen_x + 16;
                reg_y_off = d.screen_y + 16;
        }
        if( d.direction == JUMP ){
                //reg_x_off = d.screen_x + 16;
                reg_y_off = d.screen_y + 16;
        }

        //if( d.screen_y >= player_y && is_jumping ){
        //if( (d.screen_y >= prev_y || get_obj_type( &lvl, (d.screen_x) / 16, d.screen_y / 16 ) == 01) && is_jumping ){
        if( get_obj_type( &lvl, reg_x_off / 16, reg_y_off / 16 ) == 01 && is_jumping ){
        //if( get_obj_type( &lvl, d.screen_x / 16, d.screen_y / 16 ) == 01 && is_jumping  ){
            //d.screen_y = d.screen_y - 16;
            
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

            apply_surface( d.screen_x, d.screen_y, state_image, screen, &tmp );            
        
            is_jumping = false;
            initial_jmp_vel = 18;
            //accel = 10;
        }
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
    if( lvl.data != NULL )
        free( lvl.data );
    return EXIT_SUCCESS;
}/* ----------  end of function main  ---------- */
