
#ifndef		__CONFIG_H
#define		__CONFIG_H

/*
1、如果 ISR 和主程序使用同一寄存器组（主程序缺省使用BANK 0，若 ISR 没有使用 using 为其指定寄存器区，
则缺省也使用 BANK 0），则不需其他设置。
2、如果 ISR 和主程序使用不同的寄存器组（主程序缺省使用BANK 0，ISR 使用 using 指定了其他 BANK），
则被调用函数必须放在：
#pragma NOAREGS
#pragma AREGS
控制参数对中，指定编译器不要对该函数使用绝对寄存器寻址方式；
或者也可在 Options->C51，选中“Don't use absolute register accesses”，
使所有代码均不使用绝对寄存器寻址方式（这样，执行效率将稍有降低）。
不论以上的哪一种情况，编译器均会给出重入警告，需手工更改 OVERLAY 参数，做重入说明。
3、还有一种办法：如果被调用函数的代码不是很长，还是将该函数复制一份，用不同的函数名代替，
这种情况适合ROM有足够多余的空间。
*/

#ifdef KEILC51
#define CODE		code
#define INT_USING	using 3
#else
#define CODE    	const
#define INT_USING		
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
#include "romfs/fifo.h"

//操作系统头文件
//#include "os/os_sch.h"

//shell界面头文件
#include "shell/shell.h"
#include "shell/str.h"

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

#include "shell/printk.h"

extern u8 cur_task_id;



#endif
