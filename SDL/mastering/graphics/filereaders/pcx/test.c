#include <stdio.h>

#include "SDL/SDL.h"
#include "pcx.h"

SDL_Surface *screen;
SDL_Surface *image;

int
main( int argc, char *argv[] )
{
    pcx_picture_t image;

    read_pcx( "all2.pcx", &image );

    SDL_Init( SDL_INIT_VIDEO );
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    SDL_WM_SetCaption( "Raw image Data", NULL );

    //printf("== Image Data ==\n");
    //printf("Image Width = %d\n",  image.header.h_screen_size);
    //printf("Image Height = %d\n", image.header.v_screen_size);

    SDL_FreeSurface( image );
    SDL_FreeSurface( screen );

    SDL_Quit();

    return 0;
}

