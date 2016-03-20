/*
 * =====================================================================================
 *
 *       Filename:  leds.c
 *
 *    Description:  Blinks the LEDS on the keyboard. Needs superuser permisions to run.
 *
 *        Version:  1.0
 *        Created:  06/24/2012 12:07:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <linux/kd.h>
#include <stdio.h>

#define KEYBOARD_DEVICE "/dev/console"

int keyboard_fd;
unsigned int old_status;
unsigned int cur_status;

//signal(SIGHUP, SIG_IGN);
//signal(SIGTERM, my_signal_handler);
//signal(SIGINT, my_signal_handler);
//signal(SIGQUIT, my_signal_handler);
//signal(SIGTSTP, my_signal_handler); 
//signal(SIGUSR2, SIG_IGN);
//signal(SIGPIPE, my_signal_handler);

int main( int argc , char **argv )
{
	//int rc,i;
	//if (argc != 4) exit(0);
    int i;

    if( geteuid() == 0 ){
        keyboard_fd = open(KEYBOARD_DEVICE, O_WRONLY);
    }else{
        printf("This program requires root permissions to run.\n");
        exit(1);
    }

    if (keyboard_fd == 0) keyboard_fd = 1;

    printf(" fd = %d\n", keyboard_fd);

    ioctl( keyboard_fd , KDGETLED , old_status );

    printf(" old = %d\n", old_status);

    // Resetting keyborad leds, this is required for some keyboards
    cur_status = 0;
    ioctl( keyboard_fd , KDSETLED , cur_status );
    // ------------------------------------------------------------
    // 4 2 1
    cur_status = 4;

    for(i=0;i<10;i++){
        //cur_status = 4;
        //ioctl( keyboard_fd , KDSETLED , cur_status );
        //usleep(1000000);
        //sleep(1);
        ioctl( keyboard_fd , KDSETLED , 2 );
        usleep(100000);
        ioctl( keyboard_fd , KDSETLED , 1 );
        usleep(100000);
        ioctl( keyboard_fd , KDSETLED , 4 );
        usleep(100000);
    }

    for(i=0;i<10;i++){
        //cur_status = 4;
        //ioctl( keyboard_fd , KDSETLED , cur_status );
        //usleep(1000000);
        //sleep(1);
        ioctl( keyboard_fd , KDSETLED , 2 );
        usleep(1000000);
        ioctl( keyboard_fd , KDSETLED , 1 );
        usleep(1000000);
        ioctl( keyboard_fd , KDSETLED , 4 );
        usleep(1000000);
    }

    //rc = open(KEYBOARD_DEVICE, O_WRONLY);
	//rc = syscall(SYS_open,"/dev/console",O_WRONLY,7*64+7*8+7); //open cosole
	//if (rc == 0) rc = 1;
	
	//i = (argv[1][0]-'0')*2+(argv[2][0]-'0')*4+(argv[3][0]-'0');
    //printf(" i = %d\n", i);
    //printf("user = %d\n", geteuid());
	//ioctl( rc , KDSETLED , i );
    // Restoring old setting
    ioctl( keyboard_fd , KDSETLED , old_status );
	
	return 0;
}
