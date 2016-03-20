#ifndef __PLAYER_HEADER__
#define __PLAYER_HEADER__

/*
struct player {
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
};
*/


void
move_player( player_t * );

void
draw( player_t *, ga_object *, SDL_Surface *, int );

#endif
