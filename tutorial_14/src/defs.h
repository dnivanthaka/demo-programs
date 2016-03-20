#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_MAP_X 400
#define MAX_MAP_Y 300

#define TILE_SIZE 32

#define SCROLL_SPEED 8

#define GRAVITY_SPEED 0.8

#define MAX_FALL_SPEED 20

#define PLAYER_SPEED 4

#define TRANS_R 127
#define TRANS_G 0
#define TRANS_B 127

#define MAX_MESSAGE_LENGTH 100

#define BLANK_TILE 0

#define MAX_TILES 10
