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
#include <string.h>
#include <time.h>

#define STR_BUFF_SIZE   256
#define SERVER_PORT     3333
/*
 * socket
 * bind
 * listen
 * accept
 * fork
 *
 */

//-------------------------------------------------//
int authenticate(int);
void send_meta(int);
void send_status(int, char *);
void read_response(int, char *);
void send_response(int, char *);
void read_gpio_command(int, char *);
//-------------------------------------------------//


int
authenticate( int client_fd )
{
    char response[25];
    int bytes_read = 0, pass_ok = 0;
    char *pass = "1234";

    while(1){
        write( client_fd, "AUTH: ", 7 );
        bytes_read = read( client_fd, &response, 25 );
        response[ bytes_read - 1 ] = '\0';

        printf("Client Response : %s\n", response);

        if( strncmp( response, pass, (bytes_read - 2) ) == 0 ){
            pass_ok = 1;
            break;
        }else{}
    }

    return pass_ok;
}

void
send_meta( int client_fd )
{
    time_t currenttime;
    char *datetime;

    time(&currenttime);
    datetime = ctime( &currenttime );
    write( client_fd, datetime, 26 );
}

void
send_status( int client_fd, char *message )
{
    int strl;

    strl = strlen(message);
    char str_2_send[ strl + 9 ];
    //printf("strlen = %d\n", strl);
    sprintf(str_2_send, "STATUS: %s\n", message);
    write( client_fd, str_2_send, strl + 9 );
}

void
read_response( int client_fd, char *buff )
{
    int bytes_read;

    bytes_read = read( client_fd, buff, STR_BUFF_SIZE );
    // To remove \n from the read data
    buff[ bytes_read - 2 ] = '\0';
}

void
execute_command( char *command, char *response )
{
    printf("Command = %s\n", command);
    system( command );
}

void
read_gpio_command( int client_fd, char *buff )
{
    char *gpio_pin, *cmd, *val;
    char command[60];
    char command_response[60];

    while(1){
        send_response(client_fd, "GPIO: ");
        read_response(client_fd, buff);

        cmd = strtok( buff, " " );

        if( strcmp( cmd, "mode" ) == 0 || 
                strcmp( cmd, "write" ) == 0 || 
                strcmp( cmd, "read" ) == 0 ){
            printf("GPIO %s command\n", cmd);
            gpio_pin = strtok( NULL, " " );
            val = strtok( NULL, " " );

            sprintf( command, "gpio %s %s %s\n", cmd, gpio_pin, val);
            printf("Command = %s\n", command);
            //system( command );
            execute_command( command, command_response );
            send_status(client_fd, "OK");

        }else{
            //send_status(client_fd, "INVALID_COMMAND");
        }

        //fflush(stdout);

        if( strcmp( buff, "quit" ) == 0 || strcmp( buff, "QUIT" ) == 0 ){
            printf("GPIO quit Command\n");
            send_status(client_fd, "OK");
            break;
        }
    }

    // Cleaning up command buffer
    buff[0] = '\0';
}


void
send_response( int client_fd, char *message )
{
    int strl;

    strl = strlen(message);
    char str_2_send[ strl ];
    //printf("strlen = %d\n", strl);
    sprintf(str_2_send, "%s\n", message);
    write( client_fd, str_2_send, strl );
}
 
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
    //server_props.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server_props.sin_addr.s_addr = htons(inet_addr("127.0.0.1"));
    server_props.sin_addr.s_addr = INADDR_ANY;
    server_props.sin_port = htons(SERVER_PORT);
    

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
        //char ch;
        char buff[ STR_BUFF_SIZE ];
        int client_bytes = 0;

        printf("Server waiting\n");
        client_len = sizeof( struct sockaddr_in );
        c_fd = accept( s_fd, (struct sockaddr *)&server_props, &client_len );

        if( fork() == 0 ){
            //read(c_fd, &ch, 1);
            //sleep(5);
            //ch++;
            //write(c_fd, &ch, 1);
            //close(c_fd);
            //exit(0);
            //for(;;){
            //Authenticate
            //Send meta info
            //Accept commands until exit
                //write( c_fd, "AUTH: ", 7 );
                //client_bytes = read(c_fd, &buff, 255);
                //buff[ client_bytes - 1 ] = '\0';
            //for(;;){
                //printf("Client Sent: %s\n", buff);
                //sleep(5);
                //break;
            //}
            if( authenticate(c_fd) == 1 ){
                //write(c_fd, "STATUS: OK\n", 12);
                send_status(c_fd, "OK");
                //send_status(c_fd, "HELO");
                send_meta( c_fd );
                send_status(c_fd, "OK");
                while(1){
                    send_response(c_fd, "CMD: ");
                    read_response(c_fd, buff);

                    if( strcmp( buff, "GPIO" ) == 0 ){
                        printf("GPIO Command\n");
                        send_status(c_fd, "OK");
                        read_gpio_command( c_fd, buff );
                        //break;
                    }

                    if( strcmp( buff, "quit" ) == 0 || strcmp( buff, "QUIT" ) == 0 ){
                        printf("Quit Command\n");
                        send_status(c_fd, "OK");
                        send_response(c_fd, "Bye\n");
                        break;
                    }
                }
            }
            close(c_fd);
            exit(0);
        }else{
            // In parent, close client fd
            close( c_fd );
        }
    }

    return 0;
}
 
