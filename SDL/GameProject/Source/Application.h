#pragma once

#include<map>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<sdl/sdl_ttf.h>
#include"Timer.h"
#include"Player.h"
#include"Wraith.h"
#include"Physics.h"
#include"Environment.h"
#include"Screens.h"
#include"Arrow.h"
#include"Mummy.h"
#include"Seeker.h"
#include"Ghost.h"

#include<list>
#include<string>
#include<sstream>
#include<iomanip>
#include<fstream>

#define KEY_UP 2
#define KEY_DOWN 1

using namespace std;

class Application
{

public:

    Application();
    //initializes the supplemental methods of the application
    void Initialize();
    //runs the game loop
    void gameLoop();
    //clears the screen upon application finishing
    void clearSurface();

private:
    //surfaces to be used by the application
    SDL_Surface * screen;
    SDL_Surface * camera;
    SDL_Surface * background;
    SDL_Surface * ground;
    SDL_Surface * ground1;
    SDL_Surface * ground2;
    SDL_Surface * stairs1;
    SDL_Surface * stairs2;
    SDL_Surface * stairs3;
    SDL_Surface * stairs4;
    SDL_Surface * stairs5;
    SDL_Surface * stairs6;
    SDL_Surface * island1;
    SDL_Surface * spikes;
    SDL_Surface * spikes1;
    SDL_Surface * pillar;
    SDL_Surface * wall1;
    SDL_Surface * wall2;
    SDL_Surface * wall3;
    SDL_Surface * wall4;
    SDL_Surface * wall5;
    SDL_Surface * island2;
    SDL_Surface * island3;
    SDL_Surface * island4;
    SDL_Surface * platform1;
    SDL_Surface * platform2;
    SDL_Surface * platform3;
    SDL_Surface * platform4;
    SDL_Surface * platform5;
    SDL_Surface * platform6;
    SDL_Surface * platform7;
    SDL_Surface * finish;

    //variables used when drawing text
    TTF_Font * font;
    SDL_Color color;

    SDL_Event event;//event variable to hold inputs
    bool gameRunning;
    bool dead;
    bool shotFlagR;
    bool thing;
    bool shotFlagL;
    bool deadMonster;
    bool pointTracker;
    bool finished;
    int keys[323];//array to hold SDL keys
    int frame;
    int lastKey;
    int checker;
    int freeze;
    int time;
    int points;
    double animDelta;

    //variables to handle arrow behavior
    Arrow quiver[100];
    int arrows;
    list<Arrow> arrowListR;
    list<Arrow> arrowListL;

    //various clocks used by the application
    Timer delta;
    Timer update;
    Timer fps;
    Timer cooldown;
    Timer deathClock;
    Timer global;

    //declaration of the active objects within the game
    Player player;
    Wraith wraithFactory[2];
    Mummy mummyFactory[2];
    Seeker seeker;
    Ghost ghost;

    //interface of objects crucial to the functionality
    //of the application
    Physics phy;
    Environment environment;
    Screen screens;

    SDL_Rect cameraPos;//declaration of the camera to follow player

    //method to take a filename and an associated rectangular position
    //and register it within the physics database to handle collision detection
    //between the player and inanimate objects
    SDL_Surface* addItem(const char * file, SDL_Rect& region);
    //method to update the player within the game loop
    void updatePlayer();
    //method to update the monsters within the game loop
    void updateMonsters();
    //handles player input events
    void handleEvents();
    //updates the environment and player interaction with it
    void handleEnvironment();
    //initializes the applications various clocks
    void startClocks();
    //method to handle all of the surface blitting within the game loop
    void drawSurface();
    //method to draw text to a given position on the screen
    void drawText(SDL_Surface * destination, string msg, int x, int y, int size, SDL_Color color);
    //handles updating the fps
    void updateFPS();
    //uses a simple formula to update the points the player has earned
    void updatePoints();
    //sets the color key for the objects within the world
    void setKey();
    //defines the file names for the SDL_Surfaces
    void loadSurfaces();
    //makes sure the player and camera do not exceed the screen dimensions
    void checkBoundaries();
    //handles the basic physics interactions and provides the appropriate behavior
    void handlePhysics();
    //resets the objects within the world upon a player death
    void reset();
    //defines the application behavior upon a player death
    void handleDeath();
    //handles the behavior of arrows that have been shot
    void handleArrows();
    //maintains arrows positions and whether or not to add them to the screen
    void checkShots();
    //loads the map ADT with the filename and associated rectangular position
    void loadMap();
    //shows final points when player has finished course
    void showFinal();

    //map ADT to load
    map<SDL_Surface*, SDL_Rect> blitMap;
    map<SDL_Surface*, SDL_Rect>::iterator bliterator;//cool name for this iterator

};




