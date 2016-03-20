#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"


SDL_Surface *screen;

void putpixel(int x, int y, int color)
{
    unsigned int *ptr = (unsigned int *) screen->pixels;
    int lineoffset = y * ( screen->pitch / 4 );
    ptr[ lineoffset + x ] = color;
}

void render()
{
    if(SDL_MUSTLOCK(screen))
        if( SDL_LockSurface(screen) < 0 )
            return;

    int tick = SDL_GetTicks();

    int i, j, yofs, ofs;

    yofs = 0;

    for(i=0;i<480;i++){
        for(j=0, ofs = yofs; j < 640; j++, ofs++){
           //( (unsigned int *)screen->pixels )[ofs] = i * i + j * j + tick; 
           ( (unsigned int *)screen->pixels )[ofs] = j * tick; 
        }

        yofs += screen->pitch / 4;
    }

    putpixel(10, 10, 0xff0000);
    //putpixel(11, 10, 0xff0000);
    //putpixel(10, 11, 0xff0000);
    //putpixel(11, 11, 0xff0000);

    if(SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);

    SDL_UpdateRect( screen, 0, 0, 640, 480 );
}

int main(int argc, char **argv)
{
    SDL_Event event;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        exit(1);
    }

    atexit( SDL_Quit );

    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }

    // Game loop
    for(;;){
        render();

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    return 0;
                    break;
                case SDL_QUIT:
                    return 0;
            }
        }
    }
    return 0;
}
