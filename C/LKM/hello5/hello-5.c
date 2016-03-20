/*
 * hello-5.c - Demonstrates command line argument passing to a module
 * Linux raspberrypi 3.10.24+ #614 PREEMPT Thu Dec 19 20:38:42 GMT 2013 armv6l GNU/Linux
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
static int myintArray[2] = { -1, -1 };
static int arr_argc = 0;

/*
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits,
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 *
 */

module_param( myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
MODULE_PARAM_DESC(myshort, "A short integer");
module_param( myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
MODULE_PARAM_DESC(myshort, "An integer");
module_param( mylong, long, S_IRUSR );
MODULE_PARAM_DESC(myshort, "A long integer");
module_param( mystring, charp, 0000 );
MODULE_PARAM_DESC(mystring, "A character string");

/*
 * module_param_array(name, type, num, perm)
 */
module_param_array( myintArray, int, &arr_argc, 0000 );
MODULE_PARAM_DESC( myintArray, "An array of integers" );

static int __init hello_5_init(void)
{
	int i;
	printk( KERN_INFO "Hello world5\n" );
	printk( KERN_INFO "myshort is a short integer: %hd\n", myshort );
	printk( KERN_INFO "mylong is a long integer: %d\n", myint );
	printk( KERN_INFO "mystring is a string: %s\n", mystring );

	for( i=0;i<(sizeof myintArray / sizeof(int)); i++ ){
		printk( KERN_INFO "myintArray[%d] = %d\n", i, myintArray[i] );
	}

	printk( KERN_INFO "got %d arguments for myintArray.\n", arr_argc );
	return 0;
}

static void __exit hello_5_exit(void)
{
	printk( KERN_INFO "Goodbye, world 5\n" );
}

module_init( hello_5_init );
module_init( hello_5_exit );