/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  TCP Client
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe, nivanthaka@gmail.com
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proto.h"

#define PORT_NUM  3333
#define BACK_LOG  5
#define BUFF_SIZE 55

// inorder to send message put message struct in a malloced buffer and send it.

void serialize_message( struct message *msg, void *buffer );
void deserialize_message( struct message *msg, void *buffer );

void
get_file( char *file, int fd )
{
    int idx = 0, num_bytes = 0;
    //char *msg_code = "test";
    void *buff;
    //unsigned long filesize = 0;
    int message_length = 0;
    short message_code = 0;
    int filesize = 0;

    struct message msg;

    // sending get me file command
    msg.m_length = htonl( sizeof(struct message) + strlen(file) + 1 );
    //printf("%d ", (int)strlen(file));
    //msg.m_length = ( sizeof(struct message) + 5 );
    //msg.m_code   = (short)htons(101);
    msg.m_code   = 101;
    //msg.chr   = 'P';
    msg.m_param  = malloc( strlen(file) + 1 );
    //msg.m_param = "test";

    //serialize_message( &msg, buff );
    buff = malloc( sizeof(struct message) + strlen(file) + 1 );
    //*buff = 100;
    //*(buff + 1) = 5;
    strcpy( msg.m_param, file );
    memcpy( buff, &msg, sizeof(struct message) );
    memcpy( buff +  sizeof(struct message) , msg.m_param, strlen(file) + 1 );
    
    //memcpy( msg.m_param, &msg.chr, 1 );
    //memcpy( buff, &msg.chr, 1 );
    //send( fd, &msg, ntohl( msg.m_length ), 0 );
    //send( fd, buff, sizeof(struct message) + strlen(file) + 1, 0 );
    send( fd, buff, sizeof(struct message) + strlen(file) + 1, 0 );

    //free(msg.m_param);
    //memset( &msg, 0, sizeof(struct message) );
    // reading the response
    //msg.m_param  = (char *)malloc( sizeof(unsigned long) );
    //num_bytes = recv( fd, msg, sizeof(struct message), 0 );
    //num_bytes = recv( fd, &message_length, sizeof(int), 0 );
    //num_bytes = ntohl( num_bytes );

    //num_bytes = recv( fd, &message_code, sizeof(short), 0 );

    if( ntohl(message_code) == 301 ){
        filesize = num_bytes - sizeof( struct message );

        buff = malloc( sizeof( char ) * filesize );

    //num_bytes = send( fd, "101", 3, 0 );
    //num_bytes = recv( fd, msg_code, 3, 0 );
        /*
        while( idx <  filesize ){
            num_bytes = recv( fd, &buff[idx], 1, 0 );
            //buff[ idx + num_bytes ] = '\0';
            printf("%c ", buff[idx]);
            //idx += num_bytes;
            idx++;
       }
        */
    }
}

void
serialize_message( struct message *msg, void *buffer )
{
    buffer = malloc( msg->m_length );

    memcpy( buffer, msg, sizeof(struct message) );
    memcpy( buffer + sizeof(struct message), msg->m_param, (msg->m_length - sizeof(struct message)) );
}

void
deserialize_message( struct message *msg, void *buffer )
{
    //msg = (struct message *) buffer;
    memcpy( msg, buffer, sizeof(struct message) );
    //memcpy( buffer + sizeof(struct message), msg->m_param, msg->m_length );
    //printf("Length = %d\n", msg->m_length);
    //printf("Code = %d\n", msg->m_code);
    msg->m_param = malloc( msg->m_length - sizeof(struct message) );
    
    memcpy( msg->m_param, (char *)buffer + (msg->m_length - sizeof(struct message) - 7), msg->m_length - sizeof(struct message) );
}

int
main( int argc, char *argv[] )
{
    int fd, ret, cli_fd, num_bytes;
    struct sockaddr_in svr;
    char buff[ BUFF_SIZE ];
    char op[10];
    char param1[1];
    char param2[2];
    char *file = "test.txt";
    struct message msg;
    void *b;
    struct message *m;
    char *data;

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
        close(fd);
        return -1;
    }else{
        printf("Connected to Server\n");
    }
    
    int len;
    short cde;

    //msg.m_param = malloc(12);
    //num_bytes = recv( fd, &msg, sizeof(struct message), 0 );
    //num_bytes = recv( fd, &msg, 6, 0 );
    //printf("%d\n", (int)sizeof(struct message));
    num_bytes = recv( fd, &len, sizeof(int), MSG_PEEK );

    if( len > 0 ){
        b = malloc( len );

        num_bytes = recv( fd, b, len, 0 );
        //m = (struct message *) b;
        //len = *((int *)b);
        //cde = (short)*((short *)b + 4);
        //data = (char *)b + (len - sizeof(struct message) - 7);
        //printf("len = %d\n", len);
        //printf("red len = %d\n", (int)(len - sizeof(struct message)));
        //printf("code = %d\n", m->m_code);
        //printf("code %d\n", cde);
        //printf("data = %s\n", data);
        deserialize_message( &msg, b );
        printf("len = %d\n", msg.m_length);
        printf("code = %d\n", msg.m_code);
        printf("data = %s\n", msg.m_param);
    }
    //num_bytes = recv( fd, &cde, sizeof(short), 0 );
    //num_bytes = recv( fd, buff, BUFF_SIZE, 0 );
    //printf("%d ", ntohl(msg.m_code));
    //printf("%d ", msg.m_code);
    printf("%d ", cde);
    //printf("%d ", ntohl(msg.m_length));
    //msg.m_param[12] = '\0';
    //printf("%d ", msg.m_length);
    //printf("%s ", msg.m_param);
    printf("%d\n", len);
    //num_bytes = send( fd, "hello", strlen("hello"), 0 );
    //num_bytes = recv( fd, buff, ntohl(msg.m_length) - sizeof(struct message), 0 );
    //num_bytes = recv( fd, buff, BUFF_SIZE, 0 );
    //buff[ num_bytes ] = '\0';
    //printf("%d ", (int)&buff[0]);
    //printf("%syy \n", buff);
    if( strcmp( buff, "hello there" ) == 0 )
        printf("Server sent hello message.\n");
    //printf("Number of riddles: %s\n", buff);

    while(1){
        /*
        printf("Command: ");
        //scanf("%s", buff);
        fgets(buff, BUFF_SIZE, stdin );
        // kill the new line char
        buff[strlen(buff) - 1] = '\0';
        if( strcmp(buff, "bye") == 0 ){
            num_bytes = send( fd, "bye", strlen("bye"), 0 );
            close(fd);
            break;
        }else{
            num_bytes = send( fd, buff, strlen(buff), 0 );
            //num_bytes = recv( fd, buff, BUFF_SIZE, 0 );
            //buff[ num_bytes ] = '\0';
            //read_message(buff, fd);
            //printf("** Server Response **\n");
            //printf("%s\n", buff);
            //printf("** End Response **\n");
            
            get_file( file, fd );
        }
        */
        printf("Command: ");
        //scanf("%s", buff);
        fgets(buff, BUFF_SIZE, stdin );
        // kill the new line char
        buff[strlen(buff) - 1] = '\0';
        if( strcmp(buff, "bye") == 0 ){
            //num_bytes = send( fd, "bye", strlen("bye"), 0 );
            close(fd);
            break;
        }else{
            //num_bytes = send( fd, buff, strlen(buff), 0 );
            //num_bytes = recv( fd, buff, BUFF_SIZE, 0 );
            //buff[ num_bytes ] = '\0';
            //read_message(buff, fd);
            //printf("** Server Response **\n");
            printf("%s\n", buff);
            //printf("** End Response **\n");
            //strcpy( file );
            get_file( buff, fd );
        }
        //get_file( file, fd );
        //num_bytes = send( fd, "" );
        fflush(stdin);
        num_bytes = 0;
        memset( buff, 0, BUFF_SIZE );
    }
    //write( fd, "AAA", 3 );
    close(fd);

    return 0;
}
