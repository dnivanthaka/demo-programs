#include <iostream>
#include <iomanip>
#include <string>
#include "ioSingleton.h"

IOSingleton* IOSingleton::getInstance(SDL_Surface *screen) {
  if (!instance) instance = new IOSingleton(screen); 
  return instance;
}

SDL_Surface* IOSingleton::loadAndSet(const char* filename) {
  SDL_Surface *tmp = IMG_Load(filename);
  if (tmp == NULL) {
    throw std::string("Unable to load bitmap ")+filename;
  }
  Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
  SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);

  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormat(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

IOSingleton::IOSingleton(SDL_Surface *scr) : screen(scr) {
  if ( TTF_Init() == -1 ) {
    throw std::string("TTF_Init failed: ") + TTF_GetError();
  }
  font = TTF_OpenFont("font/FreeSerifBold.ttf", 20);
  if ( !font ) {
    throw std::string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  SDL_EnableUNICODE( SDL_ENABLE );
  atexit(TTF_Quit);
}

void IOSingleton::printMessageAt(const string& msg, Uint32 x, Uint32 y) {
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {0, 0, 0, 0};
   stext = TTF_RenderText_Solid(font, msg.c_str(), color);
   SDL_BlitSurface( stext, NULL, screen, &dest );
}

void IOSingleton::printMessageCenteredAt( const string& msg, Uint32 y) {
   SDL_Color color = {0, 0, 0, 0};
   stext = TTF_RenderText_Solid(font, msg.c_str(), color);
   Uint32 x = ( WIDTH - stext->w ) / 2;
   SDL_Rect dest = {x,y,0,0};
   SDL_BlitSurface( stext, NULL, screen, &dest );
}

void IOSingleton::printMessageValueAt(const string& msg, float value, 
     Uint32 x, Uint32 y) {
   std::stringstream strm;
   std::string message = msg;
   strm.setf(std::ios::fixed, std::ios::floatfield);
   strm.setf(std::ios::showpoint);
   strm << message << std::setprecision(2);
   strm << value << "\0";
   message = strm.str();
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {0, 0, 0, 0};
   stext = TTF_RenderText_Solid(font, message.c_str(), color);
   SDL_BlitSurface( stext, NULL, screen, &dest );
}

void IOSingleton::printStringAfterMessage( const string& msg,
       Uint32 x, Uint32 y ) {
   printMessageAt(msg+inputString, x, y);
}

void IOSingleton::buildString(SDL_Event event) {
  if( inputString.size() <= MAX_STRING ) {
    unsigned ch = event.key.keysym.sym;
    if (isalpha(ch) || isdigit(ch) || ch == ' ') {
      inputString += char(event.key.keysym.unicode);
    }
  }     
  if( event.key.keysym.sym == SDLK_BACKSPACE
      && inputString.length() > 0 ) {
      // remove a character from the end
      int length = inputString.size();
      inputString.erase( length - 1 );
  }
}

