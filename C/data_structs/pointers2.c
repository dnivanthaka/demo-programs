#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int i = 5;
	int *j;
	int **k;

	j = &i;
	k = &j;

	printf("\nAddress of i = %p", &i);
	printf("\nAddress of i = %p", j);
	printf("\nAddress of i = %p", *k);
	printf("\nAddress of j = %p", &j);
	printf("\nAddress of j = %p", k);
	printf("\nAddress of k = %p", &k);

	return 0;
}
