/*
 * =====================================================================================
 *
 *       Filename:  keyb_utils.c
 *
 *    Description:  terminal handler
 *
 *        Version:  1.0
 *        Created:  02/20/2012 09:23:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <termios.h>
#include <stdlib.h>
#include <stdio.h>

#include "keyb_utils.h"

static struct termios org_termios;
static int ttyfd = 0;

int 
tty_reset()
{
    if( tcsetattr( ttyfd, TCSAFLUSH, &org_termios ) < 0 )
        return -1;

    return 0;
}

void
tty_raw()
{
    struct termios raw;

    tcgetattr( ttyfd, &org_termios );

    raw = org_termios;

    raw.c_lflag     &= ~ICANON;
    raw.c_lflag     &= ~ECHO;
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;

    if( tcsetattr( ttyfd, TCSANOW, &raw ) < 0 )
        fprintf( stderr, "Could not switch to raw mode\n" );
}

