/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2018, Main, China, QD.
**                           All Rights Reserved
**
**                                 By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: usart2.c
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
#include <15W4KxxS4.h>
#include "config.h"
#include "usart.h"
#include "delay.h"
//#include "atcmd.h"
bit busy1;
bit busy2;

void usart_init( int8 usartNum )
{

    if(usartNum == USART1)
    {
        ACC = P_SW1;
        ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
        P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)

        //  ACC = P_SW1;
        //  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
        //  ACC |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
        //  P_SW1 = ACC;
        //
        //  ACC = P_SW1;
        //  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
        //  ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
        //  P_SW1 = ACC;

#if (PARITYBIT1 == NONE_PARITY)
        SCON = 0x50;                //8位可变波特率
#endif
        AUXR |= 0x40;                //定时器1为1T模式
        TMOD = 0x00;                //定时器1为模式0(16位自动重载)
        TL1 = (65536 - (FOSC / 4 / BAUD1152)); //设置波特率重装值
        TH1 = (65536 - (FOSC / 4 / BAUD1152)) >> 8;
        TR1 = 1;                    //定时器1开始启动
        ES = 1;                     //使能串口中断
        EA = 1;
    }
    else if ( usartNum == USART2 )
    {
        P_SW2 &= ~S2_S0;            //S2_S0=0 (P1.0/RxD2, P1.1/TxD2)
        //  P_SW2 |= S2_S0;             //S2_S0=1 (P4.6/RxD2_2, P4.7/TxD2_2)

#if (PARITYBIT2 == NONE_PARITY)
        S2CON = 0x50;               //8位可变波特率
#endif
        T2L = ( 65536 - ( FOSC / 4 / BAUD1152 ) ); //设置波特率重装值
        T2H = ( 65536 - ( FOSC / 4 / BAUD1152 ) ) >> 8;
        AUXR |= 0x14;                //T2为1T模式, 并启动定时器2
        IE2 = 0x01;                 //使能串口2中断
        EA = 1;
    }

}

/*----------------------------
UART2 中断服务程序
-----------------------------*/
//void Uart2() interrupt 8 using 1
//{
//    if (S2CON & S2RI)
//    {
//        if(esp8266_recv_cnt>=RECVMAXLEN)
//            esp8266_recv_cnt=0;
//        esp8266_recv_buf[esp8266_recv_cnt++]=S2BUF;//保存串口接收数据
//        S2CON &= ~S2RI;         //清除S2RI位
//    }
//    if (S2CON & S2TI)
//    {
//        S2CON &= ~S2TI;         //清除S2TI位
//        busy2 = 0;               //清忙标志
//    }
//}

/*----------------------------
UART1 中断服务程序
-----------------------------*/
void Uart1() interrupt 4 using 2
{
    if (RI)
    {
        P0 = SBUF;
        RI = 0;                 //清除RI位

    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy1 = 0;               //清忙标志
    }
}
/*----------------------------
发送串口数据
----------------------------*/
void SendData(int8 dat, int8 usartNum)
{
    if ( usartNum == USART2 )
    {
        while (busy2);               //等待前面的数据发送完成
        ACC = dat;                   //获取校验位P (PSW.0)
        busy2 = 1;
        S2BUF = ACC;                 //写数据到UART2数据寄存器
    }
    else if(usartNum == USART1)
    {
        while (busy1);               //等待前面的数据发送完成
        ACC = dat;                  //获取校验位P (PSW.0)
        busy1 = 1;
        SBUF = ACC;                 //写数据到UART数据寄存器
    }
}
/*----------------------------
发送串口字符串
----------------------------*/
void SendString( int8 *s, int8 usartNum )
{
    if ( usartNum == USART2 )
    {
        while (*s)                  //检测字符串结束标志
        {
            SendData(*s++, USART2);        //发送当前字符
        }
    }
    else if(usartNum == USART1)
    {
        while (*s)                  //检测字符串结束标志
        {
            SendData(*s++, USART1);        //发送当前字符
        }
    }

}
/*----------------------------
putchar()
----------------------------*/
int8 putchar ( int8 c)
{
    SendData(c, USART1);        //发送当前字符
    return c;
}

/********************************End of File************************************/