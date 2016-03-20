#pragma once

#include<SDL/SDL.h>
#include<SDL/SDL_image.h>

#define W 100
#define H 100

class Player
{
public:
    Player();
    ~Player(){}

    double posX;
    double posY;

    int xVel;
    int yVel;
    int frame_x;
    int frame_y;
    double posDelta;

    SDL_Rect playerPos;
    SDL_Rect playerAnim;

    SDL_Surface * player;

public:

    void forward(double delta);
    void backward(double delta);
};


