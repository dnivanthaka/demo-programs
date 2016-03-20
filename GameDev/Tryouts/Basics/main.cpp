/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Tryout 01
 *
 *        Version:  1.0
 *        Created:  04/27/2013 09:13:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


const int SCREEN_WIDTH        = 640;
const int SCREEN_HEIGHT       = 320;
const int SCREEN_BPP          = 32;
const int GAME_FRAME_RATE_HZ  = 30;

SDL_Surface *screen       = NULL;
SDL_Surface *background   = NULL;
SDL_Surface *sprite_sheet = NULL;

SDL_Event event;

bool gameIsRunning = true;

struct entity{
    unsigned int x;
    unsigned int y;
    int vel_x;
    int vel_y;
    unsigned short width;
    unsigned short height;
    unsigned short max_frames;
    unsigned short current_frame;
    SDL_Rect *frames;
    SDL_Surface *background;
    bool is_visible;
    bool first_time;
};

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
apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool
init()
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return false;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
        return false;

    SDL_WM_SetCaption( "Tryout 01", NULL );

    return true;
}

bool
load_resources()
{
    sprite_sheet = load_image( "assets/bouncing.bmp" );

    if( sprite_sheet == NULL )
        return false;

    background = load_image( "assets/back1.jpg" );

    if( background == NULL )
        return false;
    return true;
}

void
clean_up()
{
    SDL_FreeSurface( sprite_sheet );
    SDL_FreeSurface( background );

    SDL_Quit();
}

int
main( int argc, char *argv[] )
{
    Uint32 last_updated;

    if( init() == false ){
        fprintf(stderr, "Unable to create window.\n%s", SDL_GetError());
        return -1;
    }

    if( load_resources() == false ){
        fprintf(stderr, "Unable to load resource(s).\n%s", SDL_GetError());
        return -1;
    }


    // creating the main character -----------------------------
    struct entity penguin;
    penguin.x              = 0;
    penguin.y              = 0;
    penguin.vel_x          = 0;
    penguin.vel_y          = 0;
    penguin.width          = 32;
    penguin.height         = 32;
    penguin.max_frames     = 8;
    penguin.current_frame  = 0;
    penguin.is_visible     = true;
    penguin.first_time     = true;
    penguin.frames = new SDL_Rect[8];
    for(int i=0;i<8;i++){
        penguin.frames[i].x = i * penguin.width;
        //penguin.frames[i].x = 32;
        penguin.frames[i].y = 0;
        penguin.frames[i].w = penguin.width;
        penguin.frames[i].h = penguin.height;
    }
    penguin.background = SDL_CreateRGBSurface(SDL_SWSURFACE, penguin.width, 
            penguin.height, SCREEN_BPP, screen->format->Rmask, 
            screen->format->Gmask, screen->format->Bmask, 
            screen->format->Amask );
    //----------------------------------------------------------


    last_updated = SDL_GetTicks();
    int i = 0;
    int j = 0;

    SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
    //apply_surface( 0, 0, background, screen );
    // Putting the penguin in mid screen
    penguin.x = SCREEN_WIDTH / 2  - penguin.width / 2;
    penguin.y = SCREEN_HEIGHT / 2 - penguin.height / 2;
    SDL_Rect tmp;
    
    while( gameIsRunning ){
        //SDL_Delay(1000);
        // Handling keyboard events ----------------------------
        while( SDL_PollEvent(&event) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            penguin.vel_x = -1;
                            break;
                        case SDLK_RIGHT:
                            penguin.vel_x = 1;
                            break;
                        case SDLK_UP:
                            penguin.vel_y = -1;
                            break;
                        case SDLK_DOWN:
                            penguin.vel_y = 1;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            if( penguin.vel_x < 0 )
                                penguin.vel_x = 0;
                            break;
                        case SDLK_RIGHT:
                            if( penguin.vel_x > 0 )
                                penguin.vel_x = 0;
                            break;
                        case SDLK_UP:
                            if(penguin.vel_y < 0){
                                penguin.vel_y = 0;
                            }
                            break;
                        case SDLK_DOWN:
                            if(penguin.vel_y > 0){
                                penguin.vel_y = 0;
                            }
                            break;
                        case SDLK_ESCAPE:
                            gameIsRunning = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    gameIsRunning = false;
                    break;
                default:
                    break;
            }
        }

        if( penguin.vel_x > 0 && penguin.x >= (SCREEN_WIDTH / 2  - penguin.width / 2) ){
            //penguin.x += penguin.vel_x;
            j += penguin.vel_x;
            //penguin.x = (SCREEN_WIDTH / 2  - penguin.width / 2);
        }else{
            //j += penguin.vel_x;
            penguin.x += penguin.vel_x;
        }
        penguin.y += penguin.vel_y;

        // ------------------------------------------------------
        i = i % 8;
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
        //SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //apply_surface( 100, 100, , screen, &penguin.frames[i] );


        // Drawing the background
        SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xff, 0x00, 0x00 ) );
        //SDL_Rect tmp;
        tmp.w = background->w - j;
        fprintf(stdout, "%d\n", tmp.w);
        tmp.h = background->h;
        tmp.x = j;
        tmp.y = 0;
        apply_surface( 0, 0, background, screen, &tmp );
        tmp.w = j;
        fprintf(stdout, "%d\n", tmp.w);
        tmp.h = background->h;
        tmp.x = 0;
        tmp.y = 0;
        apply_surface( screen->w - j, 0, background, screen, &tmp );
        //j++; 
        /*
        if( j >= screen->w ){
            j = 0;
        }
        */
        j = j % screen->w;
        // Restoring previous background
        /*
        if( !penguin.first_time ){
            //apply_surface( penguin.x, penguin.y, penguin.background, screen );
        }else{
            penguin.first_time = false;
        }*/
        // Saving new background --------------------------------
        //SDL_Rect tmp;
        tmp.w = penguin.width;
        tmp.h = penguin.height;
        tmp.x = penguin.x;
        tmp.y = penguin.y;
        apply_surface( 0, 0, screen, penguin.background, &tmp );
        //apply_surface( 0, 0, background, penguin.background, &tmp );
        //-------------------------------------------------------
        //apply_surface( 100, 100, sprite_sheet, screen, &penguin.frames[i] );
        apply_surface( penguin.x, penguin.y, sprite_sheet, screen, &penguin.frames[i] );
        //apply_surface( 0, 0, penguin.background, screen );
        SDL_Flip( screen );

        // Deleting the penguin
        //apply_surface( penguin.x, penguin.y, background, screen, &tmp );
        apply_surface( penguin.x, penguin.y, penguin.background, screen );
        //SDL_Rect tmp;
        //tmp.w = penguin.width;
        //tmp.h = penguin.height;
        //tmp.x = penguin.x;
        //tmp.y = penguin.y;
        //apply_surface( penguin.x, penguin.y, background, screen, &tmp );

        // Frame rate capping
        SDL_Delay(30);
        i++;
    }
    clean_up();

    return 0;
}
