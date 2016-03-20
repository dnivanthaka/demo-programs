#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../proto.h"

int 
main(int argc, char *argv[])
{
    return 0;
}

void
daemon_loop()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    // closing the std input, output and err streams
    // should enable logging after this
    //close(fileno(stdin));
    //close(fileno(stdout));
    //close(fileno(stderr));

    // create an unnamed socket for server
    server_sockfd = socket(AF_INET, SOCK_STREM, 0);

    // Naming the socket
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s.addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);

    while(1){
        printf("Server Waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);
        read(client_sockfd, &buff, 1); 
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}
