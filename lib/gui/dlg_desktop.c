/*
 * Copyright        : Shendong MCU studio
 * File Description : Desktop Dialog
 * Created          : oliverzhang@shendongmcu.com
 */

#include "gui.h"

static void InitDesktop(void)  //初始化本窗口数据为0
{
    struct dlg_desktop_param *p = &g_all_dlg.desktop_param;
    memset(p,0,sizeof(*p));
    p->oldticks = time_GetTicks();   
}

static void ShowLogo(void)
{
    struct dlg_desktop_param *p = &g_all_dlg.desktop_param;
    uint32 ticks = time_GetTicks();
    if(ticks - p->oldticks < 15*1000ul) return;
    gui_DlgMainMenuOpen();
}

void gui_DlgDesktopProc(uint8 msg_type, uint8 msg_code)
{
    msg_code = msg_code;
    if(msg_type == WM_KEYPRESSED)
    {
        gui_DlgMainMenuOpen();
    }
    else if(msg_type == WM_TIMER)
    {
        ShowLogo();  //本例只是利用超时消息  来设置延时，延时后显示主菜单窗口
    }
}

void gui_DlgDesktopOpen(void)
{
    OLED_ShowCHinese2(36,3,"进入系统",NOMALCOLORMODE);
    gui_DlgSetActive(DLG_DESKTOP);
    InitDesktop();
}



/********************************End of File************************************/