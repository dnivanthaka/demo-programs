/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main server
 *
 *        Version:  1.0
 *        Created:  05/14/2015 11:41:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */
/*
! /bin/sh
# /etc/init.d/blah
#

# Some things that run always
touch /var/lock/blah

# Carry out specific functions when asked to by the system
case "$1" in
  start)
    echo "Starting script blah "
    echo "Could do more here"
    ;;
  stop)
    echo "Stopping script blah"
    echo "Could do more here"
    pkill pimote
    ;;
  *)
    echo "Usage: /etc/init.d/blah {start|stop}"
    exit 1
    ;;
esac

exit 0

update-rc.d blah defaults
update-rc.d -f  blah remove
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <time.h>

#include "become_daemon.h"

#define SERVER_PORT 8000

// SIGCHLD handler to reap dead child processes
static void reaper(int sig)
{
    int savedErrno;

    savedErrno = errno;
    while( waitpid(-1, NULL, WNOHANG) > 0 )
        continue;
    errno = savedErrno;
}

/*
void handle_request(int cfd)
{

	char buffer[256];
	bzero(buffer, 256);

    //while(strcmp("QUIT", buffer) != 0){
         
	    int i = read(cfd, buffer, 255);
	    if(i < 0){
	        //printf("Error reading from socket\n");
            syslog(LOG_ERR, "Pimote, Failed to read client data: %s", strerror(errno)); 
	        exit(1);
	    }

        buffer[i-1] = '\0';
	    printf("got message %s\n", buffer);

    //}
}
*/
void handle_request(int cfd, char *buffer)
{
    time_t now;

    time(&now);
    strcpy(buffer, "PIMOTE\n");
    write(cfd, buffer, strlen(buffer));
    strcpy(buffer, "HOST: ");
    write(cfd, buffer, strlen(buffer));
    gethostname(buffer, 255);
    strcat(buffer, "\n");
    write(cfd, buffer, strlen(buffer));
    strcpy(buffer, "DATE: ");
    write(cfd, buffer, strlen(buffer));
    strcpy(buffer, ctime(&now));
    //strcat(buffer, "\n");
    write(cfd, buffer, strlen(buffer));
    //Print Pi info such as hostname, date and time here
    while(1){
         
	    int i = read(cfd, buffer, 255);
	    if(i < 0){
	        //printf("Error reading from socket\n");
            syslog(LOG_ERR, "Pimote, Failed to read client data: %s", strerror(errno)); 
	        exit(1);
	    }

        buffer[i - 2] = '\0';
	    //printf("Got message %s\n", buffer);
        //fflush(stdout);

        if( strcmp("QUIT", buffer) == 0 ){
            strcpy(buffer, "OK\n");
            write(cfd, buffer, strlen(buffer));
            break; 
        }
        if( strcmp("SHUTDOWN", buffer) == 0){
            strcpy(buffer, "OK\n");
            write(cfd, buffer, strlen(buffer));
            //system("shutdown -h now");
        }
        if( strcmp("RESTART", buffer) == 0){
            strcpy(buffer, "OK\n");
            write(cfd, buffer, strlen(buffer));
            //system("shutdown -r now");
        }
    }
}

void start_service()
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
		//printf("Socket creation failed\n");
        syslog(LOG_ERR, "Pimote, Failed to create socket: %s", strerror(errno)); 
		exit(1);
	}

	if( bind(sockfd, (struct sockaddr *) &saddr, sizeof(struct sockaddr))  < 0){
		//printf("Socket bind failed\n");
        syslog(LOG_ERR, "Pimote, Failed to bind to socket: %s", strerror(errno)); 
		exit(1);
	}

	listen(sockfd, 5);
	int clen = sizeof(struct sockaddr_in);
    while(1){
	    csockfd = accept(sockfd, (struct sockaddr *)&caddr, &clen);	
	    if(csockfd < 0){
		    printf("Client accept failed\n");
            syslog(LOG_ERR, "Pimote, Failed to accept client connection: %s", strerror(errno)); 
		    exit(1);
	    }

	    bzero(buffer, 256);
        /*
	    int i = read(csockfd, buffer, 255);
	    if(i < 0){
		    printf("Error reading from socket\n");
            syslog(LOG_ERR, "Pimote, Failed to read client data: %s", strerror(errno)); 
		    exit(1);
	    }
        */
	    //printf("got message %s\n", buffer);
        handle_request(csockfd, buffer);

        //fflush(stdout);

	    if(csockfd > 0)
		    close(csockfd);

    }
	if(sockfd > 0)
		close(sockfd);
}

int main(int argc, char *argv[])
{
    int lfd, cfd;

	struct sigaction sa;

	if(become_daemon(0) == -1){
		//printf("Failed to become daemon\n");
        syslog(LOG_ERR, "Pimote, Error from become_daemon(): %s", strerror(errno)); 
		exit(1);
	}

	sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = reaper;

    if( sigaction(SIGCHLD, &sa, NULL) == -1 ){
        syslog(LOG_ERR, "Pimote, Error from sigaction(): %s", strerror(errno)); 
        exit(EXIT_FAILURE);
    }


    start_service();

    return 0;
}
