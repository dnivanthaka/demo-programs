#include"Application.h"

//defines application variables
Application::Application()
{
    gameRunning = true;
    dead = false;
    keys = {NULL};
    frame = 0;
    font = TTF_OpenFont("georgia.ttf", 18);
    lastKey = 2;

    cameraPos = {player.posX-500,0, 1100, 700};
    checker = 0;
    freeze = 0;
    animDelta = 0;
    shotFlagR = false;
    shotFlagL = false;
    thing = false;
    finished = false;
    arrows = 0;
    points = 0;
    pointTracker = true;

    color = {255, 255, 255};
    wraithFactory[0].posX = 900;
    wraithFactory[1].posX = 3000;
    wraithFactory[1].posY = 180;
    mummyFactory[0].posX = 6130;
    mummyFactory[0].posY = 0;
    mummyFactory[1].posX = 8560;
    mummyFactory[1].posY = 410;
    seeker.posX = 9500;
    seeker.posY = 400;
    ghost.posX = 4830;
    ghost.posY = 100;
    ghost.lightningPos.x = 4450;


}

//initializes the supplemental methods of the application
void Application::Initialize()
{
    screen = SDL_SetVideoMode(1000, 700, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    screens.loadFirst();

    startClocks();
    loadSurfaces();
    loadMap();
    setKey();
}

//defines the file names for the SDL_Surfaces
void Application::loadSurfaces()
{
    camera = SDL_LoadBMP("media/backdrop.bmp");
    background = SDL_LoadBMP("media/background5.bmp");

    ground = addItem("media/ground.bmp", environment.groundPos);
    ground1 = addItem("media/ground4.bmp", environment.groundPos1);
    ground2 = addItem("media/ground6.bmp", environment.groundPos2);
    stairs1 = addItem("media/bricks.bmp", environment.stairs1Pos);
    stairs2 = addItem("media/bricks2.bmp", environment.stairs2Pos);
    stairs3 = addItem("media/stairs3.bmp", environment.stairs3Pos);
    pillar = addItem("media/pillar.bmp", environment.pillarPos);
    wall1 = addItem("media/wall1.bmp", environment.wallPos1);
    wall2 = addItem("media/wall3.bmp", environment.wall2Pos);
    wall3 = addItem("media/wall4.bmp", environment.wall3Pos);
    wall4 = addItem("media/wall5.bmp", environment.wall4Pos);
    wall5 = addItem("media/stairs3.bmp", environment.wall5Pos);
    platform1 = addItem("media/platform1.bmp", environment.platform1Pos);
    platform2 = addItem("media/platform1.bmp", environment.platform2Pos);
    platform3 = addItem("media/platform2.bmp", environment.platform3Pos);
    platform4 = addItem("media/platform1.bmp", environment.platform4Pos);
    platform5 = addItem("media/platform1.bmp", environment.platform5Pos);
    platform6 = addItem("media/platform1.bmp", environment.platform6Pos);
    platform7 = addItem("media/platform1.bmp", environment.platform7Pos);

    stairs4 = addItem("media/bricks.bmp", environment.stairs4Pos);
    stairs5 = addItem("media/bricks2.bmp", environment.stairs5Pos);
    stairs6 = addItem("media/stairs3.bmp", environment.stairs6Pos);

    island1 = SDL_LoadBMP("media/fisland1.bmp");
    island2 = SDL_LoadBMP("media/fisland1.bmp");
    island3 = SDL_LoadBMP("media/fisland1.bmp");
    island4 = SDL_LoadBMP("media/fisland1.bmp");
    spikes = SDL_LoadBMP("media/spikes1.bmp");
    spikes1 = SDL_LoadBMP("media/spikes2.bmp");

    finish = SDL_LoadBMP("media/finish.bmp");

    for(int i = 0; i<=99; i++)//load arrow surfaces
    {
        quiver[i].arrowR = SDL_LoadBMP("media/arrowR.bmp");
        quiver[i].arrowL = SDL_LoadBMP("media/arrowL.bmp");
    }

}

//loads the map ADT with the filename and associated rectangular position,
//this allows for all inanimate objects to be confined to one easily manageable
//object
void Application::loadMap()
{
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(ground, environment.groundPos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(ground1, environment.groundPos1));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(ground2, environment.groundPos2));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(stairs2, environment.stairs2Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(stairs3, environment.stairs3Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(stairs4, environment.stairs4Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(stairs5, environment.stairs5Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(stairs6, environment.stairs6Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(pillar, environment.pillarPos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(wall1, environment.wallPos1));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(wall2, environment.wall2Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(wall3, environment.wall3Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(wall4, environment.wall4Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(wall5, environment.wall5Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform1, environment.platform1Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform2, environment.platform2Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform3, environment.platform3Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(spikes, environment.spikesPos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(spikes1, environment.spikes1Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform4, environment.platform4Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform5, environment.platform5Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform6, environment.platform6Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(platform7, environment.platform7Pos));
    blitMap.insert(pair<SDL_Surface*, SDL_Rect>(finish, environment.finishRect));
}

//the game loop, calls all of the supplemental
//methods of the application to continuously
//update and maintain the functionality of the
//game
void Application::gameLoop()
{
    while(gameRunning)
    {
        handleEnvironment();

        updateMonsters();

        handleEvents();

        updatePlayer();

        handleArrows();

        handlePhysics();

        delta.start();

        checkBoundaries();
        updateFPS();
        updatePoints();
        drawSurface();

        if(finished)
        {
            showFinal();
        }

    }
}

//method to take a filename and an associated rectangular position
//and register it within the physics database to handle collision detection
//between the player and inanimate objects
SDL_Surface* Application::addItem(const char * file, SDL_Rect& region)
{
    SDL_Surface * temp;
    SDL_Surface * formatted;
    temp = IMG_Load(file);
    formatted = SDL_DisplayFormat(temp);
    temp = NULL;

    phy.phyRegister(region);

    return formatted;
}

//initializes the applications various clocks
void Application::startClocks()
{
    delta.start();
    update.start();
    fps.start();
    cooldown.start();
    deathClock.start();
    global.start();
}

void Application::drawSurface()
{
    SDL_BlitSurface(background, &cameraPos, screen, NULL);
    SDL_BlitSurface(camera, NULL, background, &cameraPos);
    //special case:  object requires persistent blitting
    SDL_BlitSurface(stairs1, NULL, background, &environment.stairs1Pos);

    //iterates through the map ADT of inanimate rectangles and surfaces, and will only blit the surfaces that appear on the
    //screen in relation to the player
    for(bliterator = blitMap.begin(); bliterator!=blitMap.end(); bliterator++)
    {
        if(bliterator->second.x < player.posX + player.playerPos.w + 600 && bliterator->second.x + bliterator->second.w > player.posX - 600)
        {
           SDL_BlitSurface(bliterator->first, NULL, background, &(bliterator->second));
        }
    }

    SDL_BlitSurface(player.player, &player.playerAnim, background, &player.playerPos);

    //brute force blit logic for moving objects
    if(environment.island1.pos.x < player.posX + player.playerPos.w + 600 && environment.island1.pos.x + environment.island1.pos.w > player.posX - 600)
    {
        SDL_BlitSurface(island1, NULL, background, &environment.island1.pos);
    }
    if(environment.island2.pos.x < player.posX + player.playerPos.w + 600 && environment.island2.pos.x + environment.island2.pos.w > player.posX - 600)
    {
        SDL_BlitSurface(island2, NULL, background, &environment.island2.pos);
    }
    if(environment.island3.pos.x < player.posX + player.playerPos.w + 600 && environment.island3.pos.x + environment.island3.pos.w > player.posX - 600)
    {
        SDL_BlitSurface(island3, NULL, background, &environment.island3.pos);
    }
    if(environment.island4.pos.x < player.posX + player.playerPos.w + 600 && environment.island4.pos.x + environment.island4.pos.w > player.posX - 600)
    {
        SDL_BlitSurface(island4, NULL, background, &environment.island4.pos);
    }

    //if wraith is still alive, blit it
    for(int i = 0; i<2; i++)
    {
        if(!wraithFactory[i].monsterDead)
        {
            SDL_BlitSurface(wraithFactory[i].wraith, &wraithFactory[i].monsterAnim, background, &wraithFactory[i].monsterPos);
        }
    }
    //if mummy is still alive, blit it
    for(int i = 0; i<2; i++)
    {
        if(!mummyFactory[i].monsterDead)
        {
            SDL_BlitSurface(mummyFactory[i].mummy, &mummyFactory[i].monsterAnim, background, &mummyFactory[i].monsterPos);
        }
    }
    //if seeker is still alive, blit it
    if(!seeker.monsterDead)
    {
        SDL_BlitSurface(seeker.seeker, &seeker.monsterAnim, background, &seeker.monsterPos);
    }
    //if ghost is still alive, blit it
    if(!ghost.monsterDead)
    {
        SDL_BlitSurface(ghost.ghost, &ghost.monsterAnim, background, &ghost.monsterPos);
    }
    //if ghost is still alive, blit lightning
    if(ghost.isLightning)
    {
        SDL_BlitSurface(ghost.lightning, &ghost.lightningAnim, background, &ghost.lightningPos);
    }

    SDL_Flip(screen);
}

void Application::updateFPS()
{
    frame++;//tracks frames

    if(update.get_ticks() > 1000)
    {
        //The frame rate as a string
        std::stringstream caption;

        //Calculate the frames per second and create the string
        caption << "Undead Desert"<<setw(100)<<"Time: "<<global.get_ticks()/1000<<setw(20)<<"Points: "<<points<<"  "<<player.posX
        <<setw(50)<<right<<"FPS: " << frame / (fps.get_ticks()/1000) << "  "<< "Arrows: "<< 99 - arrows;

        //Reset the caption
        SDL_WM_SetCaption( caption.str().c_str(), NULL );

        //Restart the update timer
        update.start();
    }
}

//sets the color key for the objects within the world
void Application::setKey()
{
    SDL_SetColorKey(player.player, SDL_SRCCOLORKEY, SDL_MapRGB(player.player->format, 0, 128, 128));

    for(int i = 0; i<2; i++)//set key for wraiths
    {
        SDL_SetColorKey(wraithFactory[i].wraith, SDL_SRCCOLORKEY, SDL_MapRGB(wraithFactory[i].wraith->format, 0, 128, 128));
    }

    for(int i = 0; i<2; i++)//set key for mummy
    {
        SDL_SetColorKey(mummyFactory[i].mummy, SDL_SRCCOLORKEY, SDL_MapRGB(mummyFactory[i].mummy->format, 0, 128, 128));
    }

    SDL_SetColorKey(seeker.seeker, SDL_SRCCOLORKEY, SDL_MapRGB(seeker.seeker->format, 0, 128, 128));
    SDL_SetColorKey(ghost.ghost, SDL_SRCCOLORKEY, SDL_MapRGB(ghost.ghost->format, 0, 128, 128));

    SDL_SetColorKey(island1, SDL_SRCCOLORKEY, SDL_MapRGB(island1->format, 0, 128, 128));
    SDL_SetColorKey(island2, SDL_SRCCOLORKEY, SDL_MapRGB(island2->format, 0, 128, 128));
    SDL_SetColorKey(island3, SDL_SRCCOLORKEY, SDL_MapRGB(island3->format, 0, 128, 128));
    SDL_SetColorKey(island4, SDL_SRCCOLORKEY, SDL_MapRGB(island4->format, 0, 128, 128));
    SDL_SetColorKey(spikes, SDL_SRCCOLORKEY, SDL_MapRGB(spikes->format, 0, 128, 128));
    SDL_SetColorKey(spikes1, SDL_SRCCOLORKEY, SDL_MapRGB(spikes1->format, 0, 128, 128));
    SDL_SetColorKey(pillar, SDL_SRCCOLORKEY, SDL_MapRGB(pillar->format, 0, 128, 128));
    SDL_SetColorKey(finish, SDL_SRCCOLORKEY, SDL_MapRGB(finish->format, 0, 128, 128));
    SDL_SetColorKey(ghost.lightning, SDL_SRCCOLORKEY, SDL_MapRGB(ghost.lightning->format, 0, 128, 128));

    for(int i = 0; i<100; i++)//set key for all the arrows
    {
        SDL_SetColorKey(quiver[i].arrowR, SDL_SRCCOLORKEY, SDL_MapRGB(quiver[i].arrowR->format, 0, 128, 128));
        SDL_SetColorKey(quiver[i].arrowL, SDL_SRCCOLORKEY, SDL_MapRGB(quiver[i].arrowL->format, 0, 128, 128));
    }

}

//makes sure the player and camera do not exceed the screen dimensions
void Application::checkBoundaries()
{

    if(player.playerPos.y > 510)
    {
        player.playerPos.y = 510;
    }
        //keep camera in bounds
        if(cameraPos.x<0)
        {
            cameraPos.x = 0;
        }
        if(cameraPos.x>10000)
        {
            cameraPos.x = 10000;
        }

        //keep player in bounds
        if(player.posX > 10900)
        {
            player.posX = 10900;
        }

        if(player.posX < 1)
        {
            player.posX = 0;
        }

}

void Application::handlePhysics()
{
    //apply gravity
    phy.gravity(delta.get_ticks()/1000.f, player.posY);
    //the call to check for collision between the player and all of the inanimate objects
    //registered in the physics "database"
    phy.isCollision(delta.get_ticks()/1000.f, player.playerPos, player.posX, player.posY);

    //checks for collision between the player and the spikes
    if(phy.Collision(&player.playerPos, &environment.spikesPos))
    {
        //handles the death behavior
        handleDeath();
    }

    if(phy.Collision(&player.playerPos, &environment.spikes1Pos))
    {
        handleDeath();
    }

    //if arrow hits wraith from the right
    for(list<Arrow>::iterator itr = arrowListR.begin(); itr!=arrowListR.end(); itr++)
    {
        for(int i = 0; i<2; i++)//for each wraith
        {
            if(phy.Collision(&itr->arrowRpos, &wraithFactory[i].monsterPos))
            {
                wraithFactory[i].deadMonsterR = true;//stops updating the monster
                itr->used = true;//sets arrow as used
                wraithFactory[i].monsterAnim = {wraithFactory[i].frame_x*100, wraithFactory[i].frame_y*150, 100, 150};//update death animation
            }

            if(wraithFactory[i].deadMonsterR)//goes into death animation
            {
                if(wraithFactory[i].killedMonsterR(delta.get_ticks()/1000.f))
                {
                    wraithFactory[i].monsterDead = true;
                }

            }
        }
    }

    //if arrow hits wraith from the left
    for(list<Arrow>::iterator itr = arrowListL.begin(); itr!=arrowListL.end(); itr++)
    {
        for(int i = 0; i<2; i++)
        {
            if(phy.Collision(&itr->arrowLpos, &wraithFactory[i].monsterPos))
            {
                wraithFactory[i].deadMonsterL = true;//stops updating the monster
                itr->used = true;
                wraithFactory[i].monsterAnim = {wraithFactory[i].frame_x*100, wraithFactory[i].frame_y*150, 100, 150};//update death animation
            }

            if(wraithFactory[i].deadMonsterL)//goes into death animation
            {
                if(wraithFactory[i].killedMonsterL(delta.get_ticks()/1000.f))
                {
                    wraithFactory[i].monsterDead = true;

                }

            }
        }

    }

    //if wraith is alive and collides with player, kill player
    for(int i = 0; i < 2; i++)
    {
        //calls individual collision detection method
        if(!wraithFactory[i].monsterDead && phy.Collision(&wraithFactory[i].monsterPos, &player.playerPos))
        {
            handleDeath();//player is killed
        }
    }


    //if arrow hits mummy from the right
    for(list<Arrow>::iterator itr = arrowListR.begin(); itr!=arrowListR.end(); itr++)
    {
        for(int i = 0; i<2; i++)//for each mummy
        {
            if(phy.Collision(&itr->arrowRpos, &mummyFactory[i].monsterPos))//if arrow collides with mummy's current position
            {
                mummyFactory[i].deadMonsterR = true;//stops updating the monster
                itr->used = true;//sets arrow as used
                mummyFactory[i].monsterAnim = {mummyFactory[i].frame_x*100, mummyFactory[i].frame_y*100, 100, 100};//update death animation
            }

            if(mummyFactory[i].deadMonsterR)//goes into death animation
            {
                if(mummyFactory[i].killedMonsterR(delta.get_ticks()/1000.f))//death animation method
                {
                    mummyFactory[i].monsterDead = true;//sets monster to dead when animation finishes
                }

            }
        }
    }

    //if arrow hits mummy from the left
    for(list<Arrow>::iterator itr = arrowListL.begin(); itr!=arrowListL.end(); itr++)
    {
        for(int i = 0; i<2; i++)//for each mummy
        {
            if(phy.Collision(&itr->arrowLpos, &mummyFactory[i].monsterPos))//if arrow collides with mummy current position
            {
                mummyFactory[i].deadMonsterL = true;//stops updating the monster
                itr->used = true;//set arrow to used
                mummyFactory[i].monsterAnim = {mummyFactory[i].frame_x*100, mummyFactory[i].frame_y*100, 100, 100};//update death animation
            }

            if(mummyFactory[i].deadMonsterL)//goes into death animation
            {
                if(mummyFactory[i].killedMonsterL(delta.get_ticks()/1000.f))//calls death animation method
                {
                    mummyFactory[i].monsterDead = true;//sets monster to dead

                }

            }
        }

    }

    //if mummy is alive and collides with player, kill player
    for(int i = 0; i < 2; i++)
    {
        if(!mummyFactory[i].monsterDead && phy.Collision(&mummyFactory[i].monsterPos, &player.playerPos))
        {
            handleDeath();//player is killed
        }
    }

    //if arrow hits seeker from the right
    for(list<Arrow>::iterator itr = arrowListR.begin(); itr!=arrowListR.end(); itr++)
    {
        if(phy.Collision(&itr->arrowRpos, &seeker.monsterPos))
        {
            seeker.deadMonsterR = true;//stops updating the monster
            itr->used = true;//sets arrow as used
            seeker.monsterAnim = {seeker.frame_x*100, seeker.frame_y*100, 100, 100};//update death animation
        }

        if(seeker.deadMonsterR)//goes into death animation
        {
            if(seeker.killedMonsterR(delta.get_ticks()/1000.f))
            {
                seeker.monsterDead = true;
            }

        }
    }

    //if arrow hits seeker from the left
    for(list<Arrow>::iterator itr = arrowListL.begin(); itr!=arrowListL.end(); itr++)
    {
        if(phy.Collision(&itr->arrowLpos, &seeker.monsterPos))
        {
            seeker.deadMonsterL = true;//stops updating the monster
            itr->used = true;//sets arrow as used
            seeker.monsterAnim = {seeker.frame_x*100, seeker.frame_y*100, 100, 100};//update death animation
        }

        if(seeker.deadMonsterL)//goes into death animation
        {
            if(seeker.killedMonsterL(delta.get_ticks()/1000.f))
            {
                seeker.monsterDead = true;
            }

        }
    }

    //if seeker is alive and collides with player, kill player
    if(!seeker.monsterDead && phy.Collision(&seeker.monsterPos, &player.playerPos))
    {
        handleDeath();//player is killed
    }

    //ghost
    for(list<Arrow>::iterator itr = arrowListR.begin(); itr!=arrowListR.end(); itr++)
    {
        if(phy.Collision(&itr->arrowRpos, &ghost.monsterPos))
        {
            ghost.deadMonsterR = true;//stops updating the monster
            itr->used = true;//sets arrow as used
            ghost.monsterAnim = {ghost.frame_x*122, ghost.frame_y*130, 122, 130};//update death animation
        }

        if(ghost.deadMonsterR)//goes into death animation
        {
            if(ghost.killedMonsterR(delta.get_ticks()/1000.f))
            {
                ghost.monsterDead = true;
                ghost.isLightning = false;
            }

        }
    }

    for(list<Arrow>::iterator itr = arrowListL.begin(); itr!=arrowListL.end(); itr++)
    {
        if(phy.Collision(&itr->arrowLpos, &ghost.monsterPos))
        {
            ghost.deadMonsterL = true;//stops updating the monster
            itr->used = true;//sets arrow as used
            ghost.monsterAnim = {ghost.frame_x*122, ghost.frame_y*130, 122, 130};//update death animation
        }

        if(ghost.deadMonsterL)//goes into death animation
        {
            if(ghost.killedMonsterL(delta.get_ticks()/1000.f))
            {
                ghost.monsterDead = true;
                ghost.isLightning = false;
            }

        }
    }
    //if ghost's lightning hits player, kill player
    if(ghost.isLightning && phy.Collision(&player.playerPos, &ghost.lightningPos))
    {
        handleDeath();
    }
}

//resets the objects within the world upon a player death
void Application::reset()
{
    player.posX = 300;//reset player position
    player.posY = 300;

    global.start();//reset game timer
    arrows = 0;//reset arrow counter
    points = 0;

    keys[SDLK_a] = KEY_UP;
    keys[SDLK_d] = KEY_UP;
    keys[SDLK_SPACE] = KEY_UP;

    //calls the reset method for the monsters
    wraithFactory[0].resetMonster();
    wraithFactory[1].resetMonster();
    mummyFactory[0].resetMonster();
    mummyFactory[1].resetMonster();
    seeker.resetMonster();
    ghost.resetMonster();

    //resets monsters positions
    wraithFactory[0].posX = 900;
    wraithFactory[1].posX = 3000;
    wraithFactory[1].posY = 180;
    mummyFactory[0].posX = 6130;
    mummyFactory[0].posY = 0;
    mummyFactory[1].posX = 8560;
    mummyFactory[1].posY = 410;
    seeker.posX = 9500;
    seeker.posY = 400;
    ghost.posX = 4830;
    ghost.posY = 100;

    for(int i = 0; i<2; i++)//set key for wraiths
    {
        SDL_SetColorKey(wraithFactory[i].wraith, SDL_SRCCOLORKEY, SDL_MapRGB(wraithFactory[i].wraith->format, 0, 128, 128));
    }
    for(int i = 0; i<2; i++)//set key for mummies
    {
        SDL_SetColorKey(mummyFactory[i].mummy, SDL_SRCCOLORKEY, SDL_MapRGB(mummyFactory[i].mummy->format, 0, 128, 128));
    }

    SDL_SetColorKey(seeker.seeker, SDL_SRCCOLORKEY, SDL_MapRGB(seeker.seeker->format, 0, 128, 128));
    SDL_SetColorKey(ghost.ghost, SDL_SRCCOLORKEY, SDL_MapRGB(ghost.ghost->format, 0, 128, 128));
    SDL_SetColorKey(ghost.lightning, SDL_SRCCOLORKEY, SDL_MapRGB(ghost.lightning->format, 0, 128, 128));
}

//updates the environment and player interaction with it
void Application::handleEnvironment()
{
    //calls methods to oscillate and elevate floating islands, passing as
    //parameters, a frame cycle time, two limits of oscillation or elevation,
    //and a velocity
    environment.island1.oscillate(delta.get_ticks()/1000.f, 1230, 1750, 300);

    environment.island2.elevate(delta.get_ticks()/1000.f);

    environment.island3.oscillate(delta.get_ticks()/1000.f, 5400, 5700, 200);

    environment.island4.oscillate(delta.get_ticks()/1000.f, 6300, 6800, 400);

    //calls the island's interaction horizontal and vertical methods which determine player collisions and their
    //movement patterns while on the island
    if(environment.island1.interactH(delta.get_ticks()/1000.f, player.posX, player.posY, player.playerPos, 300))
    {
        phy.onTop =true;
    }

    if(environment.island2.interactV(delta.get_ticks()/1000.f, player.posX, player.posY, player.playerPos))
    {
        phy.onTop = true;
    }

    if(environment.island3.interactH(delta.get_ticks()/1000.f, player.posX, player.posY, player.playerPos, 200))
    {
        phy.onTop =true;
    }

    if(environment.island4.interactH(delta.get_ticks()/1000.f, player.posX, player.posY, player.playerPos, 400))
    {
        phy.onTop =true;
    }
}

//handles player input events
void Application::handleEvents()
{
    if(!dead)
    {

        // defines event types
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            if(event.type == SDL_KEYDOWN)
           {
               keys[event.key.keysym.sym] = KEY_DOWN;

           }
           if(event.type == SDL_KEYUP)
           {
               keys[event.key.keysym.sym] = KEY_UP;
           }
        }

        //behavior for moving backward
        if(keys[SDLK_a] == KEY_DOWN)
        {
            player.frame_y = 2;//reset to walking column
            player.backward(delta.get_ticks()/1000.f);//if player hit the 'a' key, move backward
            lastKey = 1;
        }

        //behavior for moving forward
        if(keys[SDLK_d] == KEY_DOWN)
        {
            player.frame_y = 2;//reset to walking column
            player.forward(delta.get_ticks()/1000.f);//if the player hit the 'd' key, move forward
            lastKey = 2;
        }

        //handles jumps
        if(keys[SDLK_SPACE] == KEY_DOWN && (cooldown.get_ticks() > checker) && phy.onTop)
        {
            cooldown.start();
            checker = cooldown.get_ticks() + 300;
        }

        //if cooldown is up, jump
        if(checker > cooldown.get_ticks())
        {
           player.posY-= 1200 * (delta.get_ticks() / 1000.f);
        }

        //handles character behavior when standing still
        if((keys[SDLK_d] == KEY_UP || keys[SDLK_d] == NULL)
           && (keys[SDLK_a] == KEY_UP || keys[SDLK_a] == NULL))//resets animation to still
        {

                if(lastKey == 2)//facing right
                {
                    player.frame_x = 7;
                    player.frame_y = 1;

                    if(event.type == SDL_MOUSEBUTTONDOWN)//if player clicks down and is standing still...
                    {
                        //timer for animation cycle
                        animDelta-=10*(delta.get_ticks()/1000.f);
                        player.frame_x = (int)animDelta;

                        //if shot animation has cycled
                        if(player.frame_x < 0)
                        {
                            //when shot animation ends, set the shotFlag
                            shotFlagR = true;

                            player.frame_x = 7;//reset shot animation
                            animDelta = 7;
                        }

                    }
                }

                if(lastKey == 1)//facing left
                {
                    player.frame_x = 0;
                    player.frame_y = 0;

                    if(event.type == SDL_MOUSEBUTTONDOWN)//if player clicks down and is standing still...
                    {
                        //timer for shot animation cycle
                        animDelta+=10*(delta.get_ticks()/1000.f);
                        player.frame_x = (int)animDelta;

                        //if shot animation has cycled
                        if(player.frame_x > 7)
                        {
                            shotFlagL = true;

                            player.frame_x = 0;
                            animDelta = 0;
                        }
                    }
                }
        }
    }
}

//method to update the player within the game loop
void Application::updatePlayer()
{
    player.playerPos = {player.posX, player.posY, 100, 100};
    player.playerAnim = {player.frame_x*W, player.frame_y*H, W, H};
    cameraPos = {player.posX-500,0, 1100, 700};

    checkShots();//decides whether to set the shotFlag
}

//clears the screen upon application finishing
void Application::clearSurface()
{
    SDL_FreeSurface(camera);
    SDL_FreeSurface(background);
    SDL_FreeSurface(ground);
    SDL_FreeSurface(ground1);
    SDL_FreeSurface(ground2);
    SDL_FreeSurface(stairs1);
    SDL_FreeSurface(stairs2);
    SDL_FreeSurface(stairs3);
    SDL_FreeSurface(stairs4);
    SDL_FreeSurface(stairs5);
    SDL_FreeSurface(stairs6);
    SDL_FreeSurface(island1);
    SDL_FreeSurface(island2);
    SDL_FreeSurface(island3);
    SDL_FreeSurface(island4);
    SDL_FreeSurface(spikes);
    SDL_FreeSurface(spikes1);
    SDL_FreeSurface(pillar);
    SDL_FreeSurface(wall1);
    SDL_FreeSurface(wall2);
    SDL_FreeSurface(wall3);
    SDL_FreeSurface(wall4);
    SDL_FreeSurface(wall5);
    SDL_FreeSurface(platform1);
    SDL_FreeSurface(platform2);
    SDL_FreeSurface(platform3);
    SDL_FreeSurface(platform4);
    SDL_FreeSurface(platform5);
    SDL_FreeSurface(platform6);
    SDL_FreeSurface(platform7);
    SDL_FreeSurface(finish);

}

//defines the application behavior upon a player death
void Application::handleDeath()
{
        bool loadFlag = true;
        player.frame_x = 8;//show death frame and disable player movement
        player.frame_y = 2;

        player.posY -= 400 * delta.get_ticks()/1000.f;//stops dead body from falling

        dead = true;//player is dead, disables movement
        freeze++;//keeps track of delay


        if(freeze < 800)//how long to delay before loadscreen
        {
            if(SDL_PollEvent(&event))//poll events and allow player to quit after death
            {
                if(event.type == SDL_QUIT)
                {
                    gameRunning = false;
                }
            }
            loadFlag = false;//disable loadscreen for this period of time
        }

        //load screen
        if(loadFlag)
        {
            freeze = 0;//reset death delay counter

            if(screens.loadFirst())
            {
                phy.onTop = true;
                reset();
                dead = false;
            }
        }
}

//handles the behavior of arrows that have been shot
void Application::handleArrows()
{
    //update arrows in the queue for right shot
    for(list<Arrow>::iterator itr = arrowListR.begin(); itr!=arrowListR.end(); itr++)
    {
        (*itr).arrowRpos = {(*itr).arrowRpos.x+=600*delta.get_ticks()/1000.f, (*itr).arrowRpos.y, 70, 25};//adjust position
        SDL_BlitSurface((*itr).arrowR, NULL, background, &(*itr).arrowRpos);

    }

    if(arrowListR.front().arrowRpos.x > player.posX + 1000)//if arrows are out of range, clear them
    {
        arrowListR.pop_front();
    }

    //update arrows in the queue for left shot
    for(list<Arrow>::iterator itr = arrowListL.begin(); itr!=arrowListL.end(); itr++)
    {
        (*itr).arrowLpos = {(*itr).arrowLpos.x-=600*delta.get_ticks()/1000.f, (*itr).arrowLpos.y, 70, 25};//adjust position
        SDL_BlitSurface((*itr).arrowL, NULL, background, &(*itr).arrowLpos);

    }

    if(arrowListL.front().arrowLpos.x < 1)//if arrows are out of range, clear them
    {
        arrowListL.pop_front();
    }


}

//maintains arrows positions and whether or not to add them to the screen
void Application::checkShots()
{
    //constantly update position of the arrows as player moves
    if(!shotFlagR)
    {
        for(int i = 0; i<=99; i++)
        {
            quiver[i].arrowRpos = {player.posX + player.playerPos.w - 20, player.posY - 60 + player.playerPos.w, 70, 25};
        }

    }

    if(!shotFlagL)
    {
        for(int i = 0; i<=99; i++)
        {
            quiver[i].arrowLpos = {player.posX , player.posY - 60 + player.playerPos.w, 70, 25};
        }

    }

    //if shotFlag is set, add arrows to the visual queue
    if(shotFlagR)
    {
        if(arrows<100)
        {
           arrowListR.push_back(quiver[arrows++]);
        }

        shotFlagR = false;
    }

    //if shotFlag is set, add arrows to the visual queue
    if(shotFlagL)
    {
        if(arrows<100)
        {
           arrowListL.push_back(quiver[arrows++]);
        }

        shotFlagL = false;
    }
}

//method to draw text to a given position on the screen
void Application::drawText(SDL_Surface * destination, string msg, int x, int y, int size, SDL_Color color)
{
    TTF_Font * font;
    //define font variable
    font = TTF_OpenFont("media/georgia.ttf", size);

    //define coordinate rectangle using the given parameters
    SDL_Rect coordinates;
    coordinates.x = (int)x;
    coordinates.y = (int)y;
    coordinates.w = 400;
    coordinates.h = 200;

    SDL_Surface * message = NULL;
    //define message
    message = TTF_RenderText_Solid(font, msg.c_str(), color);
    //blit message
    SDL_BlitSurface(message, NULL, destination, &coordinates);

    TTF_CloseFont(font);
    SDL_FreeSurface(message);
}

//method to update the monsters within the game loop
void Application::updateMonsters()
{
    //first wraith: if 1 second has passed in the game and the monster is not dead
    if(global.get_ticks() > 1000 && !wraithFactory[0].monsterDead && !wraithFactory[0].deadMonsterR && !wraithFactory[0].deadMonsterL)
    {
        //if the wraith's x position is greater than the players
        if(wraithFactory[0].posX > player.posX)
        {
            //move backward toward player
            wraithFactory[0].backward(delta.get_ticks()/1000.f);
        }
        //else, move forward
        if(wraithFactory[0].posX < player.posX)
        {
            wraithFactory[0].forward(delta.get_ticks()/1000.f);
        }
        //update newly adjusted position and animation sprite
        wraithFactory[0].monsterPos = {wraithFactory[0].posX, wraithFactory[0].posY, 150, 100};
        wraithFactory[0].monsterAnim = {wraithFactory[0].frame_x*100, wraithFactory[0].frame_y*150, 100, 150};
    }

    //second wraith:  if player's x position has passed 1800, spawn wraith
    if(player.posX > 1800 && !wraithFactory[1].monsterDead && !wraithFactory[1].deadMonsterR && !wraithFactory[1].deadMonsterL)
    {
        //oscillate between 2250 and 2940
        if(wraithFactory[1].posX < 2250)
        {
            wraithFactory[1].Hstate = false;
        }
        if(wraithFactory[1].posX > 2940)
        {
            wraithFactory[1].Hstate = true;
        }
        if(wraithFactory[1].Hstate)
        {
            wraithFactory[1].backward(delta.get_ticks()/1000.f);
        }
        if(!wraithFactory[1].Hstate)
        {
            wraithFactory[1].forward(delta.get_ticks()/1000.f);
        }
        //update newly adjusted position and animation
        wraithFactory[1].monsterPos = {wraithFactory[1].posX, wraithFactory[1].posY, 150, 100};
        wraithFactory[1].monsterAnim = {wraithFactory[1].frame_x*100, wraithFactory[1].frame_y*150, 100, 150};
    }

    //first mummy:  if 1 second has passed, spawn mummy
    if(global.get_ticks() > 1000 && !mummyFactory[0].monsterDead && !mummyFactory[0].deadMonsterR && !mummyFactory[0].deadMonsterL)
    {
        //oscillate between 5730 and 6130
        if(mummyFactory[0].posX < 5730)
        {
            mummyFactory[0].Hstate = false;
        }
        if(mummyFactory[0].posX > 6130)
        {
            mummyFactory[0].Hstate = true;
        }
        if(mummyFactory[0].Hstate)
        {
            mummyFactory[0].backward(delta.get_ticks()/1000.f);
        }
        if(!mummyFactory[0].Hstate)
        {
            mummyFactory[0].forward(delta.get_ticks()/1000.f);
        }
        //update position and animation rects
        mummyFactory[0].monsterPos = {mummyFactory[0].posX, mummyFactory[0].posY, 100, 100};
        mummyFactory[0].monsterAnim = {mummyFactory[0].frame_x*100, mummyFactory[0].frame_y*100, 100, 100};
    }
    //second mummy:  if player has passed 8660, spawn
    if(player.posX > 8660 && !mummyFactory[1].monsterDead && !mummyFactory[1].deadMonsterR && !mummyFactory[1].deadMonsterL)
    {
        //oscillate between 8560 and 9500
        if(mummyFactory[1].posX < 8560)
        {
            mummyFactory[1].Hstate = false;
        }
        if(mummyFactory[1].posX > 9500)
        {
            mummyFactory[1].Hstate = true;
        }
        if(mummyFactory[1].Hstate)
        {
            mummyFactory[1].backward(delta.get_ticks()/1000.f);
        }
        if(!mummyFactory[1].Hstate)
        {
            mummyFactory[1].forward(delta.get_ticks()/1000.f);
        }
        //update position and animation rects
        mummyFactory[1].monsterPos = {mummyFactory[1].posX, mummyFactory[1].posY, 60 , 100};
        mummyFactory[1].monsterAnim = {mummyFactory[1].frame_x*100, mummyFactory[1].frame_y*100, 100, 100};
    }
    //seeker:  is player has passed 8660, spawn
    if(player.posX > 8660 && !seeker.monsterDead && !seeker.deadMonsterR && !seeker.deadMonsterL)
    {
        //move towards player
        if(seeker.posX > player.posX)
        {
            seeker.backward(delta.get_ticks()/1000.f);
        }

        if(seeker.posX < player.posX)
        {
            seeker.forward(delta.get_ticks()/1000.f);
        }
        //updates position and animation
        seeker.monsterPos = {seeker.posX, seeker.posY, 100, 100};
        seeker.monsterAnim = {seeker.frame_x*100, seeker.frame_y*100, 100, 100};
    }

    //ghost:  if player has passed 3500, spawn
    if(player.posX > 3500 && !ghost.monsterDead && !ghost.deadMonsterR && !ghost.deadMonsterL)
    {
        //oscillate between 4500 and 4830
        if(ghost.posX > 4830)
        {
            ghost.Hstate = true;
        }
        if(ghost.Hstate && ghost.attacking == false)
        {
            ghost.backward(delta.get_ticks()/1000.f);
        }
        if(!ghost.Hstate && ghost.attacking == false)
        {
            ghost.forward(delta.get_ticks()/1000.f);
        }
        //if ghost has passed 4500, go into attack mode
        if(ghost.Hstate && ghost.posX < 4500 && ghost.attacking == false)
        {
            ghost.attacking = true;
            ghost.Hstate = false;
        }
        //ghost casts a stream lightning bolt
        if(ghost.attacking)
        {
            //goes into ghosts attack animation
            if(ghost.attack(delta.get_ticks()/1000.f))
            {
                ghost.attacking = false;
                ghost.isLightning = true;//enables lightning display after skelly is done attacking
            }
        }
        //update both the ghost's position and animation rects along with the lightning attack animation
        ghost.monsterPos = {ghost.posX, ghost.posY, 122, 130};
        ghost.monsterAnim = {ghost.frame_x*122, ghost.frame_y*130, 122, 130};
        ghost.lightningAnim = {ghost.Lframe_x*80, 0, 80, 240};
        ghost.lightningPos = {4470, 380, 80, 240};
    }
    //if isLightning is set
    if(ghost.isLightning)
    {
        //go through the lightning strike animation
        if(ghost.showLightning(delta.get_ticks()/1000.f))
        {
            if(ghost.showLightning(delta.get_ticks()/1000.f))
            {
               ghost.isLightning = false;
            }
        }
    }

}

//uses a simple formula to update the points the player has earned
void Application::updatePoints()
{
    if(pointTracker)
    {
        //if wraiths were killed, add 5
        for(int i = 0;i<2; i++)
        {
            if(wraithFactory[i].monsterDead && !wraithFactory[i].deathCounted)
            {
                points+=5;
                wraithFactory[i].deathCounted = true;
            }
        }
        //if mummies were killed, add 5
        for(int i = 0;i<2; i++)
        {
            if(mummyFactory[i].monsterDead && !mummyFactory[i].deathCounted)
            {
                points+=5;
                mummyFactory[i].deathCounted = true;
            }
        }
        //if seeker was killed, add 5
        if(seeker.monsterDead && !seeker.deathCounted)
        {
            points+=5;
            seeker.deathCounted = true;
        }

        //if ghost was killed, add 5
        if(ghost.monsterDead && !ghost.deathCounted)
        {
            points+=5;
            ghost.deathCounted = true;
        }
        //if player has passed the finish flag, calculate points based off of time finished
        if(phy.Collision(&player.playerPos, &environment.finishRect))
        {
            points+=120-(global.get_ticks()/1000);
            pointTracker = false;
            finished = true;
        }
    }


}

//shows final points when player has finished course
void Application::showFinal()
{
    stringstream gameInterface;
    gameInterface<<"Your total score is: "<<points;
    drawText(background, gameInterface.str(), 10300, 200, 18, color);

}







