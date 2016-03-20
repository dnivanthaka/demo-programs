#include <stdio.h>

int print_array(void *, int);

int 
main(int argc, char *argv[])
{
    //int (*i_arr)[4];
    //(*i_arr)[0] = 2;

    int j[2] = {1, 3};
    //j[0] = 2;

    //printf("-------------------------");
    printf("\n%d\n",j[1]);

    print_array(&j, 2);
    return 0;
}

int
print_array(void *array, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        //going through the array
        printf("%d\n",*(((int *)array) + i));
    }
}

int
search_value_in_array(void *haystack, void *needle, int size)
{
   int i = 0;
   while(*((int *)haystack + i) != *needle){
        i++
   } 

   return i;
}
