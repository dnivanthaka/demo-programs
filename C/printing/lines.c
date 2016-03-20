/*
 * =====================================================================================
 *
 *       Filename:  lines.c
 *
 *    Description:  prints lines
 *
 *        Version:  1.0
 *        Created:  08/14/2012 11:26:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdio.h>

int main(int argc,char *argv[]){
    int i;

    printf("Line printing Demo\n");

    for(i=0;i<25;i++){
        //printf("%-5d", i);
        //printf("2\b");
        //printf("\b");
       // printf("\r");
        fprintf(stdout, "Test : %d\r", i);
        fflush(stdout);
        sleep(1);
    }

    printf("\n");
    
    return 0;
}
