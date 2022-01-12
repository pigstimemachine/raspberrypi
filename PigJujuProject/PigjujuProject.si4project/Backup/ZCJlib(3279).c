#include "./ZCJlib.h"

#include "../LCD/Config/DEV_Config.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include<fcntl.h>
#include<unistd.h>
#include <pthread.h>
#include <string.h>
#include <linux/errno.h>
#include <linux/gpio.h>


/**

  * @brief   	查看相关命令并返回
  * @Name	 	int main Name ( void sth)
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/06/ Create
  * @Version 	1.0 2020/08/17
  *		     	1.1 2020/08/17 change sth
  * @Note

  **/
char* ReturnCMDResult(char* dbuf,char* cmd)
{
    FILE *pf;
    char buffer[4096];
    pf = popen(cmd, "r");
    fread(buffer, sizeof(buffer), 1, pf);

    //printf("ReturnCMDResult=%s\n", buffer);
    //printf("strlenbuffer=%d\n",strlen(buffer));
    memcpy(dbuf, buffer,strlen(buffer));
    //printf("dbuf=%s\n",dbuf);
    memset(buffer,0,sizeof(buffer));
    pclose(pf);
    return dbuf;
}
/*
	RX NET SPEED
	ZCJ
	20201203
*/
void  *RXnetspeed(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;

    char cur_rxnetspeed[30]= {0},next_rxnetspeed[30]= {0};
    float cur_rx_speed=0.0,next_rx_speed=0.0,real_speed=0.0;
    while (1)
    {
        //printf("start RXnetspeed\n");
        memset(cur_rxnetspeed,0,sizeof(cur_rxnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(cur_rxnetspeed,CMD_RX_netspeed);
        cur_rx_speed = atof(cur_rxnetspeed);
        sleep(1);


        memset(next_rxnetspeed,0,sizeof(next_rxnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(next_rxnetspeed,CMD_RX_netspeed);
        //printf("start next_rxnetspeed\n");
        next_rx_speed = atof(next_rxnetspeed);

        //sleep(1);

        real_speed = (next_rx_speed -cur_rx_speed)/1024;
        Maindata->RX_netspeed_eth0 = real_speed;
        //printf("real_speed=%lf\n",real_speed);
        // memset(Maindata->RX_netspeed,0,sizeof(Maindata->RX_netspeed));    //必须清零 否则会乱码
        // ReturnCMDResult(Maindata->RX_netspeed,CMD_RX_netspeed);
    }
    return 0;
}
/*
	TX NET SPEED
	ZCJ
	20201203
*/

void  *TXnetspeed(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;

    char cur_txnetspeed[30]= {0},next_txnetspeed[30]= {0};
    float cur_tx_speed=0.0,next_tx_speed=0.0,real_tx_speed=0.0;
    while (1)
    {
        //printf("start RXnetspeed\n");
        memset(cur_txnetspeed,0,sizeof(cur_txnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(cur_txnetspeed,CMD_TX_netspeed);
        cur_tx_speed = atof(cur_txnetspeed);
        sleep(1);


        memset(next_txnetspeed,0,sizeof(next_txnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(next_txnetspeed,CMD_TX_netspeed);
        //printf("start next_rxnetspeed\n");
        next_tx_speed = atof(next_txnetspeed);

        //sleep(1);

        real_tx_speed = (next_tx_speed -cur_tx_speed)/1024;
        Maindata->TX_netspeed_eth0 = real_tx_speed;
        //printf("real_speed=%lf\n",real_speed);
        // memset(Maindata->RX_netspeed,0,sizeof(Maindata->RX_netspeed));    //必须清零 否则会乱码
        // ReturnCMDResult(Maindata->RX_netspeed,CMD_RX_netspeed);
    }
    return 0;
}

/*
	RX NET SPEED
	ZCJ
	20201203
*/
void  *RXnetspeed_wlan0(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;

    char cur_rxnetspeed[30]= {0},next_rxnetspeed[30]= {0};
    float cur_rx_speed=0.0,next_rx_speed=0.0,real_speed=0.0;
    while (1)
    {
        //printf("start RXnetspeed\n");
        memset(cur_rxnetspeed,0,sizeof(cur_rxnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(cur_rxnetspeed,CMD_RX_netspeed_wlan0);
        cur_rx_speed = atof(cur_rxnetspeed);
        sleep(1);


        memset(next_rxnetspeed,0,sizeof(next_rxnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(next_rxnetspeed,CMD_RX_netspeed_wlan0);
        //printf("start next_rxnetspeed\n");
        next_rx_speed = atof(next_rxnetspeed);

        //sleep(1);

        real_speed = (next_rx_speed -cur_rx_speed)/1024;
        Maindata->RX_netspeed_wlan0 = real_speed;
        //printf("real_speed=%lf\n",real_speed);
        // memset(Maindata->RX_netspeed,0,sizeof(Maindata->RX_netspeed));    //必须清零 否则会乱码
        // ReturnCMDResult(Maindata->RX_netspeed,CMD_RX_netspeed);
    }
    return 0;
}
/*
	TX NET SPEED
	ZCJ
	20201203
*/

void  *TXnetspeed_wlan0(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;

    char cur_txnetspeed[30]= {0},next_txnetspeed[30]= {0};
    float cur_tx_speed=0.0,next_tx_speed=0.0,real_tx_speed=0.0;
    while (1)
    {
        //printf("start RXnetspeed\n");
        memset(cur_txnetspeed,0,sizeof(cur_txnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(cur_txnetspeed,CMD_TX_netspeed_wlan0);
        cur_tx_speed = atof(cur_txnetspeed);
        sleep(1);


        memset(next_txnetspeed,0,sizeof(next_txnetspeed));    //必须清零 否则会乱码
        ReturnCMDResult(next_txnetspeed,CMD_TX_netspeed_wlan0);
        //printf("start next_rxnetspeed\n");
        next_tx_speed = atof(next_txnetspeed);

        //sleep(1);

        real_tx_speed = (next_tx_speed -cur_tx_speed)/1024;
        Maindata->TX_netspeed_wlan0 = real_tx_speed;
        //printf("real_speed=%lf\n",real_speed);
        // memset(Maindata->RX_netspeed,0,sizeof(Maindata->RX_netspeed));    //必须清零 否则会乱码
        // ReturnCMDResult(Maindata->RX_netspeed,CMD_RX_netspeed);
    }
    return 0;
}
/*
	cpu use
	ZCJ
	20201203
*/
void  *thread_cpu_usUSE(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while (1)
    {
        memset(Maindata->cpu_usUSE,0,sizeof(Maindata->cpu_usUSE)); //love time
        ReturnCMDResult(Maindata->cpu_usUSE,CMD_CPU_usUSE);
		sleep(2);
    }
    return 0;
}
void  *thread_cpu_syUSE(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while (1)
    {
        memset(Maindata->cpu_syUSE,0,sizeof(Maindata->cpu_syUSE)); //love time
        ReturnCMDResult(Maindata->cpu_syUSE,CMD_CPU_syUSE);
		sleep(2);
    }
    return 0;
}
void  *thread_cpu_idFree(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while (1)
    {
        memset(Maindata->cpu_idFree,0,sizeof(Maindata->cpu_idFree)); //love time
        ReturnCMDResult(Maindata->cpu_idFree,CMD_CPU_idFREE);
		sleep(2);
    }
    return 0;
}

void  *thread_cpu_use(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    char cpu_id_null[10];
    float cpu_id=0.0,cpu_us=0.0;
    pthread_t pidcpu_usUSE;
    pthread_create(&pidcpu_usUSE,0,thread_cpu_usUSE,Maindata);	
    pthread_t pidcpu_syUSE;
    pthread_create(&pidcpu_syUSE,0,thread_cpu_syUSE,Maindata);	
    pthread_t pidcpu_idFree;
    pthread_create(&pidcpu_idFree,0,thread_cpu_idFree,Maindata);		
    while (1)
    {
#if 0
        memset(cpu_id_null,0,sizeof(cpu_id_null));    //必须清零 否则会乱码
        ReturnCMDResult(cpu_id_null,CMD_CPU_USE);
        cpu_id = atof(cpu_id_null);
#if 0
        printf("cpu_id=%f",cpu_id);
#endif
        sleep(1);
        Maindata->cpu_use = 100.0-cpu_id;
#endif
		sleep(10);
    }
    return 0;
}
/*
	mem use
	ZCJ
	20201204
*/
void  *thread_mem_buff(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while (1)
    {

        memset(Maindata->memery_buff,0,sizeof(Maindata->memery_buff)); //love time
        ReturnCMDResult(Maindata->memery_buff,CMD_Memry_buff);
		sleep(1);
    }
    return 0;
}
void  *thread_mem_cache(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while (1)
    {
        memset(Maindata->memery_cache,0,sizeof(Maindata->memery_cache)); //love time
        ReturnCMDResult(Maindata->memery_cache,CMD_Memry_cache);
		sleep(1);
    }
    return 0;
}
void  *thread_mem_free(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    while (1)
    {
        memset(Maindata->memery_free,0,sizeof(Maindata->memery_free)); //love time
        ReturnCMDResult(Maindata->memery_free,CMD_Memry_free);
		sleep(1);
    }
    return 0;
}

void  *thread_mem_use(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;

    pthread_t pidmem_buff;
    pthread_create(&pidmem_buff,0,thread_mem_buff,Maindata);
    pthread_t pidmem_cache;
    pthread_create(&pidmem_cache,0,thread_mem_cache,Maindata);
    pthread_t pidmem_free;
    pthread_create(&pidmem_free,0,thread_mem_free,Maindata);	
    while (1)
    {
		sleep(10);
    }
    return 0;
}

void  *CMDReturn(void *arg)
{
    MAIN_STRUCT *Maindata = (MAIN_STRUCT *)arg;
    pthread_t pidRXnetspeed;
    pthread_create(&pidRXnetspeed,0,RXnetspeed,Maindata);
    pthread_t pidTXnetspeed;
    pthread_create(&pidTXnetspeed,0,TXnetspeed,Maindata);

    pthread_t pidRXnetspeed_wlan0;
    pthread_create(&pidRXnetspeed_wlan0,0,RXnetspeed_wlan0,Maindata);
    pthread_t pidTXnetspeed_wlan0;
    pthread_create(&pidTXnetspeed_wlan0,0,TXnetspeed_wlan0,Maindata);

    pthread_t pidcpu_use;
    pthread_create(&pidcpu_use,0,thread_cpu_use,Maindata);

    pthread_t pidmem_use;
    pthread_create(&pidmem_use,0,thread_mem_use,Maindata);	

    while(1)
    {
        memset(Maindata->curtime,0,sizeof(Maindata->curtime));    //必须清零 否则会乱码
        ReturnCMDResult(Maindata->curtime,CurTime);
        //printf("curtime=%s\n",Maindata->curtime);

        memset(Maindata->curdate,0,sizeof(Maindata->curdate));    //必须清零 否则会乱码
        ReturnCMDResult(Maindata->curdate,CurDATE);

        memset(Maindata->systemp,0,sizeof(Maindata->systemp));
        ReturnCMDResult(Maindata->systemp,RunCpuTemp);

        memset(Maindata->curIP,0,sizeof(Maindata->curIP));
        ReturnCMDResult(Maindata->curIP,CurIP);

        memset(Maindata->curIP_wlan0,0,sizeof(Maindata->curIP_wlan0));
        ReturnCMDResult(Maindata->curIP_wlan0,CurIP_wlan0);

        memset(Maindata->curtime_s,0,sizeof(Maindata->curtime_s)); //cur second time
        ReturnCMDResult(Maindata->curtime_s,Curtime_s);

        memset(Maindata->keytime_s,0,sizeof(Maindata->keytime_s)); //love time
        ReturnCMDResult(Maindata->keytime_s,Keytime_s);

#if 0
        memset(Maindata->memery_total,0,sizeof(Maindata->memery_total)); //love time
        ReturnCMDResult(Maindata->memery_total,CMD_Memry_total);

        memset(Maindata->memery_free,0,sizeof(Maindata->memery_free)); //love time
        ReturnCMDResult(Maindata->memery_free,CMD_Memry_free);
#endif
        memset(Maindata->disk_total,0,sizeof(Maindata->disk_total)); //love time
        ReturnCMDResult(Maindata->disk_total,CMD_DISK_total);

        memset(Maindata->disk_use,0,sizeof(Maindata->disk_use)); //love time
        ReturnCMDResult(Maindata->disk_use,CMD_DISK_use);

        memset(Maindata->disk_rate,0,sizeof(Maindata->disk_rate)); //love time
        ReturnCMDResult(Maindata->disk_rate,CMD_DISK_UsetoTotal);

        memset(Maindata->ip_vpn_google_netspeed,0,sizeof(Maindata->ip_vpn_google_netspeed)); //love time
        ReturnCMDResult(Maindata->ip_vpn_google_netspeed,CMD_VPN_GOOGLE_SPEED);
		//printf("CMD_VPN_GOOGLE_SPEED = %s\n" ,Maindata->ip_vpn_google_netspeed );

        //printf("curtemp=%s\n",Maindata->systemp);
        ///ReturnCMDResult(arg,RunCpuTemp);

        //OpenCpuTemp();
        sleep(1);
    }
}



/**

 * @brief   	查看相关命令并返回
 * @Name	 	int main Name ( void sth)
 * @param   	None
 * @retval  	None
 * @Author  	ZCJ
 * @Date 	 	2020/06/ Create
 * @Version 	1.0 2020/08/17
 *		     	1.1 2020/08/17 change sth
 * @Note

 **/

int OpenCpuTemp(void)
{
    int fd;
    double temp = 0;
    char buffer[MAX_SIZE];
    int i;

    while(i < 100)
    {
        i+=1;

        //寤舵椂1s
        sleep(1);

        //鎵撳紑鏂囦欢
        fd = open(TEMP_PATH,O_RDONLY);
        if(fd < 0)
        {
            fprintf(stderr,"Failed to open thermal_zone0/temp\n");
            return - 1;
        }

        //璇诲彇鏂囦欢
        if(read(fd,buffer,MAX_SIZE) < 0)
        {
            fprintf(stderr,"Failed to read temp\n");
            return -1;
        }

        //璁＄畻娓╁害鍊?
        temp = atoi(buffer) / 1000.0;

        //鎵撳嵃杈撳嚭娓╁害
        printf("Temp:%.4f\n",temp);

        //鍏抽棴鏂囦欢
        close(fd);
    }
    return 0;
}

/*将指令读取到的数据写入到txt文本中
	ZCJ
	20201203
	*/
int write_cmd_to_txt( void )
{
    FILE   *stream;
    FILE    *wstream;
    char   buf[1024];
    memset( buf, '/0', sizeof(buf) );//初始化buf,以免后面写如乱码到文件中
    stream = popen( "ls -l", "r" ); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
    wstream = fopen( "test_popen.txt", "w+"); //新建一个可写的文件
    fread( buf, sizeof(char), sizeof(buf), stream); //将刚刚FILE* stream的数据流读取到buf中
    fwrite( buf, 1, sizeof(buf), wstream );//将buf中的数据写到FILE    *wstream对应的流中，也是写到文件中
    pclose( stream );
    fclose( wstream );
    return 0;
}


