// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS  = 60;
const int FPMS = FPS / 1000;

SDL_Surface *screen = NULL;
SDL_Surface *image1 = NULL;
SDL_Surface *image2 = NULL;
Mix_Music *music = NULL;
SDL_Event event;
int num_stars = 20;
bool gameRunning = true;
//SDL_Surface *blit_1 = NULL;
//SDL_Surface *stage_objects;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_input();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
//void move_stars( star_t *stars, frame_t *cont );
void cross_fade( SDL_Surface *from, SDL_Surface *to );


int 
main(int argc, char *argv[])
{
    int i;
    Uint32 start_time = 0, numTicks = 0;
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

    //Initialize SDL_mixer 
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) { 
        return false; 
    }

    SDL_WM_SetCaption( "SDL Examples", NULL );

    //image1 = loadImage( "pic1.png" );

    //Load the music 
    music = Mix_LoadMUS( "STARTREK.MID" );

    Mix_PlayMusic( music, -1 );

    while( gameRunning ){
        
        handle_input();

        // clearing old stars
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
            
        //move_stars( stars, &container );

        //cross_fade( screen, image1 );

        //SDL_Flip( screen );
            
            
        if( SDL_GetTicks() - start_time < 1000 / FPS ){
            //if( SDL_GetTicks() - start_time < FPMS ){
            SDL_Delay( (1000 / FPS) - (SDL_GetTicks() - start_time) );
        }
        start_time = SDL_GetTicks();
        numTicks++;
    }
        //SDL_Delay(2000);

    //Stop the music 
    Mix_HaltMusic();

    SDL_FreeSurface( screen );
    //Free the music 
    Mix_FreeMusic( music );
    SDL_Quit();

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

    //src_img = IMG_Load( file.c_str() );

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
        if( event.type == SDL_QUIT ){
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
cross_fade( SDL_Surface *from, SDL_Surface *to )
{
    int x, y;
    Uint32 pix_f, pix_t;
    Uint8 r_t, g_t, b_t, r_f, g_f, b_f;

    if ( SDL_MUSTLOCK(from) ) {
        if ( SDL_LockSurface(from) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }
    if ( SDL_MUSTLOCK(to) ) {
        if ( SDL_LockSurface(to) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

    for(y=0;y<from->h;y++){
        for(x=0;x<from->w;x++){
            pix_f = getpixel(from, x, y);
            pix_t = getpixel(to, x, y);

            SDL_GetRGB( pix_f, from->format, &r_f, &g_f, &b_f );
            SDL_GetRGB( pix_t, to->format, &r_t, &g_t, &b_t );

            if( r_t > r_f ){
                r_f++;
            }else if( r_t < r_f ){
                r_f--;
            }

            if( g_t > g_f ){
                g_f++;
            }else if( g_t < g_f ){
                g_f--;
            }

            if( b_t > b_f ){
                b_f++;
            }else if( b_t < b_f ){
                b_f--;
            }
            

            //if( pix_t > pix_f ) pix_f++;
            //if( pix_t < pix_f ) pix_f--;


            putpixel(from, x, y, SDL_MapRGB( from->format, r_f, g_f, b_f ));
            //putpixel( from, x, y, pix_f );

        }
    }


    if ( SDL_MUSTLOCK(from) ) {
        SDL_UnlockSurface(from);
    }
    if ( SDL_MUSTLOCK(to) ) {
        SDL_UnlockSurface(to);
    }
}
