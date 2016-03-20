#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    printf("\t Number \t\t Square of Number\n\n");

    for(i=0;i<=25;++i)
    {
        printf("\t %d \t\t\t %d \n", i, i * i);
    }

    return 0;
}
