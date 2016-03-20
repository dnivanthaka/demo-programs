#include <stdio.h>
#include <stdlib.h>

void show_val(int *i){
	printf( "value = %d\n", *i );
}

void change_val(int **i){
	int *j;
	int k = 10;

	//if(*i == NULL){
		//printf("Im here\n");
		j = malloc( sizeof(int) );
		//*j = 10;
		j = &k;
		i = &j;
	//}
}

int main(int argc, char ** argv){
	int i = 5;
	int *j = NULL;
	//j = &i;
	//printf( "value of j = %d\n", *j );
	//show_val( j );
	change_val(&j);
	printf( "value of j = %d\n", *j );
	return 0;
}
