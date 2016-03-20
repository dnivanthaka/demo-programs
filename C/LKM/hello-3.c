/*
 * hello-2.c - Demonstrating thje module_init() and module_exit()  macros.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello3_data __initdata = 3;

static int __init hello_3_init(void)
{
	printk( KERN_INFO "Hello, world 2.\n" );
	return 0;
}

static void __exit hello_3_exit(void)
{
	printk( KERN_INFO "Goodbye, world.\n" );
}

module_init( hello_3_init );
module_exit( hello_3_exit );
