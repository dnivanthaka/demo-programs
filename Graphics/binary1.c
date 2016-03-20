// ex1.c
//
#include <stdio.h>


void PrintBinary(int x,int d)
{
	char buffer[33];
	int index=0;
	for (;d>0;d--)
		{
		buffer[index++] = '0'+ (x & 1);
		x >>= 1;
		}
  while (index >0 )
    printf("%c",buffer[--index]);

  printf("B\n");
  return;
}

void print_binary2( int x )
{
    int i = 0, j;

    j = 16;

    while( i++ < 5 ){
        if( x & j ){
            printf("1");
        }else{
            printf("0");
        }

        j = j >> 1;
        //printf("j = %d ", j);
    }

    printf("\n");
}

int main(int argc, char* argv[])
{
	PrintBinary(10,6);
	PrintBinary(8,4);
	PrintBinary(32765,16);
    print_binary2( 9 );
	return 0;
}

