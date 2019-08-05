/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: key.h
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

#ifndef __KEY_H_
#define __KEY_H_

#include <15W4KxxS4.h>
#include <stdio.h>
#include <intrins.h>
#include "config.h"

sbit  KEY1 = P3 ^ 5;//OK SET
sbit  KEY2 = P3 ^ 6;//UP  PLUS
sbit  KEY3 = P3 ^ 7;//DOWN MINUS
sbit  KEY4 = P2 ^ 0;//RETURN BACK

enum _key_code_e_ { KEY_SET,KEY_PLUS,KEY_MINUS,KEY_RETURN,KEY_UNKNOWN,KEY_NONE};
enum  _key_type_e_ {KEY_PRESSED,KEY_REPEATED,KEY_RELEASED};

void  key_init(void);
void key_Task(void);
unsigned char key_InsertKeyCode(unsigned char key_code, unsigned char state);
unsigned char key_GetKeyCode(unsigned char *pcode,unsigned char *pstate);

#endif


/********************************End of File************************************/