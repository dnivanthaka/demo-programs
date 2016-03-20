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
#define BUFF_SIZE 25

int
main( int argc, char *argv[] )
{
    int fd, ret, cli_fd, num_bytes;
    struct sockaddr_in svr;
    char buff[ BUFF_SIZE ];

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
        return -1;
    }else{
        printf("connect() Succeeded...\n");
    }

    write( fd, "AAA", 3 );
    close(fd);

}
