/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Lesson 3 on Loading Images using SDL Image
 *
 *        Version:  1.0
 *        Created:  12/21/2011 09:46:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include	<stdlib.h>
#include <string>
#include	"SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL;

    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

int main(int argc, char **argv)
{
    return 0;
}
