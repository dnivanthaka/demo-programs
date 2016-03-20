#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[]){
    int **ptr;
    int p[] = {2, 5, 7, 9};
    int i;

    for(i=0;i<5;i++){
        *(ptr + i) = malloc(sizeof(int) * 5);
        //*(ptr + i) = {2, 3, 5, 7};
        *(ptr + i) = (int *)&p;
    }

    printf("ptr = %d\n", ptr + 1);

    return 0;
}
