#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydevice"

static dev_t dev_num;  // Device number
static struct cdev my_cdev;  // Character device structure

// Open function
static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

// Close function
static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Read function
static ssize_t my_read(struct file *filp, char __user *buffer, size_t len, loff_t *offset) {
    printk(KERN_INFO "Reading from device\n");
    return 0;  // No data to read, just an example
}

// File operations structure
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
};

// Module init function
static int __init my_module_init(void) {
    int ret;

    // Allocate major number dynamically
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "Failed to allocate major number\n");
        return ret;
    }

    printk(KERN_INFO "Major: %d Minor: %d\n", MAJOR(dev_num), MINOR(dev_num));

    // Initialize the character device
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    // Add the character device to the system
    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        printk(KERN_ALERT "Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    printk(KERN_INFO "Device registered\n");
    return 0;
}

// Module exit function
static void __exit my_module_exit(void) {
    cdev_del(&my_cdev);  // Remove the character device
    unregister_chrdev_region(dev_num, 1);  // Unregister device numbers
    printk(KERN_INFO "Device unregistered\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("1.0");

module_init(my_module_init);
module_exit(my_module_exit);
