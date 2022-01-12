#include<stdio.h>
#include <unistd.h>
#include "dht_driver.h"
#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "../ZCJlib/ZCJlib.h"

void *DHT11_pid(void *arg)
{
    MAIN_STRUCT *Maindata =(MAIN_STRUCT *)arg;

    int ret_val ;
    struct dht_sensor_data data;

    printf("DHT11 Sensor test:\n");
    while(1)
    {
        ret_val = dht_read(0,26, &data);
        if(ret_val < 0)
        {
            switch(ret_val)
            {
            case DHT_HANDSHAKE_ERROR:
                printf("Error: Hanshake!\n");
                break;
            case DHT_TIMEOUT_ERROR:
                printf("Error: Timeout!\n");
                break;
            case DHT_CHECKSUM_ERROR:
                printf("Error: Checksum check!\n");
                break;
            case DHT_INIT_ERROR:
                printf("Error: Init!\n");
                break;
            }
        }
        else
        {
            printf("Humidity %f and Temperature %f \n", data.humidity, data.temperature);
			Maindata->DHT11_humidity = data.humidity ; 
			Maindata->DHT11_temp = data.temperature ;
        }

        sleep(3);
    }
}