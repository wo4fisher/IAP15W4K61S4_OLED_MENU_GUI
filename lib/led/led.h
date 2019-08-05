/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: led.h
** 创建人员: wht
** 创建日期: 2019-01-31
** 文档描述:
**
**----------------------------------版本信息------------------------------------
** 版本代号: V0.1
** 版本说明: 初始版本
**
**------------------------------------------------------------------------------
\********************************End of Head************************************/

#ifndef __LED_H_
#define __LED_H_

#include <15W4KxxS4.h>

sbit   LED1 = P0 ^ 4;
sbit   LED2 = P0 ^ 3;
sbit   LED3 = P0 ^ 2;

sbit   LED4 = P0 ^ 1;
sbit   LED5 = P0 ^ 0;
sbit   LED6 = P2 ^ 7;

sbit   LED7 = P2 ^ 6;
sbit   LED8 = P2 ^ 5;
sbit   LED9 = P2 ^ 4;

#define   LEDR1ON()   LED1=0
#define   LEDR1OFF()   LED1=1
#define   LEDG1ON()   LED2=0
#define   LEDG1OFF()   LED2=1
#define   LEDB1ON()   LED3=0
#define   LEDB1OFF()   LED3=1
#define   LEDR2ON()   LED4=0
#define   LEDR2OFF()   LED4=1
#define   LEDG2ON()   LED5=0
#define   LEDG2OFF()   LED5=1
#define   LEDB2ON()   LED6=0
#define   LEDB2OFF()   LED6=1
#define   LEDR3ON()   LED7=0
#define   LEDR3OFF()   LED7=1
#define   LEDG3ON()   LED8=0
#define   LEDG3OFF()   LED8=1
#define   LEDB3ON()   LED9=0
#define   LEDB3OFF()   LED9=1

void  led_init(void);
void  led_r_on(void);
void  led_g_on(void);
void  led_b_on(void);
void  led_r_off(void);
void  led_g_off(void);
void  led_b_off(void);
void  led_all_on(void);
void  led_all_off(void);
#endif


/********************************End of File************************************/