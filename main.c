/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                 By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: main.c
** 创建人员: wht
** 创建日期: 2019-02-17
** 文档描述:
**
**----------------------------------版本信息------------------------------------
** 版本代号: V0.1
** 版本说明: 初始版本
**
**------------------------------------------------------------------------------
\********************************End of Head************************************/
#include <15W4KxxS4.h>
#include <intrins.h>
#include "stdio.h"
#include "config.h"
#include "delay.h"
#include "oled.h"
#include "bmp.h"
#include "led.h"
#include "key.h"
#include "ds1302.h"
#include "usart.h"
#include "DHT11.H"
#include "timer.h"
#include "gui.h"
#include "buzzer.h"

void PWMIO_init(void);
//void ProcessKey(void)
//{
//    unsigned char ret, keycode, keystate;

//    ret = key_GetKeyCode(&keycode, &keystate);
//    if(ret == 0) return;
//    printf("keycode=%bu   key_state=%bu\r\n", keycode, keystate);
//}
int main ( void )
{
    PWMIO_init();
    AUXR = 0X00;//串口1 串口2  定时器1 定时器2 速度选择，bit1：extram允许位。
    usart_init ( USART1 );
    //usart_init ( USART2 );
    //Ds1302Init();
    led_init();
    key_init();
	
    play_tick();
	
    OLED_DC_Clr();
    delayxms ( 500 );
    OLED_CS_Clr();

    delayxms ( 1000 );
    OLED_Init();            //初始化OLED
    OLED_Clear()    ;
    delayxms ( 200 );

    Timer4Init();     //多任务设计时间片定时器初始化
    printf("Hello world.\r\n");

    OLED_Clear();
    delayxms ( 300 );

    EA = 1;    //使能全局中断

    gui_DlgDesktopOpen(); //GUI初始窗口/对话框打开之后，开始使用gui_task()调度对话框

    while ( 1 )
    {
        key_Task();
        //ProcessKey();
        gui_Task();
    }

}
void PWMIO_init(void)
{
    /////////////////////////////////////////////////
    //注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
    //      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
    //相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
    //        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
    /////////////////////////////////////////////////
    P0M1 = 0x00;
    P0M0 = 0x00;    //设置P0.0~P0.7为准双向口
    P1M1 = 0x00;
    P1M0 = 0x00;    //设置P1.0~P1.7为准双向口
    P2M1 = 0x00;
    P2M0 = 0x00;    //设置P2.0~P2.7为准双向口
    P3M1 = 0x00;
    P3M0 = 0x00;    //设置P3.0~P3.7为准双向口
    P4M1 = 0x00;
    P4M0 = 0x00;    //设置P4.0~P4.7为准双向口
    P5M1 = 0x00;
    P5M0 = 0x00;    //设置P5.0~P5.5为准双向口
    P6M1 = 0x00;
    P6M0 = 0x00;    //设置P6.0~P6.7为准双向口
    P7M1 = 0x00;
    P7M0 = 0x00;    //设置P7.0~P7.7为准双向口
}
/********************************End of File************************************/

