
/*
����ϵͳ�ص㣺
1��ʹ����������ready��������ȷ��������Ҫִ�е�����λ��ͷ��
2��������������ΪOS_TSK_MAX-1��
3��������Ҫ����������
4��tick��תʱ������©��������
5��ʹ�ö��ַ���������

5��tick
	a��֧��us�����tick
	b��ʹ��16bit��timer��Ϊtick�ĵ�16bit
	c��32bit��tick��ʹ�õ�24bit��tick��12M����ʱ�����16�뼶��ʱ��
	d����С1us��ʱ��ʵ�ʲ��ԣ���С���Դﵽ150us��
	e����8bit��tick������ϵͳ�����ǡ�

6�����֧���������ȼ���

*/

#include "bsp/config.h"

//������Ϣlist,ÿ��ռ��9B
os_task OS_DATA 	os_taskInfo[OS_TSK_MAX];

//��task��ʱ�����taskid
//�������os_taskIdָ���os_task��˳���
u8		OS_DATA		os_taskSort[OS_TSK_MAX];
//task����������ȴ�״̬��ͳ�ơ�
u8		OS_DATA		os_taskWaitNum = 0;

//��ʱtick��ת���
u8 		OS_DATA 	os_tickFlip = 0x00;
//32bit��ϵͳtick�����ڶ�ʱ��
//ֻʹ�ø�16bit������bit[31:24]�����ж����
//bit[23:16]�ϲ���os_curTick��[23:16]
os_u32 	OS_DATA 	os_sysTick = {0};
//24bit�ĵ�ǰtick�����ڵ��ȡ�
os_u32 	OS_DATA 	os_curTick = {0};

#define OS_WAIT			0xff		//����ȴ�״̬
#define OS_OVERTIME		0x01		//�������״̬


u32 	OS_DATA		os_max_delay = 0;


void os_init()
{
	int i;

	//��ʼ������ĺ���ָ��
	for(i=0;i<OS_TSK_MAX;i++)
	{
	    os_taskInfo[i].os_timer.dword = 0xffffffff;
	    os_taskInfo[i].os_func = (void OS_CODE *)0;

		os_taskSort[i] = i;

		os_taskWaitNum++;
	}

}


/*
����delayֵ�ı仯����������
*/
void os_taskUpdate(u8 task_id, u32 delay)
{
	s8 pos;
	s8 i;

	//����delay��������Ҫ�����λ��
	pos = os_seekGt(delay);
	if(pos == task_id)//ֱ�Ӹ���
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

//���ַ����Ҵ��ڵ�ǰdelay��λ��
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
	//��ǰ������0������
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

	//����delay��������Ҫ�����λ��
	//��ǰִ�е�����Ĭ����0
	pos = os_seekGt2(os_taskInfo[task_id].os_timer.dword);
	for(i=1;i<pos;i++)
	{
		os_taskSort[i-1] = os_taskSort[i];
	}
	os_taskSort[pos-1] = task_id;
}


/*
�����µ�����
����
task_id		:	�µ�����id
task_func	:   ����ĺ���
delay		:	��ʱ�������������0.
*/
void os_taskCreate(u8 task_id, void (code *task_func)(void), u32 delay)
{
	u32 new_delay;

	//������
	os_taskInfo[task_id].os_func = task_func;
	
	//�����µ�������Ҫ�ӵ�ǰtick��ʼ��ʱ��
	os_updateTick();
	new_delay = os_curTick.dword + delay;
	
	os_taskUpdate(task_id,new_delay);

	//������������¼
	if(os_taskInfo[task_id].os_timer.byte[0] != 0)
		os_taskWaitNum++;
	else
		os_taskWaitNum--;
}


/*
���������һ�������Լ�����
*/
void os_taskSuspend(u8 task_id)
{

	os_taskUpdate(task_id,0xffffffff);
	//os_debug();	
}

/*
��������һ�����ж��л��ѡ�
*/
void os_taskResume(u8 task_id)
{
	os_updateTick();
	os_taskUpdate(task_id,os_curTick.dword);	
}

//��Ե�������ʱ
void os_addDelay(u8 task_id, u32 delay)
{
	u8 tmp;
	u32 new_delay;

	os_updateTick();
	tmp = os_taskInfo[task_id].os_timer.byte[0];
	new_delay = os_curTick.dword + delay;
	os_taskUpdate(task_id,new_delay);

	//�����os_timer���
	if((os_taskInfo[task_id].os_timer.byte[0] == 0x01) && (tmp == 0x0))
		os_taskWaitNum++;

}

/**
* 
* @brief ��ʱ���ɸ�ϵͳtick�����������е���ʱ��
* @param 
* @return 
*/
void os_delayTick(u16 us)
{
	u32 tmp;
	tmp = os_getTick() + us;	
	
}

//�����Ե�����ʱ
void os_addPeriod(u8 task_id, u32 delay)
{
	os_taskInfo[task_id].os_timer.dword = os_taskInfo[task_id].os_timer.dword + delay;
	os_taskUpdate2(task_id);

	//�����os_timer���
	if(os_taskInfo[task_id].os_timer.byte[0] == OS_OVERTIME)
		os_taskWaitNum++;
}

void os_runing()
{

	os_start();
	
	//os_taskSort[0]���浱ǰ��Сtick������id��
	if(os_curTick.dword >= os_taskInfo[os_taskSort[0]].os_timer.dword)
	{
		#if OS_DBG_EN
		//��¼�������delay
		if((os_curTick.dword - os_taskInfo[os_taskSort[0]].os_timer.dword) > os_max_delay)
		{
			os_max_delay = os_curTick.dword - os_taskInfo[os_taskSort[0]].os_timer.dword;
		}
		#endif

		//ִ������
	   	os_taskInfo[os_taskSort[0]].os_func(os_taskSort[0]);
		
	}		
}

/*
�������Զ�ʱʱ�����tick�Ѿ��������δִ����ϣ��������

ĳ����û��ִ�е�ԭ��
��������Ĵ���ʱ������ĳ��������ڡ�
*/
void os_start(void)
{
	u8 i;

	os_updateTick();

	//����tick�Ѿ����
	//�Ѿ���������񲻻ᱻִ��
	if(os_tickFlip != os_sysTick.byte[0])
	{
		//����tickΪ���ֵ�������ֵ�����ִ���ꡣ
		os_curTick.dword = 0x00ffffff;
		
		//���е������ڱ��ֶ�ִ�������
		if(os_taskWaitNum >= OS_TSK_MAX)
		{
			//������״̬������ĸ�λ�ֽ�
			//������������
			for(i=0;i<OS_TSK_MAX;i++)
			{
				if(os_taskInfo[i].os_timer.byte[0] == OS_OVERTIME)
				{
					os_taskInfo[i].os_timer.byte[0] = 0;
					os_taskWaitNum--;	
				}
			}
			
			//���浱ǰ��8bit��������һ������ж�
			os_tickFlip = os_sysTick.byte[0];
			//����������ٸ���һ��tick
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
	//��ӡ����������ʱ
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

//�˺������ڶ�ʱ������ж��
//��ʱ���ļ�ʱ��Χ��0~65535
//����ϵͳ��ʱ����2B����timer.
//ֻ�õ�24bit��������֧��16��Ķ�ʱ��
void os_incTick(void)
{
	os_sysTick.dword += 0x10000;
}

/*
����Ҫ��ʱ�򣬸���ϵͳ��tick��os_curTick�����ڵ��ȡ�
Ĭ��ֻʹ��os_sysTick�ĵ�24bit��
��ȡus�����ʱ��������ڷ��ж��С�
*/
void os_updateTick(void)
{
	os_curTick.byte[3] = TL0;
	os_curTick.byte[2] = TH0;
	os_curTick.byte[1] = os_sysTick.byte[1];//ֻ��1��byte�����ùر��жϡ�
	//os_curTick.byte[0] = os_sysTick.byte[0];
	//��ʱ��������ת�����»�ȡ
	if(os_curTick.byte[3] > TL0)
	{
		os_curTick.byte[3] = TL0;
		os_curTick.byte[2] = TH0;
		os_curTick.byte[1] = os_sysTick.byte[1];
		//os_curTick.byte[0] = os_sysTick.byte[0];
	}
}

/*
��ȡus�����ʱ����������ж��С�
���ж��У���Ҫȷ��os_incTick��������ȼ������ܱ�֤
os_tickCurr��������
*/
u32 os_getTick(void)
{
	os_u32 tick;

	tick.byte[3] = TL0;
	tick.byte[2] = TH0;
	tick.byte[1] = os_sysTick.byte[1];
	tick.byte[0] = 0x00;

	//TL0��ת�����ض�
	if(tick.byte[3] > TL0)
	{
		tick.byte[3] = TL0;
		tick.byte[2] = TH0;
		tick.byte[1] = os_sysTick.byte[1];
	}

	return tick.dword;			
}

