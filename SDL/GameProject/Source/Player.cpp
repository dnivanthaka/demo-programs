#include"Player.h"

Player::Player()
{
    posX = 300;
    posY = 300;

    xVel = 300;
    yVel = 300;

    playerPos = {posX, posY, 100, 100};
    playerAnim = {posX, posY, 100, 100};
    player = SDL_LoadBMP("media/sprite.bmp");


    frame_x = 0;
    frame_y = 2;
    posDelta = 0;

}

void Player::forward(double delta)
{
    frame_x = 0;
    posX+=xVel*delta;

    posDelta+=10*delta;
    frame_x = (int)posDelta;

    if(frame_x > 3)
    {
        frame_x = 0;
        posDelta = 0;
    }
}

void Player::backward(double delta)
{
    frame_x = 4;
    posX-=xVel*delta;

    posDelta+=10*delta;
    frame_x = (int)posDelta + 4;

    if(frame_x <4 || frame_x > 7)
    {
        frame_x = 4;
        posDelta = 0;
    }
}


