#ifndef _DHT11_H_
#define _DHT11_H_
#include "stdio.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../ZCJlib/ZCJlib.h"
/*
typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;
 */
 
#define HIGH_TIME 32
#define pinNumber 25//7
//int pinNumber = 7;
uint32 databuf;
  
uint8 readSensorData(void);
void *DHT11_read(void *arg);
#endif