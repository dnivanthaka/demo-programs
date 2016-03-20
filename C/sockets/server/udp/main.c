/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  TCP Server Demo
 *
 *        Version:  1.0
 *        Created:  01/25/2012 10:09:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
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

int
main( int argc, char *argv[] )
{
    int fd, ret, cli_fd, num_bytes;
    struct sockaddr_in svr, cli;
    char buff[ BUFF_SIZE ];

    memset( &svr, 0, sizeof(struct sockaddr_in) );

    svr.sin_family = AF_INET;
    svr.sin_port = htons( PORT_NUM );
    //inet_aton( "127.0.0.1", ( struct in_addr * )&svr.sin_addr.s_addr );
    svr.sin_addr.s_addr = INADDR_ANY;


/*
 * For Server Side
 * socket()
 * bind()
 * listen()
 * accept()
 */

    fd = socket( AF_INET, SOCK_DGRAM, 0 );
    if( fd == -1 ){
        perror("socket");
        return -1;
    }

    ret = bind( fd, (struct sockaddr *)&svr, 
    sizeof( struct sockaddr )  );

    if( ret == -1 ){
        perror("bind");
        return -1;
    }else{
        printf("bind() Succeeded...\n");
    }


    int f = sizeof(struct sockaddr_in);

    for(;;){
        /*
        cli_fd = accept( fd, (struct sockaddr *)&cli, 
        ( socklen_t * )sizeof(struct sockaddr_in) );
        */

        while( (num_bytes = recvfrom( fd, buff, BUFF_SIZE, 0, (struct sockaddr *)&cli, &f )) > 0 ){
            printf("reading bytes...\n");
            buff[ BUFF_SIZE ] = '\0';
            printf( "%s\n", buff );
        }

        if( num_bytes == -1 ){
            perror("read");
            break;
        }

        if( close(cli_fd) == -1 ){
            perror("close");
            //break;
        }
    }
}
