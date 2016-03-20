/*
 * =====================================================================================
 *
 *       Filename:  video.cpp
 *
 *    Description:  Displays the current video properties
 *
 *        Version:  1.0
 *        Created:  08/18/2012 09:49:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>

#include "SDL/SDL.h"


int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);


    const SDL_VideoInfo *display_props = SDL_GetVideoInfo();    
    std::cout << "Current video resolution" << std::endl;
    std::cout << "W = " << display_props->current_w << std::endl;
    std::cout << "H = " << display_props->current_h << std::endl;
    std::cout << "Total Video memory " << display_props->video_mem << std::endl;
    
    return 0;
}
