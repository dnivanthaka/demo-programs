#include <vector>
#include <iostream>
using std::vector;

#include "sprite.h"

void Sprite::blit() { 
  Uint32 x = static_cast<Uint32>(xCoordinate);
  Uint32 y = static_cast<Uint32>(yCoordinate);
  frame.blit(x, y); 
}

void Sprite::move(Uint32 ticks) { 
  float incr = speed * static_cast<float>(ticks) * 0.001;
  xCoordinate -= incr;
  float width = static_cast<float>(frame.getWidth());
  float height = static_cast<float>(frame.getHeight());
  //std::cout << "xCoordinate: " << xCoordinate << std::endl;
  //std::cout << "-width: " << -width << std::endl;
  if ( xCoordinate < -width ) xCoordinate = width;
  if ( yCoordinate < -height ) yCoordinate = height;
}
