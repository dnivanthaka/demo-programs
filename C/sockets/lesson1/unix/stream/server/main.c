/*
 * This program demonstrates the action of server.
 * creates a socket, binds the socket, listens to incoming traffic 
 * and accepts client connections.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

int
main(int argc, char *argv[])
{
    int sock_fd, client_fd;
    struct sockaddr_un sock_addr;
    const char *SOCKNAME = "/tmp/mysock";
    char read_buffer[255];
    int read_len;


    // Creating the socket
    sock_fd = socket( AF_UNIX, SOCK_STREAM, 0 );
    if(sock_fd == -1){
        perror("socket");
        exit(1);
    }


    if(remove(SOCKNAME) == -1 && errno != ENOENT){
        printf("remove - %s", SOCKNAME);
        exit(1);
    }

    // Clrearing out the structure
    memset(&sock_addr, 0, sizeof(struct sockaddr_un));
    // Setting props
    sock_addr.sun_family = AF_UNIX;
    strncpy(sock_addr.sun_path, SOCKNAME, (sizeof(sock_addr.sun_path) - 1));

    //socklen_t sock_size;


    // binding to the socket
    if(bind( sock_fd, (struct sockaddr *) &sock_addr, 
        sizeof(struct sockaddr_un) ) == -1){
        perror("bind");
        //printf("Bind error");
        exit(1);
    }
    // Listening to client connections
    if(listen( sock_fd, 5 ) == -1){
        perror("listen");
        exit(1);
    }

    for(;;){
        // Accepting client connections
        client_fd = accept( sock_fd, NULL, NULL );
        if(client_fd == -1){
            perror("accept");
            exit(1);
        }
        // Reading from the connected client
        while((read_len = read( client_fd, read_buffer, 255 )) > 0){
            // Writing to the connected client
            write( 1, read_buffer, read_len );
        }
        // closing the client connection
        close(client_fd);
    }
    return 0;
}
