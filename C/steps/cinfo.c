/*
 *  Compile this as gcc -o cinfo -DDEBUG cinfo.c
 */
#include <stdio.h>

int main()
{
#ifdef DEBUG
    printf("Compiled: "__DATE__" at "__TIME__"\n");
    printf("This is line %d of file %s\n", __LINE__, __FILE__);
#endif
    printf("Hello World\n");
    return 0;
}
