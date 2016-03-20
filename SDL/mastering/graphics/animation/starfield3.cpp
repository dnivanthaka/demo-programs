// HEADER FILES ------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <vector>


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// PUBLIC DATA -------------------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;
const int FPS  = 60;
const int FPMS = FPS / 1000;

typedef struct {
    int x;
    int y;
    int w;
    int h;
    int x_vel;
    int y_vel;
    short size;
    Uint32 color;
} star_t;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} frame_t;

SDL_Surface *screen = NULL;
SDL_Event event;
int num_stars = 20;
bool gameRunning = true;

std::vector<star_t> far_stars;
std::vector<star_t> mid_stars;
std::vector<star_t> close_stars;
//SDL_Surface *blit_1 = NULL;
//SDL_Surface *stage_objects;

SDL_Surface* loadImage( std::string file, bool setColorKey = true, int r = 0xFF, int g = 0x00, int b = 0xFF );
void handle_input();
Uint32  getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void move_stars( star_t *stars, frame_t *cont );

//--------------------------------------
static int seed = 0;

static void 
init_rand()
{
    seed = time(NULL);
}

static unsigned int 
getrand()
{
    int p1 = 1103515245;
    int p2 = 12345;
    seed = (seed*p1+p2) % 2147483647;
    return (unsigned)seed/3;
}
//--------------------------------------

int 
main(int argc, char *argv[])
{
    int i;
    Uint32 start_time = 0, numTicks = 0;
    star_t stars[ num_stars ];
    frame_t container;

    // seeding the rand generator
    //srand( (unsigned)time( NULL ) );
    init_rand();

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 )
        return EXIT_FAILURE;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        fprintf( stderr, "Unable to create screen: %s - %d\n", __FILE__, __LINE__ );
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption( "SDL Examples", NULL );

    // star container, we start with 20 x 20, in screen middle
    container.w = 20;
    container.h = 20;
    container.x = (SCREEN_WIDTH / 2)  - (container.w / 2);
    container.y = (SCREEN_HEIGHT / 2) - (container.h / 2);

    for( i = 0; i < num_stars; i++ ){
        star_t tmp;
        tmp.x = getrand() % SCREEN_WIDTH;
        tmp.y = getrand() % SCREEN_HEIGHT;
        tmp.size = 1;
        tmp.x_vel = 1;
        tmp.y_vel = 1;
        //tmp.color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );
        tmp.color = SDL_MapRGB( screen->format, getrand() % 255, getrand() % 255, getrand() % 255 );
        //stars[ i ].x = container.x + (rand() % container.w);
        //stars[ i ].x = rand() % SCREEN_WIDTH;
        //stars[ i ].x = getrand() % SCREEN_WIDTH;
        //stars[ i ].y = container.y + (rand() % container.h);
        //stars[ i ].y = rand() % SCREEN_HEIGHT;
        //stars[ i ].y = getrand() % SCREEN_HEIGHT;
        //stars[ i ].x_vel = 1;
        //stars[ i ].y_vel = 1;
        //stars[ i ].size  = 1 + (rand() % 3);
        //stars[ i ].size  = 1;
        //stars[ i ].color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );
        //stars[ i ].color = SDL_MapRGB( screen->format, rand() % 255, rand() % 255, rand() % 255 );
        //stars[ i ].color = SDL_MapRGB( screen->format, getrand() % 255, getrand() % 255, getrand() % 255 );
        far_stars.push_back( tmp );
    }

    for( i = 0; i < 10; i++ ){
        star_t tmp;
        tmp.x = getrand() % SCREEN_WIDTH;
        tmp.y = getrand() % SCREEN_HEIGHT;
        tmp.size = 1;
        tmp.x_vel = 2;
        tmp.y_vel = 1;
        tmp.color = SDL_MapRGB( screen->format, getrand() % 255, getrand() % 255, getrand() % 255 );
        //tmp.color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );

        mid_stars.push_back( tmp );
    }

    for( i = 0; i < 5; i++ ){
        star_t tmp;
        int dim;

        tmp.x = getrand() % SCREEN_WIDTH;
        tmp.y = getrand() % SCREEN_HEIGHT;
        //tmp.size  = 1 + (rand() % 3);
        dim = 1 + (rand() % 3);
        tmp.w     = dim;
        tmp.h     = dim;
        tmp.size  = 4;
        tmp.x_vel = 3;
        tmp.y_vel = 1;
        tmp.color = SDL_MapRGB( screen->format, getrand() % 255, getrand() % 255, getrand() % 255 );
        //tmp.color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );

        close_stars.push_back( tmp );
    }

    //blit_1 = loadImage( "mario3.png" );

    while( gameRunning ){
        
        handle_input();

        // clearing old stars
        SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
            
        move_stars( stars, &container );

        SDL_Flip( screen );
            
            
        if( SDL_GetTicks() - start_time < 1000 / FPS ){
            //if( SDL_GetTicks() - start_time < FPMS ){
            SDL_Delay( (1000 / FPS) - (SDL_GetTicks() - start_time) );
        }
        start_time = SDL_GetTicks();
        numTicks++;
    }
        //SDL_Delay(2000);

    SDL_FreeSurface( screen );

    return 0;
}

// -------------------------------------------------------------------------
// loadImage
//
// Creates a [screen] type optimized surface from given image file, doesnot handle alpha chanels. Supports color keying
//
// -------------------------------------------------------------------------
SDL_Surface* 
loadImage( std::string file, bool setColorKey, int r, int g, int b )
{
    SDL_Surface *src_img = NULL;
    SDL_Surface *dst_img = NULL;

    src_img = IMG_Load( file.c_str() );

    if( src_img != NULL ){
        if( setColorKey )
        SDL_SetColorKey( src_img, SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, r, g, b) );

        dst_img = SDL_DisplayFormat( src_img );
        SDL_FreeSurface( src_img );

        return dst_img;
        
    }else{
        return NULL;
    }
}

// -------------------------------------------------------------------------
// handle_events
//
// Handles inputs
//
// -------------------------------------------------------------------------
void
handle_input()
{
    while( SDL_PollEvent( &event ) ){
        if( event.type == SDL_QUIT ){
            gameRunning = false;
        }
    }
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 
getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void 
putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void
move_stars( star_t *stars, frame_t *cont )
{
    int i, j, k;

    // star container, we start with 20 x 20, in screen middle
    //cont->w = ( cont->w + 10 ) % SCREEN_WIDTH;
    //cont->h = ( cont->h + 10 ) % SCREEN_HEIGHT;

    //cont->x = (SCREEN_WIDTH / 2)  - (cont->w / 2);
    //cont->y = (SCREEN_HEIGHT / 2) - (cont->h / 2);

    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }

    for( i=0;i<far_stars.size();i++ ){
        //star_t tmp = far_stars.at(i);
        //tmp.x = tmp.x - tmp.x_vel;
        far_stars[i].x = far_stars[i].x - far_stars[i].x_vel;
        if( far_stars[i].x <= 0 )
            far_stars[i].x = SCREEN_WIDTH - (getrand() % 10);
    }

    for( i=0;i<mid_stars.size();i++ ){
        //star_t tmp = far_stars.at(i);
        //tmp.x = tmp.x - tmp.x_vel;
        mid_stars[i].x = mid_stars[i].x - mid_stars[i].x_vel;
        if( mid_stars[i].x <= 0 )
            mid_stars[i].x = SCREEN_WIDTH - (getrand() % 10);
    }

    for( i=0;i<close_stars.size();i++ ){
        //star_t tmp = far_stars.at(i);
        //tmp.x = tmp.x - tmp.x_vel;
        close_stars[i].x = close_stars[i].x - close_stars[i].x_vel;
        if( close_stars[i].x <= 0 )
            close_stars[i].x = SCREEN_WIDTH - (getrand() % 10);
    }

    //for( i = 0; i < num_stars; i++ ){
        //(stars + i)->x = rand() % SCREEN_WIDTH;
        //(stars + i)->x = (stars + i)->x + (stars + i)->x_vel;
        //(stars + i)->y = (stars + i)->y + (stars + i)->y_vel;

        /*
        if( (stars + i)->x >= (SCREEN_WIDTH / 2) ){
            // on the right half
            (stars + i)->x = (stars + i)->x + (stars + i)->x_vel;
        }else{
            // on the left half
            (stars + i)->x = (stars + i)->x - (stars + i)->x_vel;
        }

        if( (stars + i)->y >= (SCREEN_HEIGHT / 2) ){
            // on the bottom half
            (stars + i)->y = (stars + i)->y + (stars + i)->y_vel;
        }else{
            // on the top half
            (stars + i)->y = (stars + i)->y - (stars + i)->y_vel;
        }
        */

        //(stars + i)->x = (stars + i)->x - (stars + i)->x_vel;

        /*
        if( (stars + i)->x <= 0 ) 
            (stars + i)->x = 0;

        if( (stars + i)->y <= 0 ) 
            (stars + i)->y = 0;
        */

        //(stars + i)->x = (stars + i)->x % SCREEN_WIDTH;
        //(stars + i)->y = (stars + i)->y % SCREEN_HEIGHT;

        //if( (stars + i)->x <= 0 ){
            //(stars + i)->x = (SCREEN_WIDTH / 2) - 1;
            //(stars + i)->x = cont->x + (rand() % cont->w);
            //(stars + i)->y = cont->y + (rand() % cont->h);
            //(stars + i)->x = (SCREEN_WIDTH / 2 - 10) + (rand() % (100));
            //(stars + i)->y = (SCREEN_HEIGHT / 2 - 10) + (rand() % (100));
            //(stars + i)->y = (SCREEN_HEIGHT / 2);
            //(stars + i)->x = ((SCREEN_WIDTH / 2) - (getrand() % 160)) + (getrand() % (160));
            //(stars + i)->y = ((SCREEN_HEIGHT / 2) - (getrand() % 160)) + (getrand() % (160));
        //}

        //if( (stars + i)->y <= 0 ){
            //(stars + i)->x = cont->x + (rand() % cont->w);
            //(stars + i)->y = cont->y + (rand() % cont->h);
            //(stars + i)->x = (SCREEN_WIDTH / 2 - 10) + (rand() % (100));
            //(stars + i)->y = (SCREEN_HEIGHT / 2 - 10) + (rand() % (100));
            //(stars + i)->y = (SCREEN_HEIGHT / 2) - 1;
            //(stars + i)->x = (SCREEN_WIDTH / 2);
            //(stars + i)->x = ((SCREEN_WIDTH / 2) - (getrand() % 160)) + (getrand() % (160));
            //(stars + i)->y = ((SCREEN_HEIGHT / 2) - (getrand() % 160)) + (getrand() % (160));
        //}

        //if( (stars + i)->x + (stars + i)->size >= SCREEN_WIDTH){
            //(stars + i)->x = cont->x + (rand() % cont->w);
            //(stars + i)->y = cont->y + (rand() % cont->h);
            //(stars + i)->x = cont->x;
            //(stars + i)->x = (SCREEN_WIDTH / 2) + 1;
            //(stars + i)->y = (SCREEN_HEIGHT / 2);
            //(stars + i)->x = (SCREEN_WIDTH / 2 - 10) + (rand() % (100));
            //(stars + i)->y = (SCREEN_HEIGHT / 2 - 10) + (rand() % (100));
            //(stars + i)->x = ((SCREEN_WIDTH / 2) - (getrand() % 160)) + (getrand() % (160));
            //(stars + i)->y = ((SCREEN_HEIGHT / 2) - (getrand() % 160)) + (getrand() % (160));
        //}

        //if( (stars + i)->y + (stars + i)->size >= SCREEN_HEIGHT){
            //(stars + i)->y = cont->y + (rand() % cont->h);
            //(stars + i)->x = cont->x + (rand() % cont->w);
            //(stars + i)->y = cont->y;
            //(stars + i)->y = (SCREEN_HEIGHT / 2) + 1;
            //(stars + i)->x = (SCREEN_WIDTH / 2);
            //(stars + i)->x = (SCREEN_WIDTH / 2 - 10) + (rand() % (100));
            //(stars + i)->y = (SCREEN_HEIGHT / 2 - 10) + (rand() % (100));
            //(stars + i)->x = ((SCREEN_WIDTH / 2) - (getrand() % 160)) + (getrand() % (160));
            //(stars + i)->y = ((SCREEN_HEIGHT / 2) - (getrand() % 160)) + (getrand() % (160));
        //}

        //printf("X = %d, Y = %d\n", (stars + i)->x, (stars + i)->y);

        for(j=0;j<far_stars.size();j++){
                star_t tmp = far_stars.at(j);
                printf("X %d\n", tmp.x);
                putpixel(screen, tmp.x, tmp.y, tmp.color);
        }
        for(j=0;j<mid_stars.size();j++){
                star_t tmp = mid_stars.at(j);
                //printf("X %d\n", tmp.x);
                putpixel(screen, tmp.x, tmp.y, tmp.color);
        }
        for(i=0;i<close_stars.size();i++){
            star_t tmp = close_stars.at(i);
            for(j=0;j<tmp.h;j++){
                for(k=0;k<tmp.w;k++){
                    //star_t tmp = close_stars.at(j);
                    //printf("X %d\n", tmp.x);
                    putpixel(screen, tmp.x + k, tmp.y + j, tmp.color);
                }
            }
        }
        //stars[ i ].y = rand() % SCREEN_HEIGHT;
        //stars[ i ].x_vel = 1;
        //stars[ i ].y_vel = 1;
        //stars[ i ].color = SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF );
    //}

    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }  
}
