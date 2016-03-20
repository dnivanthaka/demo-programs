#include <stdio.h>

void inc_val();
void add_val(int a, int b);

int
main(int argc, char *argv[])
{
    inc_val();
    add_val(5, 7);
    return 0;
}

void
inc_val()
{
    int a = 5;
    int b;
    __asm__ volatile(
        "movl %0, %%eax;"
        "inc %%eax;"
        "movl %%eax, %0;"
        :"=r" (b) /* output */
        :"r" (a)  /* input */
        :"%eax"   /* clobbered register */
    );

    printf("b = %d\n", b);
}

void
add_val(int a, int b)
{
    __asm__ volatile(
        "addl %%ebx,%%eax;"
        :"=a"(a)
        :"a"(a), "b"(b)
    );

    printf("Answer = %d\n", a);
}

