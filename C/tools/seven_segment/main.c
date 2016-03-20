#include <stdio.h>

void print_char(char ch, int pat_code);

int 
main(int argc, char *argv[])
{
    char h_line = '-';
    char v_line = '|';

    // 0xF, 0x9, 0x9, 0xF, 0x9, 0x9, 0xF

    //printf("+----+\n" );
    //printf("|    |\n" );
    //printf("|    |\n" );
    //printf("+----+\n" );
    //printf("|    |\n" );
    //printf("|    |\n" );
    //printf("+----+\n" );

    printf(" ---- \n" );
    printf("|    |\n" );
    printf("|    |\n" );
    printf(" ---- \n" );
    printf("|    |\n" );
    printf("|    |\n" );
    printf(" ---- \n" );

    print_char(h_line, 0xF);
    print_char(h_line, 0xA);
    print_char(h_line, 0x1);
    print_char(h_line, 0x5);
    print_char(h_line, 0x9);
    return 0;
}

void 
print_char(char ch, int pat_code)
{
    int i, k, res;

    for(i=0;i<4;i++){
        k = 8 >> i;

        if( (res = pat_code - k) >= 0 ){
            printf("1");
            pat_code = res;
        }else{
            printf("0");
        }
    }
    printf("\n");
}
