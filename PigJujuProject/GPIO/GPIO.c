#include "GPIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

 /****************************************************************
 * Constants
       

#bin/bash
echo 87 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio87/direction
echo 1 > /sys/class/gpio/gpio87/value


���ϵĽű���������Ҫ����GPIO�ı�ţ�������Ҫ����PC(23)����ôC���ǵ�������ô�������ù�ʽ
NUM=��N-1��X 32 + M 
����num��GPIO�ı�ţ�n�ǵڼ���gpio��m�ǵ�ǰ��gpio����š���������PC23��GPIO���Ϊ87��

 ****************************************************************/


/****************************************************************
 * gpio_export
 ****************************************************************/
int gpio_export(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0 ) 
	{
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
int gpio_unexport(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
    if (fd < 0)
	{
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0)
	{
        perror("gpio/direction");
        return fd;
    }

    if (out_flag)
        write(fd, "out", 4);
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
int gpio_set_value(unsigned int gpio, unsigned int value)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) 
	{
        perror("gpio/set-value");
        return fd;
    }

    if (value)
        write(fd, "1", 2);
    else
        write(fd, "0", 2);

    close(fd);
    return 0;
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
int gpio_get_value(unsigned int gpio, unsigned int *value)
{
    int fd, len;
    char buf[MAX_BUF];
    char ch;

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY);
    if (fd < 0)
	{
        perror("gpio/get-value");
        return fd;
    }

    read(fd, &ch, 1);

    if (ch != '0') 
	{
        *value = 1;
    } else
	{
        *value = 0;
    }

    close(fd);
    return 0;
}


/****************************************************************
 * gpio_set_edge
 ****************************************************************/

int gpio_set_edge(unsigned int gpio, char *edge)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0)
	{
        perror("gpio/set-edge");
        return fd;
    }

    write(fd, edge, strlen(edge) + );
    close(fd);
    return 0;
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/

int gpio_fd_open(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY | O_NONBLOCK );
    if (fd < 0)
	{
        perror("gpio/fd_open");
    }
    return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/

int gpio_fd_close(int fd)
{
    return close(fd);
}

/****************************************************************
 * Main
 ****************************************************************/
int main(int argc, char **argv, char **envp)
{
    struct pollfd fdset[2];
    int nfds = 2;
    int gpio_fd, timeout, rc;
    char *buf[MAX_BUF];
    unsigned int gpio;
    int len;



    if (argc < 2) 
	{
        printf("Usage: gpio-int <gpio-pin>\n\n");
        printf("Waits for a change in the GPIO pin voltage level or input on stdin\n");
        exit(-1);
    }

    gpio = atoi(argv[1]);

    gpio_export(gpio);
    gpio_set_dir(gpio, 0);
    gpio_set_edge(gpio, "rising");
    gpio_fd = gpio_fd_open(gpio);

    timeout = POLL_TIMEOUT;

    while (1) {
        memset((void*)fdset,0 , sizeof(fdset));

        fdset[0].fd = STDIN_FILENO;
        fdset[0].events = POLLIN;

        fdset[1].fd = gpio_fd;
        fdset[1].events = POLLPRI;

        rc = poll(fdset, nfds, timeout);     

        if (rc < 0) 
		{
            printf("\npoll() failed!\n");
            return -1;
        }

        if (rc == 0) 
		{
            printf(".");
        }

        if (fdset[1].revents & POLLPRI) {
            len = read(fdset[1].fd, buf, MAX_BUF);
            printf("\npoll() GPIO %d interrupt occurred\n", gpio);
        }

        if (fdset[0].revents & POLLIN) {
            (void)read(fdset[0].fd, buf, 1);
            printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
        }

        fflush(stdout);
    }

    gpio_fd_close(gpio_fd);
    return 0;
}




/**
 * drviers/char/tfmv2_gpio.c
 *
 * GPIO driver
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/bitops.h>
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

#define DEVICE_NAME            "gpiodrv"
#define GPIO_MAJOR            0
#define IOCTL_MAGIC            'g'
#define GPIO_OUT_LOW        _IOW(IOCTL_MAGIC, 0x00, unsigned long)
#define GPIO_OUT_HIG        _IOW(IOCTL_MAGIC, 0x01, unsigned long)
#define GPIO_INPUT            _IOR(IOCTL_MAGIC, 0x02, unsigned long)

static struct cdev cdev;
static struct class *gpio_class;
static dev_t devno;

/*OPEN*/
static int gpio_open(struct inode *inode, struct file *filp)
{
    int ret = ;

    filp->private_data = &cdev;

    return ret;
}

/*RELEASE*/
static int gpio_release(struct inode *inode, struct file *filp)
{
    return ;
}

/*READ*/
static ssize_t gpio_read(struct file *filp, char __user *buff,
                size_t count, loff_t *offp)
{
    return ;
}

/*IOCTL*/
static long gpio_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    unsigned int ret = ,err = ;

    if (_IOC_TYPE(cmd) != IOCTL_MAGIC)
        return -EINVAL;

    if (arg > )
        return -EINVAL;

    //����gpio����
    err = gpio_request(arg,NULL);
    if(err)
    {
        //printk("gpio_ioctl request err!\n");
    }

    switch(cmd) {
    case GPIO_OUT_LOW:
        gpio_direction_output(arg,);
        break;

    case GPIO_OUT_HIG:
        gpio_direction_output(arg,);
        break;

    case GPIO_INPUT:
        gpio_direction_input(arg);
        ret = gpio_get_value(arg);
        break;

    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static struct file_operations gpio_fops = {
    .owner = THIS_MODULE,
    .open = gpio_open,
    .release = gpio_release,
    .read = gpio_read,
    .unlocked_ioctl = gpio_ioctl,

};

/*DEV SETUP*/
static int gpio_setup(struct cdev *cdevp, dev_t dev)
{
    int ret = ;

    cdev_init(cdevp, &gpio_fops);
    cdevp->owner = THIS_MODULE;
    cdevp->ops = &gpio_fops;
    ret = cdev_add(cdevp, dev, );
    if (ret)
        printk(KERN_ALERT"add gpio setup failed!\n");

    return ret;
}


/*DEV INIT*/
static int __init gpio_init(void)
{
    struct device *dev;
    int ret;
    unsigned int gpio_major;

    printk("init gpio driver module...\n");
    //1.���������豸��
    devno = MKDEV(GPIO_MAJOR, );
    gpio_major = MAJOR(devno);
    if (gpio_major)
        ret = register_chrdev_region(devno, , DEVICE_NAME);
    else
        ret = alloc_chrdev_region(&devno, , , DEVICE_NAME);

    if (ret < ) {
        printk(KERN_ALERT"failed in registering dev.\n");
        return ret;
    }
    //2.�����ַ��豸�ṹ��
    ret = gpio_setup(&cdev, devno);
    if (ret < ) {
        printk(KERN_ALERT"failed in setup dev.\n");
        return ret;
    }
    //3.��classĿ¼�д����ļ�
    gpio_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(gpio_class)) {
        printk(KERN_ALERT"failed in creating class.\n");
        return -1;
    }
    //4.�����豸�ڵ�
    dev = device_create(gpio_class, NULL, devno, NULL, DEVICE_NAME "%d", );
    if (IS_ERR(dev)) {
        printk(KERN_ALERT"failed in creating class.\n");
        return -1;
    }

    return ret;
}

/*DEV EXIT*/
static void __exit gpio_exit(void)
{
    cdev_del(&cdev);
    unregister_chrdev_region(devno, );
    device_destroy(gpio_class, devno);
    class_destroy(gpio_class);
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZFJ");
MODULE_DESCRIPTION("GPIO driver for test");

/**
 *  test.c
 *
 *  Copyright (C) 2014 W.J, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define GPIO(X)   X
#define GPIO_IOC_MAGIC 'g'

/* general APIs - GPIO_IOC_MAGIC */
enum {
    IOC_OUTPUT_CLR,
    IOC_OUTPUT_SET,
    IOC_SET_INPUT,
};

#define GPIO_IOC_OUTPUT_LOW        _IOW(GPIO_IOC_MAGIC, IOC_OUTPUT_CLR, unsigned int)
#define GPIO_IOC_OUTPUT_HIG        _IOW(GPIO_IOC_MAGIC, IOC_OUTPUT_SET, unsigned int)
#define GPIO_IOC_INPUT            _IOR(GPIO_IOC_MAGIC, IOC_SET_INPUT, unsigned int)

int main(int argc, char **argv)
{
    int gpiofd = , gpio = ;
    int gpio_state = ;

    if (argc != ) { 
        printf("Usage: gpio-pin <on/off>\n\n"); 
        printf("gpio test\n"); 
        exit(-1); 
    } 

    gpio = atoi(argv[]);

    if ((gpiofd = open("/dev/gpiodrv0", O_RDWR)) < ) {
        perror("open");
        return -1;
    }

    if(strcmp(argv[],"on")==)
    {
        gpio_state = GPIO_IOC_OUTPUT_HIG;
    }
    else if(strcmp(argv[],"off")==)
    {
        gpio_state = GPIO_IOC_OUTPUT_LOW;
    }
    else
    {
        gpio_state = GPIO_IOC_INPUT;
    }

    if ((gpio_state = ioctl(gpiofd, gpio_state, gpio)) < ) {
        perror("ioctl err");
        return -1;
    }

    printf("GPIO state:%d\n", gpio_state);
    close(gpiofd);

    return ;
}


