#pragma once
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>

class Ghost
{
public:
    Ghost();
    ~Ghost(){}

    int frame_x;
    int frame_y;
    int Lframe_x;
    int Lframe_y;

    int xVel;
    int yVel;

    bool monsterDead;
    bool deadMonsterR;
    bool deadMonsterL;
    bool deathCounted;
    bool Hstate;
    bool attacking;
    bool isLightning;

    double posX;
    double posY;
    double posDelta;
    double deathDeltaR;
    double deathDeltaL;
    double attackDelta;
    double lightningDelta;

    SDL_Rect monsterPos;
    SDL_Rect monsterAnim;
    SDL_Rect lightningPos;
    SDL_Rect lightningAnim;

    SDL_Surface * ghost;
    SDL_Surface * lightning;

    void resetMonster();

public:

    void forward(double delta);//
    void backward(double delta);//
    bool killedMonsterR(double delta);//
    bool killedMonsterL(double delta);//
    bool attack(double delta);
    bool showLightning(double delta);
};



