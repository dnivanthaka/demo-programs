#ifndef SPRITETexture__H
#define SPRITETexture__H

#include <iostream>
#include "ioSingleton.h"

class Frame {
public:
  // Need to pass width and height in here because the sprite
  // might not consist of the whole surface, but only part of
  // the surface.
  Frame( SDL_Surface* spr, SDL_Surface* scr,
      int sprite_width, int sprite_height,
      int src_x, int src_y);

  void blit(Uint32 x, Uint32 y);

  int getWidth()  const { return spriteWidth; }
  int getHeight() const { return spriteHeight; }
private:
  SDL_Surface * sprite;
  SDL_Surface * screen;
  Uint32 spriteWidth;
  Uint32 spriteHeight;
  Uint32 spriteSourceX;
  Uint32 spriteSourceY;
};

#endif
