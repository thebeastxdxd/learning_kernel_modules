/*
 * hello-4.c - Demonstrates module documentation 
 */

#include <linux/module.h>        /* Needed by all modules */
#include <linux/kernel.h>        /* Needed for KERN_INFO  */
#include <linux/init.h>          /* Needed for the macros */

#define DRIVER_AUTHOR "ido ben amram"
#define DRIVER_DESC "A sample driver"


static int __init init_hello_4(void) {
	printk(KERN_INFO "Hello Kworld 4.\n");
	return 0;
}

static void __exit cleanup_hello_4(void) {
	printk(KERN_INFO "Goodbye world 2.\n");

}

module_init(init_hello_4);
module_exit(cleanup_hello_4);

/*
 * Get rid of taint message by declaring code as GPL.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

/*
 * This module uses /dev/testdevice. The MODULE_SUPPORTED_DEVICE macro might
 * be used in the future to help automatic configuration of modules, but is 
 * currently unsed other than for documentation purposes.
 */
MODULE_SUPPORTED_DEVICE("testdevice");
