#include <cstdlib>

#include "g_rand.h"

static int seed = 0;

static void 
init_rand()
{
    seed = time(NULL);
}

static unsigned int 
getrand()
{
    int p1 = 1103515245;
    int p2 = 12345;
    seed = (seed*p1+p2) % 2147483647;
    return (unsigned)seed/3;
}
