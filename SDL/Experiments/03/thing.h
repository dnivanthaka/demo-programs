#ifndef __THING_H__
#define __THING_H__

struct thing {
    int width, height;
    coord pos;
    coord vel;
    coord accel;
    coord current_frame;
    Uint8 max_frames;
    bool isplayer;
    bool isjumping;
    SDL_Surface *sprites;
    SDL_Surface *back;
};

//------------------------------------------------------------------------
void init_thing(struct thing *t, bool isp);
void set_vel_thing(struct thing *t, int x, int y);
void set_vel_thing_x(struct thing *t, int x);
void set_vel_thing_y(struct thing *t, int y);
void set_jumping_thing(struct thing *t, bool isj);
void set_accel_thing(struct thing *t, int x, int y);
void set_pos_thing(struct thing *t, int x, int y);
void handle_collisions_thing(struct thing *t);
void handle_events_thing(struct thing *t, SDL_Event *e);
void update_state_thing(struct thing *t); 
void animate();
void draw_thing(struct thing *t, SDL_Surface *s);
void erase_thing(struct thing *t, SDL_Surface *s);
void cleanup_thing(struct thing *t);
//------------------------------------------------------------------------
#endif
