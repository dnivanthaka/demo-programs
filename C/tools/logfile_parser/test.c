#include <stdio.h>

int 
main(int argc, char *argv[])
{
    char i = 'A';
    char *j = "This is a string";
    char *ptr;
    int x;

    ptr = &i;
    x = i;

    printf("%c\n", i);
    printf("%d\n", i);
    printf("%d\n", *ptr);
    printf("%d\n", *(j + 1));
    printf("%d\n", x);
    printf("%c\n", *++j);
    printf("%c\n", *j++);
    printf("%c\n", *(j+1));
    return 0;
}

int
chpos(char *str, char *needle){
    //while(){}
}
