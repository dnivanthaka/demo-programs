#include <cmath>
#include "manager.h"

Manager::Manager() :
  cur_ticks(0), prev_ticks(0), ticks(0),
  screen(SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_HWSURFACE)),
  one( IOSingleton::getInstance(screen) ),
  background_surface(one->loadAndSet("images/back.bmp")),
  background1(background_surface, screen, 0, 0, 0, -80, MIN_BACKGROUND_SPEED),
  background2(background_surface, screen, 0, 0, -1280, -80, MIN_BACKGROUND_SPEED) {

  srand(time(0));
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
   throw string("Unable to initialize SDL: ");
  }
  if (screen == NULL) { throw string("Unable to set video mode"); }
  atexit(SDL_Quit);
}

void Manager::moveAndBlit() {
  background1.move(ticks);
  background1.blit();
  background2.move(ticks);
  background2.blit();
}

void Manager::play() {
  int frames = 0;
  SDL_Event event;
  cur_ticks = SDL_GetTicks();
  while ( true ) {
     prev_ticks = cur_ticks;
     cur_ticks = SDL_GetTicks();
     ticks = cur_ticks-prev_ticks;

     moveAndBlit();

     ++frames;
     one->printMessageValueAt("fps: ", frames/(0.001*cur_ticks), 20, 20);
     one->printMessageValueAt("frames: ", frames, 20, 40);
     SDL_Flip(screen);

     SDL_PollEvent(&event);
     Uint8 *keystate = SDL_GetKeyState(NULL);
     if (keystate[SDLK_q] || keystate[SDLK_ESCAPE]) break;
     if (event.type == SDL_QUIT) break;
     if (event.key.keysym.sym == SDLK_q) break;
  }
}
