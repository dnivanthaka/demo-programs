#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <signal.h>
#include <sys/time.h>
//#include <pthread.h>

#include "utils.h"

static int max_x = 0, max_y = 0;
static int fl_alarm = 0;

static int x_val = 0;
static int y_val = 0;

void sigalarm_handler();
void sigint_handler();

int
main(int argc, char *argv[])
{
    //int res;
    //pthread_t a_thread;
    //pid_t pid;
    struct itimerval delay;

    delay.it_value.tv_sec = 0;
    delay.it_value.tv_usec = 40000;
    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_usec = 40000;

    /*
        Setting up signal handlers
    */
    (void) signal(SIGALRM, sigalarm_handler);
    (void) signal(SIGINT, sigint_handler);

    /* Initialize window */
    initscr();
    // Set color mode
    if(has_colors()){
        start_color();

        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_GREEN);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
    }else{
        endwin();
        fprintf(stderr, "Error, No color support\n");
        exit(1);
    }
    // Switch to keyboard raw mode
    cbreak();
    // Do not print keyboard input
    noecho();
    // Hide blinking cursor
    curs_set(0);
    // Clear the screen
    clear();
    // get screen dimensions
    getmaxyx(stdscr, max_y, max_x);

    refresh();
    // setting up the walls, scoreboard etc.
    setup_env(max_x, max_y);

    setitimer(ITIMER_REAL, &delay, 0);

    while(TRUE){
        //put_bug(15, 18);
        //res = pthread_create(&a_thread, NULL, put_bug, );
        //res = pthread_create(&a_thread, NULL, thread_function, "Hello");
        //put_bug(10, 10);
        //pid = fork();
        //if(pid == 0){
            // This is the child
            //put_bug(15, 15);
        //}else{
            //put_bug(10 ,10);
        //}
        /*
        if(res != 0){
            endwin();
            perror("Thread creation failed");
            exit(1);
        }
        */
        pause();
    }

    // end curses session
    endwin();

    return 0;
}

void
sigalarm_handler()
{
    //fl_alarm = 1;
    put_bug(10 + (++y_val) ,10);
    put_bug(15 + (y_val) ,12);
    put_bug(18 + (y_val) ,14);

}

void
sigint_handler()
{
    (void) signal(SIGALRM, SIG_DFL);
    (void) signal(SIGINT, SIG_DFL);
    endwin();
    exit(1);
}
