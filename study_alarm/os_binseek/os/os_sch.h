
#ifndef __OS_SCH_H__
#define __OS_SCH_H__

#define OS_DBG_EN

//定义系统支持的最大任务个数，可用任务为OS_TSK_MAX-1。
//#define OS_TSK_MAX		8

//定义系统的数据、代码存储类型
#define OS_DATA		idata
#define OS_CODE		code

//tick使用的定时器
#define TICK_BYTE0	TL0
#define TICK_BYTE1	TH0

//#define OS_DBG_EN			1

//C51使用大端存储模式
//byte[0] = dword[31:24]
//byte[1] = dword[23:16]
//byte[2] = dword[15:8]
//byte[3] = dword[7:0]
typedef union
{
	u8 	byte[4];
	u32	dword;
} os_u32;

typedef struct os_task os_task;

typedef struct os_task {
    os_u32	    os_timer;
    void        (OS_CODE *os_func)(u8 task_id);

};

//在定时中调用此函数
void os_incTick(void);

//外部调用的操作系统函数
void os_init(void);
void os_runing();
void os_taskCreate(u8 task_id, void (code *task_func)(void), u32 delay);
void os_taskSuspend(u8 task_id);
void os_taskResume(u8 task_id);
void os_addPeriod(u8 task_id, u32 delay);
void os_addDelay(u8 task_id, u32 delay);
u32 os_getTick(void);

void os_updateTick(void);
void os_updateDelay(u8 task_id, u32 delay);
void os_start(void);
void os_debug();

#endif
