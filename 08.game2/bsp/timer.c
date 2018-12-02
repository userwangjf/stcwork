

#include "bsp/config.h"


//15W408，无Timer1.
//15W1K，有Timer1.
//先除12T，然后将16bit的计数器用满
//操作系统使用了timer的计数器作为低16bit。
void Timer_config(void)
{
	
	TIM_InitTypeDef		TIM_InitStructure;					//结构定义

	#if 1
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityHigh;			//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;			//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 0x10000 - 125;			//8K的频率
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2
	#endif

	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityHigh;				//指定中断优先级, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//中断是否允许,   ENABLE或DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
	TIM_InitStructure.TIM_Value     = 0x10000 - 500;		//500us
	TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
	Timer_Inilize(Timer1,&TIM_InitStructure);				//初始化Timer0	  Timer0,Timer1,Timer2

}



/********************* Timer0中断函数************************/
void timer0_int (void) interrupt TIMER0_VECTOR using 3
{
	EA = 0;
	CCAP0H = music_play();
	CCAP1H = CCAP0H;
	EA = 1;
}



u8 timer1_step = 0;
u8 cur_task_id = 0;
/********************* Timer1中断函数************************/
void timer1_int (void) interrupt TIMER1_VECTOR
{
 	//led_scan();

	cur_task_id = timer1_step;

	timer1_step++;
	if(timer1_step >= 10)timer1_step = 0;
	//5ms一个周期

}

/********************* Timer2中断函数************************/
void timer2_int (void) interrupt TIMER2_VECTOR
{
		
}


//========================================================================
// 函数: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数: TIMx: 结构参数,请参考timer.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//空操作

	if(TIM == Timer0)
	{
		TR0 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		else									ET0 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		else									PT0 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		else										TMOD &= ~0x04;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//输出时钟
		else							INT_CLKO &= ~0x01;	//不输出时钟
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//允许中断
		else									ET1 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		else									PT1 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//对外计数或分频
		else										TMOD &= ~0x40;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//输出时钟
		else							INT_CLKO &= ~0x02;	//不输出时钟
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		AUXR &= ~(1<<4);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//允许中断
		else										IE2  &= ~(1<<2);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//对外计数或分频
		else										AUXR &= ~(1<<3);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//输出时钟
		else							INT_CLKO &= ~0x04;	//不输出时钟

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
		return	0;		//成功
	}
	return 2;	//错误
}
