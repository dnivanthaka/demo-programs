#ifndef __GTYPEDEF_HEADER__
#define __GTYPEDEF_HEADER__

#include "SDL/SDL.h"

// Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;


typedef enum {
    LEFT, 
    RIGHT, 
    JUMP, 
    CROUCH
} dir;

typedef enum {
    BOTTOM_HIT,
    TOP_HIT,
    LEFT_HIT,
    RIGHT_HIT        
} collision_t;

typedef struct {
    int x;
    int y;
} frame;

const int frame_delay = 25;

// Level Types-------------------------------------------------
typedef struct {
    int width;
    int height;
    frame start_pos;
    char *data;
} level;

struct ga_object {
    int w;
    int h;
    int screen_x;
    int screen_y;
    int o_type;
    struct ga_object *next;
} ;

typedef struct {
    collision_t hit;
    struct ga_object *ob;
} collision_info;

typedef struct {
    int w;
    int h;
    int screen_x;
    int screen_y;
    dir direction;
    int vel_x;
    int vel_y;
    frame l_frames[4];
    frame r_frames[4];
    frame j_frames[2];
    frame c_frames[2];
    SDL_Surface *sprites;
    SDL_Surface *bg_ptr;
    SDL_Rect current_bg;
} player_t;

// Im putting this here for testing only

//player_t d;

#endif
