/*
 * hello-4.c - Demonstrates module documentation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "D.N. Amerasinghe <nivanthaka@gmail.com>"

#define DRIVER_DESC "Sample Driver"

static int hello3_data __initdata = 3;

static int __init hello_4_init(void)
{
	printk( KERN_INFO "Hello, world 4\n" );
	return 0;
}

static void __exit hello_4_exit(void)
{
	printk( KERN_INFO "Goodbye, world\n" );
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");

module_init( hello_4_init );
module_exit( hello_4_exit );
