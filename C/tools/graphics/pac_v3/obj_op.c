#include <stdio.h>
#include "include/ghost.h"
#include "include/pac.h"

void move_ghost(struct ghost *);
void move_pac(struct pac *);
void screen_init();
void stop_echo();
void enable_echo();

int
main(int argc, char *argv[])
{
   struct ghost gst;
   struct pac p;

   gst.y = 30;
   gst.x = 20;

   p.y = 20;
   p.x = 20;

   screen_init();
   //while(1){
    //sleep(1);
    move_ghost( &gst );
    move_pac( &p );
    //sleep(100);
   //}

   return 0;
}


void
move_ghost(struct ghost *gst)
{
    printf("\033[%d;%dH@", gst->y, gst->x);
}

void
move_pac(struct pac *p)
{
    printf("\033[%d;%dHc", p->y, p->x);
}

void
screen_init()
{
    printf("\033[2J");
    printf("\033[H");
}

void
stop_echo()
{
    printf("\033[?25l");
}

void
enable_echo()
{
    printf("\033[?25h");
}
