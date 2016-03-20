#include <stdio.h>

int main(int argc, char ** argv){
	int i = 0, j = 0;
	char input[256];

	printf("Enter number of loops to run : ");
	if(fgets(input, 255, stdin)){
		for(j=0;j<sizeof(input);j++){
			printf("j = %d\n",j);
		}
	}
	return 0;
}
