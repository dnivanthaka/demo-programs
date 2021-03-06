#include <stdlib.h>
#include "SDL/SDL.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define COLOR_DEPTH   32

void load_optimized_image(char *filename, SDL_Surface *surf)
{
    SDL_Surface *tmp;
    tmp = SDL_LoadBMP( filename );

    if( tmp != NULL ){
        surf = SDL_DisplayFormat( tmp );

        SDL_FreeSurface( tmp );
    }
}

void apply_surface( int x, int y, SDL_Surface *src, SDL_Surface *dest )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( src, NULL, dest, &offset );
}

void draw_background( SDL_Surface *background, SDL_Surface *image, int tiling )
{
   int width  = background->w;
   int height = background->h;
   int i, j, yofs, ofs;
   unsigned int *ptr_bk = (unsigned int *) background->pixels;
   unsigned int *ptr_im = (unsigned int *) image->pixels;

   SDL_Rect offset;

   offset.x = 0;
   offset.y = 0;

   yofs = 0;

   for( i=0;i<height;i++ ){
       for(j=0, ofs = yofs;j<width;j++, ofs++){
           //ptr_bk[ (height * i) + j ] = ptr_im[ ((height * i) % image->h) + (j % image->w) ];
           *(ptr_bk + ofs) = *(ptr_im +  ofs % (image->w + image->h) );
       }

       yofs += background->pitch / 4;
   }
   
   
   //SDL_BlitSurface( image, NULL, background, &offset  );
}


int main(int argc, char **argv)
{
    SDL_Surface *screen     = NULL;
    SDL_Surface *background = NULL;
    SDL_Surface *message    = NULL;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        exit(1);
    }

    SDL_WM_SetCaption( "Hello World", NULL );

    atexit( SDL_Quit );

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH, SDL_SWSURFACE  );

    if( screen == NULL ){
        fprintf(stderr, "Unable to set video mode %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    // Logic
    //load_optimized_image( "/home/dinusha/programs/SDL/images/ZIGZAG.BMP", background );
    background = SDL_LoadBMP("/home/dinusha/programs/SDL/images/ZIGZAG.BMP");
    
    //draw_background( screen, background, 1 );
    apply_surface( 0, 0, background, screen  );

    if(SDL_Flip(screen) == -1){
        return -1;
    }

    SDL_Delay(5000);

    SDL_FreeSurface( message );
    SDL_FreeSurface( background );
    SDL_FreeSurface( screen );
    return 0;
}
