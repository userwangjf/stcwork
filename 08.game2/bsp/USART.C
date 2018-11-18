


#include "USART.h"


bool uart1_tx_rdy = 1;
u8* uart1_tx_ptr;
u8 uart1_echo_buf = 0;


u8 USART_Configuration(u8 UARTx, COMx_InitDefine *COMx)
{
	u32	j;
	
	if(UARTx == USART1)
	{
		if(COMx->UART_Mode > UART_9bit_BRTx)	return 2;	//模式错误
		if(COMx->UART_Polity == PolityHigh)		PS = 1;	//高优先级中断
		else									PS = 0;	//低优先级中断
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return 2;	//错误
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (u8)(j>>8);
				TL1 = (u8)j;
				ET1 = 0;	//禁止中断
				TMOD &= ~0x40;	//定时
				INT_CLKO &= ~0x02;	//不输出时钟
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
				AUXR |=  (1<<2);	//Timer2 set as 1T mode
				TH2 = (u8)(j>>8);
				TL2 = (u8)j;
				IE2  &= ~(1<<2);	//禁止中断
				AUXR &= ~(1<<3);	//定时
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//错误
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//固定波特率SysClk/2
			else								AUXR &= ~(1<<5);	//固定波特率SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//固定波特率SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//固定波特率SysClk/32
			else								PCON &= ~(1<<7);	//固定波特率SysClk/64
		}
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//允许中断
		else								ES = 0;	//禁止中断
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//允许接收
		else								REN = 0;	//禁止接收
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//切换IO
		if(COMx->UART_RXD_TXD_Short == ENABLE)	PCON2 |=  (1<<4);	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
		else									PCON2 &= ~(1<<4);
		return	0;
	}

	if(UARTx == USART2)
	{
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			if(COMx->UART_Polity == PolityHigh)		IP2 |=  1;	//高优先级中断
			else									IP2 &= ~1;	//低优先级中断
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return 2;	//错误
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			TH2 = (u8)(j>>8);
			TL2 = (u8)j;
			IE2  &= ~(1<<2);	//禁止中断
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//模式错误
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//允许中断
		else								IE2   &= ~1;		//禁止中断
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//允许接收
		else								S2CON &= ~(1<<4);	//禁止接收
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//切换IO
	}

	return 0;
}

#define S2RI 0x01
#define S2TI 0x02
void Uart2_Tx(u8* buf)
{
	for(;;)
	{
		if(*buf == 0)break;
		S2BUF = *buf++;
		while(!(S2CON & S2TI));
		S2CON &= ~S2TI;
	}
}

//发送时，仅拷贝指针，不拷贝数据。
void Uart1_Tx(u8 *string)
{
	//不能打断echo
	while(uart1_echo_buf != 0);
	//等待上一次传输完成
	#if UART_TX_WAIT
		//等上次传输完成。
		while(!uart1_tx_rdy);
	#else
		//发生溢出错误，打印~
		if(!uart1_tx_rdy)
		{
			ES = 0;
			while(!TI);
			SBUF = '~';
			while(!TI);
			ES = 1;
		}		
	#endif
	uart1_tx_rdy = 0;
	uart1_tx_ptr = string;
	while(uart1_echo_buf != 0);
	TI = 1;					//触发发送中断
}

void Uart1_Echo(u8 dat)
{
	uart1_echo_buf = dat;
	if(uart1_tx_rdy)
		TI = 1;
}

bool Uart1_Busy(void)
{
	if(uart1_tx_rdy)
		return 0;
	else
		return 1;
}

/********************* UART1中断函数************************/
void UART1_int (void) interrupt UART1_VECTOR
{
	u8 tmp;

	if(RI)
	{
		RI = 0;
		tmp = SBUF;		
		shell_rx_dat(tmp);
	}

	if(TI)
	{
		TI = 0;
		//ECHO有最高优先级，插队了。
		if(uart1_echo_buf == 0xff)
		{
			uart1_echo_buf = 0;
			if(!uart1_tx_rdy)//上次发送未完成
				SBUF = *uart1_tx_ptr++;
		}
		else if(uart1_echo_buf != 0)
		{
			SBUF = uart1_echo_buf;
			uart1_echo_buf = 0xff;
		}
		else if(uart1_tx_rdy)
			;
		else if(*uart1_tx_ptr == 0)
			uart1_tx_rdy = 1;
		else
			SBUF = *uart1_tx_ptr++; 	
	}
}

/********************* UART2中断函数************************/
void UART2_int (void) interrupt UART2_VECTOR
{
	if(RI2)
	{
		CLR_RI2();

	}

	if(TI2)
	{
		CLR_TI2();
	}

}



