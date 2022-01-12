#include "./LED.h"
#include "stdlib.h"
#include "stdio.h"
#include<fcntl.h>
#include<unistd.h>
#include <pthread.h>
#include <string.h>



void *LED_Blink(void *arg) 
{ 
 
    int fd; 
 
         //�򿪶˿�/sys/class/gpio# echo 117 > export
     printf("LED_Blink\n");
     fd = open(SYSFS_GPIO_EXPORT, O_WRONLY);
     if(fd == -1)
     {
                   printf("ERR: Radio hard reset pin open error.\n");
       //            return EXIT_FAILURE;
      }
      write(fd, SYSFS_GPIO_RST_PIN_VAL ,sizeof(SYSFS_GPIO_RST_PIN_VAL)); 
      close(fd); 
 
         //���ö˿ڷ���/sys/class/gpio/gpio117# echo out > direction
 
       fd = open(SYSFS_GPIO_RST_DIR, O_WRONLY);
       if(fd == -1)
         {
 
                   printf("ERR: Radio hard reset pin direction open error.\n");
 
             //      return EXIT_FAILURE;
 
         }
         write(fd, SYSFS_GPIO_RST_DIR_VAL, sizeof(SYSFS_GPIO_RST_DIR_VAL)); 
         close(fd); 

		 
         fd = open(SYSFS_GPIO_RST_VAL, O_RDWR);
         if(fd == -1)
 
         {
                   printf("ERR: Radio hard reset pin value open error.\n");
 
              //     return EXIT_FAILURE;
 
         }     
         //����ߵ�ƽ
         write(fd, SYSFS_GPIO_RST_VAL_H, sizeof(SYSFS_GPIO_RST_VAL_H));  
 
         while(1)
         {
         }
 
         close(fd);
 
         printf("INFO: Radio hard reset pin value open error.\n");

} 
/*
��uboot������gpio�ڵĵ�ƽ

gpio set gpioao_10  ����gpioao_10 �ĵ�ƽ

gpio clear gpioao_10  ����gpioao_10 �ĵ�ƽ

*/

