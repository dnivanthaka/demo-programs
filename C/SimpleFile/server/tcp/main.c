/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  TCP Server
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe, nivanthaka@gmail.com
 *
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proto.h"

#define PORT_NUM  3333
#define BACK_LOG  5
#define BUFF_SIZE 255

void
reserve_space( struct buffer *b, int size )
{
    if( (b->next + size) > b->size ){
        b->data = realloc( b->data, (b->next + size) - b->size );
        b->size += (b->next + size);
    }
}

void
serialize_string( char *str, struct buffer *b )
{
    reserve_space( b, sizeof(char) * strlen(str) );
    memcpy( ((char *) b->data) + b->next, str, sizeof(char) * strlen(str) );
    b->next += (sizeof(char) * strlen(str));
}

void
serialize_int( int x, struct buffer *b )
{
    //x = htonl(x);

    reserve_space( b, sizeof(int) );
    memcpy( ((char *) b->data) + b->next, &x, sizeof(int) );
    b->next += sizeof(int);
}

void
serialize_short( short x, struct buffer *b )
{
    //x = htonl(x);

    reserve_space( b, sizeof(short) );
    memcpy( ((char *) b->data) + b->next, &x, sizeof(short) );
    b->next += sizeof(short);
}

void
serialize_message( struct message *msg, struct buffer *b )
{
    //buffer = malloc( sizeof(struct message) + 13 );
    //printf("%d \n", msg->m_length);

    //msg->m_length = htonl( msg->m_length );

    //memmove( buffer, msg, sizeof(struct message) );
    //memcpy( buffer + sizeof(struct message), msg.m_param, msg.m_length );
    serialize_int( msg->m_length, b );
    serialize_short( msg->m_code, b );
    serialize_string( msg->m_param, b );
}

struct buffer *
init_buffer()
{
   struct buffer *b = malloc( sizeof(struct buffer) );

   b->data = malloc( 32 );
   b->size = 32;
   b->next = 0;

   return b;
}

void
deserialize_message( struct message *msg, void *buffer )
{
    msg = (struct message *) buffer;
    //memcpy( buffer, msg, sizeof(struct message) );
    //memcpy( buffer + sizeof(struct message), msg->m_param, msg->m_length );
    printf("Length = %d\n", msg->m_length);
    printf("Code = %d\n", msg->m_code);
}

void
send_file( char *file, int fd )
{
    char *m = "This is a test";

    struct message msg;

    // sending get me file command
    msg.m_length = htonl( sizeof(struct message) + strlen(m) );
    msg.m_code   = (short)htons(301);
    //msg.m_param  = malloc( sizeof(char) * strlen(m) );

    //strcpy( msg.m_param, m );
    //send( fd, &msg, msg.m_length, 0 );

    //free(msg.m_param);
}

int
main( int argc, char *argv[] )
{
    int fd, ret, cli_fd, num_bytes;
    int length;
    short code;
    char tmp;
    struct sockaddr_in svr, cli;
    char buff[ BUFF_SIZE ];
    char *command, *param1, *param2;
    struct message msg;
    //char *b;
    void *msg_buff;
    struct buffer *b;

    memset( &svr, 0, sizeof(struct sockaddr_in) );

    srand( (unsigned)time(NULL) );

    svr.sin_family = AF_INET;
    svr.sin_port = htons( PORT_NUM );
    //inet_aton( "127.0.0.1", ( struct in_addr * )&svr.sin_addr.s_addr );
    svr.sin_addr.s_addr = INADDR_ANY;

    //printf("%s\n", riddles[0]);
    //printf("%d\n", (int)sizeof(riddles)/(int)sizeof(char));


/*
 * For Server Side
 * socket()
 * bind()
 * listen()
 * accept()
 */
    b = init_buffer();

    fd = socket( AF_INET, SOCK_STREAM, 0 );
    if( fd == -1 ){
        perror("socket");
        return -1;
    }

    ret = bind( fd, (struct sockaddr *)&svr, 
    sizeof( struct sockaddr )  );

    if( ret == -1 ){
        perror("bind");
        close(fd);
        return -1;
    }

    ret = listen( fd, 5 );

    if( ret == -1 ){
        perror("listen");
        return -1;
    }

    int f = sizeof(struct sockaddr_in);

    for(;;){
        /*
        cli_fd = accept( fd, (struct sockaddr *)&cli, 
        ( socklen_t * )sizeof(struct sockaddr_in) );
        */

        cli_fd = accept( fd, (struct sockaddr *)&cli, &f );

        if( cli_fd == -1 ){
            perror("accept");
            return -1;
            break;
        }else{
            printf("Accepting Connection....\n");
        }

        msg.m_length = sizeof(struct message) + 13;
        msg.m_code = 1;
        msg.m_param = "hello there";

        /*
        msg_buff = malloc( sizeof(struct message) + 13 );

        memcpy( msg_buff, &msg, sizeof(struct message) );
        memcpy( msg_buff + sizeof(struct message), msg.m_param, 13 );
        */

        serialize_message( &msg, b );

        //printf("%c ", (char)&b->data[0]);
        //printf("%c ", &b->data[1]);
        //printf("%c ", &b[2]);
        //printf("%c ", &b[3]);

        send( cli_fd, (char *)b->data, b->size, 0 );
        
        recv( cli_fd, &msg, sizeof( struct message ), 0 );
        printf( "%d \n", ntohl(msg.m_length) );
        printf( "%d \n", msg.m_code );
        //recv( cli_fd, &length, sizeof(int), 0 );
        //length = (int)ntohl(length);
        //printf("%d \n", length);

        b = malloc( ntohl( msg.m_length ) - sizeof( struct message ) );

        //recv( cli_fd, &code, sizeof(int), 0 );
        //code = (short)ntohs(code);
        //printf("%d \n", code);

        //recv( cli_fd, b, ntohl( msg.m_length ) - sizeof( struct message ), 0 );
        //code = (short)ntohs(code);
        //printf("%s \n", b);
        //recv( cli_fd, &tmp, sizeof(char), 0 );
        //code = (short)ntohs(code);
        //printf("%c \n", tmp);
        //recv( cli_fd, &tmp, sizeof(char), 0 );
        //printf("%c \n", tmp);
        //num_bytes = recv( cli_fd, buff, 5, 0 );
        //buff[ num_bytes ] = '\0';
       // printf( "%sxx\n", buff );
        //break;
        /*        
        while( (num_bytes = recv( cli_fd, buff, BUFF_SIZE, 0 )) > 0 ){
            //printf("reading bytes...\n");
            buff[ num_bytes ] = '\0';
            printf( "%s\n", buff );

            if( strcmp( buff, "hello" ) == 0 ){
                //send( cli_fd,  );
                strcpy( buff, "9" );
                send( cli_fd, buff, strlen(buff), 0 );
            }else if( strcmp( buff, "bye" ) == 0 ){
                printf("Closing Client Connection....\n");
                close( cli_fd );
                break;
            }else if( strcmp( buff, "riddle" ) == 0 ){
                //printf("....\n");
                send_message( riddles[ rand() % 9 ], cli_fd );
                //close( cli_fd );
                //break;
            }else if( strstr( buff, "riddle" ) != NULL && 
                strchr( buff, ' ' ) != NULL ){
                
                command = strtok( buff, " " );

                if( strcmp( command, "riddle" ) == 0 ){
                    //printf("Im here\n");
                    param1 = strtok( NULL, " " );
                    //printf("param1 = %s\n", param1);
                    if( param1 != NULL ){
                        //send( cli_fd, riddles[ atoi(param1) - 1 ], strlen(riddles[ atoi(param1) - 1 ]), 0);

                        send_message( riddles[ atoi(param1) - 1 ], cli_fd );
                    }
                }

                //printf("%s\n", command);
                
            }else if( strstr( buff, "answer n" ) ){
            
                strtok( buff, " " );
                strtok( NULL, " " );
                param2 = strtok( NULL, " " );
                if( param2 != NULL ){
                    //printf("xxxx %d\n", atoi(param2));
                    send_message( answers[ atoi(param2) - 1 ], cli_fd );
                }
            }else{
                send_message( "Unknown Message", cli_fd );
            }
            */
        
            /*            
            if( strcmp( buff, "riddle" ) == 0 ){
                //send( cli_fd,  );
                strcpy( buff, riddles[], strlen(riddles[]) );
                send( cli_fd, buff, strlen(buff), 0 );
            }
            
        }
        */
        
        if( num_bytes == -1 ){
            perror("read");
            break;
        }

    }
}
