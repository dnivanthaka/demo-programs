#include <malloc.h>
#include <stdlib.h>

#include "types.h"

BYTE *
get_memory(BYTE size)
{
    BYTE *m;

    m = malloc(sizeof(BYTE) * size);
    if(m == NULL){
        perror("malloc");
        exit(1);
    }

    return m;
}

void 
free_memory(BYTE *m)
{
    if(m != (BYTE *)NULL)
        free(m);
}
