/*
 * Copyright        : Shendong MCU studio
 * File Description : Keyboard demo dialog
 * Created          : oliverzhang@shendongmcu.com
 */
#include "gui.h"
#include "DHT11.H"
#include "oledfont.h"

uint8  temp_s[3] = {"--\0"}, humi_s[3] = {"--\0"};

static uint8 idata g_con_active = 0;
static const struct gui_control code g_con_list[] =
{
    {CON_BMPBUTTON, 128 - 16, 7, icon_backup},
    {CON_ENDFLAG, 0, 0, NULL},
};

static void InitDHTDemo(void)
{
    struct dlg_DHT_demo_param *p = &g_all_dlg.dht_demo;
    memset(p, 0 , sizeof(*p));
    p->oldticks = time_GetTicks();
}

void gui_DlgDHTDemoProc(uint8 msg_type, uint8 msg_code)
{
    uint8  DHT_temp;
    struct dlg_DHT_demo_param *p = &g_all_dlg.dht_demo;
    uint32 ticks = time_GetTicks();
    msg_code = msg_code;

    if(msg_type == WM_KEYPRESSED || msg_type == WM_KEYREPEATED)
    {
        //按下任意按键返回mainmenu
        gui_DlgMainMenuOpen();
        return;
    }
    if(msg_type == WM_TIMER)
    {
        //超时的时候，获取温湿度并且显示温湿度值 T:76,2;H:76,4.坐标
        if(ticks - p->oldticks > 200u)
        {
            p->oldticks =  ticks   ;
            EA = 0;
            DHT11_receive();
            DHT_temp = (DHT11_RT[0] & 0x0F) + ((DHT11_RT[0] >> 4) * 10);
            humi_s[1] = (DHT_temp % 10)  + '0';
            humi_s[0] = (DHT_temp / 10) + '0';
            DHT_temp = (DHT11_RT[1] & 0x0F) + ((DHT11_RT[1] >> 4) * 10);
            temp_s[1] = (DHT_temp % 10)  + '0';
            temp_s[0] = (DHT_temp / 10) + '0';
            OLED_ShowString(76, 3, temp_s , 16, NOMALCOLORMODE); //temp
            OLED_ShowString(76, 5, humi_s , 16, NOMALCOLORMODE);	//humi
            EA = 1;
        }

        /*Add your code here.*/
    }
    gui_DlgDefaultProc(msg_type, msg_code);
}

void gui_DlgDHTDemoOpen(void)
{
    gui_DlgSetActive(DLG_DHTDEMO);
    memset(g_con_param_list, 0x00u, sizeof(g_con_param_list));

    OLED_Clear();
    OLED_ShowString((128 - 8 * 8) >> 1, 0, "DHT Demo", 16, NOMALCOLORMODE); //标题行
    OLED_ShowString((128 - 8 * 9) >> 1, 3, "temp: --C", 16, NOMALCOLORMODE); //temp
    OLED_ShowString((128 - 8 * 9) >> 1, 5, "humi: --%", 16, NOMALCOLORMODE);	//humi

    gui_DrawAllControls(g_con_list, g_con_active);
    InitDHTDemo();
    //    printf("DHT dialog open.\r\n");
}




/********************************End of File************************************/