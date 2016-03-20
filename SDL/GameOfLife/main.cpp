/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Game of Life Demo
 *
 *        Version:  1.0
 *        Created:  27/11/2013
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

const int OBJ_WIDTH = 20;
const int OBJ_HEIGHT = 20;

SDL_Surface *screen = NULL;
//SDL_Surface *entity = NULL;
//SDL_Surface *entity2 = NULL;
//SDL_Joystick *stick = NULL;

bool *buttonStates;

SDL_Event event;

bool gameIsRunning = true;

// ------------- Function Prototypes ----------- //
void init();
void shutdown();
void load_files();
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
// -------------------------------------------- //

class Ball
{
    private:
        int xPos, yPos;

        int xVel, yVel;
    public:
        Ball();
        ~Ball();

        void handle_input();
        void move();
        void show();
        void hide();
};

Ball::Ball()
{
    xVel, yVel = 0;

    xPos = SCREEN_WIDTH / 2;
    yPos = SCREEN_HEIGHT / 2;
};

Ball::~Ball(){};

void Ball::handle_input()
{
    if(event.type == SDL_JOYAXISMOTION){
        if( event.jaxis.which == 0 ){
            if( event.jaxis.axis == 0 ){
                if( (event.jaxis.value > -8000) && (event.jaxis.value < 8000) ){
                    xVel = 0;
                }else{
                    if( event.jaxis.value < 0 ){
                        xVel = -OBJ_WIDTH / 2;
                    }else{
                        xVel = OBJ_WIDTH / 2;
                    }
                }
            }else if( event.jaxis.axis == 1 ){
                if( (event.jaxis.value > -8000) && (event.jaxis.value < 8000) ){
                    yVel = 0;
                }else{
                    if( event.jaxis.value < 0 ){
                        yVel = -OBJ_HEIGHT / 2;
                    }else{
                        yVel = OBJ_HEIGHT / 2;
                    }
                }
            }
        }
    }
};

void Ball::move()
{
    xPos += xVel;

    if( (xPos < 0) || (xPos + OBJ_WIDTH > SCREEN_WIDTH) ){
        xPos -= xVel;
    }

    yPos += yVel;

    if( (yPos < 0) || (yPos + OBJ_HEIGHT > SCREEN_HEIGHT) ){
        yPos -= yVel;
    }
};

void Ball::show()
{
    //apply_surface( xPos, yPos, entity, screen );
};

void Ball::hide(){};

void 
init()
{
    //int count_joy = 0;

    //if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1 ){
    if( SDL_Init(SDL_INIT_VIDEO) == -1 ){
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Setting up screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        std::cerr << "Couldn't Setup Screen: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_WM_SetCaption("Game of life Demo", NULL);

    SDL_ShowCursor( 0 );

    //count_joy = SDL_NumJoysticks();

    //std::cout << "Joysticks/GamePads detected: " << count_joy << std::endl;

    //for(int i = 0; i < count_joy; i++){
        //std::cout << "(" << (i + 1) << ")" << " - " << SDL_JoystickName(i) << std::endl;
    //}
    
    //if( count_joy > 0 ){
        //std::cout << "Using Joystick/Gamepad 1 as the default input device" << std::endl;
        //stick = SDL_JoystickOpen(0);

        //if( stick == NULL ){
            //std::cerr << "Couldn't Setup Joystick/Gamepad: " << SDL_GetError() << std::endl;
            //exit(1);
        //}

        //std::cout << "======= Joystick/Gamepad Properties ========" << std::endl;
        //std::cout << "No: of Axes:    " <<SDL_JoystickNumAxes(stick) << std::endl;
        //std::cout << "No: of Balls:   " <<SDL_JoystickNumBalls(stick) << std::endl;
        //std::cout << "No: of Hats:    " <<SDL_JoystickNumHats(stick) << std::endl;
        //std::cout << "No: of Buttons: " <<SDL_JoystickNumButtons(stick) << std::endl;
        //std::cout << "============================================" << std::endl;

        //Initializing button states
        //buttonStates = new bool[ SDL_JoystickNumButtons(stick) ];
        //for(int i=0; i < SDL_JoystickNumButtons(stick); i++){
            //buttonStates[i] = false;
        //}

    //}else{
        //std::cout << "No Joysticks/Gamepads Detected" << std::endl;
    //}
}

void
draw_buttons_panel()
{
    /*
    int padding = 5;
    int btn_count = SDL_JoystickNumButtons(stick);

    for(int i=0; i < btn_count;i++){        
        if( !buttonStates[i] ){
            apply_surface( (i * (OBJ_WIDTH + padding)) + padding, 5, entity, screen );
        }else{
            apply_surface( (i * (OBJ_WIDTH + padding)) + padding, 5, entity2, screen );
        }
    }
    */
}

SDL_Surface 
*load_image( std::string filename )
{
    SDL_Surface *loadedImage = NULL;

    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        if( optimizedImage != NULL ){
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
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

void
shutdown()
{
    //SDL_FreeSurface( screen );
    //SDL_JoystickClose( stick );

    //delete buttonStates;

    SDL_Quit();
}

void
load_files()
{
    //entity = load_image("ball.bmp");

    //if( entity == NULL ){
        //std::cerr << "Couldn't load image: " << SDL_GetError() << std::endl;
        //exit(1);
    //}

    //entity2 = load_image("ball2.bmp");

    //if( entity2 == NULL ){
        //std::cerr << "Couldn't load image: " << SDL_GetError() << std::endl;
        //exit(1);
    //}
}

int
main(int argc, char *argv[])
{
    //Ball obj;

    init();
    load_files();

    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x0, 0x0, 0x0 ) );

    while( gameIsRunning ){
        
        while( SDL_PollEvent( &event ) ){
            
            //obj.handle_input();
            /*
            if(event.type == SDL_JOYBUTTONDOWN){
                if( event.jaxis.which == 0 ){
                    buttonStates[ event.jbutton.button - 1 ] = true;
                }
            }else if( event.type == SDL_JOYBUTTONUP ){
                if( event.jaxis.which == 0 ){
                    buttonStates[ event.jbutton.button - 1 ] = false;
                }
            }
            */
    

            if( event.type == SDL_QUIT ){
                gameIsRunning = false;
            }
        }

        //obj.move();

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x0, 0x0, 0x0 ) );

        //obj.show();
        //draw_buttons_panel();

        SDL_Flip( screen );

        SDL_Delay(10);
    }

    shutdown();

    return 0;
}
