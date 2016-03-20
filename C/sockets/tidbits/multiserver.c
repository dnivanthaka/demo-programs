/*
 * =====================================================================================
 *
 *       Filename:  multiserver.c
 *
 *    Description:  Multiple client serviceble server
 *
 *        Version:  1.0
 *        Created:  01/14/2014 01:29:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
 * socket
 * bind
 * listen
 * accept
 * fork
 *
 */
 
int
main(int argc, char *argv[])
{
    int s_fd, c_fd, ret, client_len;
    struct sockaddr_in server_props;
    struct sockaddr_in client_props;

    s_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if( s_fd < 0 ){
        fprintf(stderr, "Socket() call failed.\n");
        exit(1);
    }

    /* Setting server properties */
    server_props.sin_family = AF_INET;
    server_props.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server_props.sin_addr.s_addr = htons(inet_addr("127.0.0.1"));
    //server_props.sin_addr.s_addr = INADDR_ANY;
    server_props.sin_port = htons(9734);
    

    ret = bind( s_fd, (struct sockaddr *)&server_props, sizeof( struct sockaddr_in ) );
    if( ret < 0 ){
        fprintf(stderr, "Bind() call failed.\n");
        exit(1);
    }

    // Backlog is set as 5
    ret = listen( s_fd, 5 );
    if( ret < 0 ){
        fprintf(stderr, "Listen() call failed.\n");
        exit(1);
    }

    signal( SIGCHLD, SIG_IGN );

    for(;;){
        char ch;

        printf("Server waiting\n");
        client_len = sizeof( struct sockaddr_in );
        c_fd = accept( s_fd, (struct sockaddr *)&server_props, &client_len );

        if( fork() == 0 ){
            read(c_fd, &ch, 1);
            sleep(5);
            ch++;
            write(c_fd, &ch, 1);
            close(c_fd);
            exit(0);
        }else{
            // In parent, close client fd
            close( c_fd );
        }
    }
}
 
