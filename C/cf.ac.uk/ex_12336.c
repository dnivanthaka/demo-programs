#include <stdio.h>

int 
main(int argc, char *argv[])
{
    char ch;

    while( ch = getchar(), ch >= 0 ){
        printf("%c\n", ch);
    }

    return 0;
}
