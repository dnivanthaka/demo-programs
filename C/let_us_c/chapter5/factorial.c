#include <stdio.h>
#include <stdlib.h>

int factorial(int);

int 
main(int argc, char *argv[])
{
    int user_input;
    int result;

    if(argc < 2){
        printf("Enter a number to find the factorial : ");
        scanf("%d", &user_input);
        //printf("\n");
    }
    else
    {
        user_input = atoi(argv[1]);
    }

    result = factorial(user_input);
    printf("\nFactorial of %d is %d\n", user_input, result);
    return 0;
}

int 
factorial(int i)
{
    if(i == 0 || i == 1)
        return 1;
    return ( i * factorial(i - 1) );
}
