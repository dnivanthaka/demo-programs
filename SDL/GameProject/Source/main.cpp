#include"SDL/SDL.h"
#include"Application.h"

//creates an object to handle the application behavior
Application appHandler;

int main(int argc, char * args[])
{
    //initialize the application
    appHandler.Initialize();

    //run the game loop
    appHandler.gameLoop();

    //clear the surface
    appHandler.clearSurface();

    SDL_Quit();
    TTF_Quit();
    return 0;

}

