/*
 * =====================================================================================
 *
 *       Filename:  screen_utils.c
 *
 *    Description:  Screen Utils
 *
 *        Version:  1.0
 *        Created:  02/20/2012 09:57:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdio.h>

#include "screen_utils.h"

void
screen_print( int x, int y, char *str )
{
    printf("\033[%d;%dH%s", (y + 1), (x + 1), str);
    fflush(stdout);
}

void
screen_print_char( int x, int y, char chr )
{
    printf("\033[%d;%dH%c", (y + 1), (x + 1), chr);
    fflush(stdout);
}

void
screen_clear()
{
    printf("\033[2J");
}

void
screen_cur_reset()
{
    printf("\033[H");
}

void
screen_enable_echo()
{
    printf("\033[?25h");
}

void
screen_disable_echo()
{
    printf("\033[?25l");
}
