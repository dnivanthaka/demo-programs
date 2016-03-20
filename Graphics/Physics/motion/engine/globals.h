/*
 * =====================================================================================
 *
 *       Filename:  globals.h
 *
 *    Description:  Global Variables
 *
 *        Version:  1.0
 *        Created:  07/23/2012 10:00:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

SDL_Surface *screen = NULL;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

const int GAME_SPEED_HZ  = 60;
const int MAX_FRAME_SKIP = 30;
