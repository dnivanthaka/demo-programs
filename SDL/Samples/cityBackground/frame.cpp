
#include "frame.h"

Frame::Frame( SDL_Surface* spr, SDL_Surface* scr,
    int sprite_width, int sprite_height,
    int src_x, int src_y)
  : sprite(spr), screen(scr),
    spriteWidth(sprite_width), spriteHeight(sprite_height),
    spriteSourceX(src_x), spriteSourceY(src_y) {
}

void Frame::blit(Uint32 x, Uint32 y) {
  SDL_Rect src = { spriteSourceX, spriteSourceY, 
                   spriteWidth, spriteHeight 
                 };    
  SDL_Rect dest = {x, y, spriteWidth, spriteHeight };
  SDL_BlitSurface(sprite, &src, screen, &dest);
}

