#include <stdio.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 255

int
main(int argc, char *argv[])
{
    return 0;
}
/**
 * copies chars from source to destination
 * It assumes number of read bytes as -1 
 * when it runs out of bytes instead of 0, the EOF
 */
int
copy_bytes(int source, int dest)
{
    int num_read, filesize, total_read = 0;
    char buffer[MAX_BUFFER_SIZE];
    struct stat src_stat;

    filesize = fstat(source, &src_stat)

    while( total_read <= filesize ){
       num_read = read(source, buffer, MAX_BUFFER_SIZE);
       total_read += num_read; 
       write(dest, buffer, num_read);
    }
}
