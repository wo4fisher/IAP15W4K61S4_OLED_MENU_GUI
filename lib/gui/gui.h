/*
 * Copyright        : Shendong MCU studio
 * File Description : GUI sub-system header
 * Created          : oliverzhang@shendongmcu.com
 */

#ifndef __GUI_H__
#define __GUI_H__

#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "timer.h"
#include "oled.h"

#define g_style_normal 1
#define g_style_reverse 0

void gui_Task(void);
enum {WM_KEYPRESSED,WM_KEYREPEATED,WM_KEYRELEASED,WM_TIMER}; //定义消息类型枚举量
const char *gui_GetMsgCodeString(uint8 msg_code);   //获取消息代码
const char *gui_GetMsgTypeString(uint8 msg_type);    //获取消息类型
void gui_DlgSetActive(uint8 dlg_index);              //激活对话框
void gui_DlgDefaultProc(uint8 msg_type, uint8 msg_code); //

enum { DLG_DESKTOP=1, DLG_MAINMENU, DLG_KEYDEMO, DLG_LEDDEMO, DLG_RTCDEMO, DLG_BUZZERDEMO, DLG_DHTDEMO};

void gui_DlgDesktopOpen(void);
void gui_DlgDesktopProc(uint8 msg_type, uint8 msg_code);

void gui_DlgMainMenuOpen(void);
void gui_DlgMainMenuProc(uint8 msg_type, uint8 msg_code);

void gui_DlgKeyDemoOpen(void);
void gui_DlgKeyDemoProc(uint8 msg_type, uint8 msg_code);

void gui_DlgLedDemoOpen(void);
void gui_DlgLedDemoProc(uint8 msg_type, uint8 msg_code);

void gui_DlgRTCDemoOpen(void);
void gui_DlgRTCDemoProc(uint8 msg_type, uint8 msg_code);

void gui_DlgDHTDemoOpen(void);
void gui_DlgDHTDemoProc(uint8 msg_type, uint8 msg_code);

void gui_DlgBuzzerDemoOpen(void);
void gui_DlgBuzzerDemoProc(uint8 msg_type, uint8 msg_code);

enum {CON_ENDFLAG,CON_TXTBUTTON,,CON_TXTBUTTON_CHS,CON_BMPBUTTON,CON_NUMBUTTON,CON_CHECKBOX,CON_LIST};
struct gui_control
{
    uint8 type;
    uint16 x;
    uint16 y;
    const char *str;
};
#define CON_MAX_ITEMS 10  //每一页一个对话框，对话框中包含控件的最大个数

extern uint8 idata g_con_param_list[CON_MAX_ITEMS];

void gui_DrawControl(const struct gui_control *pcon, uint8 is_active);
void gui_DrawAllControls(const struct gui_control *plist, uint8 active);
void gui_SearchPrevControl(const struct gui_control *plist, uint8 *pactive);
void gui_SearchNextControl(const struct gui_control *plist, uint8 *pactive);


struct dlg_desktop_param
{
    uint32 oldticks;
};
struct dlg_key_demo_param
{
    uint8 state;
    uint32 oldticks;
    uint16 x;
    uint16 y;
};
struct dlg_led_demo_param
{
    uint8 dummy;
};
struct dlg_RTC_demo_param
{
    uint8 state; //用来设置显示状态还是设置状态，默认显示状态
    uint32 oldticks;
    uint16 x;
    uint16 y;
};
struct dlg_DHT_demo_param
{
    uint32 oldticks;
    uint16 x;
    uint16 y;
};
struct dlg_buzzer_demo_param
{
    uint32 oldticks;
    uint16 x;
    uint16 y;
};

//每一个窗口初始化时使用到，作为共用体，只有激活的对话框才会有实体，是每一个dlg的局部变量
union gui_all_dlg  
{
    struct dlg_desktop_param 			 desktop_param;
    struct dlg_key_demo_param 		 key_demo;
    struct dlg_led_demo_param 		 led_demo;
	  struct dlg_RTC_demo_param 		 rtc_demo;
		struct dlg_DHT_demo_param 		 dht_demo;
		struct dlg_buzzer_demo_param  buzzer_demo;
};
extern union gui_all_dlg xdata g_all_dlg;

#endif
