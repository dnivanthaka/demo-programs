// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS  = 60;
const int FPMS = FPS / 1000;

const int gravity_accel = 1;

SDL_Surface *screen = NULL;
SDL_Surface *image1 = NULL;
SDL_Surface *image2 = NULL;
SDL_Event event;

// Implement this on an Array
bool right_pressed = false;
bool left_pressed  = false;
bool up_pressed    = false;
bool down_pressed  = false;
//---------------------------


int num_stars = 20;
bool gameRunning = true;
//SDL_Surface *blit_1 = NULL;
//SDL_Surface *stage_objects;

typedef enum {
    LEFT, 
    RIGHT, 
    JUMP_LEFT,
    JUMP_RIGHT, 
    CROUCH
} dir_t;

typedef struct {
    int w;
    int h;
    short num_frames;
    short frame_rate;
    short frame_idx;
    Uint32 last_update;
    SDL_Rect old_back;
    SDL_Rect *f_ptr;
    SDL_Rect *l_frames;
    SDL_Rect *r_frames;
    SDL_Rect *up_frames;
    SDL_Rect *down_frames;
} sprite_t;

typedef struct {
    int w;
    int h;
    int x;
    int y;
    int x_vel;
    int y_vel;
    int i_jump_vel;
    dir_t dir;
    Uint32 last_update;
    sprite_t spr;
} player_t;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_input();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void player_init( player_t *player );
void animate( sprite_t *spr, dir_t direction, short start_frame );
void move_player( player_t *player );
void player_clean_up( player_t *player );
bool player_can_move_left( player_t *player );
bool player_can_move_right( player_t *player );
bool player_can_jump( player_t *player );
//void move_stars( star_t *stars, frame_t *cont );
//void cross_fade( SDL_Surface *from, SDL_Surface *to );

int 
main(int argc, char *argv[])
{
    int i;
    Uint32 start_time = 0, numTicks = 0;
    player_t player;
    SDL_Rect tux;
    //star_t stars[ num_stars ];
    //frame_t container;

    // seeding the rand generator
    srand( (unsigned)time( NULL ) );

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "SDL Examples", NULL );

    //image1 = loadImage( "pic1.png" );
    image1 = loadImage( "mario3.png" );
    
    player_init( &player );

    //int x_part = 0, y_part = 0;
    //SDL_Rect tmp;

    tux.w = image1->w;
    tux.w = 16;
    //tux.h = 261;
    //tux.h = image1->h;
    tux.h = 16;
    tux.x = (SCREEN_WIDTH / 2) - (16 / 2);
    tux.y = (SCREEN_HEIGHT / 2) - (16 / 2);

    i = 0;

    // setting updated time
    player.spr.last_update = SDL_GetTicks();
    player.last_update = SDL_GetTicks();
    // This is the initial mario position
    player.spr.f_ptr = &player.spr.r_frames[0];
    // Setting player inital jump velocity
    player.i_jump_vel = 20;

    while( gameRunning ){
        
        handle_input();

        // clearing old stars
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
            
        //move_stars( stars, &container );

        //cross_fade( screen, image1 );
        //tmp_1.x = -1 * (x_part);
        //tmp_1.y = y_part;
        //tmp_1.w = screen->w - 100;
        //tmp_1.h = screen->h - 100;

        //tmp_2.x = screen->w - x_part;
        //tmp_2.y = y_part;
        //i = (i + 1) % 4;


        //player.spr.f_ptr = &player.spr.l_frames[ 0 ];
        move_player( &player );

        tux.x = player.x;
        tux.y = player.y;
        //animate( &player.spr, RIGHT, 1 );

        //SDL_BlitSurface( image1, NULL, screen, &tmp_1 );
        //SDL_BlitSurface( image1, NULL, screen, &tmp_2 );
        SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
        SDL_BlitSurface( image1, (player.spr.f_ptr + player.spr.frame_idx), screen, &tux );

        //player_init( player_t *player )

        SDL_Flip( screen );

        //x_part++;
        //x_part = x_part % screen->w;        
        //(--x_part) % screen->w;
        //SDL_Delay(50);
            
        //if( SDL_GetTicks() - start_time < 1000 / FPS ){
            //if( SDL_GetTicks() - start_time < FPMS ){
            //SDL_Delay( (1000 / FPS) - (SDL_GetTicks() - start_time) );
        //}
        start_time = SDL_GetTicks();
        numTicks++;
    }
        //SDL_Delay(2000);
    //delete [] player.spr.l_frames;
    player_clean_up( &player );
    SDL_FreeSurface( screen );
    SDL_FreeSurface( image1 );

    return 0;
}

// -------------------------------------------------------------------------
// loadImage
//
// Creates a [screen] type optimized surface from given image file, doesnot handle alpha chanels. Supports color keying
//
// -------------------------------------------------------------------------
SDL_Surface* 
loadImage( std::string file, bool setColorKey, int r, int g, int b )
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

// -------------------------------------------------------------------------
// handle_events
//
// Handles inputs
//
// -------------------------------------------------------------------------
void
handle_input()
{
    while( SDL_PollEvent( &event ) ){
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
            gameRunning = false;
        }
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

/*

void
move_stars( star_t *stars, frame_t *cont )
{
    int i, j, k;



    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

                putpixel(screen, (stars + i)->x + k, (stars + i)->y + j, (stars + i)->color);

    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }  
}

*/

void
animate( sprite_t *spr, dir_t direction, short start_frame )
{
    //int i;    
    //SDL_Rect *f_ptr;
    //SDL_Rect tmp;

    if( direction == RIGHT ){
        //pl->dir = RIGHT;
        spr->f_ptr = &spr->r_frames[0];
    }else if( direction == LEFT ){
        //pl->dir = LEFT;
        spr->f_ptr = &spr->l_frames[0];
    }

    //tmp.x = (SCREEN_WIDTH / 2) - (16 / 2);
    //tmp.y = (SCREEN_HEIGHT / 2) - (16 / 2);
    //tmp.w = sprite->w;
    //tmp.h = sprite->h;

    if( SDL_GetTicks() - spr->last_update > (1000 / spr->frame_rate) ){
        spr->frame_idx = spr->frame_idx + 1;
        spr->last_update = SDL_GetTicks();
    }
    
    //pl->spr.frame_idx = (pl->spr.frame_idx + 1) % pl->spr.num_frames;
    spr->frame_idx = spr->frame_idx % spr->num_frames;

    if( spr->frame_idx < start_frame ){     
        spr->frame_idx = start_frame;
    }
    // Should restore the background stuff    
    //SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
    //SDL_BlitSurface( image1, (f_ptr + sprite->frame_idx), screen, &tmp );

    //for( i = 0; i < sprite->num_frames;i++ ){
        
    //}
}

void
player_init( player_t *player )
{
    int i;

    player->w = 16;
    player->h = 16;
    player->x = (SCREEN_WIDTH / 2) - (16 / 2);
    player->y = (SCREEN_HEIGHT / 2) - (16 / 2);
    // This should be greater than the width of mario, we need this condition for jump action
    player->x_vel = 96;
    player->y_vel = 48;
    player->dir = RIGHT;

    player->spr.w = 16;
    player->spr.h = 16;
    player->spr.num_frames = 4;
    player->spr.frame_idx  = 0;
    player->spr.frame_rate = 16;
    player->spr.l_frames = new SDL_Rect[ player->spr.num_frames ];
    for(i=0;i<player->spr.num_frames;i++){
        player->spr.l_frames[i].w = 16;
        player->spr.l_frames[i].h = 16;
        player->spr.l_frames[i].x = player->spr.l_frames[i].w * ( ((7 - i) * 2) - 1 );
        player->spr.l_frames[i].y = 0;
    }

    player->spr.r_frames = new SDL_Rect[ player->spr.num_frames ];
    for(i=0;i<player->spr.num_frames;i++){
        player->spr.r_frames[i].w = 16;
        player->spr.r_frames[i].h = 16;
        player->spr.r_frames[i].x = player->spr.r_frames[i].w * ( ((8 + i) * 2) - 1 );
        player->spr.r_frames[i].y = 0;
    }
    player->spr.up_frames = new SDL_Rect[2];
    // Right jump frame
    player->spr.up_frames[0].w = 16;
    player->spr.up_frames[0].h = 16;
    player->spr.up_frames[0].x = player->spr.up_frames[0].w * 25;
    player->spr.up_frames[0].y = 0;

    // Left jump frame
    player->spr.up_frames[1].w = 16;
    player->spr.up_frames[1].h = 16;
    player->spr.up_frames[1].x = player->spr.up_frames[1].w * 3;
    player->spr.up_frames[1].y = 0;
    
    player->spr.down_frames = new SDL_Rect[2];
    player->spr.down_frames[0].w = 16;
    player->spr.down_frames[0].h = 16;
    player->spr.down_frames[0].x = player->spr.up_frames[1].w * 3;
    player->spr.down_frames[0].y = 0;
    
}

// Update player state

void
move_player( player_t *player )
{
        // Jump handling, this should come first and change the player direction/status    
    if( up_pressed ){
        
        if( player->dir == RIGHT ){
            player->dir = JUMP_RIGHT;
            player->spr.f_ptr = &player->spr.up_frames[0];
            player->spr.frame_idx = 0;
        }else if( player->dir == LEFT ){
            player->dir = JUMP_LEFT;
            player->spr.f_ptr = &player->spr.up_frames[1];
            player->spr.frame_idx = 0;
        }
        
        /*
        if( SDL_GetTicks() - player->last_update > (1000 / player->y_vel) ){
            player->y = player->y - 1;
            player->last_update = SDL_GetTicks();
        } 
        */
    }
     
    if( right_pressed && player->dir != JUMP_RIGHT && player->dir != JUMP_LEFT ){
        // move player, check if he can move in this direction
        if( player->dir != RIGHT ){
            player->dir = RIGHT;
            player->spr.f_ptr = &player->spr.r_frames[0];
            player->spr.frame_idx = 0;
        }else{
            animate( &player->spr, RIGHT, 1 );
        }

        if( SDL_GetTicks() - player->last_update > (1000 / player->x_vel) ){
            player->x = player->x + 1;
            player->last_update = SDL_GetTicks();     
        }

    }else if( left_pressed && player->dir != JUMP_RIGHT && player->dir != JUMP_LEFT ){
        if( player->dir != LEFT ){
            player->dir = LEFT;
            player->spr.f_ptr = &player->spr.l_frames[0];
            player->spr.frame_idx = 0;
        }else{
            animate( &player->spr, LEFT, 1 );
        }

        if( SDL_GetTicks() - player->last_update > (1000 / player->x_vel) ){
            player->x = player->x - 1;
            player->last_update = SDL_GetTicks();
        }

        //animate( &player->spr, LEFT, 1 );
    }

    if( !up_pressed && !right_pressed && !left_pressed ){
        // Resetting the frame to 0, for both left and right
        //printf("Z");
        if( player->dir == RIGHT ){
            player->dir = RIGHT;
            player->spr.f_ptr = &player->spr.r_frames[0];
            player->spr.frame_idx = 0;
        }else if( player->dir == LEFT ){
            player->dir = LEFT;
            player->spr.f_ptr = &player->spr.l_frames[0];
            player->spr.frame_idx = 0;
        }
    }

    if( player->dir == JUMP_RIGHT || player->dir == JUMP_LEFT ){
        //gravity_accel
        //player->i_jump_vel = player->i_jump_vel - gravity_accel;
        //player->y = player->y - player->i_jump_vel;
        //printf("Im here\n");

        if( SDL_GetTicks() - player->last_update > (1000 / player->y_vel) ){
            //player->y = player->y - 1;

            // Im using a crude eqn which relies on the player x_vel to determine the x position when jumping
            if(right_pressed)
                player->x = player->x + ( (player->x_vel / (player->w * 2)) + 1 );
                //player->x = player->x + player->x_vel;

            if(left_pressed)
                player->x = player->x - ( (player->x_vel / (player->w * 2)) + 1 );
                //player->x = player->x - player->x_vel;

            player->i_jump_vel = player->i_jump_vel - gravity_accel;
            player->y = player->y - player->i_jump_vel;
            player->last_update = SDL_GetTicks();
        }
    }

    // This is to stop mario falling below the center
    if( player->y >= (SCREEN_HEIGHT / 2) - (16 / 2) ){
        player->y = (SCREEN_HEIGHT / 2) - (16 / 2);
        player->i_jump_vel = 20;

        if( player->dir == JUMP_RIGHT )
            player->dir = RIGHT;

        if( player->dir == JUMP_LEFT )
            player->dir = LEFT;
        
    }

    //printf("Y = %d\n", player->y);

    // Check if mario is standing on a platform, otherwise fall
    if( player->y < (SCREEN_HEIGHT / 2) - (16 / 2) && player->dir != JUMP_RIGHT && player->dir != JUMP_LEFT ){
        if( SDL_GetTicks() - player->last_update > (1000 / player->y_vel) ){
            //player->i_jump_vel = player->i_jump_vel - gravity_accel;
            player->y = player->y + 4; 
        }
        //printf("X");
    }
}

void
player_clean_up( player_t *player )
{
    if( player ){
        delete [] player->spr.l_frames;
        delete [] player->spr.r_frames;
        delete [] player->spr.up_frames;
        delete [] player->spr.down_frames;
    }
}

