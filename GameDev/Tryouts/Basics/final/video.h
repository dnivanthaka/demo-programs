/*
 * =====================================================================================
 *
 *       Filename:  video.h
 *
 *    Description:  Video Functions
 *
 *        Version:  1.0
 *        Created:  05/01/2013 10:15:31 PM
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

#ifndef __VIDEO_H__
#define __VIDEO_H__

SDL_Surface* load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
bool init( SDL_Surface ** );

#endif
