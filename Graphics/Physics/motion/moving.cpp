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
SDL_Surface *char_img   = NULL;
SDL_Surface *floor      = NULL;

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
    int w;
    int h;
    unsigned short current_frame;
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
void update_game( float dt );
void render( float in );
void  handle_events();
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface* load_image( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0xFF, int b = 0xFF );
// -------------------------------------------------------------------------------------

struct entity guy;


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
        
            // Important to put this, otherwise you cannot exit from fullscreen.
            if( key_pressed() == SDLK_ESCAPE ){
                gameIsRunning = false;
            }

            if( key_pressed() == SDLK_RIGHT ){
                guy.current_frame++;
                guy.current_frame = guy.current_frame % 4;
            }

            //update_game( 1000 / GAME_SPEED_HZ );

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

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF );
    //screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );


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
    char_img = load_image( "mario3.png", true, 0xFF, 0, 0xFF  );
    floor    = load_image( "bricks.png", true, 0xFF, 0, 0xFF  );

}

void
init_entities()
{
    guy.w = 16;
    guy.h = 16;
    guy.x = SCREEN_WIDTH / 2  - guy.w / 2;
    //guy.y = SCREEN_HEIGHT / 2 - guy.h / 2;
    guy.y = SCREEN_HEIGHT - (guy.h + 16);
    guy.prev_x = guy.x;
    guy.prev_y = guy.y;
    guy.vel_x = 4;
    guy.vel_y = 4;
    guy.acc_x = 0;
    guy.acc_y = 1;
    guy.current_frame = 15;
}

void
update_game( float dt )
{
    SDL_Rect r_guy;

    //fprintf(stdout, "dt = %f\n", dt);

    //guy.vel_x = guy.vel_x * dt;
    //guy.vel_y = guy.vel_y * dt;
    guy.vel_x += guy.acc_x;
    guy.vel_y += guy.acc_y;

     // Checking for wall collisions
     // Left Wall
     if( guy.x + guy.vel_x <= 0 && guy.vel_x < 0 ){
         guy.vel_x = -1 * guy.vel_x;
         //guy.acc_x = -1 * guy.acc_x;
         //guy.acc_x = 0;
         //guy.acc_x--;
     }
     // Right Wall
     if( guy.x + guy.vel_x + guy.w >= SCREEN_WIDTH && guy.vel_x > 0){
         guy.vel_x = -1 * guy.vel_x;
         //guy.acc_x = -1 * guy.acc_x;
         //guy.acc_x = 0;
         //guy.acc_x--;
     }
     // Top Wall
     if( guy.y + guy.vel_y <= 0 && guy.vel_y < 0 ){
         guy.vel_y = -1 * guy.vel_y;
         //guy.acc_y = -1 * guy.acc_y;
         //guy.acc_y = 0;
         //guy.acc_y--;
     }
     // Bottom Wall
     if( guy.y + guy.vel_y + guy.h >= SCREEN_HEIGHT && guy.vel_y > 0 ){
         guy.vel_y = -1 * guy.vel_y;
         //guy.acc_y = -1 * guy.acc_y;
         //guy.acc_y = 0;
         //guy.acc_y--;
     }
    fprintf(stdout, "vel_x = %d\n", guy.vel_x);
    fprintf(stdout, "vel_y = %d\n", guy.vel_y);
    fprintf(stdout, "acc_x = %d\n", guy.acc_x);
    fprintf(stdout, "acc_y = %d\n", guy.acc_y);

    guy.x += guy.vel_x;
    guy.y += guy.vel_y;
     
}

void render( float in )
{
    SDL_Rect r_guy, ani_guy, r_floor;
    int prev_x, prev_y;
    
    ani_guy.w = guy.w;
    ani_guy.h = guy.h;
    ani_guy.x = guy.w * guy.current_frame;
    ani_guy.y = 0;

    r_guy.w = guy.w;
    r_guy.h = guy.h;
    r_guy.x = guy.x * in + (guy.prev_x * (1 - in));
    r_guy.y = guy.y * in + (guy.prev_y * (1 - in));

    // Drawing the sky
    SDL_FillRect( screen, NULL,SDL_MapRGB( screen->format, 0x5A, 0x94, 0xFF ) );

    // Drawing the floor
    for(int i=0;i<SCREEN_WIDTH / 16;i++){
        r_floor.w = 16;
        r_floor.h = 16;
        r_floor.x = i * 16;
        r_floor.y = SCREEN_HEIGHT - 16;


        //SDL_FillRect( screen, &r_guy,SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        SDL_BlitSurface( floor, NULL, screen, &r_floor );
    }
    SDL_BlitSurface( char_img, &ani_guy, screen, &r_guy );

    SDL_Flip(screen);

    guy.prev_x = guy.x;
    guy.prev_y = guy.y;

    // Removing the already drawn object ** This works
    SDL_FillRect( screen, &r_guy,SDL_MapRGB( screen->format, 0, 0, 0 ) );
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
