#include <iostream>

#include "SDL/SDL.h"
#include "config.h"
#include "types.h"

SDL_Surface *screen = NULL;

int init_screen()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        //fprintf(stderr, "Error initializing video.\n%s\n", SDL_GetError());
        std::cerr << "Error initializing video. " << SDL_GetError() << std::endl;
        exit(1);
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if( screen == NULL ){
        //fprintf(stderr, "Error setting video mode.\n%s\n", SDL_GetError());
        std::cerr << "Error setting video mode. " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_WM_SetCaption( "Demo Window", NULL );
    return 0;
}

SDL_Surface *load_image( char *filename )
{
    SDL_Surface *tmp;

    tmp = SDL_LoadBMP(filename );
    if( tmp == NULL ){
        std::cerr << "Couldn't load " << filename << "\n" << SDL_GetError() << std::endl;
        return NULL;
    }

    if( SDL_SetColorKey( tmp, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0xff, 0x00, 0xff) ) < 0 ){
        std::cerr << "Unable to set colorkey." << "\n" << SDL_GetError() << std::endl;
        return NULL;
    }

    return SDL_DisplayFormat(tmp);
}

void cleanup_screen()
{
    SDL_FreeSurface(screen);
}
