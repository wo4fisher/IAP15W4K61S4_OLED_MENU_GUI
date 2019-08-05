/*
 * Copyright        : Shendong MCU studio
 * File Description : Keyboard demo dialog
 * Created          : oliverzhang@shendongmcu.com
 */
#include "gui.h"
#include "oledfont.h"
#include "key.h"

static uint8 idata g_con_active = 0;
static const struct gui_control code g_con_list[] =
{
    {CON_BMPBUTTON, 128 - 16, 7, icon_backup},
    {CON_TXTBUTTON, 25, 2, "1.song 1"},
    {CON_TXTBUTTON, 25, 3, "2.song 2"},
    {CON_TXTBUTTON, 25, 4, "3.song 3"},
    {CON_TXTBUTTON, 25, 5, "4.song 4"},
    {CON_TXTBUTTON, 25, 6, "5.song 5"},
    {CON_ENDFLAG, 0, 0, NULL},
};

static void InitBuzzerDemo(void)
{
    struct dlg_buzzer_demo_param *p = &g_all_dlg.buzzer_demo;
    memset(p, 0 , sizeof(*p));
    p->oldticks = time_GetTicks();
}

void gui_DlgBuzzerDemoProc(uint8 msg_type, uint8 msg_code)
{
    struct dlg_buzzer_demo_param *p = &g_all_dlg.buzzer_demo;
    uint32 ticks = time_GetTicks();
    msg_code = msg_code;

    if(msg_type == WM_KEYPRESSED )//|| msg_type == WM_KEYREPEATED
    {
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
    }
    if(msg_type == WM_TIMER)
    {
        //超时的时候，获取温湿度并且显示温湿度值 T:76,2;H:76,4.坐标
        if(ticks - p->oldticks > 200u)
        {
            p->oldticks =  ticks   ;
        }
    }
    gui_DlgDefaultProc(msg_type, msg_code);
}

void gui_DlgBuzzerDemoOpen(void)
{
    gui_DlgSetActive(DLG_BUZZERDEMO);
    memset(g_con_param_list, 0x00u, sizeof(g_con_param_list));

    OLED_Clear();
    OLED_ShowString((128 - 8 * 11) >> 1, 0, "Buzzer Demo", 16, NOMALCOLORMODE); //标题行

    gui_DrawAllControls(g_con_list, g_con_active);
    InitBuzzerDemo();
}




/********************************End of File************************************/