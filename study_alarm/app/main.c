

#include "bsp/config.h"

extern void os_test();

void main()
{
	u8 idle_cnt = 0;
	bit uart1_ren = 0;
	u8 key = 0xff;
	u8 xon = 0;

	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	P5 = 0xff;

	GPIO_Config();
	
	//PCA_config();
	//disp_clear();

	
	Timer_config();
	EA = 1;
   	UART_config(0,115200);
	printk("\r\nHelloUart1\r\n");
	printk("\r\n%d,%x,%c",11223344,0x11223344,'c');
	
	init_595();
	//test_595();
	
	os_test();
	
	//初始化操作系统
	os_init();
	
	//创建任务
	os_taskCreate(0,task_ds3231,100000);
	
	//无限循环
	os_start();

	while(1);
	
}


void GPIO_Config(void)
{
	GPIO_InitTypeDef	GPIO_Init;		//结构定义
	GPIO_Init.Pin  = GPIO_Pin_All;		//指定要初始化的IO, GPIO_Pin_0 ! GPIO_Pin_7, 或操作
	GPIO_Init.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP

	//配置键盘列,P3.0~P3.5
	#if 0
	GPIO_Init.Pin = 0x3f;
	GPIO_Init.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3,&GPIO_Init);
	#endif


}


void UART_config(u8 int_en,u32 rate)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义

	//UART1
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,       UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//使用波特率,   BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = rate;		    	//波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
	if(int_en)
		COMx_InitStructure.UART_Interrupt = ENABLE;				//中断允许,   ENABLE或DISABLE
	else
		COMx_InitStructure.UART_Interrupt = DISABLE;
	COMx_InitStructure.UART_Polity    = PolityLow;			//中断优先级, PolityLow,PolityHigh
	COMx_InitStructure.UART_P_SW      = UART1_SW_P30_P31;	//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;		//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
	USART_Configuration(USART1, &COMx_InitStructure);		//初始化串口1 USART1,USART2

	//UART2
	#if 0
	COMx_InitStructure.UART_Interrupt = DISABLE;
   	COMx_InitStructure.UART_P_SW = UART2_SW_P10_P11;
	USART_Configuration(USART2, &COMx_InitStructure);
	#endif
}

void PCA_config ( void )
{
	PCA_InitTypeDef		PCA_InitStructure;

	#if 1
	//配置作为高速PWM模式，用于8bit pcm数据播放
	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_IoUse    = PCA_P34_P35_P36_P37;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//ENABLE, DISABLE
	PCA_InitStructure.PCA_Polity   = PolityLow;			//优先级设置	PolityHigh,PolityLow
	//PCA_InitStructure.PCA_RUN      = DISABLE;			//ENABLE, DISABLE
	PCA_Init ( PCA_Counter,&PCA_InitStructure );

	PCA_InitStructure.PCA_Mode     = PCA_Mode_PWM;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;					//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 0x8080;				//对于软件定时, 为匹配比较值

	PCA_Init ( PCA1,&PCA_InitStructure );

	#endif

}


//
/**
*外部中断初始化，使能鼠标的clk下降沿中断
*@brief
*@param
*@return

*/
void EXTI_config(void)
{
 	EXTI_InitTypeDef exti;

	exti.EXTI_Interrupt = ENABLE;
	exti.EXTI_Polity = PolityLow;
	exti.EXTI_Mode = EXT_MODE_RiseFall;

	//作为超声echo的接收
	Ext_Inilize(EXT_INT0,&exti);
}








