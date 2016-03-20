#include <stdio.h>

#include "types.h"
#include "process.h"

int
main(int argc, char *argv[])
{
    //new_process("p1.psr");

    printf("size of byte = %d\n", (int)sizeof(BYTE));
    printf("size of word = %d\n", (int)sizeof(WORD));
    printf("size of dword = %d\n", (int)sizeof(DWORD));

    return 0;
}
