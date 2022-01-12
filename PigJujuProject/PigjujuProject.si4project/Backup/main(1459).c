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
//#include "./DHT11/DHT11.h"
#include "./DHT11/dht_driver.h"
#include "./GPIO/GPIO.h"
#include "./LCD/LCD/LCD.h"
#include "math.h"
///opt/vc/bin/vcgencmd measure_temp 鏌ョ湅cpu娓╁害

/*
import RPi.GPIO as GPIO  //引入RPi.GPIO库
GPIO.setmode(GPIO.BCM) //设置引脚编号为BCM编码方式；
GPIO.setmode(GPIO.BOARD) //设置GPIO引脚为BOARD编码方式。

*/

void  *CMDtest(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while(1)
    {

		if(Maindata->testcnt<270)
			{
			Maindata->testcnt ++;
			}
		else
        Maindata->testcnt =200;
		
        usleep(10);
    }
}
void  *CMDMath(void *arg)
{
	int x;
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while(1)
    {


		if(x<360)
			{
			x++;
			}
		else{
			x=0;
			}
		Maindata->mathSin = sin(30*3/180  );
		printf("Maindata->mathSin=%s\n",Maindata->mathSin);
        sleep(1);
    }
}


	

int main(int argc, char **argv)
{	
    MAIN_STRUCT MainStruct ;

    pthread_t pidtest;
	pthread_create(&pidtest,0,CMDtest,&MainStruct);

    pthread_t pidCMDMath;
	//pthread_create(&pidCMDMath,0,CMDMath,&MainStruct);




    
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

#if 0 //DHT11_NG
	printf("start pidDHT11 \n");
    pthread_t pidDHT11_NG;
	pthread_create(&pidDHT11_NG,0,DHT11_read,&MainStruct);
#endif

#if 1 //DHT11_NG
		printf("start pidDHT11 DRIVER \n");
		pthread_t pidDHT11;
		pthread_create(&pidDHT11,0,DHT11_pid,&MainStruct);
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






