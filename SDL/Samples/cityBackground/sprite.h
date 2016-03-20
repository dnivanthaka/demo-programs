#ifndef SPRITE__H
#define SPRITE__H

#include <vector>
#include <iostream>
using std::vector;

#include "frame.h"

class Sprite {
public:
  Sprite(SDL_Surface *surface, SDL_Surface *screen)
    : frame(surface, screen, surface->w, surface->h, 0, 0),
      xCoordinate(0), yCoordinate(0), speed(0) { }

  Sprite(SDL_Surface *surface, SDL_Surface *screen, 
    int w, int h, int src_x, int src_y,
    float x, float y, float s) : 
    frame(surface, screen, w, h, src_x, src_y),
    xCoordinate(x), yCoordinate(y), speed(s) { }

  void blit();
  void move(Uint32 ticks);
  float getX() const { return xCoordinate; }
  float getY() const { return yCoordinate; }
  float getSpeed() const { return speed; }
  void incrSpeed(float incr) { speed += incr; }
  void decrSpeed(float incr) { speed -= incr; }
private:
  Frame frame;
  float xCoordinate;
  float yCoordinate;
protected:
  float speed;
};
#endif
