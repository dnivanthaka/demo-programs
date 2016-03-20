#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <pthread.h>

#include "utils.h"

#define WALL_CHAR 0x23 

void
setup_env(int max_x, int max_y)
{
    int i;
    //printw("max_x = %d, max_y = %d\n", max_x, max_y);
    /*
    move(6, 6);
    attrset(COLOR_PAIR(1));
    printw("@@@");
    move(6, 10);
    attrset(COLOR_PAIR(1) | A_BOLD);
    printw("AAAA");
    refresh();
    */
    
    // Drawing top and bottom
    for(i = 0; i < max_x;i++){
        move(0, i);
        attrset(COLOR_PAIR(1));
        printw("%c", WALL_CHAR);
        // attroff()
        // Printing scorebar serperator
        attrset(COLOR_PAIR(1));
        move(max_y-5, i);
        printw("%c", WALL_CHAR);

        attrset(COLOR_PAIR(1));
        move(max_y-1, i);
        printw("%c", WALL_CHAR);
    }
    refresh();

    // Drawing left and right
    for(i = 0; i < max_y;i++){
        move(i, 0);
        attrset(COLOR_PAIR(1));
        printw("%c", WALL_CHAR);
        // attroff()
        attrset(COLOR_PAIR(1));
        move(i, max_x-1);
        printw("%c", WALL_CHAR);
    }
    
    refresh();
}

void
put_bug(int x, int y)
{
    int i, cur_x, cur_y;
    //int tmp;

    move(y, x);
    cur_x = x;
    cur_y = y;
    attrset(COLOR_PAIR(3) | A_BOLD);
    printw("%c", '@');
    refresh();
    //clear();
}

int
get_rand(int max)
{
    srand( (unsigned)time(NULL) );
    return ((1 + rand()) % max);
}

void *
thread_function(void *arg)
{
    //put_bug(15, 12);
    move(10, 15);
    printw("Thread function running. Argument was %s\n", (char *)arg);
    refresh();
    //sleep(3);
    pthread_exit("Bye");
}
