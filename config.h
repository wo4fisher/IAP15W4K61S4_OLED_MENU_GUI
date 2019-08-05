/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2018, Main, China, QD.
**                           All Rights Reserved
**
**                                By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: config.h
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

#ifndef __CONFIG_H_
#define __CONFIG_H_

//类型定义
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
typedef  char int8;
typedef  int  int16;
typedef  long  int32;

#define FOSC 11059200L          //系统频率
#define BAUD1152 115200             //串口波特率115200
#define BAUD96   9600               //串口波特率9600

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

#define PARITYBIT1 NONE_PARITY   //定义校验位
#define PARITYBIT2 NONE_PARITY   //定义校验位

#define SUCCESS 0
#define FAIL    1

#endif


/********************************End of File************************************/
