/*
 * =====================================================================================
 *
 *       Filename:  video.cpp
 *
 *    Description:  Video Functions
 *
 *        Version:  1.0
 *        Created:  05/01/2013 10:01:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include "globals.h"
#include "video.h"



/*
 * Returns an optimized image for a given display format
 * Sets the color key as 0xff,0,0xff
 */
SDL_Surface*
load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL, *optimizedImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        if( optimizedImage != NULL ){
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void 
apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool
init( SDL_Surface **screen )
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return false;

    *screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( *screen == NULL )
        return false;

    SDL_WM_SetCaption( "Luigi Demo", NULL );

    return true;
}

