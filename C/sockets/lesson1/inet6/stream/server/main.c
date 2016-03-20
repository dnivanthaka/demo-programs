/*
 * This program demonstrates the action of server.
 * creates a socket, binds the socket, listens to incoming traffic 
 * and accepts client connections.
 *
 */
#include <stdio.h>
#include <sys/socket.h>

int
main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in sock_addr;
    //socklen_t sock_size;

    // Creating the socket
    sock_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if(sock_fd == -1){
        perror("socket");
        exit(1);
    }

    // clearing the structure
    memset(&sock_addr, 0, sizeof(struct sockaddr_in));
    // binding to the socket
    bind( sock_fd, (struct sockaddr *) &sock_addr, sizeof(struct sockaddr_in) );
    // Listening to client connections
    listen( sock_fd, 5 );
    // Accepting client connections
    accept();
    // Reading from the connected client
    read();
    // Writing to the connected client
    write();

    return 0;
}
