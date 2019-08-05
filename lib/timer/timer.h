/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: timer.h
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

#ifndef __TIMER_H_
#define __TIMER_H_

#include <15W4KxxS4.h>
#include <intrins.h>
#include "config.h"

void Timer4Init(void);
unsigned long time_GetTicks(void);
void Timer3Init(void);
#define T3_START()   T4T3M|=0X08  
#define T3_STOP()    T4T3M &=~0X08
#endif


/********************************End of File************************************/