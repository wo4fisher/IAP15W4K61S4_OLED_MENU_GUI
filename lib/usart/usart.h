/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2018, Main, China, QD.
**                           All Rights Reserved
**
**                                By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: usart.h
** 创建人员: wht
** 创建日期: 2018-12-21
** 文档描述:
**
**----------------------------------版本信息------------------------------------
** 版本代号: V0.1
** 版本说明: 初始版本
**
**------------------------------------------------------------------------------
\********************************End of Head************************************/

#ifndef __USART_H_
#define __USART_H_

#include <15W4KxxS4.h>
#include "config.h"

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3

#define S2_S0 0x01              //P_SW2.0
#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

#define USART1   1
#define USART2   2


void usart_init(int8 usartNum);
void SendData(int8 dat,int8 usartNum);
void SendString(int8 *s,int8 usartNum);
int8 putchar(int8 c);

#endif


/********************************End of File************************************/