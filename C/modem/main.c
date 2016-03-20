#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>

char buff[1024] = "";

int result_end(char *line)
{
        
}

int main(int argc, char *argv[])
{
        struct termios options;
        int fd, read_bytes, byte_count = 0;
        char *line;
        char b;

        fd = open("/dev/ttyUSB_utps_modem", O_RDWR | O_NOCTTY | O_NDELAY);

        if (fd < 0)
        {
            printf("Error opening serial port\n");
            exit(1);
        }

        bzero(&options, sizeof(options));
        options.c_cflag = B115200 | CS8 | CLOCAL | CREAD | IGNPAR;
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd, TCSANOW, &options);

        if (write(fd, "ATI\r", 4) < 4)
        {
            printf("Write error - %s \n", strerror(errno));
            exit (1);
        }
        sleep(1);
        // read back for OK or KO then do your stuff...
        read_bytes = 0;

        do{
                //if(read(fd, buff, 64) < 0){
                        
                //}
                read_bytes = read(fd, &b, 1);

                if( b == '\r' || b == '\n'){
                        //b = '';
                        //byte_count++;
                        continue;
                }

                //printf("%c\n", b);

                buff[ byte_count++ ] = b;

        //}while(!result_end( line ));
        }while( read_bytes > 0 );

        buff[byte_count] = '\0';

        //read(fd, buff, 64);
        printf("%d\n", read_bytes);
        printf("%s\n", buff);

        close(fd);

        return EXIT_SUCCESS;
}
