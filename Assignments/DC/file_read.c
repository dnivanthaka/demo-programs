/*
 * =====================================================================================
 *
 *       Filename:  file_read.c
 *
 *    Description:  Reads the riddle file
 *
 *        Version:  1.0
 *        Created:  02/06/2012 11:10:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

#define DELIMITER #
#define BUFFER_SIZE 255

int 
main(int argc, char *argv[])
{
    FILE *fp;
    char *file = "riddles.txt";

    fp = fopen( file, "r" );

    return 0;
}

int
get_riddle_count( FILE *fp )
{
    int ret = 0;
    char buff[BUFFER_SIZE];
    
    while( fgets( buff, BUFFER_SIZE, fp ) != NULL ){
        //buff[ strlen(buff) - 1 ] = '\0'; 
        ret++;
    }

    fseek(fp, 0, SEEK_SET);

    return ret;
}

void
get_riddle( FILE *fp, int num, char *buff )
{
    int ret = 0;
    //char buff[BUFFER_SIZE];
    
    while( ret < num && fgets( buff, BUFFER_SIZE, fp ) != NULL ){
        buff[ strlen(buff) - 1 ] = '\0'; 
        ret++;
    }

    fseek(fp, 0, SEEK_SET);
}

void
write_riddle( char *buff, int fd )
{

}
