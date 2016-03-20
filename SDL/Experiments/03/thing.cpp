#include "SDL/SDL.h"

#include "config.h"
#include "types.h"
#include "thing.h"
#include "layout.h"

void init_thing(struct thing *t, bool isp = false)
{
    t->width  = 32;
    t->height = 32;
    t->pos.x = 0;
    t->pos.y = 0;
    t->vel.x = 0;
    t->vel.y = 0;
    t->accel.x = 0;
    t->accel.y = 0;
    t->current_frame.x = 0;
    t->current_frame.y = 0;
    t->isplayer = isp;
    t->back     = NULL;
    t->sprites  = NULL;
}

void set_vel_thing(struct thing *t, int x, int y)
{
   t->vel.x = x; 
   t->vel.y = y; 
}

void set_vel_thing_x(struct thing *t, int x)
{
   t->vel.x = x; 
   //t->vel.y = y; 
}

void set_vel_thing_y(struct thing *t, int y)
{
   //t->vel.x = x; 
   t->vel.y = y; 
}

void set_accel_thing(struct thing *t, int x, int y)
{
   t->accel.x = x; 
   t->accel.y = y; 
}

void draw_thing(struct thing *t, SDL_Surface *s)
{

    SDL_Rect tmp, tmp2;

    tmp.x = t->current_frame.x * TILE_SIZE;
    tmp.y = t->current_frame.y * TILE_SIZE;
    tmp.w = TILE_SIZE;
    tmp.h = TILE_SIZE;

    tmp2.x = t->pos.x;
    tmp2.y = t->pos.y;
    tmp2.w = TILE_SIZE;
    tmp2.h = TILE_SIZE;

    //Saving background
    SDL_BlitSurface(s, &tmp2, t->back, NULL);

    // Blitting object
    SDL_BlitSurface(t->sprites, &tmp, s, &tmp2);
    //SDL_BlitSurface(t->sprites, NULL, s, NULL);
}

void set_pos_thing(struct thing *t, int x, int y)
{
   t->pos.x = x;
   t->pos.y = y;
}

//+---+---+
//|       |
//+       +
//|       |
//+---+---+

void handle_collisions_thing(struct thing *t)
{
    coord tmp;

    //tmp.x = TILE_SIZE / 2 + t->pos.x + t->vel.x + t->accel.x;
    //tmp.y = TILE_SIZE + t->pos.y + t->vel.y + t->accel.y;

    //TODO should check for grounding first
    /*
    if( t->vel.y >= 0 ){
        //printf("Should fall\n");
    //if( t->isjumping ){
        if( t->isjumping && get_tile_type( &tmp ) > 0x00 ){
            t->isjumping = false;
            t->vel.y   = 0;
            t->accel.y = 0;
            //Should correct position
            coord *tmp2 = get_nearest_tile(&tmp);
            //t->pos.x = tmp2->x * TILE_SIZE;
            t->pos.y = tmp2->y * TILE_SIZE;
        }else{
            if( !t->isjumping && get_tile_type( &tmp ) == 0x00){
                printf("Should fall\n");
                t->isjumping = true;
                t->vel.y   = 0;
                t->accel.y = 1;
            }
        }
    }else{
        if( !t->isjumping && get_tile_type( &tmp ) == 0x00 ){
         
            t->isjumping = true;
            t->vel.y   = 0;
            t->accel.y = 1;
        }
    }*/

    tmp.x = (TILE_SIZE / 2) + t->pos.x + t->vel.x + t->accel.x;
    tmp.y = TILE_SIZE + t->pos.y + t->vel.y + t->accel.y;

    /*
    if( t->isjumping ){
        if( get_tile_type( &tmp ) > 0x00 ){
            t->isjumping = false;
            t->vel.y   = 0;
            t->accel.y = 0;
            //Should correct position
            coord *tmp2 = get_nearest_tile(&tmp);
            //t->pos.x = tmp2->x * TILE_SIZE;
            t->pos.y = tmp2->y * TILE_SIZE;
        }
    }else{
        if( get_tile_type( &tmp ) == 0x00 ){
            printf("Should fall\n");
            t->isjumping = true;
            t->vel.y   = 0;
            t->accel.y = 1;
        }
    }
    */
    if( t->vel.y > 0 ){
        if( t->isjumping && get_tile_type( &tmp ) > 0x00 ){
            t->isjumping = false;
            t->vel.y   = 0;
            t->accel.y = 0;
            //Should correct position
            coord *tmp2 = get_nearest_tile(&tmp);
            //t->pos.x = tmp2->x * TILE_SIZE;
            t->pos.y = (tmp2->y * TILE_SIZE) + 1;
        }
    }else if( t->vel.y == 0 ){

        tmp.x = (TILE_SIZE / 2) + t->pos.x + t->vel.x + t->accel.x;
        tmp.y = TILE_SIZE + t->pos.y + t->vel.y + t->accel.y;

        if( get_tile_type( &tmp ) == 0x00 ){
            printf("Should fall\n");
            t->isjumping = true;
            t->vel.y   = 1;
            t->accel.y = 1;
        }
    }else{
        tmp.x = (TILE_SIZE / 2) + t->pos.x + t->vel.x + t->accel.x;
        tmp.y = t->pos.y + t->vel.y + t->accel.y;
        //Top collision
        if( t->isjumping && get_tile_type( &tmp ) > 0x00 ){
            t->isjumping = false;
            t->vel.y   = 0;
            t->accel.y = 0;
            //Should correct position
            tmp.y = TILE_SIZE + t->pos.y + t->vel.y + t->accel.y;
            coord *tmp2 = get_nearest_tile(&tmp);
            //t->pos.x = tmp2->x * TILE_SIZE;
            t->pos.y = (tmp2->y  * TILE_SIZE) + 1;
        }
    }

    //Top collisions
    //Left collisions
    //Right collisions


    //TODO collisions should be handled according to moving direction
    //tmp.x = TILE_SIZE + t->pos.x + t->vel.x + t->accel.x;
    //tmp.y = TILE_SIZE + t->pos.y + t->vel.y + t->accel.y;
    /*
    if( get_tile_type(&tmp) > 0x00 ){
        t->vel.x   = 0;
        t->accel.x = 0;
        t->vel.y   = 0;
        t->accel.y = 0;
    }
    */


    //Right movement
    if( t->vel.x > 0 ){
        printf("Moving Right\n");
        tmp.x = TILE_SIZE + t->pos.x + t->vel.x + t->accel.x;
        tmp.y = (TILE_SIZE / 2) + t->pos.y + t->vel.y + t->accel.y;
        if( get_tile_type(&tmp) > 0x00 ){
            t->vel.x = 0;
            t->accel.x = 0;
        } 
    }else if( t->vel.x < 0 ){
    //Left movement    
        printf("Moving Left\n");
        tmp.x = t->pos.x + t->vel.x + t->accel.x;
        tmp.y = (TILE_SIZE / 2) + t->pos.y + t->vel.y + t->accel.y;
        if( get_tile_type(&tmp) > 0x00 ){
            t->vel.x = 0;
            t->accel.x = 0;
        } 
    }

    //Jump movement
    if( t->vel.y < 0 ){
    
    }else if( t->vel.y < 0 ){
    //Falling movement    
    }
}

void animate()
{

}

void set_jumping_thing(struct thing *t, bool isj)
{
    t->isjumping = isj;
}

void update_state_thing(struct thing *t)
{
    t->vel.x += t->accel.x;
    t->vel.y += t->accel.y;

    t->pos.x = t->pos.x + t->vel.x;
    t->pos.y = t->pos.y + t->vel.y;
}

void handle_events_thing(struct thing *t, SDL_Event *e)
{
    //while( SDL_PollEvent(e) ){
        switch( e->type ){
            case SDL_KEYDOWN:
                if( e->key.keysym.sym == SDLK_RIGHT ){
                    t->vel.x = 1;
                }
                if( e->key.keysym.sym == SDLK_LEFT ){
                    t->vel.x = -1;
                }
                if( e->key.keysym.sym == SDLK_UP ){
                    if( !t->isjumping ){
                        t->vel.y = -16;
                        t->accel.y = 1;
                        t->isjumping = true;

                        printf("Jumping\n");
                    }
                    //set_vel_thing(t, 0, 0);
                }
            break;
        case SDL_KEYUP:
            if( e->key.keysym.sym == SDLK_RIGHT ){
                t->vel.x = 0;
             }
             if( e->key.keysym.sym == SDLK_LEFT ){
                t->vel.x = 0;
             }
            if( e->key.keysym.sym == SDLK_UP ){
                if( !t->isjumping ){
                
                }
                //t->isjumping = false;
            }
            break;

        default:
                //std::cerr << "Not implemented event." << std::endl;
            ;
        }
    //}
}

void erase_thing(struct thing *t, SDL_Surface *s)
{
    SDL_Rect tmp;

    tmp.x = t->pos.x;
    tmp.y = t->pos.y;
    tmp.w = TILE_SIZE;
    tmp.h = TILE_SIZE;

    //Restoring background 
    SDL_BlitSurface(t->back, NULL, s, &tmp);
}

void cleanup_thing(struct thing *t)
{
    SDL_FreeSurface( t->back );
    SDL_FreeSurface( t->sprites );
}

