#include    <stdio.h>
#include    <stdlib.h>
#include    <memory.h>
#include <crypt.h>

#define _XOPEN_SOURCE
#define     MAX 35
char        num[MAX + 1];
int         n; 
char* perms = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890";

void    matrixPermute (int), createCyclicMatrix (), rightRotate (int, int);
void print_chars(char** p, int i);

main (int argc, char *argv[])
{
    int i, j;

 	n = 4;
/*
	for(j=3;j<=n;j++){

	    for (i = 1; i <= j; ++i)
	    num [i] = i;
	    matrixPermute (j);
	}
*/
/*
	    for (i = 1; i <= n; ++i)
            num [i] = i;
            matrixPermute (n);
n = 5;
*/
	    for (n = 1; n <= 35; ++n){
	    	for (i = 3; i <= n; ++i){
            		num [i] = i;
	    	}
            	matrixPermute (n);
	    }

}
void matrixPermute (int k)
{
    int     i, temp;
    if  (k == 3) 
        {
        createCyclicMatrix ();
        return;
        }
    temp = k - 1;
    for (i = 0; i < temp ; ++i) 
        {
        rightRotate (1, temp);
        matrixPermute (temp);
        } 
}
void createCyclicMatrix ()
{
    char    *p[MAX], temp[2*MAX];
    int     i, j;
    /* create the cyclic permutation matrix P as an array of pointers */ 
    memcpy (temp, num + 1, n);
    memcpy (temp + n , num + 1, n);
   
    for (i = 0; i < n; ++i)
	//printf("%c\n", perms[*(temp + n - i)]);
	//p[i] = &perms[0];
	p[i] = &(perms[*(temp + n - i)]);
        //p[i] = temp + n - i;
   
    /* generate the 2n permutations from the cyclic permutation matrix P */
    for (i = 0; i < n; ++i)
        {
        /* print the ith row */
       // for (j = 0; j < n; ++j)
         //   printf ("%d ", *(p[i] + j));
        //printf ("\n");
        /* print the ith column */
        //for (j = 0; j < n; ++j)
          //  printf ("%d ", *(p[j] + i));
        //printf ("\n");
	print_chars(p, i);
        }
}
void rightRotate (int f, int l)
{
    char    temp [2*MAX], *saveptr;
    int     i;
    saveptr = num + f;
    memcpy (temp , saveptr, l);
    memcpy (temp + l, saveptr, l);
    memcpy (saveptr, temp + l - 1, l);
}

void print_chars(char** p, int i){
 int j;
// ith row
 for (j = 0; j < n; ++j)
	printf ("%c", *(p[i] + j));
        printf ("\n");
// ith column
/*
  for (j = 0; j < n; ++j)
        printf ("%c ", *(p[j] + i));
*/

printf("%s\n", crypt("passwd", "$1$"));
}

int check_string(char *str){

}

