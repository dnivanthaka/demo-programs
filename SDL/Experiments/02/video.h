#ifndef __VIDEO_H__
#define __VIDEO_H__

extern SDL_Surface *screen;

int init_screen();
SDL_Surface *load_image( char *filename );
void cleanup_screen();

#endif
