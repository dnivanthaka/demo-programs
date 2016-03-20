/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Just refreshing my SDL knowledge
 *
 *        Version:  1.0
 *        Created:  12/25/2012 12:23:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <sstream>

SDL_Sufrace *screen = NULL;

SDL_Event event;

bool
handle_events()
{
    bool quit = false;

    while( SDL_PollEvent( &event ) ){
       if( event.type == SDL_KEYDOWN ){} 

       if( event.type == SDL_QUIT ){
            quit = true;
       }
    }
}

int
main( int argc, char *argv[] )
{
    bool quit = false;

    if( init() == false )
        return EXIT_FAILURE;

    if( load_files() == false )
        return EXIT_FAILURE;


    while( quit == false ){
    }

    return 0;
}
