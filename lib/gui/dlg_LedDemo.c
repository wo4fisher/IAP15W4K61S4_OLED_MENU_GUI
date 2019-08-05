/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                 By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: dlg_LedDemo.c
** 创建人员: wht
** 创建日期: 2019-02-19
** 文档描述:
**
**----------------------------------版本信息------------------------------------
** 版本代号: V0.1
** 版本说明: 初始版本
**
**------------------------------------------------------------------------------
\********************************End of Head************************************/
#include "gui.h"
#include "led.h"
#include "key.h"
#include "timer.h"

#define LED_FLASH_SPAN   300
#define LED_FLASH_SPANP10   30
static uint8 idata g_con_active = 0; //当前对话框激活的控件索引号

static const struct gui_control code g_con_list[] =
{
    {CON_BMPBUTTON, 128 - 16, 7, icon_backup},
    {CON_TXTBUTTON, 10, 3, "1.mode 1"},
    {CON_TXTBUTTON, 10, 4, "2.mode 2"},
    {CON_TXTBUTTON, 10, 5, "3.mode 3"},
    {CON_ENDFLAG, 0, 0, NULL},
};
void flash1(uint16 span, uint8 spanmini)
{
    static uint16 xdata count = 0;
    if(count++ > span)count = 0;
    switch (count / spanmini)
    {
    case 0:
        led_r_on();
        break;
    case 1:
        led_r_off();
        break;
    case 2:
        led_g_on();
        break;
    case 3:
        led_g_off();
        break;
    case 4:
        led_b_on();
        break;
    case 5:
        led_b_off();
        break;
    default:
        led_all_off();
        break;
    }
}
void flash2(uint16 span, uint8 spanmini)
{
    static uint16 xdata count = 0;
    if(count++ > span)count = 0;
    switch (count / spanmini)
    {
    case 0:
        LEDR1ON();
        break;
    case 1:
        LEDR2ON();
        break;
    case 2:
        LEDR3ON();
        break;
    case 3:
    case 4:
    case 5:
        led_r_off();
        break;
    case 6:
        LEDG1ON();
        break;
    case 7:
        LEDG2ON();
        break;
    case 8:
        LEDG3ON();
        break;
    case 9:
    case 10:
    case 11:
        led_g_off();
        break;
    case 12:
        LEDB1ON();
        break;
    case 13:
        LEDB2ON();
        break;
    case 14:
        LEDB3ON();
        break;
    case 15:
    case 16:
    case 17:
        led_b_off();
        break;
    default:
        led_all_off();
        break;
    }
}

void flash3(uint16 span, uint8 spanmini)
{
    static uint16 xdata count = 0;
    if(count++ > span)count = 0;
    switch (count / spanmini)
    {
    case 0:
        led_all_off();
        break;
    case 1:
        LEDR1ON();
        LEDG2ON();
        LEDR3ON();
        break;
    case 2:
        LEDR1OFF();
        LEDG2OFF();
        LEDR3OFF();
        LEDG1ON();
        LEDB2ON();
        LEDG3ON();
        break;
    case 3:
        LEDG1OFF();
        LEDB2OFF();
        LEDG3OFF();
        LEDB1ON();
        LEDR2ON();
        LEDB3ON();
        break;
    default:
        led_all_off();
        break;
    }
}

void led_flash(uint8 mode) //传入参数是  g_con_active
{
    switch (mode)
    {
    case 0:
        led_all_off();
        break;
    case 1:
        flash1(180, 30);
        break;
    case 2:
        flash2(180, 10);
        break;
    case 3:
        flash3(160, 40);
        break;
    default :
        break;

    }
}
static void InitLEDDemo(void)
{
    led_all_off();
    switch(g_con_active)
    {
    case 0:
        break;
    case 1:
        break;
    default:
        break;
    }
}

void gui_DlgLedDemoProc(uint8 msg_type, uint8 msg_code)
{
    if(msg_type == WM_TIMER)
    {
        /*Add your code here.*/
        led_flash(g_con_active);
    }
    else if(msg_type == WM_KEYPRESSED || msg_type == WM_KEYREPEATED)
    {
        led_all_off();
        if(msg_code == KEY_PLUS)
        {
            gui_SearchPrevControl(g_con_list, &g_con_active);
            return;
        }
        else if(msg_code == KEY_MINUS)
        {
            gui_SearchNextControl(g_con_list, &g_con_active);
            return;
        }
        else if(msg_code == KEY_RETURN)
        {
            gui_DlgMainMenuOpen();
            return;
        }
        else if(msg_code == KEY_SET)
        {
            if(g_con_active == 0)
            {
                gui_DlgMainMenuOpen();
            }
            else
            {
                InitLEDDemo();
            }
            return;
        }
    }
    gui_DlgDefaultProc(msg_type, msg_code);
}

void gui_DlgLedDemoOpen(void)
{
    gui_DlgSetActive(DLG_LEDDEMO);
    memset(g_con_param_list, 0x00u, sizeof(g_con_param_list));
    g_con_active = 0;
    OLED_Clear();
    OLED_ShowString(38, 0, "LED", 16, NOMALCOLORMODE);
    OLED_ShowCHinese2(62, 0, "演示\0", NOMALCOLORMODE);
    gui_DrawAllControls(g_con_list, g_con_active);
    InitLEDDemo();
}


/********************************End of File************************************/