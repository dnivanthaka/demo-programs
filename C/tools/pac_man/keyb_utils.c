#include <stdio.h>
#include <termios.h>

struct termios initial_settings;

void
keyb_raw(FILE *input)
{
    struct termios new_settings;

    // save old settings first
    tcgetattr(fileno(input), &initial_settings);

    new_settings = initial_settings;
    new_settings.c_lflag     &= ~ICANON;
    new_settings.c_lflag     &= ~ECHO;
    new_settings.c_cc[VMIN]  = 1;
    new_settings.c_cc[VTIME] = 0;

    if(tcsetattr(fileno(input), TCSANOW, &new_settings) != 0)
        fprintf(stderr, "Could not switch input mode\n");
}

void
keyb_restore(FILE *input)
{

    if(tcsetattr(fileno(input), TCSANOW, &initial_settings) != 0)
        fprintf(stderr, "Could not restore input mode\n");
}
