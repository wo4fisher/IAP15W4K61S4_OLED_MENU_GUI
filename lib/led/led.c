/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                 By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: led.c
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
#include "led.h"
#include "delay.h"
#include "config.h"



void led_init(void)
{
    LEDR1OFF();
    LEDG1OFF();
    LEDB1OFF();
    LEDR2OFF();
    LEDG2OFF();
    LEDB2OFF();
    LEDR3OFF();
    LEDG3OFF();
    LEDB3OFF();
}

void  led_r_on(void)
{
    LEDR1ON();
    LEDR2ON();
    LEDR3ON() ;
}
void led_g_on(void)
{
    LEDG1ON();
    LEDG2ON();
    LEDG3ON();
}
void led_b_on(void)
{
    LEDB1ON();
    LEDB2ON();
    LEDB3ON();
}
void led_r_off(void)
{
    LEDR1OFF();
    LEDR2OFF();
    LEDR3OFF();
}
void led_g_off(void)
{
    LEDG1OFF();
    LEDG2OFF();
    LEDG3OFF();
}
void led_b_off(void)
{
    LEDB1OFF();
    LEDB2OFF();
    LEDB3OFF();
}

void led_all_on(void)
{
    led_r_on();
    led_g_on();
    led_b_on();
}
void led_all_off(void)
{
    led_r_off();
    led_g_off();
    led_b_off();
}
/********************************End of File************************************/