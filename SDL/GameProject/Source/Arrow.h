
#pragma once
#include<SDL/SDL.h>

class Arrow
{
public:
    Arrow();
    //rect to represent arrow position from the right
    SDL_Rect arrowRpos;
    //SDL_Surface to hold arrow image
    SDL_Surface * arrowR;
    //rect to represent arrow position from the left
    SDL_Rect arrowLpos;
    //SDL_Surface to hold arrow image from left
    SDL_Surface * arrowL;

    bool used;

};



