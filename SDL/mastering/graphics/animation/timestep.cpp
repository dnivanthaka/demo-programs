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

SDL_Surface *screen = NULL;
SDL_Surface *blit_1 = NULL;
SDL_Surface *stage_objects;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_events();

int 
main(int argc, char *argv[])
{
    SDL_Rect tux;
    SDL_Rect char_rect;
    Uint32 start_time;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "SDL Examples", NULL );

    blit_1 = loadImage( "mario3.png" );

    if( blit_1 != NULL ){
        //tux.w = 220;
        tux.w = blit_1->w;
        //tux.h = 261;
        tux.h = blit_1->h;
        tux.x = (SCREEN_WIDTH / 2) - (16 / 2);
        tux.y = (SCREEN_HEIGHT / 2) - (16 / 2);

        char_rect.w = 16;
        char_rect.h = 16;
        char_rect.y = 0;

        short i = 0;
        int frameToDraw = 0;
        Uint32 anim_time;
        Uint32 numTicks = 0;
        start_time = SDL_GetTicks();
        anim_time = start_time;

        while( numTicks != 800 ){
            
            // handle input
            // logic
                        
            // rendering
            char_rect.x = (15 + i) * char_rect.w;
            //frameToDraw = ( ((SDL_GetTicks() - start_time) * (14 / 1000)) % 14 );
            
            //frameToDraw = ( ((SDL_GetTicks() - anim_time) / (100)) % 4 );
            //printf("%d\n", frameToDraw);
            
            //if( numTicks % 4 == 0 )
                //frameToDraw = (frameToDraw + 2) % 8;

            if( SDL_GetTicks() - start_time > (1000 / 16)  ){
                tux.x = tux.x + 4;
                frameToDraw = (frameToDraw + 2) % 8;
                start_time = SDL_GetTicks();
            }

            i = frameToDraw;
            printf("%d\n", i);
            //i = (i + 2) % 6;
            //SDL_BlitSurface( blit_1, NULL, screen, &tux );
            SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0) );
            SDL_BlitSurface( blit_1, &char_rect, screen, &tux );
            SDL_Flip( screen );
            
            
            //if( SDL_GetTicks() - start_time < 1000 / FPS ){
            //if( SDL_GetTicks() - start_time < FPMS ){
                //printf("pppppppppppp");
                //SDL_Delay( (1000 / FPS) - (SDL_GetTicks() - start_time) );
            //}
            //start_time = SDL_GetTicks();
            numTicks++;
        }
        //SDL_Delay(2000);
    }

    SDL_FreeSurface( blit_1 );
    SDL_FreeSurface( screen );

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

}
