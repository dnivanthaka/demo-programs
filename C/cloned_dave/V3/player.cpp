// HEADER FILES ------------------------------------------------------------
#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <sstream>

#include "gtypedef.h"
#include "entities.h"
#include "level.h"
#include "player.h"
#include "graphics.h"


// MACROS ------------------------------------------------------------------

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// CODE --------------------------------------------------------------------

void
move_player( player_t *pla )
{
    if( pla->direction == RIGHT ){
        pla->screen_x += pla->vel_x;
    }else if( pla->direction == LEFT ){
        pla->screen_x -= pla->vel_x;
    }else if( pla->direction == JUMP ){
        pla->screen_y -= pla->vel_y;       
    }else if( pla->direction == CROUCH ){
        pla->screen_y += pla->vel_y;      
    }
}


void
draw( player_t *pla, ga_object *go, SDL_Surface *screen, int start_frame )
{
    //int s;
    //SDL_Rect tmp;
    
    //apply_surface( pla->screen_x, pla->screen_y, pla->sprites, screen, &tmp );
    int i;
    SDL_Rect tmp;
    unsigned int start_time, end_time;
    int mv_val= 0;
    int frame_count = 0;
    int prev_x, prev_y, player_w_off = 0;

    frame *f_ptr;
    //f_ptr = &test[0];

    if( pla->direction == RIGHT ){
        f_ptr = &pla->r_frames[0];
        mv_val = pla->vel_x;
        frame_count = sizeof(pla->r_frames)/sizeof(pla->r_frames[0]);
        player_w_off = pla->w;
        //frame_count = 4;
    }else if( pla->direction == LEFT ){
        f_ptr = &pla->l_frames[0];
        mv_val = -1 * (pla->vel_x);
        frame_count = sizeof(pla->r_frames)/sizeof(pla->r_frames[0]);
        player_w_off = 0;
        //frame_count = 4;
    }else if( pla->direction == JUMP ){
        f_ptr = &pla->j_frames[0];
        //mv_val = -4;
        frame_count = sizeof(pla->j_frames)/sizeof(pla->j_frames[0]);
    }

    if( pla->direction == RIGHT || pla->direction == LEFT ){
        for( i=0;i<frame_count;i++ ){
            start_time = SDL_GetTicks();
            // Apply previous background
            //apply_surface( p->screen_x, p->screen_y, background, screen, &p->current_bg );
            //printf("Im here %d\n", i);
            /*            
            pla->current_bg.x = pla->screen_x;
            pla->current_bg.y = pla->screen_y;
            pla->current_bg.w = pla->w;
            pla->current_bg.h = pla->h;
            */

            apply_surface( pla->screen_x, pla->screen_y, pla->bg_ptr, screen, &pla->current_bg );

            pla->current_bg.x = pla->screen_x;
            pla->current_bg.y = pla->screen_y;
            pla->current_bg.w = pla->w;
            pla->current_bg.h = pla->h;

            //apply_surface( pla->screen_x, pla->screen_y, pla->bg_ptr, screen, &pla->current_bg );

            //tmp.x = pla->r_frames[i].x;
            tmp.x = (f_ptr + i)->x;
            //tmp.y = pla->r_frames[i].y;
            tmp.y = (f_ptr + i)->y;
            tmp.w = pla->w;
            tmp.h = pla->h;
            
            prev_x = pla->screen_x;
            prev_y = pla->screen_y;

            // Im limiting the movement here
            pla->screen_x = (pla->screen_x + mv_val);
            //p->screen_x = p->screen_x + mv_val;
            /*
            if( get_obj_type( lvl, (pla->screen_x + player_w_off) / 16, pla->screen_y / 16 ) == 01 ){
                //printf("Got it\n");
                pla->screen_x = prev_x;
                pla->screen_y = prev_y;
                
            }
            */


            //collision_info *t;
            // remove this comment
            /*
            if( (t = get_object(go, pla->screen_x, pla->screen_y, pla->w, pla->h )) != NULL ){
                    printf("collision\n");
                   if( t->hit == LEFT_HIT || t->hit == RIGHT_HIT ){
                        //printf("LEFT_HIT\n");
                        printf("c w = %d\n", t->ob->w);
                        printf("c h = %d\n", t->ob->h);
                        printf("c type = %d\n", t->ob->o_type);
                        pla->screen_x = prev_x;
                        pla->screen_y = prev_y;
                    }
            }
            */

            //pla->screen_x = pla->screen_x % (SCREEN_WIDTH - (pla->w + 16));
            //pla->screen_x = (pla->screen_x <= 0) ? 0 : (pla->screen_x >= (SCREEN_WIDTH - pla->w)) ? (SCREEN_WIDTH - pla->w) : pla->screen_x;
            //printf("pitch = %d\n", screen->pitch);
            //printf("width = %d\n", screen->w);
            // im giving width as 16, TODO change this
            
            //printf(" player x = %d\n ", pla->screen_x);
            //printf("%d ", get_obj_type( lvl, pla->screen_x, pla->screen_y ));
            apply_surface( pla->screen_x, pla->screen_y, pla->sprites, screen, &tmp );

            if( SDL_Flip( screen ) == -1 ){
                return;
            }

            end_time = SDL_GetTicks();
            /*
            if((end_time - start_time) < (player_anim_fps * 100)){
                SDL_Delay( (player_anim_fps * 100) - (end_time - start_time) );
            }
            */
            if( (SDL_GetTicks() - start_time) <= (frame_delay + 25) ){
                SDL_Delay( (frame_delay + 25) -  (SDL_GetTicks() -  start_time) );
            }
            //SDL_Delay(50);
        }
        // Resetting to initial position
        apply_surface( pla->screen_x, pla->screen_y, pla->bg_ptr, screen, &pla->current_bg );
        //apply_surface( pla->screen_x, pla->screen_y, st, screen, &pla->current_bg );

        tmp.x = (f_ptr + start_frame)->x;
        tmp.y = (f_ptr + start_frame)->y;
        tmp.w = pla->w;
        tmp.h = pla->h;

        pla->current_bg.x = pla->screen_x;
        pla->current_bg.y = pla->screen_y;
        pla->current_bg.w = pla->w;
        pla->current_bg.h = pla->h;

        apply_surface( pla->screen_x, pla->screen_y, pla->sprites, screen, &tmp );
        //apply_surface( pla->screen_x, pla->screen_y, st, screen, &tmp );
    }else if( pla->direction == JUMP ){
        
    }
}
