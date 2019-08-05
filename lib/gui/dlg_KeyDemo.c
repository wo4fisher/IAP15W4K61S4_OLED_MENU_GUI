/*
 * Copyright        : Shendong MCU studio
 * File Description : Keyboard demo dialog
 * Created          : oliverzhang@shendongmcu.com
 */
#include "gui.h"
#include "key.h"
#include "oledfont.h"

static uint8 idata g_con_active = 0;
static const struct gui_control code g_con_list[] =
{
    {CON_BMPBUTTON,128-16,7,icon_backup},
    {CON_ENDFLAG,0,0,NULL},
};

static void InitKeyDemo(void)
{

    struct dlg_key_demo_param *p = &g_all_dlg.key_demo;

    memset(p, 0 , sizeof(*p));
    p->oldticks = time_GetTicks();
    p->x = 5;
    p->y = 2;
}

static void DumpKeyInfo(uint8 msg_type, uint8 msg_code)
{
    struct dlg_key_demo_param *p = &g_all_dlg.key_demo;

    OLED_ShowString(p->x, p->y, gui_GetMsgCodeString(msg_code),8,NOMALCOLORMODE);
    p->x += 8*11;
    OLED_ShowString(p->x, p->y, gui_GetMsgTypeString(msg_type),8,NOMALCOLORMODE);
    p->y+= 1;
    p->x = 5;
    if(p->y >= 7)
    {
        p->y = 2;
    }
}

void gui_DlgkeyDemoProc(uint8 msg_type, uint8 msg_code)
{
    if(msg_type == WM_KEYPRESSED || msg_type == WM_KEYRELEASED || msg_type == WM_KEYREPEATED)
    {
        DumpKeyInfo(msg_type, msg_code);
    }
    if(msg_type == WM_TIMER)
    {
        /*Add your code here.*/
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
        else if(msg_code == KEY_SET)
        {
            gui_DlgMainMenuOpen();
            return;
        }
//        else if(msg_code == KEY_RETURN)
//        {
//            switch(g_con_active)
//            {
//            case 0:
//                gui_DlgMainMenuOpen();
//                break;
//            default:
//                break;
//            }
//            return;
//        }
    }
    gui_DlgDefaultProc(msg_type, msg_code);
}

void gui_DlgKeyDemoOpen(void)
{
    gui_DlgSetActive(DLG_KEYDEMO);
    memset(g_con_param_list,0x00u,sizeof(g_con_param_list));
    g_con_active = 0;
    OLED_Clear();
    OLED_ShowCHinese2((128-14*4)>>1,0,"°´¼üÑÝÊ¾",NOMALCOLORMODE);
    gui_DrawAllControls(g_con_list,g_con_active);

    InitKeyDemo();
}




/********************************End of File************************************/