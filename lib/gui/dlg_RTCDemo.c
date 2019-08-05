/********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, Main, China, QD.
**                           All Rights Reserved
**
**                                 By(wo4fisher)
**                           http://www.wo4fisher.com
**
**----------------------------------文件信息------------------------------------
** 文件名称: dlg_RTCDemo.c
** 创建人员: wht
** 创建日期: 2019-06-06
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
#include "ds1302.h"

#define DISMODE 0
#define SETMODE 1

uint8  year[3] = {"--\0"}, month[3] = {"--\0"}, day[3] = {"--\0"}, hour[3] = {"--\0"}, minute[3] = {"--\0"}, second[3] = {"--\0"}, week_i[2] = {"0\0"};
bit  RTCMode = DISMODE; //实时时钟窗口的模式：显示时间模式和设置时间模式

static uint8 idata g_con_active = 0; //当前对话框激活的控件索引号
static bit DotFlash = 0;
static const struct gui_control code g_con_list[] =
{
    {CON_BMPBUTTON, 128 - 16, 7, icon_backup},  //0
    {CON_TXTBUTTON,  5, 7, "SET"}, //8号字      //1
    {CON_TXTBUTTON, 40, 3, year},//16号字       //2
    {CON_TXTBUTTON, 64, 3, month},              //3
    {CON_TXTBUTTON, 88, 3, day},               //4
    {CON_TXTBUTTON, 14, 5, hour},                //5
    {CON_TXTBUTTON, 38, 5, minute},               //6
    {CON_TXTBUTTON, 62, 5, second},               //7
    {CON_TXTBUTTON, 104, 5, week_i},             //8
    {CON_ENDFLAG, 0, 0, NULL},
};
/*******************************************************************************
* 函 数 名         : DEC2BCD
* 函数功能         : 设置模式转换为显示模式时，把修改的参数进行进制转换，并保存到TIME[]中
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void  DEC2BCD(void)
{
    TIME[6] = ((OldTime[0] / 10) << 4) + (OldTime[0] % 10);
    TIME[4] = ((OldTime[1] / 10) << 4) + (OldTime[1] % 10);
    TIME[3] = ((OldTime[2] / 10) << 4) + (OldTime[2] % 10);
    TIME[2] = ((OldTime[3] / 10) << 4) + (OldTime[3] % 10);
    TIME[1] = ((OldTime[4] / 10) << 4) + (OldTime[4] % 10);
    TIME[0] = ((OldTime[5] / 10) << 4) + (OldTime[5] % 10);
    TIME[5] = ((OldTime[6] / 10) << 4) + (OldTime[6] % 10);
}
/*******************************************************************************
* 函 数 名         : BCD2DEC
* 函数功能         : 显示模式转换为设置模式时，把TIME[]中保存的时间最新值进行进制转化后保存到OLDTIME[]中
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void BCD2DEC(void)//转换时间顺序，并转换进制为10进制
{
    OldTime[0] = (TIME[6] >> 4) * 10 + (TIME[6] & 0x0f);
    OldTime[1] = (TIME[4] >> 4) * 10 + (TIME[4] & 0x0f);
    OldTime[2] = (TIME[3] >> 4) * 10 + (TIME[3] & 0x0f);
    OldTime[3] = (TIME[2] >> 4) * 10 + (TIME[2] & 0x0f);
    OldTime[4] = (TIME[1] >> 4) * 10 + (TIME[1] & 0x0f);
    OldTime[5] = (TIME[0] >> 4) * 10 + (TIME[0] & 0x0f);
    OldTime[6] = (TIME[5] >> 4) * 10 + (TIME[5] & 0x0f);
}
/*******************************************************************************
* 函 数 名         : HEXConvDT2Str
* 函数功能         : 正常显示模式时，把BCD码转换为字符串
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void  HEXConvDT2Str(void)
{
    year[0] = ( TIME[6] >> 4 ) + '0';
    year[1] = ( TIME[6] & 0x0f ) + '0';

    month[0] = ( TIME[4] >> 4) + '0';
    //if ( month[0] == '0' ) month[0] = ' ';
    month[1] = ( TIME[4] & 0x0f ) + '0';

    day[0] = ( TIME[3] >> 4) + '0';
    //if ( day[0] == '0' ) day[0] = ' ';
    day[1] = ( TIME[3] & 0x0f ) + '0';

    week_i[0] = (TIME[5] & 0x07) + '0' ;

    hour[0] = ( TIME[2] >> 4) + '0';
    //if ( hour[0] == '0' ) hour[0] = ' ';
    hour[1] = ( TIME[2] & 0x0f ) + '0';

    minute[0] = ( TIME[1] >> 4) + '0';
    // if ( minute[0] == '0' ) minute[0] = ' ';
    minute[1] = ( TIME[1] & 0x0f ) + '0';

    second[0] = ( TIME[0] >> 4) + '0';
    // if ( second[0] == '0' ) second[0] = ' ';
    second[1] = ( TIME[0] & 0x0f ) + '0';
}
/*******************************************************************************
* 函 数 名         : InitRTCDemo
* 函数功能         : 初始化相关变量
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
static void InitRTCDemo(void)
{
    struct dlg_RTC_demo_param *p = &g_all_dlg.rtc_demo;

    memset(p, 0 , sizeof(*p));
    p->state = DISMODE;
    p->oldticks = time_GetTicks();
}
/*******************************************************************************
* 函 数 名         : gui_DlgRTCDemoProc
* 函数功能         : RTC窗口消息处理函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void gui_DlgRTCDemoProc(uint8 msg_type, uint8 msg_code)
{
    struct dlg_key_demo_param *p = &g_all_dlg.key_demo;
    uint32 ticks = time_GetTicks();
    if(msg_type == WM_TIMER)
    {
        /*Add your code here.*/
        if(p->state == DISMODE) //显示模式下，读取时间并将变化的值显示到屏幕上
        {
            EA = 0;
            Ds1302ReadTime();
            HEXConvDT2Str();
            gui_DrawAllControls(g_con_list, g_con_active); //绘制本窗口所有的控件
            EA = 1;

            if(ticks - p->oldticks > 200u)
            {
                p->oldticks =  ticks   ;
                if(DotFlash)
                {
                    OLED_ShowChar ( 30, 5, ':', 8, NOMALCOLORMODE);
                    OLED_ShowChar ( 54, 5, ':', 8, NOMALCOLORMODE);
                    DotFlash = 0;
                }
                else
                {
                    OLED_ShowChar ( 30, 5, ' ', 8, NOMALCOLORMODE);
                    OLED_ShowChar ( 54, 5, ' ', 8, NOMALCOLORMODE);
                    DotFlash = 1;
                }
            }
        }
        else //设置时间模式下，更新已设置的值，并将变化的值显示到屏幕上
        {

        }

    }
    else if(msg_type == WM_KEYPRESSED || msg_type == WM_KEYREPEATED)//有按键按下
    {
        if(msg_code == KEY_RETURN)// 返回按键只轮询每一个控件
        {
            gui_SearchNextControl(g_con_list, &g_con_active);
            return;
        }
        if(msg_code == KEY_SET)
        {
            if(g_con_active == 0) //确认返回
            {
                gui_DlgMainMenuOpen();
                return;
            }
            else if(g_con_active == 1) //确认 SET
            {
                if(p->state == DISMODE) //显示模式切换到设置模式
                {
                    p->state = SETMODE;
                    EA = 0;
                    Ds1302ReadTime();
                    BCD2DEC();
                    EA = 1;

                    OLED_ShowChar ( 30, 5, ':', 8, NOMALCOLORMODE);
                    OLED_ShowChar ( 54, 5, ':', 8, NOMALCOLORMODE);

                    //读取最新时间日期值到内存 OldTime
                }
                else //设置模式切换到显示模式
                {
                    //添加更新已设置参数保存到DS1302的代码，把oldtime的值转换为16进制保存到time，并且write到ds1302
                    DEC2BCD();
                    Ds1302Init();
                    p->state = DISMODE;
                }
            }

        }
        if(p->state == SETMODE)
        {
            if(msg_code == KEY_PLUS)   //'+' key
            {
                switch(g_con_active) //在设置模式下，'+' 按键 对所选参数+1
                {
                case 0://
                case 1:
                    break;
                case 2:
                    if(++OldTime[g_con_active - 2] > 99)  OldTime[g_con_active - 2] = 0;
                    year[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    year[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 3:
                    if(++OldTime[g_con_active - 2] > 12)  OldTime[g_con_active - 2] = 0;
                    month[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    month[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 4:
                    if(++OldTime[g_con_active - 2] > 31)  OldTime[g_con_active - 2] = 0;
                    day[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    day[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 5:
                    if(++OldTime[g_con_active - 2] > 23)  OldTime[g_con_active - 2] = 0;
                    hour[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    hour[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 6:
                    if(++OldTime[g_con_active - 2] > 59)  OldTime[g_con_active - 2] = 0;
                    minute[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    minute[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 7:
                    if(++OldTime[g_con_active - 2] > 59)  OldTime[g_con_active - 2] = 0;
                    second[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    second[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 8:
                    if(++OldTime[g_con_active - 2] > 7)  OldTime[g_con_active - 2] = 0;
                    week_i[0] = OldTime[g_con_active - 2] + '0';
                    break;
                default:
                    break;
                }
                gui_DrawControl(&g_con_list[g_con_active], 1);//isactive
            }
            if(msg_code == KEY_MINUS)   //'- 'key
            {
                switch(g_con_active) //在设置模式下，'-' 按键 对所选参数-1
                {
                case 0://
                case 1:
                    break;
                case 2:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 99;
                    year[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    year[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 3:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 12;
                    month[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    month[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 4:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 31;
                    day[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    day[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 5:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 23;
                    hour[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    hour[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 6:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 59;
                    minute[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    minute[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 7:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 59;
                    second[0] = ( OldTime[g_con_active - 2] / 10) + '0';
                    second[1] = ( OldTime[g_con_active - 2] % 10 ) + '0';
                    break;
                case 8:
                    if(--OldTime[g_con_active - 2] < 0)  OldTime[g_con_active - 2] = 7;
                    week_i[0] = OldTime[g_con_active - 2] + '0';
                    break;
                default:
                    break;
                }
                gui_DrawControl(&g_con_list[g_con_active], 1);//isactive
            }
        }

    }
    gui_DlgDefaultProc(msg_type, msg_code);
}
/*******************************************************************************
* 函 数 名         : gui_DlgRTCDemoOpen
* 函数功能         : 打开本窗口时进行一些初始化工作
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void gui_DlgRTCDemoOpen(void)
{
    gui_DlgSetActive(DLG_RTCDEMO);//激活窗口
    memset(g_con_param_list, 0x00u, sizeof(g_con_param_list));
    g_con_active = 0;//设置默认获得焦点的控件为0#控件，即返回。

    OLED_Clear();
    OLED_ShowString(38, 0, "RTCdemo", 16, NOMALCOLORMODE); //标题

    OLED_ShowString(24, 3, "20", 8, NOMALCOLORMODE); //显示20
    OLED_ShowString(56, 3, "-", 8, NOMALCOLORMODE);  //年   2019--01--01
    OLED_ShowString(80, 3, "-", 8, NOMALCOLORMODE); //月

    OLED_ShowChar ( 30, 5, ':', 8, NOMALCOLORMODE);
    OLED_ShowChar ( 54, 5, ':', 8, NOMALCOLORMODE);

    gui_DrawAllControls(g_con_list, g_con_active); //绘制本窗口所有的控件
    InitRTCDemo();
}

/********************************End of File************************************/