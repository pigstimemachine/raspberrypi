#include "./DHT11.h"
#include "../ZCJlib/ZCJlib.h"


/**

  * @brief   	wiringPi库函数查看DHT11温湿度
  * @Name	 	int main Name ( void sth)
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/06/ Create
  * @Version 	1.0 2020/08/18
  *		     	1.1 2020/08/18 change sth
  * @Note

  **/

uint8 readSensorData(void)
{
    uint8 crc;
    uint8 i;

    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 0); // output a high level
    delay(25);
    digitalWrite(pinNumber, 1); // output a low level
    pinMode(pinNumber, INPUT); // set mode to input
    pullUpDnControl(pinNumber, PUD_UP);

    delayMicroseconds(27);
    if (digitalRead(pinNumber) == 0) //SENSOR ANS
    {
        while (!digitalRead(pinNumber))
            ; //wait to high

        for (i = 0; i < 32; i++)
        {
            while (digitalRead(pinNumber))
                ; //data clock start
            while (!digitalRead(pinNumber))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            databuf *= 2;
            if (digitalRead(pinNumber) == 1) //1
            {
                databuf++;
            }
        }

        for (i = 0; i < 8; i++)
        {
            while (digitalRead(pinNumber))
                ; //data clock start
            while (!digitalRead(pinNumber))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            crc *= 2;
            if (digitalRead(pinNumber) == 1) //1
            {
                crc++;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
/**

 * @brief   	wiringPi库函数查看DHT11温湿度
 * @Name	 	int main Name ( void sth)
 * @param   	None
 * @retval  	None
 * @Author  	ZCJ
 * @Date 	 	2020/06/ Create
 * @Version 	1.0 2020/08/18
 *		     	1.1 2020/08/18 change sth
 * @Note

 **/
void *DHT11_read(void *arg)

{	
    MAIN_STRUCT *Maindata =(MAIN_STRUCT *)arg;
    printf("PIN:%d\n", pinNumber);
	uint32 humi=0,temp=0;
    if (-1 == wiringPiSetup())
    {
        printf("Setup wiringPi failed!");
        //  return 1;
    }

    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level

    printf("Starting...\n");
    while (1)
    {
    	sleep(1);
        pinMode(pinNumber, OUTPUT); // set mode to output
        digitalWrite(pinNumber, 1); // output a high level
        delay(3000);
        if (readSensorData())
        {
            //printf("Sensor data read ok!\n");
#if 1
            printf("RH:%d.%d\n", (databuf >> 24) & 0xff, (databuf >> 16) & 0xff);
            printf("TMP:%d.%d\n", (databuf >> 8) & 0xff, databuf & 0xff);
#endif

		   Maindata->DHT11_humidity = ((databuf >> 24) & 0xff)    ;
		   Maindata->DHT11_temp = ((databuf >> 8) & 0xff)  ;
#if 0

            printf("Rh=%d\n",Maindata->DHT11_humidity);
            printf("temp=%d\n",Maindata->DHT11_temp);
#endif

            databuf = 0;
        }
        else
        {
            printf("Sensor dosent ans!\n");
            databuf = 0;
        }
    }
}

