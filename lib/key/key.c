/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                 By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: key.c
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
#include "key.h"
#include "led.h"
#include "delay.h"
#include "config.h"
#include "timer.h"
#include "usart.h"
#include "buzzer.h"

/*******************************************************************************
** 函数名称: key_init
** 功能描述:
** 参数说明: None
** 返回说明: None
** 创建人员: wht
** 创建日期: 2019-02-18
**------------------------------------------------------------------------------
** 修改人员:wht
** 修改日期:
** 修改描述:
**------------------------------------------------------------------------------
********************************************************************************/
void  key_init(void)
{
    KEY1 = 1;
    KEY2 = 1;
    KEY3 = 1;
    KEY4 = 1;
}


static unsigned char ScanKeyCode(void)
{
    /*TEST_KEY on the head board.*/
    if(KEY1 == 0) return KEY_SET;
    if(KEY2 == 0) return KEY_PLUS;
    if(KEY3 == 0) return KEY_MINUS;
    if(KEY4 == 0) return KEY_RETURN;
    /*No key pressed, return key_none.*/
    return KEY_NONE;
}

void key_Task(void)
{
    unsigned char key_code;
    unsigned long ticks = time_GetTicks();
    static unsigned long idata oldticks;
    static unsigned char idata old_code, state = 0;
    switch(state)
    {
    case 0:
        old_code = ScanKeyCode();
        if(old_code == KEY_NONE) break;
        oldticks = ticks;
        state = 1;
        break;
    case 1: /*de-bounce*/
        if(ticks - oldticks < 20) break;
        key_code = ScanKeyCode();
        if(key_code == old_code)
        {
            key_InsertKeyCode(key_code, KEY_PRESSED);
            EA = 0;
            play_tick();
            EA = 1;
            oldticks = ticks;
            state = 2;
        }
        else
        {
            state = 0;
        }
        break;
    case 2: /*Check for repeat*/
        key_code = ScanKeyCode();
        if(key_code == KEY_NONE)
        {
            oldticks = ticks;
            state = 3;
        }
        else
        {
            if(ticks - oldticks > 250)
            {
                key_InsertKeyCode(old_code, KEY_REPEATED);
                EA = 0;
                play_tick();
                EA = 1;
                oldticks = ticks;
            }
        }
        break;
    case 3: /*check for release*/
        if(ticks - oldticks < 20) break;
        key_code = ScanKeyCode();
        if(key_code == KEY_NONE)
        {
            key_InsertKeyCode(old_code, KEY_RELEASED);
            state = 0;
        }
        else
        {
            oldticks = ticks;
        }
        break;
    default:
        break;
    }
}

#define KEY_FIFOLEN 4
static struct _key_fifo_tag_
{
    unsigned char keycode[KEY_FIFOLEN];
    unsigned char state[KEY_FIFOLEN];
    unsigned char rear;
    unsigned char top;
} idata g_key_fifo;

unsigned char key_GetKeyCode(unsigned char *pcode, unsigned char *pstate)
{
    unsigned char rear = g_key_fifo.rear;
    if(rear != g_key_fifo.top)
    {
        if(pcode != NULL)*pcode = g_key_fifo.keycode[rear];
        if(pstate != NULL)*pstate = g_key_fifo.state[rear];
        rear++;
        if(rear >= KEY_FIFOLEN) rear = 0;
        g_key_fifo.rear = rear;
        return 1;
    }
    return 0;
}

unsigned char key_InsertKeyCode(unsigned char keycode, unsigned char state)
{
    unsigned char top, next;

    //printf("insert key: code = %bu state=%bu\r\n",keycode,state);
    top = g_key_fifo.top;
    next = g_key_fifo.top + 1;
    if(next >= KEY_FIFOLEN) next = 0;
    if(next != g_key_fifo.rear)
    {
        g_key_fifo.keycode[top] = keycode;
        g_key_fifo.state[top] = state;
        g_key_fifo.top = next;
        return 1;
    }
    return 0;
}

/********************************End of File************************************/

