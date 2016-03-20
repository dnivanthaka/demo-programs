/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  UDP Server
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

#define PORT_NUM  3333
#define BACK_LOG  5
#define BUFF_SIZE 255

char *riddles[] = {
"What has roots as nobody sees,\nIs taller than trees\nUp, up it goes,\nAnd yet never grows?", 
"This thing all things devours:\nBirds, beasts, trees, flowers;\nGnaws iron, bites steel;\nGrinds hard stones to meal;\nSlays king, ruins town,\nAnd beats high mountain down.",
"Thirty white horses on a red hill,\nFirst they champ,\nThen they stamp,\nThen they stand still.",
"No-legs lay on one-leg,\ntwo legs sat near on three legs,\nfour legs got some.",
"An eye in a blue face\nSaw an eye in a green face.\n‘That eye is like to this eye’\nSaid the first eye,\n‘But in low place\nNot in high place.’",
"Alive without breath,\nAs cold as death;\nNever thirsty, ever drinking,\nAll in mail never clinking",
"It cannot be seen, cannot be felt,\nCannot be heard, cannot be smelt.\nIt lies behind stars and under hills,\nAnd empty holes it fills.\nIt comes first and follows after,\nEnds life, kills laughter.",
"A box without hinges, key or lid,\nYet golden treasure inside is hid.",
"Voiceless it cries,\nWingless flutters,\nToothless bites,\nMouthless mutters."
};

char *answers[] = {
"Mountain",
"Time",
"Teeth",
"a Fish on a little one-legged table, a man at a table sitting on a three-legged stool, the cat gets the bones",
"Sun shining on daisies growing in a field",
"Fish",
"Dark",
"Egg",
"Wind"
};

void
send_message( char *riddle, int fd, struct sockaddr_in *cli )
{
    char *tmp, line[ BUFF_SIZE ];
    int len = sizeof(struct sockaddr_in);

    strcpy( line, riddle );
    printf( "%s\n", line );

    tmp = strtok( line, "#" );
    //printf("%s\n", tmp);
    //send( cli_fd, "#", 1, 0 );
    sendto( fd, tmp, strlen( tmp ), 0, (struct sockaddr *) cli, len);
    //sendto( cli_fd, tmp, strlen( tmp ), 0, NULL, NULL);
    //send( cli_fd, riddle, strlen( riddle ), 0);

    
    while( (tmp = strtok( NULL, "#" )) != NULL ){
        //printf("%s\n", tmp);
        //int len;
        sendto( fd, tmp, strlen( tmp ), 0, (struct sockaddr *) cli, len);
        //sendto( cli_fd, tmp, strlen( tmp ), 0, NULL, NULL);
    }
    sendto( fd, "#", 1, 0, (struct sockaddr *) cli, len );
    //sendto( cli_fd, "#", 1, 0, NULL, NULL );
}

int
main( int argc, char *argv[] )
{
    int fd, ret, cli_fd, num_bytes, len;
    struct sockaddr_in svr, cli;
    char buff[ BUFF_SIZE ];
    char *command, *param1, *param2;

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

    fd = socket( AF_INET, SOCK_DGRAM, 0 );
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

    int f = sizeof(struct sockaddr_in);
    len = sizeof(struct sockaddr_in);

    for(;;){
        /*
        cli_fd = accept( fd, (struct sockaddr *)&cli, 
        ( socklen_t * )sizeof(struct sockaddr_in) );
        */
        
        
        while( (num_bytes = recvfrom( fd, buff, BUFF_SIZE, 0, (struct sockaddr *) &cli, &len )) > 0 ){
            //printf("reading bytes...\n");
            buff[ num_bytes ] = '\0';
            printf( "%s\n", buff );

            if( strcmp( buff, "hello" ) == 0 ){
                //send( cli_fd,  );
                strcpy( buff, "9" );
                sendto( fd, buff, strlen(buff), 0, (struct sockaddr *) &cli, len );
            }else if( strcmp( buff, "bye" ) == 0 ){
                printf("Closing Client Connection....\n");
                close( cli_fd );
                break;
            }else if( strcmp( buff, "riddle" ) == 0 ){
                //printf("....\n");
                send_message( riddles[ rand() % 9 ], fd, &cli );
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

                        send_message( riddles[ atoi(param1) - 1 ], fd, &cli );
                    }
                }

                //printf("%s\n", command);
                
            }else if( strstr( buff, "answer n" ) ){
            
                strtok( buff, " " );
                strtok( NULL, " " );
                param2 = strtok( NULL, " " );
                if( param2 != NULL ){
                    //printf("xxxx %d\n", atoi(param2));
                    send_message( answers[ atoi(param2) - 1 ], fd, &cli );
                }
            }else{
                send_message( "Unknown Message", fd, &cli );
            }
        
            /*            
            if( strcmp( buff, "riddle" ) == 0 ){
                //send( cli_fd,  );
                strcpy( buff, riddles[], strlen(riddles[]) );
                send( cli_fd, buff, strlen(buff), 0 );
            }
            */
        }

        
        if( num_bytes == -1 ){
            perror("read");
            break;
        }

    }
}
