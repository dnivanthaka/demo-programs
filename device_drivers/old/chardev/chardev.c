/*
 * chardev.c: Creates a read-only char device that says how many times you've read from the dev
 * file.
 * Supported Operations: read
 */

 #include <linux/kernel.h>
 #include <linux/module.h>
 #include <linux/fs.h>
 #include <asm/uaccess.h> /* for put_user */

 // Prototypes
 int init_module(void);       // gets called when the driver is first loaded
 void cleanup_module(void);   // gets called when unloading the driver
 static ssize_t device_read(struct file *, char *, size_t, loff_t *);
 static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
 static int device_open(struct inode *, struct file *);
 static int device_release(struct inode *, struct file *);

 #define DEVICE_NAME "chardev"
 #define SUCCESS 0
 #define BUF_LEN 80

 static int major;
 static int dev_open = 0;

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
 init_module(void)
 {
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if(major < 0){
        printk( KERN_ALERT "Registering char device failed with %d\n", major );
        return major; 
    }

    printk( KERN_INFO "I was assigned major number %d. To talk to\n", major );
    printk( KERN_INFO "the driver, create a dev file with\n" );
    printk( KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major );
    printk( KERN_INFO "Try various minor numbers. Try to cat and echo to\n" );
    printk( KERN_INFO "the device file.\n" );
    printk( KERN_INFO "Remove the device file and module when done.\n" );

    return SUCCESS;
 }

 void
 cleanup_module(void)
 {
    printk( KERN_INFO "Unloading chardev module..." ); 
    unregister_chrdev(major, DEVICE_NAME); 
 }

 static int
 device_open(struct inode *inode, struct file *file)
 {
    static int counter = 0;

    if(dev_open)
        return -EBUSY;

    dev_open++;
    sprintf(message, "Hello for the %d time\n", counter++);
    msg_ptr = message;

    try_module_get(THIS_MODULE);

    return SUCCESS;
 }

 static ssize_t
 device_read(struct file *flip, char *buffer, size_t length, loff_t *offset)
 {
    int bytes_read = 0;

    if(*msg_ptr == '\0')
        return 0;

    while(length && *msg_ptr){
        // buffer is in user space
        put_user( *(msg_ptr++), buffer++ ); // src to dest

        length--;
        bytes_read++;
    } 

    return bytes_read;
 }

 static ssize_t
 device_write(struct file *flip, const char *buff, size_t len, loff_t *off)
 {
    printk( KERN_ALERT "This operation not supported.\n" );
    return -EINVAL;
 }

 static int
 device_release(struct inode *inode, struct file *file)
 {
    dev_open--;

    module_put(THIS_MODULE);

    return SUCCESS;
 }
