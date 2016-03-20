#pragma once
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>

class Seeker
{
public:
    Seeker();
    ~Seeker(){}

    int frame_x;
    int frame_y;
    int xVel;
    int yVel;

    bool monsterDead;
    bool deadMonsterR;
    bool deadMonsterL;
    bool deathCounted;

    double posX;
    double posY;
    double posDelta;
    double deathDeltaR;
    double deathDeltaL;


    SDL_Rect monsterPos;
    SDL_Rect monsterAnim;

    SDL_Surface * seeker;

    void resetMonster();

public:

    void forward(double delta);
    void backward(double delta);
    bool killedMonsterR(double delta);
    bool killedMonsterL(double delta);
};



