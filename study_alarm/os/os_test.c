
#include "bsp/config.h"

extern void seg_disp_num(u8 d0,u8 d1,u8 d2,u8 d3);

u32 cnt_task1 = -1;
u32 cnt_task2 = -1;
u32 cnt_task3 = -1;
u32 cnt_task4 = -1;

void os_task1(u8 task_id) {

    os_addPeriod(task_id,200000);
	
    cnt_task1++;
	printk("\r\ntask1:%d",(u32)cnt_task1);
	seg_disp_num(cnt_task1,cnt_task2,cnt_task3,cnt_task4);

	delay_ms(1);    

	//os_debug(task_id);
}


void os_task2(u8 task_id) {
    os_addDelay(task_id,400000);
	
    cnt_task2++;
	printk("\r\ntask2:%d",(u32)cnt_task2);
	seg_disp_num(cnt_task1,cnt_task2,cnt_task3,cnt_task4);


	//os_debug(task_id);
}

void os_task3(u8 task_id) {
    os_addDelay(task_id,800000);
	
    cnt_task3++;
	printk("\r\ntask3:%d",(u32)cnt_task3);
	seg_disp_num(cnt_task1,cnt_task2,cnt_task3,cnt_task4);
    
	//os_debug(task_id);
}

void os_task4(u8 task_id) {
    os_addDelay(task_id,1600000);
	
    cnt_task4++;
	printk("\r\ntask4:%d %d %d %d",(u32)cnt_task1,(u32)cnt_task2,(u32)cnt_task3,(u32)cnt_task4);
	seg_disp_num(cnt_task1,cnt_task2,cnt_task3,cnt_task4);
    
	//os_debug(task_id);
}


void os_test() {
	
	//Timer_config();
	//EA = 1;
   	//UART_config(0,115200);	
	
	os_init();
	
	//不同的启动延迟，将任务错峰
    os_taskCreate(0,os_task1,100000);
    os_taskCreate(1,os_task2,200000);
    os_taskCreate(2,os_task3,300000);
    os_taskCreate(3,os_task4,400000);

	
    os_start();
}