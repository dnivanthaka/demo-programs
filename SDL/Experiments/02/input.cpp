#include "SDL/SDL.h"

#include "input.h"

static SDL_Event event;
bool keyevents[281];

void init_events()
{
    for(int i=0;i<282;i++){
        keyevents[ i ] = false;
    }
}

void handle_events_input()
{
    while( SDL_PollEvent(&event) ){
        switch( event.type ){
            case SDL_QUIT:
                //gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                keyevents[ event.key.keysym.sym ] = true;
                break;
            case SDL_KEYUP:
                keyevents[ event.key.keysym.sym ] = false;
                break;

            default:
                //std::cerr << "Not implemented event." << std::endl;
            ;
        }
    }
}

bool get_event_status()
{
    return false;
}
