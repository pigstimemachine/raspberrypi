#ifndef  _LED_H_
#define _LED_H_
#include "stdio.h"
/*
cd /sys/class/gpio
/sys/class/gpio# echo 117 >export                                       
/sys/class/gpio# echo out >gpio117/direction
/sys/class/gpio# echo 1 >gpio117/value 输出高电平
*/

 
//芯片复位引脚:GPIO3.21
 
#define SYSFS_GPIO_EXPORT           "/sys/class/gpio/export"  
 
#define SYSFS_GPIO_RST_PIN_VAL      "0"   
 
#define SYSFS_GPIO_RST_DIR          "/sys/class/gpio/gpio0/direction"
 
#define SYSFS_GPIO_RST_DIR_VAL      "out"  
 
#define SYSFS_GPIO_RST_VAL          "/sys/class/gpio/gpio0/value"
 
#define SYSFS_GPIO_RST_VAL_H        "1"
 
#define SYSFS_GPIO_RST_VAL_L        "0"
 
 
void *LED_Blink(void *arg) ;

#endif