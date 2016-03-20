/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  UDP Client
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

//recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);

void
read_message( char *buff, int fd )
{
     int idx = 0, num_bytes = 0;
     while(1){
         num_bytes = recvfrom( fd, &buff[idx], BUFF_SIZE, 0, NULL, NULL );
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
    int fd, ret, cli_fd, num_bytes, len;
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

    fd = socket( AF_INET, SOCK_DGRAM, 0 );
    if( fd == -1 ){
        perror("socket");
        return -1;
    }

    num_bytes = sendto( fd, "hello", strlen("hello"), 0, (struct sockaddr *) &svr, sizeof(struct sockaddr_in) );
    num_bytes = recvfrom( fd, buff, BUFF_SIZE, 0, NULL, NULL );
    buff[ num_bytes ] = '\0';
    printf("Number of riddles: %s\n", buff);

    while(1){
        printf("Command: ");
        //scanf("%s", buff);
        fgets(buff, BUFF_SIZE, stdin );
        // kill the new line char
        buff[strlen(buff) - 1] = '\0';
        if( strcmp(buff, "bye") == 0 ){
            num_bytes = sendto( fd, "bye", strlen("bye"), 0, (struct sockaddr *) &svr, sizeof(struct sockaddr_in) );
            close(fd);
            break;
        }else{
            num_bytes = sendto( fd, buff, strlen(buff), 0, (struct sockaddr *) &svr, sizeof(struct sockaddr_in) );
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
