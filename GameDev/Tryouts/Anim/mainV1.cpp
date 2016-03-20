/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description: Mario Tryout 
 *
 *        Version:  1.0
 *        Created:  04/27/2013 09:13:24 PM
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

#include "globals.h"
#include "video.h"
#include "input.h"
#include "layout.h"


SDL_Surface *screen       = NULL;
SDL_Surface *background   = NULL;
SDL_Surface *sprite_sheet = NULL;
SDL_Surface *bricks       = NULL;

/*
int tile_map[ SCREEN_WIDTH / 16 ] = {
    
};
*/

bool gameIsRunning = true;

typedef enum {
    RIGHT = 0,
    LEFT = 1,
    JUMP_RIGHT = 2,
    JUMP_LEFT = 3,
    FALL_RIGHT = 2,
    FALL_LEFT = 3
} state_t;

struct solid_tile{
    unsigned int x, y;
    unsigned short width, height;
    unsigned int type;
    bool is_visible;
};

struct entity{
    unsigned int x;
    unsigned int y;
    int vel_x;
    int vel_y;
    unsigned short width;
    unsigned short height;
    unsigned short max_frames;
    unsigned short current_frame;
    unsigned short animation_fps;
    unsigned short frame_row;
    Uint32 last_frame_update;
    SDL_Rect **frames;
    SDL_Surface *background;
    bool is_visible;
    bool first_time;
    state_t action;
    bool is_jumping;
};

bool
load_resources()
{
    //sprite_sheet = load_image( "assets/bouncing.bmp" );
    //sprite_sheet = load_image( "assets/mario_tilenew2.jpg" );
    //sprite_sheet = load_image( "assets/mario1.jpg" );
    //sprite_sheet = load_image( "assets/mario_new.png" );
    sprite_sheet = load_image( "assets/luigi1.png" );

    if( sprite_sheet == NULL )
        return false;

    //background = load_image( "assets/back1.jpg" );
    background = load_image( "assets/sky1.png" );

    if( background == NULL )
        return false;

    bricks = load_image( "assets/brick1.png" );

    if( bricks == NULL )
        return false;
    return true;
}

void
clean_up()
{
    SDL_FreeSurface( sprite_sheet );
    SDL_FreeSurface( background );
    SDL_FreeSurface( bricks );
    SDL_FreeSurface( screen );

    SDL_Quit();
}

void
draw_layout( SDL_Surface **dest )
{
    for(int i=0;i<SCREEN_HEIGHT / 16;i++){
        for(int j=0;j<SCREEN_WIDTH / 16;j++){
            //printf("Tile i = %d, j = %d, index = %d | -> %d\n", i, j, (i * (SCREEN_WIDTH / 16)) + j, tile_map[ (i * (SCREEN_WIDTH / 16)) + j ]);
            //if( tile_map[i * (SCREEN_HEIGHT / 16) + j]  == 1){ 
            if( tile_map[(i * (SCREEN_WIDTH / 16)) + j]  == 1){ 
                //apply_surface( j * 16, i * 16, bricks, *dest );
                apply_surface( j * 16, i * 16, bricks, *dest );
                //printf("Tile 01\n");
            }
        }
    }

    //printf("Tile Last -> %d\n", tile_map[ 29 * 40 ]);
}


int
main( int argc, char *argv[] )
{
    Uint32 last_updated;

    if( init( &screen ) == false ){
        fprintf(stderr, "Unable to create window.\n%s", SDL_GetError());
        return -1;
    }

    if( load_resources() == false ){
        fprintf(stderr, "Unable to load resource(s).\n%s", SDL_GetError());
        return -1;
    }

    for( int i = 0; i < 323; i++ )
    {
        keyevents[i] = false;
    }


    // creating the main character -----------------------------
    struct entity mario;
    mario.x                 = 0;
    mario.y                 = 0;
    mario.vel_x             = 0;
    mario.vel_y             = 0;
    mario.width             = 16;
    mario.height            = 16;
    mario.max_frames        = 4;
    mario.current_frame     = 0;
    mario.frame_row         = 0;
    mario.animation_fps     = 16;
    mario.last_frame_update = 0;
    mario.is_visible        = true;
    mario.first_time        = true;
    mario.is_jumping        = false;
    mario.frames = new SDL_Rect*[4];
    for(int i=0;i<4;i++){
        mario.frames[i] = new SDL_Rect[4];
    }
    mario.action            = RIGHT;
    for(int h=0;h<2;h++){
        for(int i=0;i<4;i++){
            mario.frames[h][i].x = i * mario.width;
            //mario.frames[i].x = 32;
            mario.frames[h][i].y = h * mario.height;
            mario.frames[h][i].w = mario.width;
            mario.frames[h][i].h = mario.height;
        }
    }
    // Jump frames
    //
       mario.frames[2][0].x = 0;
       //mario.frames[i].x = 32;
       mario.frames[2][0].y = 2 * mario.height;
       mario.frames[2][0].w = mario.width;
       mario.frames[2][0].h = mario.height;

       mario.frames[3][0].x = 0;
       //mario.frames[i].x = 32;
       mario.frames[3][0].y = 3 * mario.height;
       mario.frames[3][0].w = mario.width;
       mario.frames[3][0].h = mario.height;
    /*
    for(int i=4;i<8;i++){
        mario.frames[i].x = i * mario.width;
        //mario.frames[i].x = 32;
        mario.frames[i].y = mario.height;
        mario.frames[i].w = mario.width;
        mario.frames[i].h = mario.height;
    }
    */
    mario.background = SDL_CreateRGBSurface(SDL_SWSURFACE, mario.width, 
            mario.height, SCREEN_BPP, screen->format->Rmask, 
            screen->format->Gmask, screen->format->Bmask, 
            screen->format->Amask );
    //----------------------------------------------------------


    last_updated = SDL_GetTicks();
    int i = 0;
    int j = 0;
    int tile_x = 0;

    SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
    //apply_surface( 0, 0, background, screen );
    // Putting the mario in mid screen
    mario.x = SCREEN_WIDTH / 2  - mario.width / 2;
    //mario.y = SCREEN_HEIGHT / 2 - mario.height / 2;
    mario.y = SCREEN_HEIGHT - 32;
    SDL_Rect tmp;

    // Drawing the tiles -------------------------------------------
    /*
    int ti = SCREEN_WIDTH / 16;
    for(i=0;i<ti;i++){
       apply_surface( 16 * i, SCREEN_HEIGHT - 16, bricks, screen );
    }
    */
    draw_layout( &screen );
    // -------------------------------------------------------------
    
    while( gameIsRunning ){
        static int last_tick = SDL_GetTicks();
        int this_tick = SDL_GetTicks();
        //SDL_Delay(1000);

        if( last_tick == this_tick ){
            SDL_Delay(1);
            continue;
        }

        while( last_tick < this_tick ){

            handle_events();

            if( keyevents[ SDLK_LEFT ] ){
                mario.vel_x = -1;
                //mario.action = LEFT;
            }else{
                if( mario.vel_x < 0 )
                    mario.vel_x = 0;
            }

            if( keyevents[ SDLK_RIGHT ] ){
                mario.vel_x = 1;
                //mario.action = RIGHT;
            }else{
                if( mario.vel_x > 0 )
                    mario.vel_x = 0;
            }

            if( !mario.is_jumping && keyevents[ SDLK_UP ] ){
                mario.vel_y = 20;
                mario.is_jumping = true;
            }


            if( mario.is_jumping ){
                mario.vel_y = mario.vel_y - 1;
                mario.y = mario.y - mario.vel_y;
                /*
                if(mario.action == RIGHT){
                    mario.action = JUMP_RIGHT;
                    mario.current_frame = 0;
                }else if(mario.action == LEFT){
                    mario.action = JUMP_LEFT;
                    mario.current_frame = 0;
                }
                */
                //if( keyevents[ SDLK_RIGHT ] ){
                    //mario.vel_x = 2;
                    //mario.x += mario.vel_x;
                //}
            }else{
                mario.y += mario.vel_y;
            }


            // handle collisions
            /*
            if( mario.is_jumping && mario.y >= (SCREEN_HEIGHT - 32) ){
                mario.is_jumping = false;
                mario.vel_y = 0;
                mario.y = SCREEN_HEIGHT - 32;

                if(mario.action == JUMP_RIGHT){
                    mario.action = RIGHT;
                    mario.current_frame = 0;
                }else{
                    mario.action = LEFT;
                    mario.current_frame = 0;
                }
            }
            */

            printf("x = %d\n", mario.x);

            if( mario.x <= 0 && mario.vel_x < 0 ){
                mario.vel_x = 0;
                mario.x = 0;
                //printf("XXXXXXXXXXX");
            }
            // Velocity Limiter
            if( mario.vel_y < -20 ){
                mario.vel_y = -20;
            }else if( mario.vel_y > 20 ){
                mario.vel_y = 20;
            }

            //int tmp = get_tile_type( mario.x + mario.width, mario.y );
            //int tmp = get_tile_type( 480, 448 );
            int tmp = 0;
            /*
            if( mario.action == RIGHT && mario.vel_x > 0 ){
                //tmp = get_tile_type( j + mario.x + mario.vel_x + mario.width, 448 );
                tmp = get_tile_type( j + mario.x + mario.vel_x + mario.width, mario.y  );
                if( tmp == 1 ){
                    mario.vel_x = 0;
                }
            }else if( mario.action == LEFT && mario.vel_x < 0 ){
                tmp = get_tile_type( j + mario.vel_x + mario.x, mario.y );
                if( tmp == 1 ){
                    mario.vel_x = 0;
                }
            }else if( mario.action == FALL_RIGHT || mario.action == FALL_LEFT ){
                printf("RRRR\n");
                tmp = get_tile_type( j + mario.vel_x + mario.x, mario.y + mario.height + mario.vel_y );
                if( tmp == 1 ){
                    mario.vel_y = 0;
                    mario.is_jumping = false;
                }
            }
            */
            // checking the quadrants
            // Right 

            if( mario.action == RIGHT && mario.vel_x > 0 ){
                //tmp = get_tile_type( j + mario.x + mario.vel_x + mario.width, 448 );
                //tmp = get_tile_type( j + mario.x + mario.vel_x + mario.width, mario.y  );
                tmp = get_tile_type( tile_x + mario.vel_x + mario.width, mario.y  );
                if( tmp == 1 ){
                    mario.vel_x = 0;
                }
            }

            // Left
            if( mario.action == LEFT && mario.vel_x < 0 ){
                tmp = get_tile_type( tile_x + mario.vel_x, mario.y );
                if( tmp == 1 ){
                    mario.vel_x = 0;
                }
            }
            // Top
            if(  mario.is_jumping && mario.vel_y >= 0 ){
                if( mario.action == JUMP_RIGHT ){
                    tmp = get_tile_type( tile_x + mario.width, mario.y + mario.vel_y - mario.height );
                    if( tmp == 1 ){
                        //printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        printf("--------------------------------------------------\n");
                        mario.vel_y = 0;
                        //mario.is_jumping = false;
                    }
                }else{
                    tmp = get_tile_type( tile_x, mario.y + mario.vel_y - mario.height );
                    if( tmp == 1 ){
                        //printf("Topyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
                        printf("--------------------------------------------------\n");
                        mario.vel_y = 0;
                        //mario.is_jumping = false;
                    }
                }
            }

            if(  mario.is_jumping && mario.vel_y <= 0 ){
            /*
                    tmp = get_tile_type( tile_x + mario.width, mario.y + mario.vel_y + mario.height );
                    if( tmp == 1 ){
                        printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        mario.vel_y = 0;
                        mario.is_jumping = false;
                        //mario.y = mario.y - ((mario.height + (mario.height / 2)) - mario.vel_y);
                        mario.y = ((mario.y / 16) * 16) - mario.height;
                        //if( mario.action == JUMP_LEFT ){
                            //mario.action = LEFT;
                            //mario.current_frame = 0;
                        //}else{
                            mario.action = RIGHT;
                            mario.current_frame = 0;
                        //}
                    }
                    */
                    
                if( mario.action == FALL_RIGHT ){
                    tmp = get_tile_type( tile_x + mario.width, mario.y + mario.vel_y + mario.height );
                    if( tmp == 1 ){
                        printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        mario.vel_y = 0;
                        mario.is_jumping = false;
                        //mario.y = mario.y - ((mario.height + (mario.height / 2)) - mario.vel_y);
                        mario.y = ((mario.y / 16) * 16) - mario.height;
                        //if( mario.action == JUMP_LEFT ){
                            //mario.action = LEFT;
                            //mario.current_frame = 0;
                        //}else{
                            mario.action = RIGHT;
                            mario.current_frame = 0;
                        //}
                    }
                }else{
                    tmp = get_tile_type( tile_x, mario.y + mario.vel_y + mario.height );
                    if( tmp == 1 ){
                        printf("Topyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
                        mario.vel_y = 0;
                        mario.is_jumping = false;
                        //mario.y = mario.y - ((mario.height + (mario.height / 2)) - mario.vel_y);
                        mario.y = ((mario.y / 16) * 16) - mario.height;
                    }
                        //if( mario.action == JUMP_LEFT ){
                            mario.action = LEFT;
                            mario.current_frame = 0;
                        //}else{
                            //mario.action = RIGHT;
                            //mario.current_frame = 0;
                        //}
                }
                
            }

            if( !mario.is_jumping ){
                printf("vel_y = %d\n **************>", mario.vel_y);
            }

/*
            // Bottom
            // Check if the player is standing on a solid tile otherwise fall
            if( mario.is_jumping ){
                tmp = get_tile_type( j + mario.x + mario.width, mario.y + mario.vel_y + mario.height );
                if( tmp == 1 ){
                    printf("Solid Tile.................\n");
                    mario.vel_y = 0;
                    mario.is_jumping = false;
                    mario.y = mario.y - 32;
                    if(mario.action == JUMP_RIGHT){
                        mario.action = RIGHT;
                        mario.current_frame = 0;
                    }else{
                        mario.action = LEFT;
                        mario.current_frame = 0;
                    }
                }else{
                    //if( !mario.is_jumping ){
                        //printf("Falling.................\n");
                        //mario.is_jumping = true;
                        //mario.vel_y = 0;
                    //}
                }
            }
            */
            /*
            if(  mario.is_jumping && mario.vel_y <= 0 ){
                if( mario.action == FALL_RIGHT ){
                    tmp = get_tile_type( j + mario.x + mario.width, mario.y + mario.vel_y + mario.height );
                    if( tmp == 1 ){
                        printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        mario.vel_y = 0;
                        //mario.is_jumping = false;
                    }
                }else{
                    tmp = get_tile_type( j + mario.x, mario.y + mario.vel_y + mario.height );
                    if( tmp == 1 ){
                        printf("Topyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
                        mario.vel_y = 0;
                        //mario.is_jumping = false;
                    }
                }
            }
            */
            //if( (mario.action == FALL_RIGHT || mario.action == FALL_LEFT) && mario.vel_y < 0 ){
            /*
            if( mario.is_jumping && mario.vel_y <= 0 ){
                tmp = get_tile_type( j + mario.x + mario.vel_x, mario.y + mario.vel_y + mario.height );
                if( tmp == 1 ){
                printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                    mario.vel_y = 0;
                    mario.is_jumping = false;
                    mario.action = RIGHT;
                    mario.current_frame = 0;
                }else{
                    //mario.vel_y = 5;
                }
            }
            */

            /*
            if( mario.vel_y == 0 ){
                tmp = get_tile_type( j + mario.x + mario.vel_x, mario.y + mario.vel_y + mario.height );
                if( tmp == 1 ){
                printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                    mario.vel_y = 1;
                    //mario.is_jumping = false;
                    //mario.action = RIGHT;
                    //mario.current_frame = 0;
                }else{
                    //mario.vel_y = 5;
                }
            }
            */
            printf("Tile Type = %d\n", tmp);

            if( !mario.is_jumping && mario.vel_y == 0 ){
                if( mario.action == RIGHT ){
                    tmp = get_tile_type( tile_x + mario.width, mario.y + mario.vel_y + mario.height );
                    if( tmp == 0 ){
                        printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        mario.vel_y = -1;
                        mario.is_jumping = true;
                        //mario.y = mario.y - ((mario.height + (mario.height / 2)) - mario.vel_y);
                        //mario.y = ((mario.y / 16) * 16) - mario.height;
                        //if( mario.action == JUMP_LEFT ){
                            //mario.action = LEFT;
                            //mario.current_frame = 0;
                        //}else{
                            mario.action = FALL_RIGHT;
                            mario.current_frame = 0;
                        //}
                    }
                }else if (mario.action == LEFT){
                    tmp = get_tile_type( tile_x, mario.y + mario.vel_y + mario.height );
                    if( tmp == 0 ){
                        printf("Topyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
                        mario.vel_y = -1;
                        mario.is_jumping = true;
                        //mario.y = mario.y - ((mario.height + (mario.height / 2)) - mario.vel_y);
                        //mario.y = ((mario.y / 16) * 16) - mario.height;
                    //}
                        //if( mario.action == JUMP_LEFT ){
                            mario.action = FALL_LEFT;
                            mario.current_frame = 0;
                        //}else{
                            //mario.action = RIGHT;
                            //mario.current_frame = 0;
                        //}
                    }
            }
        }
            if( mario.is_jumping && mario.y >= (SCREEN_HEIGHT - 32) ){
                mario.is_jumping = false;
                mario.vel_y = 0;
                mario.y = SCREEN_HEIGHT - 32;

                if(mario.action == JUMP_RIGHT){
                    mario.action = RIGHT;
                    mario.current_frame = 0;
                }else{
                    mario.action = LEFT;
                    mario.current_frame = 0;
                }
            }

            


            if( mario.vel_x > 0 && mario.x >= (SCREEN_WIDTH / 2  - mario.width / 2) ){
                //mario.x += mario.vel_x;
                //j += mario.vel_x;
                //if( mario.is_jumping ){
                    //mario.x += (mario.vel_x * 2);
                    //j += (mario.vel_x * 2);
                //}else{
                    j += mario.vel_x;
                    //tile_x = j;
                //}
                //mario.x = (SCREEN_WIDTH / 2  - mario.width / 2);
            }else{
                //j += mario.vel_x;
                //if( mario.is_jumping ){
                    //mario.x += (mario.vel_x * 2);
                //}else{
                    mario.x += mario.vel_x;
                    //tile_x = mario.x;
                //}
            }

            tile_x = (mario.x + j) % SCREEN_WIDTH;

            //printf("j = %d\n", j);
            printf("tile_y = %d\n", tile_x);
            //j = j % screen->w;

            last_tick += 1000 / GAME_PHYSICS_HZ;

        }

        // ------------------------------------------------------
        i = i % 8;
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //apply_surface( 100, 100, , screen, &mario.frames[i] );

        int rem_time = last_tick - this_tick;


        //while( rem_time > 0 ){
        // Drawing the background
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //SDL_Rect tmp;
        // Drawing the tiles -------------------------------------------
        /*
        int ti = SCREEN_WIDTH / 16;
        for(i=0;i<ti;i++){
            apply_surface( 16 * i, SCREEN_HEIGHT - 16, bricks, background );
        }
        */
        draw_layout( &background );
        // -------------------------------------------
        tmp.w = background->w - j;
        //fprintf(stdout, "%d\n", tmp.w);
        tmp.h = background->h;
        tmp.x = j;
        tmp.y = 0;
        apply_surface( 0, 0, background, screen, &tmp );
        tmp.w = j;
        //fprintf(stdout, "%d\n", tmp.w);
        tmp.h = background->h;
        tmp.x = 0;
        tmp.y = 0;
        apply_surface( screen->w - j, 0, background, screen, &tmp );
        //j++; 
        /*
        if( j >= screen->w ){
            j = 0;
        }
        */

        j = j % screen->w;
        // Restoring previous background
        /*
        if( !mario.first_time ){
            //apply_surface( mario.x, mario.y, penguin.background, screen );
        }else{
            mario.first_time = false;
        }*/
        // Saving new background --------------------------------
        //SDL_Rect tmp;
        tmp.w = mario.width;
        tmp.h = mario.height;
        tmp.x = mario.x;
        tmp.y = mario.y;
        apply_surface( 0, 0, screen, mario.background, &tmp );
        //apply_surface( 0, 0, background, mario.background, &tmp );
        //-------------------------------------------------------

        // Animation
        if( !mario.is_jumping && mario.vel_x > 0 ){
            mario.action = RIGHT;
        }else if( !mario.is_jumping && mario.vel_x < 0 ){
            mario.action = LEFT;
        }else if( mario.is_jumping && mario.vel_y < 0 ){
            printf("Falling\n"); 
            if(mario.action == JUMP_RIGHT){
                mario.action = FALL_RIGHT;
                mario.current_frame = 0;
            }else if(mario.action == JUMP_LEFT){
                mario.action = FALL_LEFT;
                mario.current_frame = 0;
            }
        }else if( mario.is_jumping && mario.vel_y > 0 ){
            //printf("Jumping\n"); 
            if(mario.action == RIGHT){
                mario.action = JUMP_RIGHT;
                mario.current_frame = 0;
            }else if(mario.action == LEFT){
                mario.action = JUMP_LEFT;
                mario.current_frame = 0;
            }
        }

        if( !mario.is_jumping && mario.vel_x != 0 ){
            if( (SDL_GetTicks() - mario.last_frame_update) >= (1000.f / mario.animation_fps) ){
                mario.current_frame = (mario.current_frame + 1) % mario.max_frames;
                mario.last_frame_update = SDL_GetTicks();
                //printf("XXXX\n");
            }
        }else{
            mario.current_frame = 0; 
        }
        //else{
            //mario.last_frame_update = SDL_GetTicks();
            //printf("YYYY\n");
        //}


        //draw_layout( &screen );
        //apply_surface( 100, 100, sprite_sheet, screen, &mario.frames[i] );
        //apply_surface( mario.x, mario.y, sprite_sheet, screen, &penguin.frames[i] );
        apply_surface( mario.x, mario.y, sprite_sheet, screen, &mario.frames[ mario.action ][ mario.current_frame ] );
        //apply_surface( 0, 0, mario.background, screen );
        SDL_Flip( screen );

        // Deleting the mario
        //apply_surface( mario.x, mario.y, background, screen, &tmp );
        apply_surface( mario.x, mario.y, mario.background, screen );
        //SDL_Rect tmp;
        //tmp.w = mario.width;
        //tmp.h = mario.height;
        //tmp.x = mario.x;
        //tmp.y = mario.y;
        //apply_surface( mario.x, mario.y, background, screen, &tmp );

        // Frame rate capping
        //SDL_Delay(30);
        i++;

        //rem_time -= 1000 / GAME_FRAME_RATE_HZ;
        //}
    }

    clean_up();

    return 0;
}
