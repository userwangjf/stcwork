
/*
操作系统特点：
1、使用数组来对ready任务排序，确保最新需要执行的任务位于头。
2、最大可用任务数为OS_TSK_MAX-1。
3、任务需要主动放弃。
4、tick翻转时，不会漏掉操作。
5、使用二分法进行排序

5、tick
	a、支持us级别的tick
	b、使用16bit的timer作为tick的低16bit
	c、32bit的tick，使用低24bit的tick，12M晶振时，最大到16秒级延时。
	d、最小1us延时，实际测试，最小可以达到150us。
	e、高8bit的tick，用作系统溢出标记。

6、如何支持任务优先级？

*/

#include "bsp/config.h"

//任务信息list,每项占用9B
os_task OS_DATA 	os_taskInfo[OS_TSK_MAX];

//按task延时排序的taskid
//本数组的os_taskId指向的os_task是顺序的
u8		OS_DATA		os_taskSort[OS_TSK_MAX];
//task进入溢出、等待状态的统计。
u8		OS_DATA		os_taskWaitNum = 0;

//定时tick翻转标记
u8 		OS_DATA 	os_tickFlip = 0x00;
//32bit的系统tick，用于定时。
//只使用高16bit，其中bit[31:24]用于判断溢出
//bit[23:16]合并到os_curTick的[23:16]
os_u32 	OS_DATA 	os_sysTick = {0};
//24bit的当前tick，用于调度。
os_u32 	OS_DATA 	os_curTick = {0};

#define OS_WAIT			0xff		//任务等待状态
#define OS_OVERTIME		0x01		//任务溢出状态


u32 	OS_DATA		os_max_delay = 0;


void os_init()
{
	int i;

	//初始化任务的函数指针
	for(i=0;i<OS_TSK_MAX;i++)
	{
	    os_taskInfo[i].os_timer.dword = 0xffffffff;
	    os_taskInfo[i].os_func = (void OS_CODE *)0;

		os_taskSort[i] = i;

		os_taskWaitNum++;
	}

}


/*
根据delay值的变化，重新排序。
*/
void os_taskUpdate(u8 task_id, u32 delay)
{
	s8 pos;
	s8 i;

	//根据delay，搜索需要插入的位置
	pos = os_seekGt(delay);
	if(pos == task_id)//直接更新
	{
		os_taskInfo[task_id].os_timer.dword = delay;	
	}
	else if(pos > task_id)
	{
		for(i=task_id;i<pos;i++)
		{
			os_taskSort[i] = os_taskSort[i+1];	
		}
		os_taskSort[pos-1] = task_id;
		os_taskInfo[task_id].os_timer.dword = delay;
	}
	else if(pos < task_id)
	{
		for(i=task_id;i>pos;i--)
		{
			os_taskSort[i] = os_taskSort[i-1];	
		}
		os_taskSort[pos] = task_id;
		os_taskInfo[task_id].os_timer.dword = delay;
	}
}

//二分法查找大于当前delay的位置
s8 os_seekGt(u32 delay)
{
	s8 low = 0;
	s8 high = OS_TSK_MAX - 1;
	s8 mid;
	while(low <= high)
	{
		mid = (high+low)/2;
		if(delay < os_taskInfo[os_taskSort[mid]].os_timer.dword)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return high + 1;
}

s8 os_seekGt2(u32 delay)
{
	//当前任务在0，跳过
	s8 low = 1;
	s8 high = OS_TSK_MAX - 1;
	s8 mid;
	while(low <= high)
	{
		mid = (high+low)/2;
		if(delay < os_taskInfo[os_taskSort[mid]].os_timer.dword)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return high + 1;
}

void os_taskUpdate2(u8 task_id)
{
	s8 pos;
	s8 i;

	//根据delay，搜索需要插入的位置
	//当前执行的任务，默认在0
	pos = os_seekGt2(os_taskInfo[task_id].os_timer.dword);
	for(i=1;i<pos;i++)
	{
		os_taskSort[i-1] = os_taskSort[i];
	}
	os_taskSort[pos-1] = task_id;
}


/*
创建新的任务
参数
task_id		:	新的任务id
task_func	:   任务的函数
delay		:	延时启动，必须大于0.
*/
void os_taskCreate(u8 task_id, void (code *task_func)(void), u32 delay)
{
	u32 new_delay;

	//任务函数
	os_taskInfo[task_id].os_func = task_func;
	
	//创建新的任务，需要从当前tick开始延时。
	os_updateTick();
	new_delay = os_curTick.dword + delay;
	
	os_taskUpdate(task_id,new_delay);

	//任务溢出，则记录
	if(os_taskInfo[task_id].os_timer.byte[0] != 0)
		os_taskWaitNum++;
	else
		os_taskWaitNum--;
}


/*
将任务挂起，一般任务自己挂起。
*/
void os_taskSuspend(u8 task_id)
{

	os_taskUpdate(task_id,0xffffffff);
	//os_debug();	
}

/*
唤醒任务，一般在中断中唤醒。
*/
void os_taskResume(u8 task_id)
{
	os_updateTick();
	os_taskUpdate(task_id,os_curTick.dword);	
}

//相对的任务延时
void os_addDelay(u8 task_id, u32 delay)
{
	u8 tmp;
	u32 new_delay;

	os_updateTick();
	tmp = os_taskInfo[task_id].os_timer.byte[0];
	new_delay = os_curTick.dword + delay;
	os_taskUpdate(task_id,new_delay);

	//任务的os_timer溢出
	if((os_taskInfo[task_id].os_timer.byte[0] == 0x01) && (tmp == 0x0))
		os_taskWaitNum++;

}

/**
* 
* @brief 延时若干个系统tick，用于任务中的延时。
* @param 
* @return 
*/
void os_delayTick(u16 us)
{
	u32 tmp;
	tmp = os_getTick() + us;	
	
}

//周期性的任务定时
void os_addPeriod(u8 task_id, u32 delay)
{
	os_taskInfo[task_id].os_timer.dword = os_taskInfo[task_id].os_timer.dword + delay;
	os_taskUpdate2(task_id);

	//任务的os_timer溢出
	if(os_taskInfo[task_id].os_timer.byte[0] == OS_OVERTIME)
		os_taskWaitNum++;
}

void os_runing()
{

	os_start();
	
	//os_taskSort[0]保存当前最小tick的任务id。
	if(os_curTick.dword >= os_taskInfo[os_taskSort[0]].os_timer.dword)
	{
		#if OS_DBG_EN
		//记录最大任务delay
		if((os_curTick.dword - os_taskInfo[os_taskSort[0]].os_timer.dword) > os_max_delay)
		{
			os_max_delay = os_curTick.dword - os_taskInfo[os_taskSort[0]].os_timer.dword;
		}
		#endif

		//执行任务
	   	os_taskInfo[os_taskSort[0]].os_func(os_taskSort[0]);
		
	}		
}

/*
在周期性定时时，如果tick已经溢出，但未执行完毕，则放弃。

某任务没有执行的原因：
其它任务的大延时，大于某任务的周期。
*/
void os_start(void)
{
	u8 i;

	os_updateTick();

	//本轮tick已经溢出
	//已经溢出的任务不会被执行
	if(os_tickFlip != os_sysTick.byte[0])
	{
		//设置tick为最大值，将本轮的任务都执行完。
		os_curTick.dword = 0x00ffffff;
		
		//所有的任务在本轮都执行完毕了
		if(os_taskWaitNum >= OS_TSK_MAX)
		{
			//清除溢出状态的任务的高位字节
			//无需重新排序。
			for(i=0;i<OS_TSK_MAX;i++)
			{
				if(os_taskInfo[i].os_timer.byte[0] == OS_OVERTIME)
				{
					os_taskInfo[i].os_timer.byte[0] = 0;
					os_taskWaitNum--;	
				}
			}
			
			//保存当前高8bit，用于下一次溢出判断
			os_tickFlip = os_sysTick.byte[0];
			//清零任务后，再更新一次tick
			os_updateTick();	
		}
	}	
}

#ifdef OS_DBG_EN
void os_debug()
{
	u8 i;

	#if 0
	Uart1_Tx("\r\n======================");
	for(i=0;i<OS_TSK_MAX;i++)
	{
		Uart1_Tx("\r\n");
		Uart1_Tx(byte2str(i));
		Uart1_Tx(",");
		Uart1_Tx(hex2str(os_taskInfo[i].os_timer.dword));
	}
	for(i=0;i<OS_TSK_MAX;i++)
	{
		Uart1_Tx("\r\nID ");
		Uart1_Tx(byte2str(i));
		Uart1_Tx(",");
		Uart1_Tx(hex2str(os_taskSort[i]));	
	}
	#endif

	#if 0
	//打印任务最大的延时
	Uart1_Tx("\r\n======================");
	Uart1_Tx("\r\nos_max_delay: ");
	Uart1_Tx(hex2str(os_max_delay));
	Uart1_Tx("\r\nid: ");
	Uart1_Tx(byte2str(os_taskSort[0]));
	Uart1_Tx("\r\ntick: ");
	Uart1_Tx(hex2str(os_taskInfo[os_taskSort[0]].os_timer.dword));
	Uart1_Tx("\r\nosTick: ");
	Uart1_Tx(hex2str(os_curTick.dword));
	#endif

	#if 0
	Uart1_Tx("\r\n======================");
	Uart1_Tx("\r\nos_waitNum: ");
	Uart1_Tx(hex2str(os_taskWaitNum));
	#endif
}

#endif

//此函数放在定时器溢出中断里。
//定时器的计时范围：0~65535
//操作系统定时，低2B来自timer.
//只用低24bit。最大可以支持16秒的定时。
void os_incTick(void)
{
	os_sysTick.dword += 0x10000;
}

/*
在需要的时候，更新系统的tick到os_curTick，用于调度。
默认只使用os_sysTick的低24bit。
获取us级别的时间戳，用于非中断中。
*/
void os_updateTick(void)
{
	os_curTick.byte[3] = TL0;
	os_curTick.byte[2] = TH0;
	os_curTick.byte[1] = os_sysTick.byte[1];//只读1个byte，不用关闭中断。
	//os_curTick.byte[0] = os_sysTick.byte[0];
	//定时器发生反转，重新获取
	if(os_curTick.byte[3] > TL0)
	{
		os_curTick.byte[3] = TL0;
		os_curTick.byte[2] = TH0;
		os_curTick.byte[1] = os_sysTick.byte[1];
		//os_curTick.byte[0] = os_sysTick.byte[0];
	}
}

/*
获取us级别的时间戳，用于中断中。
在中断中，需要确保os_incTick是最高优先级，才能保证
os_tickCurr正常递增
*/
u32 os_getTick(void)
{
	os_u32 tick;

	tick.byte[3] = TL0;
	tick.byte[2] = TH0;
	tick.byte[1] = os_sysTick.byte[1];
	tick.byte[0] = 0x00;

	//TL0翻转，则重读
	if(tick.byte[3] > TL0)
	{
		tick.byte[3] = TL0;
		tick.byte[2] = TH0;
		tick.byte[1] = os_sysTick.byte[1];
	}

	return tick.dword;			
}

