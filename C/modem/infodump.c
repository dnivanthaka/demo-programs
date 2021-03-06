/*
 * =====================================================================================
 *
 *       Filename:  infodump.c
 *
 *    Description:  Interrogates a modem to get device information
 *
 *        Version:  1.0
 *        Created:  10/06/2014 10:23:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

int init_modem(int *fd, char *device);
int send_at_command(int *fd, char *cmd);
int read_result(int *fd);
int read_line(int *fd, char *buff);
int is_last_result(char *line);

//char *buff;
char buff[512];

int main(int argc, char argv[])
{
    int fd;
    char *modem = "/dev/ttyUSB_utps_modem";

    //buff = malloc(sizeof(char) * 512);

    init_modem( &fd, modem );
    send_at_command( &fd, "I" );
    read_result( &fd );
    send_at_command( &fd, "+CSQ" );
    read_result( &fd );
    //free(buff);
    close(fd);

    return EXIT_SUCCESS;
}

int init_modem(int *fd, char *device)
{
    struct termios options;

    *fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);

    if( *fd < 0 ){
        printf("Error opening serial port\n");
        return -1;
    }

   memset(&options, 0, sizeof(struct termios)); 
   options.c_cflag = B115200 | CBAUDEX | CLOCAL | CREAD;
   options.c_iflag = IGNPAR;
   tcflush(*fd, TCIFLUSH);
   tcsetattr(*fd, TCSANOW, &options);

   // Resetting modem
   /*
   if( write(*fd, "ATZ\r", 4) < 4 ){
        printf("Write error\n");
        return -1;
   }
   read_result(fd);
   */
   send_at_command(fd, "Z");
   read_result(fd);

   return 0;
}

int send_at_command(int *fd, char *cmd)
{
    char line[128] = {0};

    strcat( line, "AT" );
    strcat( line, cmd );
    strcat( line, "\r" );

    int cmd_len = strlen(line);

    if( write( *fd, line, cmd_len ) < cmd_len ){
        printf("Error writing command\n");
        return -1;
    }


    return 0;
}

int read_result(int *fd)
{
    //char buff[512] = {0};
    //char line[256] = {0};
    //char *line = NULL;
    int idx = 0, bytes_read = 0;
    char ch;

    //line = malloc(sizeof(char) * 512);

    do{
        //read_line(fd, buff);     
        //printf("YYY %s\n", buff);
        bytes_read = read(*fd, &ch, 1);
        //printf("p = %c\n", ch);
        
        //buff[idx++] = 0;
        //buff[0] = 0;
        if( ch == '\r' || ch == '\n' ){
            buff[idx] = '\0';
            if( strlen(buff) > 0 ){
                //strncpy(line, buff, idx + 1);
                //strncpy(line, buff, 256);
                //strncpy(line, "OK", 256);
                //printf("res = %s\n", line);
                printf("= %s\n", buff);
            }
            //printf("%s\n", buff);
            idx = 0;
            //continue; 
        }else{
            buff[idx++] = ch;
        }
            //continue;
        
        //buff[idx] = '\0';
        //line = buff;

    }while( !is_last_result(buff) );
    //}while( !is_last_result(line) );
    //}while( bytes_read > 0 );
    //buff[idx] = '\0';

    //printf("%s\n", buff);
    
    //free(line);

    return 0;
}

int read_line(int *fd, char *buff)
{
    int bytes_read = 0, idx = 0;
    char ch;

    printf("XXX\n");
    /*
    while( (bytes_read = read(*fd, &ch, 1)) > 0 ){
        if( ch == '\r' || ch == '\n' )
            break;


        buff[idx++] = ch; 
    } */
    do{
        bytes_read = read(*fd, &ch, 1);
        printf("c = %c\n", ch);
        //if( ch == '\r' || ch == '\n' )
            //break;
        
        buff[idx++] = ch;

    }while( bytes_read > 0 );

    return 0;
}

int is_last_result(char *line)
{
    switch( line[0] ){
        case 'O':
            if(strcmp(line, "OK") == 0){
                return 1;
            }
        break;

        case 'E':
            if(strcmp(line, "ERROR") == 0){
                return 1;
            }
        break;

        default:
            return 0;
        break;
    }

    return 0;
}
