#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

ssize_t 
read_disk_data(char *device, char *buffer, int buff_size, int seek_pos)
{
    int fd, pos;
    ssize_t bytes_read = 0;

    fd = open(device, O_RDONLY);
    // on error
    if(fd == -1){
        printf("Error!!!, Cannot open drive %s for reading\n", device);
        return -1;
    }

    pos = lseek(fd, (off_t)seek_pos, SEEK_SET);
    if(pos == (off_t)-1){
        printf("Error!!!, Cannot seek on device %s\n", device);
        return -1;
    }
    bytes_read = read(fd, buffer, buff_size);
    if(bytes_read == -1){
        // we dont need to check for type of error (EINTR etc.) here.
       printf("Error!!!, Unable to read data on device %s\n", device);
       return -1;
    }
    close(fd);

    return bytes_read;
}

ssize_t 
write_disk_data(char *device, char *buffer, int buff_size, int seek_pos)
{
    int fd, pos;
    ssize_t bytes_written = 0;

    fd = open(device, O_RDONLY);
    // on error
    if(fd == -1){
        printf("Error!!!, Cannot open drive %s for writing\n", device);
        return -1;
    }

    pos = lseek(fd, (off_t)seek_pos, SEEK_SET);
    if(pos == (off_t)-1){
        printf("Error!!!, Cannot seek on device %s\n", device);
        return -1;
    }
    bytes_written = read(fd, buffer, buff_size);
    if(bytes_written == -1){
        // we dont need to check for type of error (EINTR etc.) here.
       printf("Error!!!, Unable to write data on device %s\n", device);
       return -1;
    }
    close(fd);

    return bytes_written;
}
