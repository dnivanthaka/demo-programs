// Brian Malloy        September, 2006
// Framework for Game Engine

#include <SDL/SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; using std::string;
#include <vector>

#include "background.h"

class Manager {
public:
   static Manager* getInstance() {
     if (instance == NULL) instance = new Manager();
     return instance;
   }
   ~Manager () { 
     SDL_FreeSurface(background_surface); 
   }
   void play();

private:
   Manager ();
   void moveAndBlit();

   static Manager* instance;

   Uint32 cur_ticks;
   Uint32 prev_ticks;
   Uint32 ticks;

   SDL_Surface *screen;
   IOSingleton *one;
   SDL_Surface *background_surface;

   Background background1;
   Background background2;
};
