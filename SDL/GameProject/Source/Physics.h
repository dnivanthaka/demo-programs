#pragma once
#include<list>
#include<SDL/SDL.h>

using namespace std;


class Physics
{
public:
    Physics();
    //checks for collisions between the player and the inanimate objects in the world
    void isCollision(double delta, SDL_Rect& playerPos, double& posX, double& posY);
    //registers a given rectangle into a list ADT to check against player coords
    void phyRegister(SDL_Rect& rect);
    //applies gravity affect to player
    void gravity(double delta, double& playerY);
    //generic collision detection between two players
    bool Collision(SDL_Rect *a, SDL_Rect *b);

    bool toRight;
    bool toLeft;
    bool onTop;
    bool below;

private:
    //database to hold inanimate objects within the world
    list<SDL_Rect> database;
    list<SDL_Rect>::iterator itr;
};


