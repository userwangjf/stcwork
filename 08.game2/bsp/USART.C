


#include "USART.h"


bool uart1_tx_rdy = 1;
u8* uart1_tx_ptr;
u8 uart1_echo_buf = 0;


u8 USART_Configuration(u8 UARTx, COMx_InitDefine *COMx)
{
	u32	j;
	
	if(UARTx == USART1)
	{
		if(COMx->UART_Mode > UART_9bit_BRTx)	return 2;	//ģʽ����
		if(COMx->UART_Polity == PolityHigh)		PS = 1;	//�����ȼ��ж�
		else									PS = 0;	//�����ȼ��ж�
		SCON = (SCON & 0x3f) | COMx->UART_Mode;
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
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
				ET1 = 0;	//��ֹ�ж�
				TMOD &= ~0x40;	//��ʱ
				INT_CLKO &= ~0x02;	//�����ʱ��
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
				IE2  &= ~(1<<2);	//��ֹ�ж�
				AUXR &= ~(1<<3);	//��ʱ
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return 2;	//����
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//�̶�������SysClk/2
			else								AUXR &= ~(1<<5);	//�̶�������SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//�̶�������SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//�̶�������SysClk/32
			else								PCON &= ~(1<<7);	//�̶�������SysClk/64
		}
		if(COMx->UART_Interrupt == ENABLE)	ES = 1;	//�����ж�
		else								ES = 0;	//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	REN = 1;	//��������
		else								REN = 0;	//��ֹ����
		P_SW1 = (P_SW1 & 0x3f) | (COMx->UART_P_SW & 0xc0);	//�л�IO
		if(COMx->UART_RXD_TXD_Short == ENABLE)	PCON2 |=  (1<<4);	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE
		else									PCON2 &= ~(1<<4);
		return	0;
	}

	if(UARTx == USART2)
	{
		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//�ɱ䲨����
		{
			if(COMx->UART_Polity == PolityHigh)		IP2 |=  1;	//�����ȼ��ж�
			else									IP2 &= ~1;	//�����ȼ��ж�
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//��1T����
			if(j >= 65536UL)	return 2;	//����
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			TH2 = (u8)(j>>8);
			TL2 = (u8)j;
			IE2  &= ~(1<<2);	//��ֹ�ж�
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return 2;	//ģʽ����
		if(COMx->UART_Interrupt == ENABLE)	IE2   |=  1;		//�����ж�
		else								IE2   &= ~1;		//��ֹ�ж�
		if(COMx->UART_RxEnable == ENABLE)	S2CON |=  (1<<4);	//��������
		else								S2CON &= ~(1<<4);	//��ֹ����
		P_SW2 = (P_SW2 & ~1) | (COMx->UART_P_SW & 0x01);	//�л�IO
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

//����ʱ��������ָ�룬���������ݡ�
void Uart1_Tx(u8 *string)
{
	//���ܴ��echo
	while(uart1_echo_buf != 0);
	//�ȴ���һ�δ������
	#if UART_TX_WAIT
		//���ϴδ�����ɡ�
		while(!uart1_tx_rdy);
	#else
		//����������󣬴�ӡ~
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
	TI = 1;					//���������ж�
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

/********************* UART1�жϺ���************************/
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
		//ECHO��������ȼ�������ˡ�
		if(uart1_echo_buf == 0xff)
		{
			uart1_echo_buf = 0;
			if(!uart1_tx_rdy)//�ϴη���δ���
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

/********************* UART2�жϺ���************************/
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


