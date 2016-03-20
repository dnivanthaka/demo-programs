#include <stdio.h>

void
print_at(int x, int y, char *str)
{
    printf("\033[%d;%dH%s", y, x, str);
}
