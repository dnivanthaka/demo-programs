#include <stdio.h>

void print_chars(void *, int);
int strlen(char *);

int 
main(int argc, char *argv[])
{
    char *str = "My name is Dinusha";

    printf("%s\n", str);
    //printf("Size = %d\n", (int)sizeof(str));
    printf("Size = %d\n", strlen(str));

    print_chars(str, strlen(str));

    return 0;
}

void
print_chars(void *str, int size)
{
    int i;

    for(i=0;i<size;i++)
     {
        printf("%c ", *(char *)(str + i));
     }
}

int
strlen(char *str)
{
    int len = 0;

    while(*str++ != '\0')
        len++;
    return len;
}
