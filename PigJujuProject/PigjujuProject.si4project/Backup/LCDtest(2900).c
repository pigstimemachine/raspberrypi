#include "./Config/DEV_Config.h"
#include "./LCD/LCD.h"
#include "./GUI/GUI_Paint.h"
#include "./GUI/GUI_BMP.h"
//#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()
#include "stdio.h"
#include<fcntl.h>
#include<unistd.h>
#include <pthread.h>
#include <string.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include "../ZCJlib/ZCJlib.h"

void *LCD_test(void *arg)

{
    MAIN_STRUCT *Maindata =(MAIN_STRUCT *)arg;

    UDOUBLE i=0,movex=200,movey;
    UDOUBLE cursecond,keysecond,totalday;
    float cur_mem_total,cur_mem_free,cur_mem_use;
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in3_LCD);

    /* Module Init */
    if(DEV_ModuleInit() != 0)
    {
        DEV_ModuleExit();
        exit(0);
    }
    /* LCD Init */
    printf("1.3inch LCD demo...\r\n");
//长宽改变后，初始化不成功 查询后发现是清零函数不成功！！！
    printf("start LCD init  \n");
    LCD_1in3_Init(HORIZONTAL);
    sleep(1);
    printf("LCD init finish \n");

    printf("start LCD LCD_1in3_Clear  \n");
    LCD_1in3_Clear(RED);
    printf("LCD LCD_1in3_Clear finish \n");
    sleep(1);
/////////////////////////////////////////////////////////////////////////////////

    UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);

    UDOUBLE *BlackImage;

    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // printf("size = %d\r\n",sizeof(BlackImage) / sizeof(UWORD));
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, WHITE, 16);
    while (1)
    {
        Paint_Clear(WHITE);
        i++;

        Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);//240 240
        Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
        Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

        Paint_DrawLine(20, 10, 70, 60, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(70, 10, 20, 60, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
        Paint_DrawLine(170, 15, 170, 55, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
        Paint_DrawLine(150, 35, 190, 35, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

        Paint_DrawRectangle(20, 10, 70, 60, BLUE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
        Paint_DrawRectangle(85, 10, 130, 60, BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);


		GUI_ReadBmp("new.txt");

			Paint_DrawCircle(Maindata->testcnt, 35, 20, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

        

		
        //  Paint_DrawCircle(170, 85, 20, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);

        //Paint_DrawString_EN(10, 60, Maindata->DHT11_humidity, &Font16, WHITE, BLACK);
        {

            Paint_DrawNum(10, 60, Maindata->DHT11_humidity, &Font16, BLUE, WHITE);
            Paint_DrawString_EN(33, 60, "%RH", &Font16, WHITE, BLACK);

            Paint_DrawNum(80, 60, Maindata->DHT11_temp, &Font16, BLUE, WHITE);
            Paint_DrawString_EN(103, 60, "'C", &Font16, WHITE, BLACK);			
        }

        Paint_DrawString_EN(170, 60, "hello world", &Font16, WHITE, BLACK);
        Paint_DrawString_EN(170, 80,"0.57721566", &Font16,  WHITE, BLACK);


        //Paint_DrawNum(150, 0,i, &Font16, RED, WHITE);
		Paint_DrawNum(150, 0,Maindata->testcnt, &Font16, RED, WHITE);

        // Paint_DrawNum(20, 200, 123456789, &Font20, BLUE, IMAGE_BACKGROUND);

        //Paint_DrawString_EN(5, 90, "XiongGu", &Font20, WHITE, BLACK);


        {
            Paint_DrawString_EN(10, 80, "Cpu:", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(55, 80, Maindata->cpu_usUSE, &Font16, WHITE, BLACK);
            Paint_DrawString_EN(80, 80, "/", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(95, 80, Maindata->cpu_syUSE, &Font16, WHITE, BLACK);
            Paint_DrawString_EN(120, 80, "/", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(135, 80, Maindata->cpu_idFree, &Font16, WHITE, BLACK);
            //Paint_DrawNum(60, 120, Maindata->cpu_use, &Font16, BLUE, WHITE);
            //Paint_DrawString_EN(90, 120, "%", &Font16, WHITE, BLACK);

        }
        {
            /*
                cur_mem_total = atof(Maindata->memery_total);
                cur_mem_free = atof(Maindata->memery_free);
                cur_mem_use = cur_mem_total - cur_mem_free;
                */
            Paint_DrawString_EN(10, 100, "Mem:", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(55, 100, Maindata->memery_buff, &Font16, WHITE, BLACK);
            Paint_DrawString_EN(120, 100, "/", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(135, 100, Maindata->memery_cache, &Font16, WHITE, BLACK);
            Paint_DrawString_EN(220, 100, "/", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(235, 100, Maindata->memery_free, &Font16, WHITE, BLACK);

        }
        {
            Paint_DrawString_EN(10, 120, "Disk:", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(70, 120, "Use:", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(115, 120, Maindata->disk_use, &Font16, WHITE, BLACK);

            Paint_DrawString_EN(160, 120, "Total:", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(225, 120, Maindata->disk_total, &Font16, WHITE, BLACK);


            Paint_DrawString_EN(275, 120, Maindata->disk_rate, &Font16, WHITE, BLACK);

        }




        {
            Paint_DrawString_EN(10, 140, "RX:", &Font16, WHITE, BLACK);
            Paint_DrawNum(40, 140, Maindata->RX_netspeed_wlan0, &Font16, BLUE, WHITE);
            Paint_DrawString_EN(95, 140, "KB/s", &Font16, WHITE, BLACK);

            Paint_DrawString_EN(155, 140, "TX:", &Font16, WHITE, BLACK);
            Paint_DrawNum(185, 140, Maindata->TX_netspeed_wlan0, &Font16, BLUE, WHITE);
            Paint_DrawString_EN(240, 140, "KB/s", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(290, 140, "wl", &Font16, WHITE, BLACK);
        }

        {

            /*if (Maindata->RX_netspeed > 1024.0 )
            	{
            		Maindata->RX_netspeed = Maindata->RX_netspeed/1024.0 ;
            		Paint_DrawString_EN(100, 160, "MB/s", &Font16, WHITE, BLACK);
            	}
            else
            	{
            		Paint_DrawString_EN(100, 160, "KB/s", &Font16, WHITE, BLACK);
            	}
            	*/
            //Paint_DrawString_EN(5, 160, "wlan0", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(10, 160, "RX:", &Font16, WHITE, BLACK);
            Paint_DrawNum(40, 160, Maindata->RX_netspeed_eth0, &Font16, BLUE, WHITE);
            Paint_DrawString_EN(95, 160, "KB/s", &Font16, WHITE, BLACK);

            Paint_DrawString_EN(155, 160, "TX:", &Font16, WHITE, BLACK);
            Paint_DrawNum(185, 160, Maindata->TX_netspeed_eth0, &Font16, BLUE, WHITE);
            Paint_DrawString_EN(240, 160, "KB/s", &Font16, WHITE, BLACK);
            Paint_DrawString_EN(290, 160, "et", &Font16, WHITE, BLACK);
        }


        Paint_DrawString_EN(10, 180, Maindata->curIP, &Font16, WHITE, BLACK);
        Paint_DrawString_EN(155, 180, Maindata->curIP_wlan0, &Font16, WHITE, BLACK);


        Paint_DrawString_EN(10, 200, Maindata->curtime, &Font16, WHITE, BLACK);

        {
            cursecond = atoi(Maindata->curtime_s);
            //printf("cursecond=%ld",cursecond);
            keysecond = atoi(Maindata->keytime_s);
            //printf("keysecond=%ld",keysecond);
            totalday = ( cursecond - keysecond)/60/60/24;
            //printf("totalday=%ld",totalday);
            Paint_DrawNum(240, 200, totalday, &Font16, RED, WHITE);
        }

        Paint_DrawString_EN(10, 220, Maindata->curdate, &Font16, WHITE, BLACK);
        Paint_DrawString_EN(160, 220, Maindata->systemp, &Font16, WHITE, BLACK);


        LCD_1in3_Display(BlackImage);
        usleep(1);

    }
    // /*3.Refresh the picture in RAM to LCD*/
    //LCD_1in3_Display(BlackImage);
    DEV_Delay_ms(2000);

    // /* show bmp */
    // printf("show bmp\r\n");
    // GUI_ReadBmp("./pic/pic.bmp");

    // LCD_1in3_Display(BlackImage);
    // DEV_Delay_ms(2000);


    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    DEV_ModuleExit();
    return 0;
}


