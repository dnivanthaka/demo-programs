#include <stdio.h>
#include <sys/io.h>

int main()
{
    int ret;

    ret = ioperm(0x60, 0xf, 1);
    if (ret < 0) {
            perror("ioperm");
            return 1;
    }
    //while (inb(0x64) & 0x2);
    //outb(0xed, 0x60);
    //while (inb(0x64) & 0x2);
    //outb(0x07, 0x60);
    int retries = 5;
    int timeout = 1500;
    int state = 1;

    //outb(DEV_MODE, DEV_PORT);
    outb(0xed, 0x60);

    usleep(timeout);
   // Wait for the device acknowledgement 
    while(retries != 0 && inb(0x64) != 0xfa){
        //printf("value = %d\n", inb(0x64));
       retries--;
       usleep(timeout);
    }

   printf("retries has value %d\n", retries);

   if(retries != 0){
       outb(0x1, 0x60);
   }

    ioperm(0x60, 0xf, 0);

    return 0;
}

