#include <stdio.h>

char roman_thousands(int);

int
main(int argc, char *argv[])
{
    char *str;
    int i;
    int year = 2011;
    int thousands = 0, 
    fivehundreds = 0, 
    hundreds = 0, 
    fifties = 0, 
    tens = 0, 
    fives = 0, 
    ones = 0;
    int tmp = 0;

    //tmp = 2550;

    //str = roman_thousands(2005);
    thousands = ((int)(year/1000) > 0) ? (int)(year/1000) : 0;
    tmp = tmp + (thousands * 1000);
    //printf("\n*** tmp = %d\n", tmp);

    fivehundreds = ( ((int)(year - tmp)/500) > 0 ) ? 
        (int)(year - tmp)/500 : 0;
    tmp = tmp + (fivehundreds * 500);
    //printf("\n*** tmp = %d\n", tmp);

    hundreds = ( ((int)(year - tmp)/100) > 0 ) ?
        (int)(year - tmp)/100 : 0;
    tmp = tmp + (hundreds * 100);
    //printf("\n*** tmp = %d\n", tmp);

    fifties = ( (int)(year - tmp)/50 > 0 ) ?
        (int)(year - tmp)/50 : 0;
    tmp = tmp + (fifties * 50);
    //printf("\n*** tmp = %d\n", tmp);

    tens = ( (int)(year - tmp)/10 > 0 ) ?
        (int)(year - tmp)/10 : 0;
    tmp = tmp + (tens * 10);
    //printf("\n*** tmp = %d\n", tmp);

    fives = ( (int)(year - tmp)/5 > 0 ) ?
        (int)(year - tmp)/5 : 0;
    tmp = tmp + (fives * 5);
    //printf("\n*** tmp = %d\n", tmp);

    ones = year - tmp;

    //printf("\n2005 = %s\n", str);
    //printf("\n2005 = %d\n", thousands);
    //printf("\n2005 = %d\n", fivehundreds);
    //printf("\n2005 = %d\n", hundreds);
    //printf("\n2005 = %d\n", fifties);
    //printf("\n2005 = %d\n", tens);
    //printf("\n2005 = %d\n", fives);
    //printf("\n2005 = %d\n", ones);
    //printing the thousands
    for(i=0;i<thousands;i++)
        printf("M");
    //printing the fivehundreds 
    for(i=0;i<fivehundreds;i++)
        printf("D");
    //printing the hundreds 
    for(i=0;i<hundreds;i++)
        printf("C");
    //printing the fifties 
    for(i=0;i<fifties;i++)
        printf("L");
    //printing the tens 
    for(i=0;i<tens;i++)
        printf("X");
    //printing the ones 
    for(i=0;i<ones;i++)
        printf("I");
    printf("\n");

    return 0;
}

char
roman_thousands(int year)
{
    if(year < 1000)
        return '\0';
    return 'm' + roman_thousands(year/1000);
}
