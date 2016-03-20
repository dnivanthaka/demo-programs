#include "SDL/SDL.h"

int main( int argc, char **argv)
{
    SDL_Surface *hello  = NULL;
    SDL_Surface *screen = NULL;

    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );

    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    hello = SDL_LoadBMP( "/home/dinusha/Pictures/SDL/hello.bmp" );

    SDL_BlitSurface( hello, NULL, screen, NULL );

    SDL_Flip( screen );

    SDL_Delay( 2000 );

    SDL_FreeSurface( hello );

    SDL_Quit();

    return 0;
}
