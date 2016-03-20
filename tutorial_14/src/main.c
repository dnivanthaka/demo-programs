/* This tutorial demonstrates tile based collision
** detection. Pressing the arrow keys
** will sprite around the screen. Pressing escape
** or closing the window will exit the program
*/

#include "main.h"

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern void loadMap(char *);
extern SDL_Surface *loadImage(char *);
extern void draw(void);
extern void doPlayer(void);
extern void initPlayer(void);
extern void delay(unsigned int);
extern void loadMapTiles(void);
extern TTF_Font *loadFont(char *, int);

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;
	
	/* Start up SDL */
	
	init("Parallel Realities Tutorial 14");
	
	/* Call the cleanup function when the program exits */
	
	atexit(cleanup);
	
	go = 1;
	
	/* Load the map tiles */
	
	loadMapTiles();
	
	/* Load the player image */
	
	playerImage = loadImage("gfx/player.png");
	
	/* If we get back a NULL image, just exit */
	
	if (playerImage == NULL)
	{
		exit(1);
	}
	
	/* Load the background image */
	
	map.background = loadImage("gfx/background.png");
	
	/* If we get back a NULL image, just exit */
	
	if (map.background == NULL)
	{
		exit(1);
	}
	
	/* Load the map */
	
	loadMap("data/maps/map01.dat");
	
	/* Initialise the player */
	
	initPlayer();
	
	/* Loop indefinitely for messages */
	
	while (go == 1)
	{
		getInput();
		
		/* Do the player */
		
		doPlayer();
		
		/* Draw the map */
		
		draw();
		
		/* Sleep briefly to stop sucking up all the CPU time */
		
		delay(frameLimit);
		
		frameLimit = SDL_GetTicks() + 16;
	}
	
	/* Exit the program */
	
	exit(0);
}
