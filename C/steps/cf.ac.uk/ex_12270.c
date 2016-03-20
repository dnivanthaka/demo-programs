#include <stdio.h>

int calc_sum(int, int);
int calc_avg(int, int);
int calc_sqr_sum(int, int);

int main(int argc, char *argv[])
{
    int tmp, param1, param2;

    if( argc < 3 )
    {
        printf("\tUsage {program} param1 param2");
        return 1;
    }

    param1 = atoi(argv[1]);
    param2 = atoi(argv[2]);

    tmp = calc_sum(param1, param2);
    printf("\n Sum of the two numbers = %d\n", tmp);

    tmp = calc_avg(param1, param2);
    printf(" Average of the two numbers = %d\n", tmp);

    tmp = calc_sqr_sum(param1, param2);
    printf(" Sum of the sqaures of each number = %d\n", tmp);

    return 0;
}

int calc_sum(int x, int y)
{
    return (x + y);
}

int calc_avg(int x, int y)
{
    return (int)( (x + y) / 2 );
}

int calc_sqr_sum(int x, int y)
{
    return (int)( (x * x) + (y * y) );
}
