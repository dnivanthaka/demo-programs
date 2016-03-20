#include"Ghost.h"

Ghost::Ghost()
{
    ghost = SDL_LoadBMP("media/ghost.bmp");
    lightning = SDL_LoadBMP("media/light.bmp");
    monsterDead = false;
    deathCounted = false;

    posX = 4450;
    posY = 490;

    xVel = 200;
    yVel = 300;

    monsterPos = {posX, posY, 122, 130};//
    monsterAnim = {posX, posY, 122, 130};//
    lightningPos = {4300, 100, 80, 240};
    lightningAnim = {0, 0, 80, 240};
    //lightningAnim = {Lframe_x*80, Lframe_y*240, 80, 240};

    frame_x = 0;
    frame_y = 0;
    Lframe_x = 0;
    Lframe_y = 0;

    posDelta = 0;
    deathDeltaR = -1;
    deathDeltaL = 6;
    attackDelta = 0;

    deadMonsterR = false;
    deadMonsterL = false;
    Hstate = false;
    attacking = false;
    isLightning = false;
}

void Ghost::resetMonster()
{
    ghost = SDL_LoadBMP("media/ghost.bmp");
    monsterDead = false;
    deathCounted = false;

    posX = 4450;
    posY = 490;

    xVel = 200;
    yVel = 300;

    monsterPos = {posX, posY, 122, 130};
    monsterAnim = {posX, posY, 122, 130};
    lightningPos = {4420, 0, 80, 240};
    lightningAnim = {Lframe_x*80, Lframe_y*Lframe_y, 80, 240};

    frame_x = 0;
    frame_y = 0;
    posDelta = 0;
    deathDeltaR = 0;
    deathDeltaL = 6;
    attackDelta = 0;

    deadMonsterR = false;
    deadMonsterL = false;
    Hstate = false;
    attacking = false;
    isLightning = true;
}

void Ghost::forward(double delta)
{
    frame_x = 0;
    frame_y = 1;

    posX+=xVel*delta;

    posDelta+=10*delta;
    frame_x = (int)posDelta;

    if(frame_x > 5)
    {
        frame_x = 0;
        frame_y = 1;
        posDelta = 0;
    }
}

void Ghost::backward(double delta)
{
    frame_x = 0;
    frame_y = 0;

    posX-=xVel*delta;//movement

    posDelta+=10*delta;//animation
    frame_x = (int)posDelta;

    if(frame_x > 5)
    {
        frame_y = 0;
        frame_x = 0;
        posDelta = 0;
    }
}

//while returning false, it hasnt finished animation
bool Ghost::killedMonsterR(double delta)
{
    frame_x = 0;
    frame_y = 2;

    deathDeltaR+=10*delta;//animation
    frame_x = (int)deathDeltaR;

    if(frame_x > 3)
    {
       return true;
    }
    return false;

}

//while returning false, it hasnt finished animation
bool Ghost::killedMonsterL(double delta)
{
    frame_x = 7;
    frame_y = 2;

    deathDeltaL-=10*delta;//animation
    frame_x = (int)deathDeltaL;

    if(frame_x < 4)
    {
       return true;
    }
    return false;

}

bool Ghost::attack(double delta)
{
    frame_y = 3;

    attackDelta+=8*delta;//animation
    frame_x = (int)attackDelta;

    if(frame_x > 5)
    {
        attackDelta = 0;
        return true;
    }
    return false;

}

bool Ghost::showLightning(double delta)
{
    lightningDelta+=10*delta;
    Lframe_x = (int)lightningDelta;

    if(Lframe_x > 7)
    {
        lightningDelta = 0;
        return true;
    }

    return false;
}









