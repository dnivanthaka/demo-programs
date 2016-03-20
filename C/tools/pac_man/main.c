#include <stdio.h>
#include <signal.h>
#include <curses.h>

#include "keyb_utils.h"
#include "screen_utils.h"

static int alarm_fired = 0;

int 
main(int argc, char *argv[])
{
    int key;

    initscr();
    clear();
    cbreak();
    //printf("\033[2J");
    //printf("\033[H");
    //printf("\033[30;20Hhello world");
    //printf("It works");
    //keyb_raw(stdin);
    //printf("Type any key except for q\n");
    //print_at(20, 30, "Type any key except for q\n");
    //do{
        //key = fgetc(stdin);
        key = getch();
        printf("key = %c\n", key);
        printf("key code = %d\n", key);
        if(key == KEY_LEFT){
            printf("You pressed up arrow key\n");
        }
        getch();
     nocbreak();
     endwin();
    //}while(key != 'q');
    //}while(key != KEY_CANCEL);

    //keyb_restore(stdin);

    return 0;
}

void
sigint_handle(int sig)
{
    keyb_restore(stdin);
    print_at(0, 0, "");
}

/* when a stop signal arrives, set the action back to default
   and then resend the signal after doing clean up operations
*/
void
sigtstp_handle(int sig)
{
    struct sigaction act;

    act.sa_handler = SIG_DFL;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    keyb_restore(stdin);
    // freeze screen
    // freeze_scr();
    sigaction(SIGTSTP, &act, 0);
}

void
sigcont_handle(int sig)
{
    signal(SIGCONT, sigcont_handle);
    signal(SIGTSTP, sigtstp_handle);
    keyb_raw(stdin);
}

void
sigalrm_handle(int sig)
{
    alarm_fired = 1;
}
