/*
 * hello.c - The simplest kernel module
 */

 #include <linux/module.h>  /* Needed by all modules */
 #include <linux/kernel.h>  /* Needed for KERN_INFO */

 MODULE_LICENSE("GPL");

 int init_module(void)
 {
    printk(KERN_INFO "Hello World.\n");
    // A non 0 return means init_module failed; module cant be loaded.
    return 0;
 }

 void cleanup_module(void)
 {
    printk(KERN_INFO "Goodbye World.\n");
 }
