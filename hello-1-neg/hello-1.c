/*
 * hello-1.c - The simplest kernel module.
 */

#include <linux/module.h>        /* Needed by all modules */
#include <linux/kernel.h>        /* Neede for KERN_INFO */


int int_module(void) {
	printk(KERN_INFO, "Hello Kworld 1.\n");

	/*
	 * A non 0 return means init_module failed; module can't be loaded.
	 */
	return -1;
}

void cleanup_module(void) {
	printk(KERN_INFO, "Goodbye world 1.\n");

}
