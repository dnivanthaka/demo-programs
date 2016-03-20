#ifndef __GRAPHICS_HEADER__
#define __GRAPHICS_HEADER__

SDL_Surface * load_image( std::string );
void apply_surface( int, int, SDL_Surface *, SDL_Surface *, SDL_Rect *clip = NULL);
void fill( SDL_Surface *dest, int r, int g, int b );

#endif
