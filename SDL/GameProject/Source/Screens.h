#pragma once
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string>


class Screen
{
public:
    Screen();
    bool loadFirst();
    SDL_Surface * screen;
    SDL_Surface * loadScreen;
    SDL_Surface * play;
    SDL_Surface * play2;
    SDL_Surface * howto;
    SDL_Surface * howto2;
    SDL_Surface * guide;

    void clearSurface();

    SDL_Rect playPos;
    SDL_Rect playPos2;
    SDL_Rect howtoPos;
    SDL_Rect howto2Pos;
    SDL_Rect guidePos;

    SDL_Event event;
    SDL_Event event1;
    int x;
    int y;

private:
    bool running;
    bool clickFlag;
    bool clickFlag2;
    bool gameGuide;
    void runGuide();

};


class StringInput
{
    private:
    //The storage string
    std::string str;

    //The text surface
    SDL_Surface *text;

    public:
    //Initializes variables
    StringInput();

    //Does clean up
    ~StringInput();

    //Handles input
    void handle_input();

    //Shows the message on screen
    void show_centered();
};








