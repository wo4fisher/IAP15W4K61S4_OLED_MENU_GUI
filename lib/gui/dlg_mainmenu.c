/*
 * Copyright        : Shendong MCU studio
 * File Description : Main Menu dialog
 * Created          : oliverzhang@shendongmcu.com
 */
#include "gui.h"
#include "key.h"
static uint8 idata g_con_active = 0;

static const struct gui_control code g_con_list[] =
{
    {CON_BMPBUTTON, 128 - 16, 7, icon_backup},
    {CON_TXTBUTTON, 10, 2, "1.KEY demo"},
    {CON_TXTBUTTON, 10, 3, "2.LED demo"},
    {CON_TXTBUTTON, 10, 4, "3.RTC demo"},
    {CON_TXTBUTTON, 10, 5, "4.BUZZER demo"},
    {CON_TXTBUTTON, 10, 6, "5.DHT11 demo"},
    {CON_ENDFLAG, 0, 0, NULL}
};

void gui_DlgMainMenuProc(uint8 msg_type, uint8 msg_code)
{
    if(msg_type == WM_TIMER)
    {
    }
    else if(msg_type == WM_KEYPRESSED || msg_type == WM_KEYREPEATED)
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
            /*gui_DlgDesktopOpen();*/
            return;
        }
        else if(msg_code == KEY_SET)
        {
            switch(g_con_active)
            {
            case 0:
                break;
            case 1:
                gui_DlgKeyDemoOpen();
                break;
            case 2:
                gui_DlgLedDemoOpen();
                break;
            case 3:
                gui_DlgRTCDemoOpen();
                break;
            case 4:
                gui_DlgBuzzerDemoOpen();
                break;
            case 5:
                gui_DlgDHTDemoOpen();
                break;
            case 6:
                break;
            default:
                break;
            }
            return;
        }
    }
    gui_DlgDefaultProc(msg_type, msg_code);
}

void gui_DlgMainMenuOpen(void)
{
    OLED_Clear();
    gui_DlgSetActive(DLG_MAINMENU);
    memset(g_con_param_list, 0x00u, sizeof(g_con_param_list));
    OLED_ShowString(32, 0, "Main Menu", 16, NOMALCOLORMODE);
    gui_DrawAllControls(g_con_list, g_con_active);
}



/********************************End of File************************************/