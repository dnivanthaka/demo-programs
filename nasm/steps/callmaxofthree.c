/*
 * callmaxthree.c
 *
 * calls the assembly routine in maxofthree
 *
 */

#include <stdio.h>

int maxofthree(int, int, int);

int main(){
	printf( "%d\n", maxofthree(1, -4, -7) );
	printf( "%d\n", maxofthree(2, -6, 1) );
	printf( "%d\n", maxofthree(2, 3, 1) );
	printf( "%d\n", maxofthree(-2, 4, 3) );
	printf( "%d\n", maxofthree(2, -6, 5) );

	return 0;

}
