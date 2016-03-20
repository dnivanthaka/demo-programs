#pragma once
#include<SDL/SDL.h>

class FloatingObj
{
public:
    FloatingObj();
    //responsible for the behavior of oscillating islands
    void oscillate(double delta, int limit1, int limit2, int speed);
    //responsible for the behavior of the elevating island
    void elevate(double delta);
    //handles the interaction between the player and oscillating islands
    bool interactH(double delta, double& posX, double& posY, SDL_Rect playerPos, int speed);
    //handles the interaction between the player and the elevating island
    bool interactV(double delta, double& posX, double& posY, SDL_Rect playerPos);
    //represents the respective x and y coordinates of the islands
    double posX;
    double posY;
    //Hstate determines whether the island needs to be going
    //forward or backward horizontally
    int Hstate;
    //Vstate determines whether the island needs to be going
    //up or down
    int Vstate;
    //the rectangle position associated with a floating object
    SDL_Rect pos;
};

class Environment
{
public:
    Environment();

    SDL_Rect groundPos;
    SDL_Rect groundPos1;
    SDL_Rect groundPos2;
    SDL_Rect stairs1Pos;
    SDL_Rect stairs2Pos;
    SDL_Rect stairs3Pos;
    SDL_Rect stairs4Pos;
    SDL_Rect stairs5Pos;
    SDL_Rect stairs6Pos;
    SDL_Rect pillarPos;
    SDL_Rect wallPos1;
    SDL_Rect platform1Pos;
    SDL_Rect platform2Pos;
    SDL_Rect platform3Pos;
    SDL_Rect platform4Pos;
    SDL_Rect platform5Pos;
    SDL_Rect platform6Pos;
    SDL_Rect platform7Pos;

    SDL_Rect spikesPos;
    SDL_Rect spikes1Pos;

    SDL_Rect wall2Pos;
    SDL_Rect wall3Pos;
    SDL_Rect wall4Pos;
    SDL_Rect wall5Pos;

    SDL_Rect finishRect;

    FloatingObj island1;
    FloatingObj island2;
    FloatingObj island3;
    FloatingObj island4;
};




