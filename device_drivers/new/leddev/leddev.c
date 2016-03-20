/*
 * chardev.c: Creates a read-only char device that says how many times you've read from the dev
 * file.
 * Supported Operations: read
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put_user */
#include <linux/string.h>
#include <asm/io.h>
//#include <linux/stdlib.h>


// Prototypes
int mod_init(void);       // gets called when the driver is first loaded
void mod_cleanup(void);   // gets called when unloading the driver

static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static void set_dev_status(void);

#define DEVICE_NAME "leddev"
#define SUCCESS 0
#define BUF_LEN 10

#define DEV_PORT  0x64
#define DEV_MODE  0xED
#define DEV_READY 0xFA

static int major;
static int dev_open   = 0;
static int port_avail;

static char *msg_ptr;
static char message[BUF_LEN];

static struct file_operations fops = {
       .open    = device_open,
       .read    = device_read,
       .write   = device_write,
       .release = device_release
};

/*
* This function gets called when the module is loaded.
* Returns a negative number when an error occurs.
*/
int
mod_init(void)
{
   major = register_chrdev(0, DEVICE_NAME, &fops);

   if(major < 0){
       printk( KERN_ALERT "Registering char device failed with %d\n", major );
       return major; 
   }

   printk( KERN_INFO "%s: major number - %d\n", DEVICE_NAME, major );

   //port_avail = check_region(DEV_PORT, 1);
   port_avail = request_region(DEV_PORT, 1, "leddev");
   if( port_avail < 0 ){
        printk( KERN_ALERT "%s: Cannot reserve device\n", DEVICE_NAME );
        goto fail;
   }

   //request_region(DEV_PORT, 1, "leddev");
   goto out;

   fail:
        unregister_chrdev(major, DEVICE_NAME);
   
   out:
    return SUCCESS;
}

void
mod_cleanup(void)
{
   if( port_avail > 0 ){
        release_region(DEV_PORT, 1);
   }

   printk( KERN_INFO "Unloading leddev module..." ); 
   unregister_chrdev(major, DEVICE_NAME); 
}

static int
device_open(struct inode *inode, struct file *file)
{
   static int counter = 0;

   if(dev_open)
       return -EBUSY;

   dev_open++;
   //sprintf(message, "Hello for the %d time\n", counter++);
   //msg_ptr = message;

   try_module_get(THIS_MODULE);

   return SUCCESS;
}

static ssize_t
device_read(struct file *flip, char *buffer, size_t length, loff_t *offset)
{
   int bytes_read = 0;

   //if(*msg_ptr == '\0')
   //    return 0;

   /*
   while(length && *msg_ptr){
       // buffer is in user space
       put_user( *(msg_ptr++), buffer++ ); // src to dest

       length--;
       bytes_read++;
   } 
   */
   printk( KERN_ALERT "This operation not supported.\n" );
   return -EINVAL;
   //return bytes_read;
}

static ssize_t
device_write(struct file *flip, const char *buffer, size_t length, loff_t *off)
{
   int cmd = 0;

   strcpy(message, buffer);

   if(length > BUF_LEN)
       message[BUF_LEN - 1] = '\0';

   //cmd = atoi( message );
   int retries = 5;
   int timeout = 1500;
   int state = 1;

   //outb(DEV_MODE, DEV_PORT);
   outb(0xed, 0x60);

   udelay(timeout);
   // Wait for the device acknowledgement 
   while(retries != 0 && inb(0x60) != 0xfa){
       retries--;
       udelay(timeout);
   }

   printk(KERN_INFO "retries has value %d\n", retries);
   printk(KERN_INFO "retries has value %d\n", retries);

   if(retries != 0){
       outb(state, DEV_PORT);
   }

   //set_dev_status();

   return (length > BUF_LEN) ? BUF_LEN : length;
}

static int
device_release(struct inode *inode, struct file *file)
{
   dev_open--;

   module_put(THIS_MODULE);

   return SUCCESS;
}

static void
set_dev_status(void)
{
   int retries = 5;
   int timeout = 1500;
   int state = 1;

   //outb(DEV_MODE, DEV_PORT);
   outb(0xed, 0x60);

   udelay(timeout);
   // Wait for the device acknowledgement 
   while(retries != 0 && inb(0x60) != 0xfa){
       retries--;
       udelay(timeout);
   }

   printk(KERN_INFO "retries has value %d\n", retries);
   printk(KERN_INFO "retries has value %d\n", retries);

   if(retries != 0){
       outb(state, DEV_PORT);
   }
}

module_init(mod_init);
module_exit(mod_cleanup);

MODULE_LICENSE("GPL");
