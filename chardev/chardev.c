/*
 * chardev.c - Creates a read-only char device that says how many times
 * you've read from the dev file
 */

#include <linux/module.h>        /* Needed by all modules */
#include <linux/kernel.h>        /* Needed for KERN_INFO  */
#include <linux/init.h>          /* Needed for the macros */
#include <linux/fs.h>
#include <asm/uaccess.h>

#define DRIVER_AUTHOR "ido ben amram"
#define DRIVER_DESC "A sample driver"
#define SUCCESS (0)
#define DEVICE_NAME ("chardev")
#define BUF_LEN (80)             /* Max length of the message from the device. */

/*
 * Get rid of taint message by declaring code as GPL.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

/*
 *  Prototypes - this would normally go in a .h file
 */
static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);


/* 
 * Global variables are declared as static, so are global within the file.
 */

static int major;                /* Major number assigned to our device driver */
static int is_device_open = 0;      /* Is device open?
				  * Used to prevent multiple access to device */
static char msg[BUF_LEN];        /* The msg the device will give when asked */
static char *msg_ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};



static int __init chardev_init(void) {

	major = register_chrdev(0, DEVICE_NAME, &fops);

	if (major < 0) {
		printk(KERN_ALERT "Registering char device failed with &d\n", major);
		return major;
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;

}

static void __exit chardev_cleanup(void) {

	unregister_chrdev(major, DEVICE_NAME);
}

module_init(chardev_init);
module_exit(chardev_cleanup);

/*
 * called when a process tries to open the device file, like
 * "cat /dev/mycharfile"
 */
static int device_open(struct inode* inode, struct file* file) {

	static int counter = 0;

	if (is_device_open)
		return -EBUSY;
	is_device_open++;
	sprintf(msg, "I already told you %d times Hello World!\n", counter++);
	msg_ptr = msg;
	try_module_get(THIS_MODULE);
	
	return SUCCESS;

}

static int device_release(struct inode* inode, struct file* file) {

	is_device_open--;

	module_put(THIS_MODULE);

	return 0;

}

static ssize_t device_read(struct file* filp,
			   char* buffer,
			   size_t length,
			   loff_t* offset) {

	int bytes_read = 0;

	if ((*msg_ptr) = 0)
		return 0;
	
	while (length && *msg_ptr) {

		/*
		 * The buffer is in the data segment, not the kernel
		 * segment so "*" assignment won't work. We have to use
		 * put_user which copies data from the kernel data segment to
		 * the user data segment.
		 */
		put_user(*(msg_ptr++), buffer++);

		length--;
		bytes_read++;
	}

	return bytes_read;

}

static ssize_t device_write(struct file* filp, const char* buff, size_t len, loff_t* off) {
	
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;

}
