#include"Environment.h"

FloatingObj::FloatingObj()
{
}
//responsible for the behavior of oscillating islands
void FloatingObj::oscillate(double delta, int limit1, int limit2, int speed)
{
    //if the x coordinate exceeds the higher limit
    //change the state
    if(posX > limit2)
    {
        Hstate = 1;
    }
    //if the x coordinate becomes lower than the
    //lower limit, change the state
    if(posX < limit1)
    {
        Hstate = 2;
    }
    //if state is 1, go backward at the passed in velocity
    if(Hstate == 1)
    {
        pos = {posX-=speed*delta, posY, 150, 80};
    }
    //if state is 2, go forward at the passed in velocity
    if(Hstate == 2)
    {
        pos = {posX+=speed*delta, posY, 150, 80};
    }

}

//responsible for the behavior of the elevating island
void FloatingObj::elevate(double delta)
{
    //if the elevating island goes higher than 300
    //set the state to 1
    if(posY < 300)
    {
        Vstate = 1;
    }
    //if the elevating island goes higher than 520
    //set the state to 0
    if(posY > 520)
    {
        Vstate = 0;
    }
    //if state is 0, elevate the island at 300 pps
    if(Vstate == 0)
    {
        pos = {posX, posY-=300*delta, 150, 80};
    }
    //if state is 1 lower island at 300 pps
    if(Vstate == 1)
    {
        pos = {posX, posY+=300*delta, 150, 80};
    }
}
//handles the interaction between the player and oscillating islands
bool FloatingObj::interactH(double delta, double& posX, double& posY, SDL_Rect playerPos, int speed)
{
    //checks if player is on top of island
    if(playerPos.x + playerPos.w - 30 > pos.x
        && playerPos.x + 30 < pos.x + pos.w
        && playerPos.y + playerPos.h -5 > pos.y
        && playerPos.y + playerPos.h < pos.y + 20)
    {
        //oppose force of gravity
        posY-=405*delta;
        //set the speed at which the player moves
        //on top of the island
        if(Hstate == 2)
        {
            posX += speed * (delta);
        }
        if(Hstate == 1)
        {
            posX -= speed * (delta);
        }
        //return true if the player is on top
        return true;
    }

    //checks if player is below island
    if(playerPos.x + playerPos.w - 30> pos.x
        && playerPos.x + 30 < pos.x + pos.w
        && (playerPos.y < pos.y + pos.h-60)
        && (playerPos.y > pos.y + pos.h - 70))
    {
        posY+= 1200*delta;//counteract jump velocity
        return false;
    }

    //coming from LEFT
    if((playerPos.x + playerPos.w - 30) > pos.x
        && playerPos.x + playerPos.w < pos.x + 40
        &&playerPos.y<pos.y + pos.h
        &&playerPos.y + playerPos.h > pos.y)
    {
        posX -= speed * (delta);
        return false;
    }

    //coming from right
    if(playerPos.x + 30 < pos.x + pos.w
        && playerPos.x > pos.x + pos.w - 40
        &&playerPos.y<pos.y + pos.h
        &&playerPos.y + playerPos.h > pos.y)
    {
        posX += speed * (delta);
        return false;
    }
    return false;
}

//handles the interaction between the player and the elevating island
bool FloatingObj::interactV(double delta, double& posX, double& posY, SDL_Rect playerPos)
{
    //checks if player is on top of island
    if(playerPos.x + playerPos.w - 30 > pos.x
        && playerPos.x + 30 < pos.x + pos.w
        && playerPos.y + playerPos.h -5 > pos.y
        && playerPos.y + playerPos.h < pos.y + 20)
        {
            posY -= 700 * delta;
            return true;
        }
        return false;
}

//sets up the positions of all objects in the environment
Environment::Environment()
{
    groundPos = {0, 600, 1250, 200};
    groundPos1 = {1850, 600, 3450, 200};
    groundPos2 = {7000, 600, 4000, 200};
    stairs1Pos = {930, 500, 100, 100};
    stairs2Pos = {1030, 400, 100, 200};
    stairs3Pos = {1130, 300, 100, 300};
    stairs4Pos = {5000, 500, 100, 100};
    stairs5Pos = {5100, 400, 100, 200};
    stairs6Pos = {5200, 300, 100, 300};
    pillarPos = {0, 300, 100, 300};

    spikesPos = {1250, 600, 600, 30};
    spikes1Pos = {5300, 600, 1700, 30};
    wallPos1 = {2300, 300, 700, 300};

    platform1Pos = {4000, 400, 200, 25};
    platform2Pos = {4200, 200, 200, 25};
    platform3Pos = {5800, 100, 400, 25};

    platform4Pos = {7600, 500, 200, 25};
    platform5Pos = {7900, 350, 200, 25};
    platform6Pos = {7600, 200, 200, 25};
    platform7Pos = {7900, 100, 200, 25};

    wall2Pos = {8300, 100, 300, 500};
    wall3Pos = {8600, 500, 1000, 100};
    wall4Pos = {8700, 200, 800, 200};
    wall5Pos = {9400, -100, 100, 300};

    finishRect = {10300, 300, 100, 300};


    island1.posX = 1150;
    island1.posY = 300;
    island1.pos = {island1.posX, island1.posY, 150, 80};
    island1.Hstate = 2;

    island2.posX = 2150;
    island2.posY = 520;
    island2.pos = {island2.posX, island2.posY, 150, 80};
    island2.Vstate = 0;

    island3.posX = 5300;
    island3.posY = 300;
    island3.pos = {island3.posX, island3.posY, 150, 80};
    island1.Hstate = 2;

    island4.posX = 6300;
    island4.posY = 500;
    island4.pos = {island4.posX, island4.posY, 150, 80};
    island4.Hstate = 2;


}




