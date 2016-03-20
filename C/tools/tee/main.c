#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define BUFF_SIZE 255

void copy_data(int input, int output);

int 
main(int argc, char *argv[])
{
    int fd;
    int opt;

    if(opt = getopt(argc, argv, "a:")){
        //printf("%s\n", optarg);
        //printf("%c\n", opt);
        //printf("%d\n", optind);
        fd = open(optarg, O_WRONLY| O_CREAT | O_TRUNC);
    }else{
        fd = -1;
    }
    //copy_data((int)stdin, fd);
    //copy_data(0, fd);
    copy_data(STDIN_FILENO, fd);
    if(fd != -1)
        close(fd);
    return 0;
}

void
copy_data(int input, int output)
{
    char buffer[BUFF_SIZE + 1];
    ssize_t num_read, num_written;

    while( (num_read = read(input, buffer, BUFF_SIZE)) > 0 ){
        if(output != -1)
            num_written = write(output, buffer, num_read); 

        if(output != -1 && num_read != num_written){
            //fprintf(STDERR_FILENO, "Read/Write Error, Count Mismatch\n");
            printf("Read/Write Error, Count Mismatch\n");
            break;
        }
        buffer[num_read] = '\0';
        //fprintf(STDOUT_FILENO, "%s", buffer);
        printf("%s", buffer);
    }

    if(num_read == -1){
        //fprintf(STDERR_FILENO, "Unable to read from input\n");
        printf("Unable to read from input\n");
        return;
    }
}
