#include"Seeker.h"

Seeker::Seeker()
{
    seeker = SDL_LoadBMP("media/seeker.bmp");

    monsterDead = false;
    deathCounted = false;


    posX = 0;
    posY = 510;

    xVel = 100;
    yVel = 300;

    monsterPos = {posX, posY, 100, 100};
    monsterAnim = {posX, posY, 100, 100};

    frame_x = 0;
    frame_y = 0;
    posDelta = 0;
    deathDeltaR = 0;
    deathDeltaL = 6;

    deadMonsterR = false;
    deadMonsterL = false;
}

void Seeker::resetMonster()
{
    seeker = SDL_LoadBMP("media/seeker.bmp");
    monsterDead = false;
    deathCounted = false;

    posX = 0;
    posY = 490;

    xVel = 100;
    yVel = 300;

    monsterPos = {posX, posY, 100, 100};
    monsterAnim = {posX, posY, 100, 100};

    frame_x = 0;
    frame_y = 0;
    posDelta = 0;
    deathDeltaR = -1;
    deathDeltaL = 6;

    deadMonsterR = false;
    deadMonsterL = false;
}

void Seeker::forward(double delta)
{
    frame_x = 0;
    frame_y = 1;

    posX+=xVel*delta;

    posDelta+=10*delta;
    frame_x = (int)posDelta;

    if(frame_x > 3)
    {
        frame_x = 0;
        frame_y = 1;
        posDelta = 0;
    }
}

void Seeker::backward(double delta)
{
    frame_x = 0;
    frame_y = 0;

    posX-=xVel*delta;//movement

    posDelta+=10*delta;//animation
    frame_x = (int)posDelta;

    if(frame_x > 3)
    {
        frame_y = 0;
        frame_x = 0;
        posDelta = 0;
    }
}

//while returning false, it hasnt finished animation
bool Seeker::killedMonsterR(double delta)
{
    frame_x = 0;
    frame_y = 2;

    deathDeltaR+=10*delta;//animation
    frame_x = (int)deathDeltaR;


    if(frame_x > 2)
    {
       return true;
    }
    return false;

}

//while returning false, it hasnt finished animation
bool Seeker::killedMonsterL(double delta)
{
    frame_x = 5;
    frame_y = 2;

    deathDeltaL-=10*delta;//animation
    frame_x = (int)deathDeltaL;

    if(frame_x < 3)
    {
       return true;
    }
    return false;

}











