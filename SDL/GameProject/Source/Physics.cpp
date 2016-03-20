#include"Physics.h"


Physics::Physics()
{
    toLeft = false;
    toRight = false;
    onTop = false;
    below = false;
}

//registers a given rectangle into a list ADT to check against player coords
void Physics::phyRegister(SDL_Rect& rect)
{
    database.push_back(rect);
}

//gravity
void Physics::gravity(double delta, double& playerY)
{
    playerY += 400 * (delta);//gravity
}

//used for detection of non moving objects
void Physics::isCollision(double delta, SDL_Rect& playerPos, double& posX, double& posY)
{
    toLeft = false;
    toRight = false;
    onTop = false;
    below = false;

    //for each object within the database
    for(itr = database.begin(); itr!=database.end();itr++)
    {

        //coming from LEFT
        if((playerPos.x + playerPos.w - 30) > (*itr).x/*if front of player is greater than the front of the box*/
           && playerPos.x + playerPos.w < (*itr).x + 40/*if front of player is less than the front of the box + 10 px*/
           &&playerPos.y<(*itr).y + (*itr).h/*if top of player is higher than bottom of box*/
           &&playerPos.y + playerPos.h > (*itr).y/*if bottom of player if lower than top of box*/)
        {
            //apply equal and opposite force (thanks Newton)
            posX -= 300 * (delta);
            toLeft = true;
        }

        //coming from right
        if(playerPos.x + 30 < (*itr).x + (*itr).w//if front of player is less than back of the box
           && playerPos.x > (*itr).x + (*itr).w - 40//if front of player is greater than back of the box - 10 px
           &&playerPos.y<(*itr).y + (*itr).h//if top of player is higher than bottom of box
           &&playerPos.y + playerPos.h > (*itr).y)//if bottom of player is lower than top of the box
        {
            //apply equal and opposite force
            posX += 300 * (delta);
            toRight = true;
        }

        //checks if player is on top of something
        if(playerPos.x + playerPos.w - 30 > (*itr).x
           && playerPos.x + 30 < (*itr).x + (*itr).w
           && playerPos.y + playerPos.h -5 > (*itr).y
           && playerPos.y + playerPos.h < (*itr).y + 20)
        {
            posY -= 400 * (delta);
            onTop = true;
        }

        //checks if player is below something
        if(playerPos.x + playerPos.w - 30> (*itr).x
           && playerPos.x + 30 < (*itr).x + (*itr).w
           && (playerPos.y < (*itr).y + (*itr).h)
           && (playerPos.y > (*itr).y + (*itr).h - 10))
        {
            below = true;
            posY += 800 * (delta);
        }

    }

}

//generic collision detection between two players
bool Physics::Collision(SDL_Rect *a, SDL_Rect *b)
{
     if( a->x < b->x + b->w &&
         a->x + a->w > b->x &&
         a->y < b->y + b->h &&
         a->y + a->h > b->y )
     {
         return true;
     }
     else
     return false;
}



