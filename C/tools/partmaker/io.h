#ifndef __DISK_IO_H__
#define __DISK_IO_H__
ssize_t 
read_disk_data(char *device, char *buffer, int buff_size, int seek_pos);

ssize_t 
write_disk_data(char *device, char *buffer, int buff_size, int seek_pos);
#endif // __DISK_IO_H__
