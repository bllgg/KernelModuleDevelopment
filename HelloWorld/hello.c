#include <linux/module.h>  // Needed for all kernel modules
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/init.h>    // Needed for the macros

// This function is called when the module is loaded into the kernel
static int __init hello_init(void) {
    printk(KERN_INFO "Hello, World from the kernel!\n");
    return 0;
}

// This function is called when the module is removed from the kernel
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World from the kernel!\n");
}

module_init(hello_init);  // Registers hello_init as the module's entry point
module_exit(hello_exit);  // Registers hello_exit as the module's exit point

MODULE_LICENSE("GPL");  // Specifies the license
MODULE_AUTHOR("Lahiru");  // Module author
MODULE_DESCRIPTION("A simple Hello World kernel module");  // Description
MODULE_VERSION("1.0");  // Version of the module

