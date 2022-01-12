#include "./ZCJlib/ZCJlib.h"
#include "./LED/LED.h"
#include "stdlib.h"
#include "stdio.h"
#include<fcntl.h>
#include<unistd.h>
#include <pthread.h>
#include <string.h>
#include <linux/errno.h>   
#include <linux/gpio.h>
#include "./DHT11/DHT11.h"
#include "./GPIO/GPIO.h"
#include "./LCD/LCD/LCD.h"
///opt/vc/bin/vcgencmd measure_temp 查看cpu温度

/*
import RPi.GPIO as GPIO  //����RPi.GPIO��
GPIO.setmode(GPIO.BCM) //�������ű��ΪBCM���뷽ʽ��
GPIO.setmode(GPIO.BOARD) //����GPIO����ΪBOARD���뷽ʽ��

*/
	

int main(int argc, char **argv)
{	
    MAIN_STRUCT MainStruct ;
    
#if 0   
    printf("start pidLED \n");
	pthread_t pidLED;
	pthread_create(&pidLED,0,LED_Blink,&MainStruct);
#endif

#if  1
    printf("start pidCMDreturn \n");
    pthread_t pidCMDreturn;
	pthread_create(&pidCMDreturn,0,CMDReturn,&MainStruct);
#endif

#if 1
	printf("start pidDHT11 \n");
    pthread_t pidDHT11;
	pthread_create(&pidDHT11,0,DHT11_read,&MainStruct);
#endif

#if 1
	printf("start pidLCD \n");
    pthread_t pidLCD;
	pthread_create(&pidLCD,0,LCD_test,&MainStruct);	
#endif
	

	while (1)
		{

			sleep(10);
		}
}






