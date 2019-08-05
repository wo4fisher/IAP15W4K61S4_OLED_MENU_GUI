#ifndef __DS1302_H_
#define __DS1302_H_

//---包含头文件---//
#include <15W4KxxS4.h>
#include <intrins.h>
#include "config.h"



//---定义ds1302使用的IO口---//
sbit DS1302_IO=P0^5;
sbit DS1302_RST=P0^6;
sbit DS1302_CLK=P0^7;

//---定义全局函数---//
void Ds1302Write(uint8 addr, uint8 dat);
uint8 Ds1302Read(uint8 addr);
void Ds1302Init(void);
void Ds1302ReadTime(void);

//---加入全局变量--//
extern uint8 TIME[7];   //加入全局变量
extern int8 OldTime[7];
#endif