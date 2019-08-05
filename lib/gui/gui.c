/*
 * Copyright        : Shendong MCU studio
 * File Description : GUI frame implementation.
 * Created          : oliverzhang@shendongmcu.com
 */
#include "gui.h"
#include "key.h"
static uint8 idata g_current_dlg;//当前对话框索引号

void gui_DlgSetActive(uint8 dlg_index) //获取当前激活的对话框索引号
{
    g_current_dlg = dlg_index;
}

void gui_Task(void)
{
    uint32 xdata ticks;
    static uint32 xdata oldticks;
    uint8 xdata ret, key_code, key_state;
    uint8 msg_type = 0xffu, msg_code = 0xffu;

    ticks = time_GetTicks();
    if(ticks - oldticks < 10) //定时消息
    {
        /*Do nothing.*/
    }
    else
    {
        oldticks = ticks;
        msg_type = WM_TIMER;
        msg_code = 0;
    }
    if(msg_type == 0xffu)//获取按键状态及键值  消息
    {
        ret = key_GetKeyCode(&key_code, &key_state);
        if(ret != 0)
        {
            msg_code = key_code;
            msg_type = key_state;
        }
    }
    if(msg_type != 0xffu)//消息不为空
    {
        switch(g_current_dlg)//根据当前对话框激活不同的窗口函数
        {
        case 0:
            break;
        case DLG_DESKTOP:
            gui_DlgDesktopProc(msg_type, msg_code);
            break;
        case DLG_MAINMENU:
            gui_DlgMainMenuProc(msg_type, msg_code);
            break;
        case DLG_KEYDEMO:
            gui_DlgKeyDemoProc(msg_type, msg_code);
            break;
        case DLG_LEDDEMO:
            gui_DlgLedDemoProc(msg_type, msg_code);
            break;
        case DLG_RTCDEMO:   /*add function here*/
            gui_DlgRTCDemoProc(msg_type, msg_code);
            break;
        case DLG_BUZZERDEMO: /*add function here*/
					  gui_DlgBuzzerDemoProc(msg_type, msg_code);
            break;
        case DLG_DHTDEMO: /*add function here*/
            gui_DlgDHTDemoProc(msg_type, msg_code);
            break;
        default:
            printf("No dialog proc.\r\n");
            break;
        }
    }
}

void gui_DlgDefaultProc(uint8 msg_type, uint8 msg_code)
{
    /*Add your default proc here.*/
    msg_type = msg_type;
    msg_code = msg_code;
}

//获取消息类型字符串
const char *gui_GetMsgTypeString(uint8 msg_type)
{
    switch(msg_type)
    {
    case WM_KEYPRESSED:
        return "0";
    case WM_KEYREPEATED:
        return "1";
    case WM_KEYRELEASED:
        return "2";
    case WM_TIMER:
        return "WM_TIMER";
    default:
        return "unknown type";
    }
}
//获取消息代码  目前返回为哪个按键
const char *gui_GetMsgCodeString(uint8 msg_code)
{
    switch(msg_code)
    {
    case KEY_PLUS:
        return("KEY_PLUS: ");
        break;
    case KEY_MINUS:
        return("KEY_MINUS: ");
        break;
    case KEY_RETURN:
        return("KEY_RETURN: ");
        break;
    case KEY_SET:
        return("KEY_SET: ");
        break;
    case KEY_NONE:
        return("KEY_NONE or unknown: ");
        break;
    default:
        return("impossible to run here:");
        break;
    }
}

void gui_DrawAllControls(const struct gui_control *plist, uint8 active)
{
    uint8 i;
    if(plist == NULL) return;
    for(i = 0; plist[i].type != CON_ENDFLAG && i < CON_MAX_ITEMS; i++)
    {
        gui_DrawControl(&plist[i], (i == active));
    }
}

void gui_DrawControl(const struct gui_control *pcon, uint8 is_active)
{
    if(pcon == NULL) return;
    if(pcon->type == CON_TXTBUTTON)//英文文本按钮控件
    {
        OLED_ShowString(pcon->x, pcon->y, pcon->str, 8, (is_active) ? g_style_reverse : g_style_normal);
    }
    else if(pcon->type == CON_BMPBUTTON)//图形按钮
    {
        OLED_DrawBMP(pcon->x, pcon->y, pcon->x + 14, pcon->y, pcon->str, (is_active) ? g_style_reverse : g_style_normal);
    }
    else if(CON_TXTBUTTON_CHS == pcon->type ) //中文文本按钮
    {
        OLED_ShowCHinese2(pcon->x, pcon->y, pcon->str, (is_active) ? g_style_reverse : g_style_normal);
    }
    else if(CON_NUMBUTTON == pcon->type) //数字按钮控件
    {
        OLED_ShowString(pcon->x, pcon->y, pcon->str, 8, (is_active) ? g_style_reverse : g_style_normal);
    }
}

void gui_SearchPrevControl(const struct gui_control *plist, uint8 *pactive)
{
    uint8 end, active = *pactive;
    if(plist == NULL) return;
    gui_DrawControl(&plist[active], 0);
    for(end = 0; plist[end].type != CON_ENDFLAG && end < CON_MAX_ITEMS; end++);
    if(active == 0) active = end - 1;
    else active --;
    gui_DrawControl(&plist[active], 1);
    *pactive = active;
}

void gui_SearchNextControl(const struct gui_control *plist, uint8 *pactive)
{
    uint8 active = *pactive;
    if(plist == NULL) return;
    gui_DrawControl(&plist[active], 0);
    active ++;
    if(plist[active].type == CON_ENDFLAG) active = 0;
    gui_DrawControl(&plist[active], 1);
    *pactive = active;
}

uint8 idata g_con_param_list[CON_MAX_ITEMS];  //每一页一个对话框，对话框中包含控件的最大个数
union gui_all_dlg xdata g_all_dlg;




/********************************End of File************************************/