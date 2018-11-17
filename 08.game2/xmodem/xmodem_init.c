
#include "bsp/config.h"


//����ʱ���ڽ��գ���12Mʱ����Լ3�룬��Ҫ�ر��жϡ�
//��ʱ����-1
s16 xmodem_getchar()
{
	u32 delay = 0x50000;
	u8 tmp;
	for(;delay>0;delay--)
	{
		if(RI)break;
	}
	if(delay == 0)return -1;
	tmp = SBUF;
	RI = 0;
	return tmp;	
}

void xmodem_putchar(u8 ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
}

u8 xmodem_get_first()
{
	if(RI){
		RI = 0;//�����һ���ַ�
		return 1;
	}
	else
		return 0;
}

void xmodem_delay1s()
{
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
}

u8 xmodem_save(u8* buff, u8 size)
{

	return 0;
}

void xmodem_init(u8* rx_buf)
{
	struct xmodem_receiver xm_rx;

	xm_rx.get_char = xmodem_getchar;
	xm_rx.put_char = xmodem_putchar;
	xm_rx.get_first = xmodem_get_first;
	xm_rx.delay_1s = xmodem_delay1s;
	xm_rx.writer = xmodem_save;
	xm_rx.rx_buf = rx_buf;
	xm_rx.rx_ok_cnt = 0;

	//�ر��жϣ�����Ӱ�쳬ʱ�ľ���
	EA = 0;
	if(0 == xmodem_rx(&xm_rx))
	{
		xm_rx.delay_1s(); //��ʱ�ȴ��˳���
		EA = 1;
		Uart1_Tx("\r\nXMODEM OK CNT: ");
		Uart1_Tx(hex2str(xm_rx.rx_ok_cnt));
		Uart1_Tx("\r\n");
	}
	else
	{
		xm_rx.delay_1s(); //��ʱ�ȴ��˳���
		EA = 1;
		Uart1_Tx("\r\nXMODEM RX ERROR\r\n");	
	}
}

