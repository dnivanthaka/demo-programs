#include "player.h"

extern void drawImage(SDL_Surface *, int, int);
extern void checkToMap(Entity *);
extern void centerEntityOnMap(Entity *);

void initPlayer()
{
	player.x = player.y = 0;
	player.dirX = player.dirY = 0;
	
	player.w = playerImage->w;
	player.h = playerImage->h;
	
	player.thinkTime = 0;
}

void doPlayer()
{
	if (player.thinkTime == 0)
	{
		player.dirX = 0;
	
		/* Gravity always pulls the player down */
	
		player.dirY += GRAVITY_SPEED;
		
		if (player.dirY >= MAX_FALL_SPEED)
		{
			player.dirY = MAX_FALL_SPEED;
		}
		
		if (input.left == 1)
		{
			player.dirX -= PLAYER_SPEED;
		}
		
		else if (input.right == 1)
		{
			player.dirX += PLAYER_SPEED;
		}
		
		if (input.jump == 1)
		{
			if (player.onGround == 1)
			{
				player.dirY = -11;
			}
			
			input.jump = 0;
		}
		
		checkToMap(&player);
		
		centerEntityOnMap(&player);
	}
	
	if (player.thinkTime > 0)
	{
		player.thinkTime--;
		
		if (player.thinkTime == 0)
		{
			initPlayer();
		}
	}
}

void drawPlayer()
{
	if (player.thinkTime == 0)
	{
		drawImage(playerImage, player.x - map.startX, player.y - map.startY);
	}
}
