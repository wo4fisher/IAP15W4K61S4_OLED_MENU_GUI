#ifndef __OLEDFONT_H
#define __OLEDFONT_H

#include "config.h"

//常用ASCII表

/************************************6*8的点阵************************************/
extern const unsigned char code F6x8[][6];
extern const unsigned char code F8X16[];

#define Hz_num    25

struct  hzk_tab_t
{
    int8  tab8[2];
    uint8 index;
};

extern struct  hzk_tab_t  hzk_tab[];

extern const unsigned char code Hzk[][28];
extern const unsigned  char  code icon_backup[];
#endif


