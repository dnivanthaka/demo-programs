#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

static int cur_pos_x = 0;
static int cur_pos_y = 0;
static int max_x, max_y;

void move_left();
void move_right();
void move_up();
void move_down();

int
main(int argc, char *argv[])
{
    int key;

    getmaxyx(stdscr, max_y, max_x);

    initscr();
    crmode();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    move(7, 5);
    refresh();
    key = getch();

    //cur_pos_x = 7;
    //cur_pos_y = 5;
    cur_pos_x = 5;
    cur_pos_y = 7;

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

        refresh();
        key = getch();
    }

    endwin();
    return 0;
}

void
move_left()
{
    if(cur_pos_x > 0){
        //printw("Im at left");
        cur_pos_x--;
        //move(cur_pos_x, cur_pos_y);
        move(cur_pos_y, cur_pos_x);
    }
}

void
move_right()
{
    if(cur_pos_x < max_x){
        //printw("Im at right");
        cur_pos_x++;
        //move(cur_pos_x, cur_pos_y);
        move(cur_pos_y, cur_pos_x);
    }
}

void
move_up(){
    if(cur_pos_y > 0){
        //printw("Im at right");
        cur_pos_y--;
        //move(cur_pos_x, cur_pos_y);
        move(cur_pos_y, cur_pos_x);
    }
}

void
move_down(){
    if(cur_pos_y < max_y){
        //printw("Im at right");
        cur_pos_y++;
        //move(cur_pos_x, cur_pos_y);
        move(cur_pos_y, cur_pos_x);
    }
}
