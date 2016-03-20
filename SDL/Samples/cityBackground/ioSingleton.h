#ifndef SINGLE__H
#define SING__H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
using std::string;

const Uint16 WORLD_WIDTH = 1280;
const Uint16 WORLD_HEIGHT = 960;

const Uint16 WIDTH = 640;
const Uint16 HEIGHT = 480;
const unsigned int MAX_STRING = 50;

const int MIN_BACKGROUND_SPEED = 50; 
const int MIN_FOREGROUND_SPEED = 100;
const int MIN_JET_SPEED = 50;
const int MAX_JET_SPEED = 200;

class IOSingleton {
public:
  ~IOSingleton() { SDL_EnableUNICODE( SDL_DISABLE ); }
  static IOSingleton* getInstance(SDL_Surface* screen);
  static SDL_Surface* loadAndSet(const char* filename);

  void printMessageAt(const string& msg, Uint32 x, Uint32 y);
  void printMessageCenteredAt(const string& msg, Uint32 y);
  void printMessageValueAt(const string& msg, float value, 
         Uint32 x, Uint32 y);

  void printStringAfterMessage(const string&, Uint32 x, Uint32 y);
  void buildString(SDL_Event);
private:
  IOSingleton(SDL_Surface*);

  SDL_Surface *screen;
  static IOSingleton* instance;
  TTF_Font *font;
  SDL_Surface *stext;
  string inputString;
};
#endif
