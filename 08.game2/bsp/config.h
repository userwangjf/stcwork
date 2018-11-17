
#ifndef		__CONFIG_H
#define		__CONFIG_H

#ifdef KEILC51
#define CODE	code
#else
#define CODE    const
#endif

//#define MAIN_Fosc		22118400L	//������ʱ��
#define MAIN_Fosc		12000000L	//������ʱ��
//#define MAIN_Fosc		11059200L	//������ʱ��
//#define MAIN_Fosc		 5529600L	//������ʱ��
//#define MAIN_Fosc		24000000L	//������ʱ��

#include "STC15Fxxxx.H"

#include "bsp/type.h"

#define DATA data

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

//���֧�ֵ��������,
#define OS_TSK_MAX		8

//����ͷ�ļ�
#include "bsp/gpio.h"
#include "bsp/delay.h"
#include "bsp/timer.h"
#include "bsp/usart.h"
#include "bsp/pca.h"
#include "bsp/exti.h"

#include "bsp/bsp.h"

//����ϵͳͷ�ļ�
//#include "os/os_sch.h"

//shell����ͷ�ļ�
#include "shell/shell.h"

//��������ͷ�ļ�
#include "app/app.h"


#include "app/key_scan.h"
#include "app/led_scan.h"
#include "snake/snake.h"
#include "tetris/tetris.h"

#include "w25qxx/w25qxx.h"
#include "xmodem/xmodem.h"

#include "music/music.h"

extern u8 cur_task_id;



#endif
