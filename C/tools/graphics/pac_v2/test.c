#include <stdio.h>

int 
main(int argc, char *argv[])
{
    int i[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int **j;
    int (*k)[3];
    int *l;
    //char *p = "wwwwwwwwwwwwwwwwwwwwwwwwwwwww";

    l = (int *)i;
    j = (int **)i;
    //l = i;
    //l = &i[0][0];
    //j = &i[0];
    //k = &i[0];

    printf("i[0][0] = %d\n", i[0][0]);
    printf("i[0][1] = %d\n", i[0][1]);
    printf("i[0][2] = %d\n", i[0][2]);

    printf("l = %d\n", *((l + 1 * 3)+1));
    //printf("j = %d\n", **((j + 1 * 3)+1));
    //printf("j = %d\n", **(j + 1 * 3));

    return 0;
}
