
#ifndef		__CONFIG_H
#define		__CONFIG_H

//#define MAIN_Fosc		22118400L	//定义主时钟
#define MAIN_Fosc		12000000L	//定义主时钟
//#define MAIN_Fosc		11059200L	//定义主时钟
//#define MAIN_Fosc		 5529600L	//定义主时钟
//#define MAIN_Fosc		24000000L	//定义主时钟

#include "STC15Fxxxx.H"

#include "bsp/type.h"

#define DATA data

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)


//驱动头文件
#include "bsp/gpio.h"
#include "bsp/delay.h"
#include "bsp/timer.h"
#include "bsp/usart.h"
#include "bsp/pca.h"
#include "bsp/exti.h"

#include "bsp/bsp.h"

//操作系统头文件
#include "os/os_sch.h"

//shell界面头文件
#include "shell/shell.h"

//其它功能头文件
#include "app/app.h"
#include "ds3231/ds3231.h"


#include "bsp/printk.h"

extern u8 cur_task_id;



#endif
