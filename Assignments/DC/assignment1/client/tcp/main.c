/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  TCP Client
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe, nivanthaka@gmail.com
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#define PORT_NUM  3333
#define BACK_LOG  5
#define BUFF_SIZE 255

void
read_message( char *buff, int fd )
{
     int idx = 0, num_bytes = 0;
     while(1){
         num_bytes = recv( fd, &buff[idx], BUFF_SIZE, 0 );
         //buff[ idx + num_bytes ] = '\0';
         idx += num_bytes;
         if( strrchr(buff, '#') != NULL ){
             buff[ idx - 1 ] = '\0';
             break;
         }
     }
}

int
main( int argc, char *argv[] )
{
    int fd, ret, cli_fd, num_bytes;
    struct sockaddr_in svr;
    char buff[ BUFF_SIZE ];
    char op[10];
    char param1[1];
    char param2[2];

    memset( &svr, 0, sizeof(struct sockaddr_in) );

    svr.sin_family = AF_INET;
    svr.sin_port = htons( PORT_NUM );
    //inet_aton( "127.0.0.1", ( struct in_addr * )&svr.sin_addr.s_addr );
    //svr.sin_addr.s_addr = INADDR_ANY;
    inet_pton( AF_INET, "127.0.0.1", &svr.sin_addr );

    /*
     * For Client Side
     * socket()
     * connect()
     */

    fd = socket( AF_INET, SOCK_STREAM, 0 );
    if( fd == -1 ){
        perror("socket");
        return -1;
    }

    ret = connect( fd, (struct sockaddr *)&svr, 
    sizeof( struct sockaddr_in )  );

    if( ret == -1 ){
        perror("connect");
        close(fd);
        return -1;
    }else{
        printf("Connected to Server\n");
    }

    num_bytes = send( fd, "hello", strlen("hello"), 0 );
    num_bytes = recv( fd, buff, BUFF_SIZE, 0 );
    buff[ num_bytes ] = '\0';
    printf("Number of riddles: %s\n", buff);

    while(1){
        printf("Command: ");
        //scanf("%s", buff);
        fgets(buff, BUFF_SIZE, stdin );
        // kill the new line char
        buff[strlen(buff) - 1] = '\0';
        if( strcmp(buff, "bye") == 0 ){
            num_bytes = send( fd, "bye", strlen("bye"), 0 );
            close(fd);
            break;
        }else{
            num_bytes = send( fd, buff, strlen(buff), 0 );
            //num_bytes = recv( fd, buff, BUFF_SIZE, 0 );
            //buff[ num_bytes ] = '\0';
            read_message(buff, fd);
            printf("** Server Response **\n");
            printf("%s\n", buff);
            printf("** End Response **\n");
        }
        //num_bytes = send( fd, "" );
        fflush(stdin);
        num_bytes = 0;
        memset( buff, 0, BUFF_SIZE );
    }
    //write( fd, "AAA", 3 );
    close(fd);

}
