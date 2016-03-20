/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description: player Tryout 
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
#include "entity.h"


SDL_Surface *screen       = NULL;
SDL_Surface *background   = NULL;
SDL_Surface *sprite_sheet = NULL;
SDL_Surface *bricks       = NULL;

/*
int tile_map[ SCREEN_WIDTH / 16 ] = {
    
};
*/

bool gameIsRunning = true;


SDL_Rect bricks_collection[3] = {
    {0, 0, TILE_WIDTH, TILE_WIDTH  }, { TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH }, { TILE_WIDTH * 2, 0, TILE_WIDTH, TILE_WIDTH }
};

bool
load_resources()
{
    //sprite_sheet = load_image( "assets/bouncing.bmp" );
    //sprite_sheet = load_image( "assets/player_tilenew2.jpg" );
    //sprite_sheet = load_image( "assets/player1.jpg" );
    //sprite_sheet = load_image( "assets/player_new.png" );
    sprite_sheet = load_image( "assets/luigi1.png" );

    if( sprite_sheet == NULL )
        return false;

    //background = load_image( "assets/back1.jpg" );
    background = load_image( "assets/sky1.png" );

    if( background == NULL )
        return false;

    //bricks = load_image( "assets/brick1.png" );
    bricks = load_image( "assets/bricks1.png" );

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
    struct entity player;
    /*
    player.x                 = 0;
    player.y                 = 0;
    player.vel_x             = 0;
    player.vel_y             = 0;
    player.width             = 16;
    player.height            = 16;
    player.max_frames        = 4;
    player.current_frame     = 0;
    player.frame_row         = 0;
    player.animation_fps     = 16;
    player.last_frame_update = 0;
    player.is_visible        = true;
    player.first_time        = true;
    player.is_jumping        = false;
    */

    init_entity( &player, true );

    player.frames = new SDL_Rect*[4];
    for(int i=0;i<4;i++){
        player.frames[i] = new SDL_Rect[4];
    }
    player.action            = RIGHT;
    for(int h=0;h<2;h++){
        for(int i=0;i<4;i++){
            player.frames[h][i].x = i * player.width;
            //player.frames[i].x = 32;
            player.frames[h][i].y = h * player.height;
            player.frames[h][i].w = player.width;
            player.frames[h][i].h = player.height;
        }
    }
    // Jump frames
    //
       player.frames[2][0].x = 0;
       //player.frames[i].x = 32;
       player.frames[2][0].y = 2 * player.height;
       player.frames[2][0].w = player.width;
       player.frames[2][0].h = player.height;

       player.frames[3][0].x = 0;
       //player.frames[i].x = 32;
       player.frames[3][0].y = 3 * player.height;
       player.frames[3][0].w = player.width;
       player.frames[3][0].h = player.height;
    /*
    for(int i=4;i<8;i++){
        player.frames[i].x = i * player.width;
        //player.frames[i].x = 32;
        player.frames[i].y = player.height;
        player.frames[i].w = player.width;
        player.frames[i].h = player.height;
    }
    */
    player.background = SDL_CreateRGBSurface(SDL_SWSURFACE, player.width, 
            player.height, SCREEN_BPP, screen->format->Rmask, 
            screen->format->Gmask, screen->format->Bmask, 
            screen->format->Amask );
    //----------------------------------------------------------


    last_updated = SDL_GetTicks();
    int i = 0;
    int j = 0;
    int tile_x = 0;

    SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
    //apply_surface( 0, 0, background, screen );
    // Putting the player in mid screen
    player.x = SCREEN_WIDTH / 2  - player.width / 2;
    //player.y = SCREEN_HEIGHT / 2 - player.height / 2;
    player.y = SCREEN_HEIGHT - 32;
    SDL_Rect tmp;

    // Drawing the tiles -------------------------------------------
    /*
    int ti = SCREEN_WIDTH / 16;
    for(i=0;i<ti;i++){
       apply_surface( 16 * i, SCREEN_HEIGHT - 16, bricks, screen );
    }
    */
    //draw_layout( &screen );
    draw_layout( &bricks, &screen, bricks_collection );
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
                player.vel_x = -1;
                //player.action = LEFT;
            }else{
                if( player.vel_x < 0 )
                    player.vel_x = 0;
            }

            if( keyevents[ SDLK_RIGHT ] ){
                player.vel_x = 1;
                //player.action = RIGHT;
            }else{
                if( player.vel_x > 0 )
                    player.vel_x = 0;
            }

            if( !player.is_jumping && keyevents[ SDLK_UP ] ){
                player.vel_y = 16;
                player.is_jumping = true;
            }


            if( player.is_jumping ){
                player.vel_y = player.vel_y - 1;
                player.y = player.y - player.vel_y;
                /*
                if(player.action == RIGHT){
                    player.action = JUMP_RIGHT;
                    player.current_frame = 0;
                }else if(player.action == LEFT){
                    player.action = JUMP_LEFT;
                    player.current_frame = 0;
                }
                */
                //if( keyevents[ SDLK_RIGHT ] ){
                    //player.vel_x = 2;
                    //player.x += player.vel_x;
                //}
            }else{
                player.y += player.vel_y;
            }


            // handle collisions
            /*
            if( player.is_jumping && player.y >= (SCREEN_HEIGHT - 32) ){
                player.is_jumping = false;
                player.vel_y = 0;
                player.y = SCREEN_HEIGHT - 32;

                if(player.action == JUMP_RIGHT){
                    player.action = RIGHT;
                    player.current_frame = 0;
                }else{
                    player.action = LEFT;
                    player.current_frame = 0;
                }
            }
            */

            //printf("x = %d\n", player.x);

            if( player.x <= 0 && player.vel_x < 0 ){
                player.vel_x = 0;
                player.x = 0;
                //printf("XXXXXXXXXXX");
            }
            // Velocity Limiter
            if( player.vel_y < -16 ){
                player.vel_y = -16;
            }else if( player.vel_y > 16 ){
                player.vel_y = 16;
            }

            //int tmp = get_tile_type( player.x + player.width, player.y );
            //int tmp = get_tile_type( 480, 448 );
            //int tmp1 = 0, tmp2 = 0;
            int tmp = 0, tmp2 = 0;
            /*
            if( player.action == RIGHT && player.vel_x > 0 ){
                //tmp = get_tile_type( j + player.x + player.vel_x + player.width, 448 );
                tmp = get_tile_type( j + player.x + player.vel_x + player.width, player.y  );
                if( tmp == 1 ){
                    player.vel_x = 0;
                }
            }else if( player.action == LEFT && player.vel_x < 0 ){
                tmp = get_tile_type( j + player.vel_x + player.x, player.y );
                if( tmp == 1 ){
                    player.vel_x = 0;
                }
            }else if( player.action == FALL_RIGHT || player.action == FALL_LEFT ){
                printf("RRRR\n");
                tmp = get_tile_type( j + player.vel_x + player.x, player.y + player.height + player.vel_y );
                if( tmp == 1 ){
                    player.vel_y = 0;
                    player.is_jumping = false;
                }
            }
            */
            // checking the quadrants
            // Right 

            if( player.action == RIGHT && player.vel_x > 0 ){
                //tmp = get_tile_type( j + player.x + player.vel_x + player.width, 448 );
                //tmp = get_tile_type( j + player.x + player.vel_x + player.width, player.y  );
                tmp = get_tile_type( tile_x + player.vel_x + player.width, player.y  );
                if( tmp == 1 || tmp == 2 || tmp == 3 ){
                    player.vel_x = 0;
                }
            }

            // Left
            if( player.action == LEFT && player.vel_x < 0 ){
                tmp = get_tile_type( tile_x + player.vel_x, player.y );
                if( tmp == 1 || tmp == 2 || tmp == 3 ){
                    player.vel_x = 0;
                }
            }
            // Top
            if( player.is_jumping && player.vel_y > 0 ){
                tmp = get_tile_type( tile_x + player.vel_x, player.y );
                tmp2 = get_tile_type( tile_x + player.vel_x + (player.width / 2), player.y );
                if( tmp == 1 || tmp2 == 1 || tmp == 2 || tmp2 == 2 || tmp == 3 || tmp2 == 3 ){
                    player.vel_y = 0;
                }
            }

            //Bottom
            if( player.is_jumping && player.vel_y < 0 ){
                tmp = get_tile_type( tile_x + player.vel_x, player.y + player.height );
                tmp2 = get_tile_type( tile_x + player.vel_x + player.width + 1, player.y + player.height );
                if( tmp == 1 || tmp2 == 1 || tmp == 2 || tmp2 == 2 || tmp == 3 || tmp2 == 3 ){
                    player.is_jumping = false;
                    player.vel_y = 0;
                    player.y = ((player.y / TILE_WIDTH) * TILE_WIDTH);
                    //printf("==============================");
                    if( player.action == JUMP_LEFT ){
                        player.action = LEFT;
                        player.current_frame = 0;
                    }else{
                        player.action = RIGHT;
                        player.current_frame = 0;
                    }
                }
            }

/*
            if( !player.is_jumping && player.vel_y == 0 ){
                if( player.action == RIGHT ){
                    tmp = get_tile_type( tile_x , player.y + player.vel_y + player.height );
                    if( tmp == 0 ){
                        //printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        player.vel_y = -1;
                        player.is_jumping = true;
                        //player.y = player.y - ((player.height + (player.height / 2)) - player.vel_y);
                        //player.y = ((player.y / 16) * 16) - player.height;
                        //if( player.action == JUMP_LEFT ){
                            //player.action = RIGHT;
                            //player.current_frame = 2;
                        //}else{
                            player.action = FALL_RIGHT;
                            player.current_frame = 0;
                        //}
                    }
                }else if (player.action == LEFT){
                    tmp = get_tile_type( tile_x, player.y + player.vel_y + player.height );
                    if( tmp == 0 ){
                        //printf("Topyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
                        player.vel_y = -1;
                        player.is_jumping = true;
                        //player.y = player.y - ((player.height + (player.height / 2)) - player.vel_y);
                        //player.y = ((player.y / 16) * 16) - player.height;
                    //}
                        //if( player.action == JUMP_LEFT ){
                            player.action = FALL_LEFT;
                            player.current_frame = 0;
                        //}else{
                            //player.action = LEFT;
                            //player.current_frame = 2;
                        //}
                    }
                }
            }

*/
            if( !player.is_jumping && player.vel_y == 0 ){
                if( player.action == RIGHT ){
                    tmp = get_tile_type( tile_x + 2 , player.y + player.vel_y + player.height );
                    tmp2 = get_tile_type( tile_x + (player.width / 2) , player.y + player.vel_y + player.height );
                    if( tmp == 0 && tmp2 == 0 ){
                        //printf("Topxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
                        player.vel_y = -1;
                        player.is_jumping = true;
                        //player.y = player.y - ((player.height + (player.height / 2)) - player.vel_y);
                        //player.y = ((player.y / 16) * 16) - player.height;
                        //if( player.action == JUMP_LEFT ){
                            //player.action = RIGHT;
                            //player.current_frame = 2;
                        //}else{
                            player.action = FALL_RIGHT;
                            player.current_frame = 0;
                        //}
                    }
                }else if (player.action == LEFT){
                    tmp = get_tile_type( tile_x, player.y + player.vel_y + player.height );
                    tmp2 = get_tile_type( tile_x + (player.width / 2), player.y + player.vel_y + player.height );
                    if( tmp == 0 && tmp2 == 0 ){
                        //printf("Topyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
                        player.vel_y = -1;
                        player.is_jumping = true;
                        //player.y = player.y - ((player.height + (player.height / 2)) - player.vel_y);
                        //player.y = ((player.y / 16) * 16) - player.height;
                    //}
                        //if( player.action == JUMP_LEFT ){
                            player.action = FALL_LEFT;
                            player.current_frame = 0;
                        //}else{
                            //player.action = LEFT;
                            //player.current_frame = 2;
                        //}
                    }
                }
            }
    /*
            if( player.is_jumping && player.y >= (SCREEN_HEIGHT - 32) ){
                player.is_jumping = false;
                player.vel_y = 0;
                player.y = SCREEN_HEIGHT - 32;

                if(player.action == JUMP_RIGHT){
                    player.action = RIGHT;
                    player.current_frame = 0;
                }else{
                    player.action = LEFT;
                    player.current_frame = 0;
                }
            }

      */      


            if( player.vel_x > 0 && player.x >= (SCREEN_WIDTH / 2  - player.width / 2) ){
                //player.x += player.vel_x;
                //j += player.vel_x;
                //if( player.is_jumping ){
                    //player.x += (player.vel_x * 2);
                    //j += (player.vel_x * 2);
                //}else{
                    j += player.vel_x;
                    //tile_x = j;
                //}
                //player.x = (SCREEN_WIDTH / 2  - player.width / 2);
            }else{
                //j += player.vel_x;
                //if( player.is_jumping ){
                    //player.x += (player.vel_x * 2);
                //}else{
                    player.x += player.vel_x;
                    //tile_x = player.x;
                //}
            }

            tile_x = (player.x + j) % SCREEN_WIDTH;

            //printf("j = %d\n", j);
            //printf("tile_y = %d\n", tile_x);
            //j = j % screen->w;

            last_tick += 1000 / GAME_PHYSICS_HZ;

        }

        // ------------------------------------------------------
        i = i % 8;
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //apply_surface( 100, 100, , screen, &player.frames[i] );

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
        //draw_layout( &background );
        draw_layout( &bricks, &background, bricks_collection );
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
        if( !player.first_time ){
            //apply_surface( player.x, player.y, penguin.background, screen );
        }else{
            player.first_time = false;
        }*/
        // Saving new background --------------------------------
        //SDL_Rect tmp;
        tmp.w = player.width;
        tmp.h = player.height;
        tmp.x = player.x;
        tmp.y = player.y;
        apply_surface( 0, 0, screen, player.background, &tmp );
        //apply_surface( 0, 0, background, player.background, &tmp );
        //-------------------------------------------------------

        // Animation
        if( !player.is_jumping && player.vel_x > 0 ){
            player.action = RIGHT;
        }else if( !player.is_jumping && player.vel_x < 0 ){
            player.action = LEFT;
        }else if( player.is_jumping && player.vel_y < 0 ){
            //printf("Falling\n"); 
            if(player.action == JUMP_RIGHT){
                player.action = FALL_RIGHT;
                player.current_frame = 0;
            }else if(player.action == JUMP_LEFT){
                player.action = FALL_LEFT;
                player.current_frame = 0;
            }
        }else if( player.is_jumping && player.vel_y > 0 ){
            //printf("Jumping\n"); 
            if(player.action == RIGHT){
                player.action = JUMP_RIGHT;
                player.current_frame = 0;
            }else if(player.action == LEFT){
                player.action = JUMP_LEFT;
                player.current_frame = 0;
            }
        }

        if( !player.is_jumping && player.vel_x != 0 ){
            if( (SDL_GetTicks() - player.last_frame_update) >= (1000.f / player.animation_fps) ){
                player.current_frame = (player.current_frame + 1) % player.max_frames;
                player.last_frame_update = SDL_GetTicks();
                //printf("XXXX\n");
            }
        }else{
            player.current_frame = 0; 
        }
        //else{
            //player.last_frame_update = SDL_GetTicks();
            //printf("YYYY\n");
        //}


        //draw_layout( &screen );
        //apply_surface( 100, 100, sprite_sheet, screen, &player.frames[i] );
        //apply_surface( player.x, player.y, sprite_sheet, screen, &penguin.frames[i] );
        apply_surface( player.x, player.y, sprite_sheet, screen, &player.frames[ player.action ][ player.current_frame ] );
        //apply_surface( 0, 0, player.background, screen );
        SDL_Flip( screen );

        // Deleting the player
        //apply_surface( player.x, player.y, background, screen, &tmp );
        apply_surface( player.x, player.y, player.background, screen );
        //SDL_Rect tmp;
        //tmp.w = player.width;
        //tmp.h = player.height;
        //tmp.x = player.x;
        //tmp.y = player.y;
        //apply_surface( player.x, player.y, background, screen, &tmp );

        // Frame rate capping
        //SDL_Delay(30);
        i++;

        //rem_time -= 1000 / GAME_FRAME_RATE_HZ;
        //}
    }

    clean_up();

    return 0;
}
