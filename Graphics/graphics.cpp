/*
 * =====================================================================================
 *
 *       Filename:  graphics.cpp
 *
 *    Description:  Handling of graphics routines
 *
 *        Version:  1.0
 *        Created:  07/15/2012 10:19:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
// HEADER FILES ------------------------------------------------------------------------
#include <string>
#include <stack>
#include <cstdlib>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
// -------------------------------------------------------------------------------------
// PUBLIC DATA -------------------------------------------------------------------------
SDL_Surface *screen = NULL;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
// -------------------------------------------------------------------------------------
// PRIVATE DATA ------------------------------------------------------------------------
bool gameIsRunning = true;
SDL_Event event;
TTF_Font *font_basic = NULL;
bool keys_held[323];
SDL_Color text_color = { 0, 0, 0 };

struct StateStruct{
    void (*StatePointer)();
};

// -------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES -----------------------------------------------------------------
int init_graphics( std::string caption );
void clean_up();
void init_events();
int key_pressed();
bool key_held(int key);
void  handle_events();
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface* load_image( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0xFF, int b = 0xFF );
void confirm_box( std::string message );
void main_menu();
void options_menu();
void game();
void intro();

bool exit();
// -------------------------------------------------------------------------------------

std::stack<StateStruct> currentState;

int
main(int argc, char *argv[])
{
    init_graphics("Graphics Demo");
    init_events();

    StateStruct in;
    in.StatePointer = intro;
    currentState.push( intro );

    /*
    while( gameIsRunning ){
        handle_events();
        //putpixel( screen, 100, 100, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        if( key_pressed() == SDLK_ESCAPE ){
            while( key_pressed() != SDLK_y ){
                confirm_box("Are you sure you want to exit? ");
                handle_events();
                SDL_Flip(screen);
            }
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            fprintf(stdout, "ESC pressed\n");
            gameIsRunning = false;
        }

        SDL_Flip(screen);
    }
    */

    while( !currentState.empty() ){
        currentState.top().StatePointer();
    }

    //SDL_FreeSurface( screen );
    clean_up();
}

int
init_graphics( std::string caption )
{
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 ){
        return -1;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create Screen surface in %d - %s\n", __LINE__, __FILE__ );
        return -1;
    }

    SDL_WM_SetCaption(caption.c_str(), NULL);

    if( TTF_Init() == -1 ){
        fprintf( stderr, "Unable to initialize Font Subsystem in %d - %s\n", __LINE__, __FILE__ );
        return -1;
    }

    font_basic = TTF_OpenFont( "VeraSe.ttf", 18 );

}

void
confirm_box( std::string message )
{
     static bool isAnimated = false;

     SDL_Rect tmp, b1, b2, msg_box, msg_box_shadow;
     SDL_Surface *txt_s;
     short padding = 15, b1_padding = 2, b2_padding = 2;
     int txt_w = 0;
     int txt_h = 0;

     tmp.w = 200;
     tmp.h = 200;
     tmp.x = 100;
     tmp.y = 100;

     // Getting text dimensions
     if( TTF_SizeText( font_basic, message.c_str(), &txt_w, &txt_h ) == -1 ){
        fprintf( stderr, "Unable to retrieve text Dimensions in %d - %s\n", __LINE__, __FILE__);
        return;
     }

     tmp.w = txt_w;
     tmp.h = txt_h;

     msg_box.w = tmp.w + (padding * 2);
     msg_box.h = tmp.h + (padding * 2);
     msg_box.x = (SCREEN_WIDTH / 2)  - (msg_box.w / 2);
     msg_box.y = (SCREEN_HEIGHT / 2) - (msg_box.h / 2);

     msg_box_shadow.w = msg_box.w / 2;
     msg_box_shadow.h = msg_box.h;
     msg_box_shadow.x = (SCREEN_WIDTH / 2)  - (msg_box_shadow.w / 2);
     msg_box_shadow.y = msg_box.y;

     b1.w = msg_box.w - (b1_padding * 2);
     b1.h = msg_box.h - (b1_padding * 2);
     b1.x = msg_box.x + b1_padding;
     b1.y = msg_box.y + b1_padding;

     b2.w = b1.w - (b2_padding * 2);
     b2.h = b1.h - (b2_padding * 2);
     b2.x = b1.x + b2_padding;
     b2.y = b1.y + b2_padding;

     tmp.x = msg_box.x + padding;
     tmp.y = msg_box.y + padding;
     if( !isAnimated ){
     //fprintf(stdout, "%d - %d\n", msg_box.x, msg_box.y);
        for(int i=0; i<(msg_box.w / 2);i++ ){
        
            SDL_FillRect( screen, &msg_box_shadow, SDL_MapRGB(screen->format, 0xDC, 0xDC, 0xDC) );
            SDL_Flip( screen );
            //SDL_Delay(1);

            msg_box_shadow.w++;
            msg_box_shadow.x = (SCREEN_WIDTH / 2)  - (msg_box_shadow.w / 2);
        }

        isAnimated = true;
     }

     txt_s = TTF_RenderText_Solid( font_basic, message.c_str(), text_color );
     // Rendering background box
     SDL_FillRect( screen, &msg_box, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
     // Rendering box 1
     SDL_FillRect( screen, &b1, SDL_MapRGB(screen->format, 0xFF, 0, 0xFF) );
     // Rendering box 2
     SDL_FillRect( screen, &b2, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF) );
     // Rendering text
     SDL_BlitSurface( txt_s, NULL, screen, &tmp );
}

void
clean_up()
{
    SDL_FreeSurface( screen );

    TTF_CloseFont( font_basic );
    TTF_Quit();
    SDL_Quit();
}

void
init_events()
{
    for(int i = 0; i < 323; i++){
        keys_held[i] = false;
    }
}

void
handle_events()
{
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_KEYDOWN ){
            keys_held[ event.key.keysym.sym ] = true;
        }else if( event.type == SDL_KEYUP ){
            keys_held[ event.key.keysym.sym ] = false;
        }else if( event.type == SDL_QUIT ){
            gameIsRunning = false;
        }
    }
}

int
key_pressed()
{
    if( event.type == SDL_KEYDOWN ){
        return event.key.keysym.sym;
    }

    return -1;
}

bool
key_held(int key)
{
    return keys_held[ key ];
}

SDL_Surface* 
load_image( std::string file, bool setColorKey, int r, int g, int b )
{
    SDL_Surface *src_img = NULL;
    SDL_Surface *dst_img = NULL;

    src_img = IMG_Load( file.c_str() );

    if( src_img != NULL ){
        if( setColorKey )
        SDL_SetColorKey( src_img, SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, r, g, b) );

        dst_img = SDL_DisplayFormat( src_img );
        SDL_FreeSurface( src_img );

        return dst_img;
        
    }else{
        return NULL;
    }
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 
getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void 
putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
