#include <vector>
#include <iostream>
using std::vector;
#include "sprite.h"

class Background {
public:
  Background(SDL_Surface *back_surface, SDL_Surface *screen,
    int src_x, int src_y, float x, float y, float s) : 
    back(back_surface, screen, back_surface->w, back_surface->h,
      src_x, src_y, x, y, s) {
  }
  void blit() { back.blit(); }
  void move(Uint32 ticks) { back.move(ticks); }
  float getX() const { return back.getX(); }
  float getY() const { return back.getY(); }
  void incrSpeed(float incr) { back.incrSpeed(incr); }
  void decrSpeed(float incr) { back.decrSpeed(incr); }
private:
  Sprite back;
};
