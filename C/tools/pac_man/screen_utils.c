#include <stdio.h>
#include <curses.h>

#include "screen_utils.h"

void
print_at_alt(int x, int y, char *str)
{
    printf("\033[%d;%dH%s", y, x, str);
    /*
    char buffer[50];
    int out_len = 0;

    out_len = sprintf(buffer, "\033[%d;%dH%s", y, x, str);
    if(out_len > 50){
        fprintf(stderr, "Yikes! buffer overflowed by %d characters\n", out_len - 49);
    }else{
        //printf(buffer);
        printf("\033[%d;%dH%s", y, x, str);
    }
    */
}

void
print_at(int x, int y, char *str)
{
    move(y, x);
    refresh();
    printw("%s", str);
}
