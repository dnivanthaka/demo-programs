#include <stdio.h>

#define BOUNDRY_INT 24
#define BOUNDRY_FRAC 8

typedef union {
    struct {
        int signi          : BOUNDRY_INT;
        unsigned int expon : BOUNDRY_FRAC;
    } part;
} fixed_t;

fixed_t itofix( int );

int
main( int argc, char *argv[] )
{
    unsigned char a, b, c;
    fixed_t i;
    //a = 14.75 * ( 1 << 2 );
    //printf("a = %d\n",(1 << 2));
    //printf("a = %d\n",a);
    //printf("a = %f\n", (float)a / (1 << 2));
    i = itofix( 5 );
    printf("%d\n", 2 << BOUNDRY_FRAC - 1);
    printf("int = %d\n", i.part.signi);
    printf("frac = %d\n", i.part.expon);
    fixtoi( i );

    return 0;
}

fixed_t
itofix( int x )
{
    fixed_t ret;
    ret.part.signi = x;
    ret.part.expon = 0;

    return ret;
}

int
fixtoi( fixed_t x )
{
    int ret, rem = 0;

    ret = x.part.signi;
    rem = (( x.part.expon >= ( (2 << (BOUNDRY_FRAC - 1) ) / 2) ) ? 1 : 0);
    ret += rem;
    //printf("%d\n", ret);
    //printf("%d\n", ( x.part.expon >= ( (2 << (BOUNDRY_FRAC - 1) ) / 2) ) ? 1 : 0);

    return ret;
}
