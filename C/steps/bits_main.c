#include <stdio.h>

#include "bits.h"

int
main(int argc, char *argv[])
{
    printf("6 and 5 = %d\n", bitAND(6, 5));
    printf("6 and 5 = %d\n", bitXOR(4, 5));
    printf("6 and 5 = %d\n", isEqual(7, 7));
    return 0;
}
