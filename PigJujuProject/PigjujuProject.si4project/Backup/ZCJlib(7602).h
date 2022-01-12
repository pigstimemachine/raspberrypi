#ifndef _ZCJLIB_H_
#define _ZCJLIB_H_
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h> //sleep函数
#include "string.h"

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

typedef struct MAINSTRUCT
{
    int test;
    char CMDReslut[4096];
    char systemp[100];
    char curtime[100];
    char curdate[100];
    char curIP[50];
    char curIP_wlan0[50];
    char keytime_s[20];
    char curtime_s[20];
    float RX_netspeed_eth0;
    float TX_netspeed_eth0;
    float RX_netspeed_wlan0;
    float TX_netspeed_wlan0;
	
    float cpu_use;
	char cpu_usUSE[5];
	char cpu_syUSE[5];
	char cpu_idFree[5];
	
    char memery_total_use[10];
    char memery_total[10];
    char memery_free[10];
    char memery_buff[10];
	char memery_cache[10];
	
    char disk_use[10];
    char disk_total[10];
    char disk_rate[10];

	int DHT11_temp;
	int DHT11_humidity;
	
} MAIN_STRUCT;

#define CatCpuTemp	"cat /sys/class/thermal/thermal_zone0/temp " //CPU温度
#define RunCpuTemp "/opt/vc/bin/vcgencmd measure_temp"

#define  TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define  CurDATE "sudo date '+week:%W'"
#define  CurTime "date '+%Y-%m-%d %H:%M:%S'"
#define  CurIP "sudo  ifconfig |head -2 |grep inet |awk '{print $2}' "
#define  CurIP_wlan0 "sudo ifconfig  |tail -10 |grep -w inet |awk '{print $2}'"
/*
	ifconfig |head -2 |tail -1 |tr -s ' ' |cut -d' ' -f3
ifconfig |grep -Eo '([0-9]{1,3}.){3}[0-9]{1,3}' |head -1
*/

//test
#define MAX_SIZE 32


#define Keytime_s "date --date=20170404 +%s"
#define Curtime_s "date +%s"


#define CMD_RX_netspeed  "cat /proc/net/dev | grep eth0 | tr : ' ' | awk '{print $2}'"
#define CMD_TX_netspeed  "cat /proc/net/dev | grep eth0 | tr : ' ' | awk '{print $10}'"

#define CMD_RX_netspeed_wlan0  "cat /proc/net/dev | grep wlan0 | tr : ' ' | awk '{print $2}'"
#define CMD_TX_netspeed_wlan0  "cat /proc/net/dev | grep wlan0 | tr : ' ' | awk '{print $10}'"
/*
使用top指令的上电自启动均无法查看，且数据无法恢复，判断是该线程卡死在某个地方
*/

#define CMD_CPU_USE "sudo top |head -3 |grep Cpu |awk '{print $8}'"

#define CMD_CPU_usUSE "vmstat 1 2 |tail -1  |awk '{print $13}'"
#define CMD_CPU_syUSE "vmstat 1 2 |tail -1  |awk '{print $14}'"
#define CMD_CPU_idFREE "vmstat 1 2 |tail -1  |awk '{print $15}'"


//#define CMD_Memry_total "top |head -4 |grep MiB |awk '{print $4}'"
#define CMD_Memry_free  "vmstat  |tail -1  |awk '{print $4}'"//"vmstat |tail -1  |awk '{print $4}' "//"top |head -4 |grep MiB |awk '{print $6}'" 

//#define CMD_Memry_use "top |head -4 |grep MiB |awk '{print $8}'"
#define CMD_Memry_buff   "vmstat  |tail -1  |awk '{print $5}'"//"top |head -4 |grep MiB |awk '{print $10}'"
#define CMD_Memry_cache   "vmstat |tail -1  |awk '{print $6}'"


#define CMD_DISK_total "df -h |head -2 |grep /dev/root |awk '{print $2}'"
#define CMD_DISK_use "df -h |head -2 |grep /dev/root |awk '{print $3}'"
#define CMD_DISK_UsetoTotal "df -h |head -2 |grep /dev/root |awk '{print $5}'"


void  *CMDReturn(void *arg) ;
int OpenCpuTemp(void);
#endif
