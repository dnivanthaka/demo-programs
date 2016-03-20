#include <stdlib.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <linux/kd.h>
#include <stdio.h>

int main( int argc , char **argv )
{
	int rc,i;
	if (argc != 4) exit(0);

    rc = open("/dev/console", O_WRONLY);
	//rc = syscall(SYS_open,"/dev/console",O_WRONLY,7*64+7*8+7); //open cosole
	if (rc == 0) rc = 1;
	
	i = (argv[1][0]-'0')*2+(argv[2][0]-'0')*4+(argv[3][0]-'0');
    printf(" i = %d\n", i);
    printf("user = %d\n", geteuid());
	ioctl( rc , KDSETLED , i );
	
	return 0;
}
