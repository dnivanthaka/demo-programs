/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Reading VideoInformation
 *
 *        Version:  1.0
 *        Created:  07/20/2012 08:56:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

/*
 * hw_available

Is it possible to create hardware surfaces ?

wm_available

Is there a window manager available ?

blit_hw

Are hardware to hardware blits accelerated ?

blit_hw_CC

Are hardware to hardware colorkey blits accelerated ?

blit_hw_A

Are hardware to hardware alpha blits accelerated ?

blit_sw

Are software to hardware blits accelerated ?

blit_sw_CC

Are software to hardware colorkey blits accelerated ?

blit_sw_A

Are software to hardware alpha blits accelerated ?

blit_fill

Are color fills accelerated ?

video_mem

Total amount of video memory in Kilobytes, should be accessed only if hw_available == 1, otherwise it is equal to 0

vfmt

Pixel format of the video device

current_w, current_h

Width and height of the current video mode, or of the desktop mode if SDL_GetVideoInfo was called before SDL_SetVideoMode (available since SDL 1.2.10)
 *
 */

//#include <cstdlib>
#include <iostream>

#include "SDL/SDL.h"

SDL_Surface *screen = NULL;

int
main(int argc, char *argv[])
{
    //SDL_VideoInfo *vid = NULL;

    SDL_Init( SDL_INIT_VIDEO );

    //screen = SDL_SetVideoMode( 640, 480, 16, SDL_DOUBLEBUF | SDL_FULLSCREEN );
    screen = SDL_SetVideoMode( 1920, 1080, 16, SDL_DOUBLEBUF | SDL_FULLSCREEN );

    const SDL_VideoInfo *vid = SDL_GetVideoInfo();
    /*
    printf("HW Available: %d\n", vid->hw_available);
    printf("WM Available: %d\n", vid->wm_available);
    printf("Blit HW: %d\n", vid->blit_hw);
    printf("Blit HW Colorkey: %d\n", vid->blit_hw_CC);
    printf("Alpha Blits HW Accelarated: %d\n", vid->blit_hw_A);
    printf("Blit SW: %d\n", vid->blit_sw);
    printf("Blit SW Colorkey: %d\n", vid->blit_sw_CC);
    printf("Alpha Blits SW Accelarated: %d\n", vid->blit_sw_A);
    printf("ColorFills Accelarated: %d\n", vid->hw_available);
    printf("Total Video Memory: %d KB\n", vid->video_mem);
    */

    std::cout << "HW Available: " << vid->hw_available << std::endl;
    std::cout << "WM Available: " << vid->wm_available << std::endl;
    std::cout << "Blit HW: " << vid->blit_hw << std::endl;
    std::cout << "Blit HW Colorkey: " << vid->blit_hw_CC << std::endl;
    std::cout << "Current Width: " << vid->current_w << std::endl;
    std::cout << "Current Height: " << vid->current_h << std::endl;
    std::cout << "Current BPP: " << vid->vfmt->BitsPerPixel << std::endl;
    //printf("Alpha Blits HW Accelarated: %d\n", vid->blit_hw_A);
    //printf("Blit SW: %d\n", vid->blit_sw);
    //printf("Blit SW Colorkey: %d\n", vid->blit_sw_CC);
    //printf("Alpha Blits SW Accelarated: %d\n", vid->blit_sw_A);
    //printf("ColorFills Accelarated: %d\n", vid->hw_available);
    //printf("Total Video Memory: %d KB\n", vid->video_mem);
    //

    SDL_FreeSurface( screen );

    SDL_Quit();

    return 0;
}
