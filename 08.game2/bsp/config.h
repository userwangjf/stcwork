
#ifndef		__CONFIG_H
#define		__CONFIG_H

#ifdef KEILC51
#define CODE	code
#else
#define CODE    const
#endif

//#define MAIN_Fosc		22118400L	//定义主时钟
#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟

#include "STC15Fxxxx.H"

#include "bsp/type.h"

#define DATA data

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

//最大支持的任务个数,
#define OS_TSK_MAX		8

//驱动头文件
#include "bsp/gpio.h"
#include "bsp/delay.h"
#include "bsp/timer.h"
#include "bsp/usart.h"
#include "bsp/pca.h"
#include "bsp/exti.h"
#include "bsp/EEPROM.h"

#include "bsp/bsp.h"

//操作系统头文件
//#include "os/os_sch.h"

//shell界面头文件
#include "shell/shell.h"

//其它功能头文件
#include "app/app.h"


#include "app/key_scan.h"
#include "app/led_scan.h"
#include "snake/snake.h"
#include "tetris/tetris.h"

#include "w25qxx/w25qxx.h"
#include "xmodem/xmodem.h"

#include "music/music.h"
#include "save/save.h"

#include "romfs/romfs.h"
#include "romfs/fifo.h"

extern u8 cur_task_id;



#endif
