#include "collisions.h"

void checkToMap(Entity *e)
{
	int i, x1, x2, y1, y2;
	
	/* Remove the user from the ground */
	
	e->onGround = 0;
	
	/* Test the horizontal movement first */
	
	i = e->h > TILE_SIZE ? TILE_SIZE : e->h;
	
	for (;;)
	{
		x1 = (e->x + e->dirX) / TILE_SIZE;
		x2 = (e->x + e->dirX + e->w - 1) / TILE_SIZE;
	
		y1 = (e->y) / TILE_SIZE;
		y2 = (e->y + i - 1) / TILE_SIZE;
		
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (e->dirX > 0)
			{
				/* Trying to move right */
		
				if ((map.tile[y1][x2] != BLANK_TILE) || (map.tile[y2][x2] != BLANK_TILE))
				{
					/* Place the player as close to the solid tile as possible */
		
					e->x = x2 * TILE_SIZE;
					
					e->x -= e->w + 1;
		
					e->dirX = 0;
				}
			}
		
			else if (e->dirX < 0)
			{
				/* Trying to move left */
		
				if ((map.tile[y1][x1] != BLANK_TILE) || (map.tile[y2][x1] != BLANK_TILE))
				{
					/* Place the player as close to the solid tile as possible */
					
					e->x = (x1 + 1) * TILE_SIZE;
		
					e->dirX = 0;
				}
			}
		}
		
		/* Exit this loop if we have tested all of the body */
		
		if (i == e->h)
		{
			break;
		}
		
		/* Test the next block */
		
		i += TILE_SIZE;
		
		if (i > e->h)
		{
			i = e->h;
		}
	}

	/* Now test the vertical movement */
	
	i = e->w > TILE_SIZE ? TILE_SIZE : e->w;
	
	for (;;)
	{
		x1 = (e->x) / TILE_SIZE;
		x2 = (e->x + i) / TILE_SIZE;
	
		y1 = (e->y + e->dirY) / TILE_SIZE;
		y2 = (e->y + e->dirY + e->h) / TILE_SIZE;
		
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (e->dirY > 0)
			{
				/* Trying to move down */
				
				if ((map.tile[y2][x1] != BLANK_TILE) || (map.tile[y2][x2] != BLANK_TILE))
				{
					/* Place the player as close to the solid tile as possible */
					
					e->y = y2 * TILE_SIZE;
					e->y -= e->h;
		
					e->dirY = 0;
					
					e->onGround = 1;
				}
			}
		
			else if (e->dirY < 0)
			{
				/* Trying to move up */
		
				if ((map.tile[y1][x1] != BLANK_TILE) || (map.tile[y1][x2] != BLANK_TILE))
				{
					/* Place the player as close to the solid tile as possible */
		
					e->y = (y1 + 1) * TILE_SIZE;
		
					e->dirY = 0;
				}
			}
		}
		
		if (i == e->w)
		{
			break;
		}
		
		i += TILE_SIZE;
		
		if (i > e->w)
		{
			i = e->w;
		}
	}

	/* Now apply the movement */

	e->x += e->dirX;
	e->y += e->dirY;
	
	if (e->x < 0)
	{
		e->x = 0;
	}
	
	else if (e->x + e->w >= map.maxX)
	{
		e->x = map.maxX - e->w - 1;
	}
	
	if (e->y > map.maxY)
	{
		e->thinkTime = 60;
	}
}
