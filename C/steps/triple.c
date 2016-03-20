/*
 * triple.c
 *
 * This program writes a list of all pythagorian triples whose elements are
 * in the range 1..100
 *
 */

#include <stdio.h>

int main(){
	int a, b, c;
	printf("        A       B       C\n");
	printf("----------------------------\n");
	for(c=1;c<=100;c++){
		for(b=1;b<=100;b++){
			for(a=1;a<=100;a++){
				if( a * a + b * b == c * c ){
					printf( "%6d%6d%6d\n", a, b, c );
				}
			}
		}
	}

	return 0;
}
