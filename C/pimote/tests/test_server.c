#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define SERVER_PORT 3142 
//#define SERVER_ADDR 10.22.128.249

int main(int argc, char *argv[])
{
	int sockfd, csockfd;
	struct sockaddr_in saddr, caddr;
	char buffer[256];

	bzero((char *)&saddr, sizeof(struct sockaddr_in));
	//bzero(saddr, sizeof(struct sockaddr_in));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SERVER_PORT);
	// Use the current machine address
	saddr.sin_addr.s_addr = INADDR_ANY;

	printf("%d\n", INADDR_ANY);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Socket creation failed\n");
		exit(1);
	}

	if( bind(sockfd, (struct sockaddr *) &saddr, sizeof(struct sockaddr))  < 0){
		printf("Socket bind failed\n");
		exit(1);
	}

	listen(sockfd, 5);
	int clen = sizeof(struct sockaddr_in);
	csockfd = accept(sockfd, (struct sockaddr *)&caddr, &clen);	
	if(csockfd < 0){
		printf("Client accept failed\n");
		exit(1);
	}

	bzero(buffer, 256);
	int i = read(csockfd, buffer, 255);
	if(i < 0){
		printf("Error reading from socket\n");
		exit(1);
	}

	printf("got message %s\n", buffer);

	if(sockfd > 0)
		close(sockfd);


	return 0;
}


