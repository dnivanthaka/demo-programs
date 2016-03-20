#include <cstdlib>
#include <string>

#include "SDL/SDL.h"
#include "pcx.h"

SDL_Surface *screen;
SDL_Surface *raw_image;

int
main( int argc, char *argv[] )
{
    pcx_picture_t image;
    std::string file = "all2.pcx";
    Uint32 rmask, gmask, bmask, amask;
    SDL_Color colors[256];
    SDL_Surface *tmp;

    read_pcx( file.c_str(), &image );

    SDL_Init( SDL_INIT_VIDEO );
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    SDL_WM_SetCaption( "Raw image Data", NULL );

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    for(int i=0;i<256;i++){
        colors[i].r = image.palette.triples[i].red;
        colors[i].g = image.palette.triples[i].green;
        colors[i].b = image.palette.triples[i].blue;
    }

/*
http://damien.douxchamps.net/ieee1394/coriander/
http://www.gamedev.net/topic/227811-sdl_creatergbsurfacefrom/
lsize = (long )hdr.BytesPerLine * hdr.Nplanes * (1 + hdr.Ymax - hdr.Ymin);
Quote from the above linked documentation: "pitch is the length of each scanline in bytes."
So if the line is 640 pixels wide, and each pixel is three bytes, then pitch is 640*3.
EDIT: That would be a line in the source image. I.e. the one "pixels" is pointing to. 
*/
/*
    raw_image = SDL_CreateRGBSurfaceFrom( image.buffer, image.header.pcx_window.x_max, 
        image.header.pcx_window.y_max, image.header.bitsperpixel, image.header.pcx_window.x_max * 3, rmask, gmask, bmask, amask );
*/
     // Set the color info for the screen
    //SDL_SetColors(screen, colors, 0, 256 );

    tmp = SDL_CreateRGBSurfaceFrom( image.buffer, 320, 
        200, 8, image.header.bytes_per_line, rmask, gmask, bmask, 0 );

    //SDL_SetPalette(tmp, SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 256);
    SDL_SetColors(tmp, colors, 0, 256);

    raw_image = SDL_DisplayFormat( tmp );

    SDL_BlitSurface( raw_image, NULL, screen, NULL );

    SDL_Flip( screen );

    //printf("== Image Data ==\n");
    //printf("Image Width = %d\n",  image.header.h_screen_size);
    //printf("Image Height = %d\n", image.header.v_screen_size);
    SDL_Delay(10000);

    SDL_FreeSurface( tmp );
    SDL_FreeSurface( raw_image );
    SDL_FreeSurface( screen );

    SDL_Quit();

    return 0;
}

