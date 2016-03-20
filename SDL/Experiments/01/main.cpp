/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Test 01
 *
 *        Version:  1.0
 *        Created:  09/10/2014 11:41:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

#include "SDL/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

bool gameIsRunning = true;

SDL_Surface *screen = NULL;
SDL_Event event;

SDL_Surface *box1 = NULL;
int box1_x, box1_xvel, box1_y, box1_yvel = 0;
int box1_xaccel, box1_yaccel = 0;
SDL_Surface *box1_back;
bool box1_jumping = false;

int box2_x, box2_xvel, box2_y, box2_yvel = 0;

// Box1 collision map
// ----+----
// |       |
// +       +
// |       |
// +---+---+
// P1  P2  P3

SDL_Surface *box2 = NULL;

//Funtion Prototypes-----------------------------------//
void init();
void load_resources();
SDL_Surface *load_image( char *filename );
void handle_events();
void move_objects();
void handle_collisions();
void update_screen();
void remove_objects();
bool solid_ground();
bool solid_side();
void cleanup();
//-----------------------------------------------------//

int main(int argc, char *argv[])
{
    init(); 
    load_resources();
    //init_objects();
    //std::cout << box1_x << std::endl;

    while( gameIsRunning ){
        handle_events();
        handle_collisions();
        move_objects();
        update_screen();

        SDL_Flip( screen );

        remove_objects();

        SDL_Delay(10);
    }

    cleanup();

    return 0;    
}

void init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        //fprintf(stderr, "Error initializing video.\n%s\n", SDL_GetError());
        std::cerr << "Error initializing video. " << SDL_GetError() << std::endl;
        exit(1);
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if( screen == NULL ){
        //fprintf(stderr, "Error setting video mode.\n%s\n", SDL_GetError());
        std::cerr << "Error setting video mode. " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_WM_SetCaption( "Demo Window", NULL );
}

void load_resources()
{
    box1 = load_image( "right_br1.bmp" );
    if( box1 == NULL ){
        std::cerr << "Error loading resource. " << std::endl;
        exit(1);
    }
    box2 = load_image( "right_gr1.bmp" );
    if( box2 == NULL ){
        std::cerr << "Error loading resource. " << std::endl;
        exit(1);
    }

    //Setting initial coords, this should be done in a seperate function

    box1_x = (SCREEN_WIDTH / 2) - (32 / 2);
    box1_y = (SCREEN_HEIGHT / 2) - (32 / 2);
    box2_x = (SCREEN_WIDTH / 2) - (32 / 2) + 32;
    box2_y = (SCREEN_HEIGHT / 2) - (32 / 2);

    box1_back = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, SCREEN_BPP, screen->format->Rmask, screen->format->Gmask, 
            screen->format->Bmask, screen->format->Amask);
}


SDL_Surface *load_image( char *filename )
{
    SDL_Surface *tmp;

    tmp = SDL_LoadBMP(filename );
    if( tmp == NULL ){
        std::cerr << "Couldn't load " << filename << "\n" << SDL_GetError() << std::endl;
        return NULL;
    }

    if( SDL_SetColorKey( tmp, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0xff, 0x00, 0xff) ) < 0 ){
        std::cerr << "Unable to set colorkey." << "\n" << SDL_GetError() << std::endl;
        return NULL;
    }

    return SDL_DisplayFormat(tmp);
}

void handle_events()
{
    while( SDL_PollEvent(&event) ){
        switch( event.type ){
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE ){
                    gameIsRunning = false; 
                }
                if( event.key.keysym.sym == SDLK_RIGHT ){
                    if( box1_jumping ){
                        box1_xvel = 2;
                    }else{
                        box1_xvel = 1; 
                    }
                }
                if( event.key.keysym.sym == SDLK_LEFT ){
                    if( box1_jumping ){
                        box1_xvel = -2;
                    }else{
                        box1_xvel = -1;
                    }
                }
                if( event.key.keysym.sym == SDLK_UP ){
                    if( !box1_jumping ){
                        box1_yvel   = -16;
                        box1_yaccel = 1;

                        box1_jumping = true;
                        std::cout << box1_yaccel << std::endl;
                    }
                }
                break;
            case SDL_KEYUP:
                if( event.key.keysym.sym == SDLK_RIGHT ){
                    box1_xvel = 0;
                }
                if( event.key.keysym.sym == SDLK_LEFT ){
                    box1_xvel = 0;
                }
                break;

            default:
                //std::cerr << "Not implemented event." << std::endl;
            ;
        }
    }
}

void handle_collisions()
{
    if( box1_jumping ){
        //if( box1_yvel < 0 ){
            //box1_yaccel += 1;
        //}else{
        //if( box1_yaccel < 0 ){
            //box1_yaccel += 1;
        //}else{
            //box1_yaccel += -1;
            //box1_yaccel = 0;
        //}
        //}
        //if(  ){}
        if( box1_yvel >= 30 ){
            //box1_yvel = 0;
            box1_yaccel = 0;
        }
    }

    /*
    if( box1_jumping && (box1_y > ((SCREEN_HEIGHT / 2) - (32 / 2))) ){
        box1_jumping = false;

        box1_yvel = 0;
        box1_yaccel = 0;
        box1_y = (SCREEN_HEIGHT / 2) - (32 / 2);
    }*/
    if( box1_jumping && solid_ground() ){
        box1_jumping = false;

        //box1_y = box1_y + box1_yvel + box1_yaccel;
        box1_yvel = 0;
        box1_yaccel = 0;
        //box1_y = (SCREEN_HEIGHT / 2) - (32 / 2);
    }else if( !box1_jumping && !solid_ground() ){
        
        box1_jumping = true;

        box1_yvel = 0;
        box1_yaccel = 1;
        //box1_xaccel = 0;
    }

    if( solid_side() ){
    
        box1_xaccel = 0;
        box1_xvel = 0;
    }


    //Jumping action
    //if( box1_jumping && box1_yvel == 0 ){
     //   box1_yaccel = -1;
    //}

    std::cout << box1_yvel << std::endl;
    std::cout << box1_yaccel << std::endl;
    std::cout << box1_y << std::endl;

    /*
    int xcol = box2_x - (box1_x + box1_xvel + box1_xaccel);
    xcol = (xcol < 0) ? -1 * xcol : xcol; 

    int ycol = box2_y - (box1_y + box1_yvel + box1_yaccel);
    ycol = (ycol < 0) ? -1 * ycol : ycol; 

    if( xcol < 32 && ycol < 32 ){
        box1_xvel = 0;
        box1_xaccel = 0;
        box1_yvel = 0;
        box1_yaccel = 0;

        box1_jumping = false;
    }*/
    

    /*
    if( ycol < 32 ){
        //box1_yvel = 0;
        //box1_yaccel = 0;
    }*/


    // Checking for screen boundaries
    // Right side
    if( box1_x + box1_xvel + box1_xaccel + 32 > SCREEN_WIDTH ){
        box1_xvel   = 0;
        box1_xaccel = 0;
    }
    // Left side
    if( box1_x + box1_xvel + box1_xaccel < 0 ){
        box1_xvel   = 0;
        box1_xaccel = 0;
    }
}

bool solid_ground()
{
    int tmpx, tmpy;

    // Checking for mid screen boundry
    if( box1_y + box1_yvel + box1_yaccel >= (SCREEN_HEIGHT / 2) - (32 / 2) ){
    //if( box1_y > ((SCREEN_HEIGHT / 2) - (32 / 2)) ){
        std::cout << "Im here" <<std::endl;
        return true;
    }

    // Checking for points P1, P2 and P3
    tmpx = box1_x + box1_xvel + box1_xaccel;
    tmpy = box1_y + box1_yvel + box1_yaccel;
    // Checking box1 bottom and box2 top
    //P1, P2, P3
    if( (tmpx >= box2_x && tmpx <= (box2_x + 32) && tmpy >= (box2_y - 32) && (tmpx + 16) >= box2_x && (tmpx + 16) <= (box2_x + 32)) || ((tmpx + 32) >= box2_x && (tmpx + 32) <= (box2_x + 32) && tmpy >= (box2_y - 32) && (tmpx + 16) >= box2_x && (tmpx + 16) <= (box2_x + 32))){
        std::cout << "Im hereXX" <<std::endl;
        return true; 
    }
    //P2
    /*
    if( (tmpx + 32) >= box2_x && (tmpx + 32) <= (box2_x + 32) && tmpy >= (box2_y - 32) ){
        std::cout << "Im hereYY" <<std::endl;
        return true; 
    }*/
    return false;
}

bool solid_side()
{
    int tmpx, tmpy, box1_midx, box1_midy, box2_midx, box2_midy;
    // Checking for points P4 and P6
    tmpx = box1_x + box1_xvel + box1_xaccel;
    tmpy = box1_y + box1_yvel + box1_yaccel;
    // Checking box1 left and box2 right
    // Checking line segments
    //Checking Direction
    // Right movement
    if( box1_xvel + box1_xaccel > 0 ){
        box1_midx = tmpx + 16;
        box1_midy = tmpy + 16;

        box2_midx = box2_x + 16;
        box2_midy = box2_y + 16;

        if( box2_midx - box1_midx < 32 && box2_midy - box1_midy < 32 ){
            return true; 
        }
    }
    //if( ((tmpx + 32) > box2_x && (tmpy - 8) > box2_y) && ((tmpx + 32) < box2_x && (tmpy - 24) < (box2_y + 32))){
    //if( ((tmpx + 32) >= box2_x && tmpy >= box2_y)){
    //if( ((tmpx + 32) >= box2_x &&  tmpy >= box2_y && (tmpy + 16) >= box2_x && (tmpx + 16) <= (box2_x + 32)) || ((tmpx + 32) >= box2_x && (tmpx + 32) <= (box2_x + 32) && tmpy >= (box2_y - 32) && (tmpx + 16) >= box2_x && (tmpx + 16) <= (box2_x + 32))){
        //std::cout << "Im hereYY" <<std::endl;
        //return true; 
    //}
    return false;
}

void move_objects()
{
    box1_xvel += box1_xaccel;
    box1_yvel += box1_yaccel;

    box1_x += box1_xvel;
    box1_y += box1_yvel;

    box2_x += box2_xvel;
    box2_y += box2_yvel;
}

void remove_objects()
{
    SDL_Rect tmp;

    tmp.x = box1_x;
    tmp.y = box1_y;
    tmp.w = 32;
    tmp.h = 32;

    // Blitting object
    SDL_BlitSurface(box1_back, NULL, screen, &tmp);
}

void update_screen()
{
    SDL_Rect tmp;

    //tmp.x = (SCREEN_WIDTH / 2) - (32 / 2);
    //tmp.y = (SCREEN_HEIGHT / 2) - (32 / 2);
    tmp.x = box1_x;
    tmp.y = box1_y;
    tmp.w = 32;
    tmp.h = 32;

    // Saving background
    SDL_BlitSurface(screen, &tmp, box1_back, NULL);
    // Blitting object
    SDL_BlitSurface(box1, NULL, screen, &tmp);
    //tmp.x = tmp.x + 32;
    tmp.x = box2_x;
    tmp.y = box2_y;
    //tmp.y = tmp.y + 32;
    SDL_BlitSurface(box2, NULL, screen, &tmp);
}

void cleanup()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(box1);
    SDL_FreeSurface(box2);
    SDL_FreeSurface(box1_back);

    SDL_Quit();
}
