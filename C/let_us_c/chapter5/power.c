#include <stdio.h>

int power(int, int);

int 
main(int argc, char *argv[])
{
    int i = 5;
    printf("\n2 raised to power %d is %d\n", i, power(2, 5));
    return 0;
}

int
power(int m, int e)
{
    if(e == 0)
        return 1;
    return (m * power(m, (e - 1)));
}
