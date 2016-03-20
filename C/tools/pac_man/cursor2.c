#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

static int cur_pos_x = 0;
static int cur_pos_y = 0;
static int max_x, max_y;

void print_at(int, int, char *);

int
main(int argc, char *argv[])
{
    int key;

    //getmaxyx(stdscr, max_y, max_x);

    initscr();   /* Initialize window */
    //crmode();
    cbreak();    /* switch to raw mode */
    //keypad(stdscr, TRUE);
    noecho();    /* Do not print characters typed on keyboard */
    clear();     /* Clears screen, puts cursor on 0, 0 */
    curs_set(0); /* Set cursor visibility 0 = no cursor */
    //move(7, 5);
    refresh();   /* Write to screen */
    getmaxyx(stdscr, max_y, max_x);
    //printw("x = %d\n", max_x);
    //printw("y = %d\n", max_y);
    //key = getch();

    //cur_pos_x = 7;
    //cur_pos_y = 5;
    cur_pos_x = 5;
    cur_pos_y = 7;
/*
    while(key != ERR && key != 'q'){
        clrtoeol();

        switch(key){
            case KEY_LEFT:
                move_left();
            break;
            case KEY_RIGHT:
                move_right();
            break;
            case KEY_UP:
                move_up();
            break;
            case KEY_DOWN:
                move_down();
            break;
            deafult:
                printw("Unmatched key - %d", key);
            break;
        }    
    }
*/
        //while((key = getch()) !=  'q' ){
        while(true){
            print_at(15,  7, "* * * * * * * * * * * * * * * * * * * * ");
            print_at(15,  8, "*                                     * ");
            print_at(15,  9, "*                                     * ");
            print_at(15, 10, "* * * * * * * * * * * * * * * * * * * * ");
            //refresh();
            sleep(1);
            print_at(15,   7, "***************************************");
            print_at(15,  10, "***************************************");
            refresh();
            sleep(1);
            //refresh();
        }
    
    endwin();
    return 0;
}

void
print_at(int x, int y, char *str)
{
    move(y, x);
    //refresh();
    printw("%s", str);
    refresh();
}
