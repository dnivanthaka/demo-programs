#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>

static int cur_pos_x = 0;
static int cur_pos_y = 0;
static int max_x, max_y;
static alarm_flag = 0;

void print_at(int, int, char *);
void alarm_handler();

int
main(int argc, char *argv[])
{
    int key;
    struct itimerval delay;

    signal(SIGALRM, alarm_handler);

    delay.it_value.tv_sec = 0;
    delay.it_value.tv_usec = 40000;
    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_usec = 40000;

    setitimer(ITIMER_REAL, &delay, NULL);
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
        //while((key = getch()) !=  'q' ){
        while(true){
            if(alarm_flag == 1){
                move(--max_y, --max_x);
                printw("@");
                refresh();
                clear();
                sleep(1);
                alarm_flag = 0;
            }
            pause();
            //refresh();
        }
    
    endwin();
    return 0;
}

void
alarm_handler()
{
    alarm_flag = 1;
}

