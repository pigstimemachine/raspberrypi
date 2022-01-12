#ifndef _GPIO_H_
#define _GPIO_H_

#include <linux/kernel.h>
//#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
//#include <linux/cdev.h>
#include <linux/types.h>
//#include <linux/spinlock.h>
//#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/seq_file.h>
#include <linux/delay.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/gpio.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/poll.h>

/*DEV INIT*/
static int __init gpio_init(void)
{
}
/*DEV EXIT*/
static void __exit gpio_exit(void)
{
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZCJ");
MODULE_DESCRIPTION("GPIO driver for test");

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64





#endif
