/*
 * =====================================================================================
 *
 *       Filename:  globals.h
 *
 *    Description:  Global Variables
 *
 *        Version:  1.0
 *        Created:  05/04/2013 10:02:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/SDL.h"

const int SCREEN_WIDTH        = 640;
const int SCREEN_HEIGHT       = 480;
const int SCREEN_BPP          = 32;
const int GAME_FRAME_RATE_HZ  = 30;
const int GAME_PHYSICS_HZ     = 60;

extern SDL_Event event;
extern bool keyevents[];
extern bool gameIsRunning;

extern int tile_map[];

#endif
