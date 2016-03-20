#include <iostream>
#include "SDL/SDL.h"

#include "types.h"
#include "config.h"
#include "layout.h"
#include "video.h"


Uint8 layout[ SCREEN_HEIGHT / TILE_SIZE ][ SCREEN_WIDTH / TILE_SIZE ] = {
    {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x02},
    {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x02},
    {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02}
};

SDL_Surface *map = NULL;

void init_layout()
{
    //map = load_image( "right_ash1.bmp" );
    map = load_image( "pattern1.bmp" );
    if( map == NULL ){
        std::cerr << "Error loading resource. " << std::endl;
        exit(1);
    }
}

void draw_layout(SDL_Surface *screen)
{
    for(int i=0;i<SCREEN_HEIGHT/TILE_SIZE;i++){
        for(int j=0;j<SCREEN_WIDTH/TILE_SIZE;j++){
            if(layout[i][j] == 0x01){
                
                SDL_Rect tmp, tmp2;

                tmp.x = j * TILE_SIZE;
                tmp.y = i * TILE_SIZE;
                tmp.w = TILE_SIZE;
                tmp.h = TILE_SIZE;

                tmp2.x = 0;
                tmp2.y = 0;
                tmp2.w = TILE_SIZE;
                tmp2.h = TILE_SIZE;

                // Blitting object
                SDL_BlitSurface(map, &tmp2, screen, &tmp);
            }else if(layout[i][j] == 0x02){
            
                SDL_Rect tmp, tmp2;

                tmp.x = j * TILE_SIZE;
                tmp.y = i * TILE_SIZE;
                tmp.w = TILE_SIZE;
                tmp.h = TILE_SIZE;

                tmp2.x = 32;
                tmp2.y = 0;
                tmp2.w = TILE_SIZE;
                tmp2.h = TILE_SIZE;

                // Blitting object
                SDL_BlitSurface(map, &tmp2, screen, &tmp);
            }else if(layout[i][j] == 0x03){
            
                SDL_Rect tmp, tmp2;

                tmp.x = j * TILE_SIZE;
                tmp.y = i * TILE_SIZE;
                tmp.w = TILE_SIZE;
                tmp.h = TILE_SIZE;

                tmp2.x = 64;
                tmp2.y = 0;
                tmp2.w = TILE_SIZE;
                tmp2.h = TILE_SIZE;

                // Blitting object
                SDL_BlitSurface(map, &tmp2, screen, &tmp);
            } 
        }
    }
    coord tmp;
    tmp.x = 100;
    tmp.y = 10;
    //std::cout << get_tile_type(&tmp) << std::endl;
    //printf("%d\n", get_tile_type(&tmp));
}

Uint8 get_tile_type(coord *p)
{
    int xseg = p->x / TILE_SIZE;
    int xoff = p->x % TILE_SIZE;

    if( xseg > 0 && xoff > 0 ){
        xseg = xseg + 1;
    }

    if( xseg > 0 ){
        xseg = xseg - 1;
        //xseg = 2;
    }

    int yseg = p->y / TILE_SIZE;
    int yoff = p->y % TILE_SIZE;

    if( yseg > 0 && yoff > 0 ){
        yseg = yseg + 1;
    }

    if( yseg > 0 ){
        yseg = yseg - 1;
    }


    printf("Pos X = %d\n", p->x);
    printf("Tile = %d %d\n", xseg, yseg);
    printf("Tile type = %d\n", layout[yseg][xseg]);
    //printf("%d\n", layout[14][19]);

    //return layout[yseg][xseg];
    return layout[yseg][xseg];
}

coord *get_nearest_tile(coord *p)
{
    coord *tmp = new coord();

    int xseg = p->x / TILE_SIZE;
    int xoff = p->x % TILE_SIZE;

    if( xseg > 0 && xoff > 0 ){
        xseg = xseg + 1;
    }

    if( xseg > 0 ){
        xseg = xseg - 1;
        //xseg = 2;
    }

    int yseg = p->y / TILE_SIZE;
    int yoff = p->y % TILE_SIZE;

    //if( yseg > 0 && yoff > 0 ){
        //yseg = yseg + 1;
    //}

    if( yseg > 0 ){
        yseg = yseg - 1;
    }

    tmp->x = xseg;
    tmp->y = yseg;


    //printf("Pos X = %d\n", p->x);
    //printf("Tile = %d %d\n", xseg, yseg);
    //printf("Tile type = %d\n", layout[yseg][xseg]);
    //printf("%d\n", layout[14][19]);

    //return layout[yseg][xseg];
    //return layout[yseg][xseg];
    return tmp;
}

coord *get_nearest_tile2(coord *p)
{
    coord *tmp = new coord();

    int xseg = p->x / TILE_SIZE;

    if( xseg > 0 ){
        xseg = xseg - 1;
        //xseg = 2;
    }

    int yseg = p->y / TILE_SIZE;

    if( yseg > 0 ){
        yseg = yseg - 1;
    }

    tmp->x = xseg;
    tmp->y = yseg;

    return tmp;
}

void cleanup_layout()
{
    SDL_FreeSurface(map);
}