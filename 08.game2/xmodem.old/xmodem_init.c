
#include "bsp/config.h"

#define XM_UART1	1


//带超时串口接收，在12M时，大约3秒，需要关闭中断。
//超时返回-1
s16 xmodem_getchar() {
	#if XM_UART1
	u32 delay = 0x50000;
	u8 tmp;

	for(; delay > 0; delay--) {
		if(RI)
			break;
	}

	if(delay == 0)
		return -1;

	tmp = SBUF;
	RI = 0;
	return tmp;
	#else
	u32 delay = 0x50000;
	u8 tmp;

	for(; delay > 0; delay--) {
		if(RI2)
			break;
	}

	if(delay == 0)
		return -1;

	tmp = S2BUF;
	CLR_RI2();
	return tmp;
	#endif
}

void xmodem_putchar(u8 ch) {
	#if XM_UART1
	SBUF = ch;

	while(!TI);

	TI = 0;
	#else
	S2BUF = ch;

	while(!TI2);

	CLR_TI2();
	#endif
}

u8 xmodem_get_first() {
	#if XM_UART1

	if(RI) {
		RI = 0;//清除第一个字符
		return 1;
	} else
		return 0;

	#else

	if(RI2) {
		CLR_RI2();//清除第一个字符
		return 1;
	} else
		return 0;

	#endif
}

void xmodem_delay1s() {
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
}

u32 romfs_waddr = 0;
u8 rx_ok = 0;
//保存从xmodem获取的信息，
//size <= 128
u8 xmodem_save(u8* buff, u8 size) {

	if((rx_ok & 0x1f) == 0x00) {
		led_col_set(0);
	} else if((rx_ok & 0x1f) == 0x10) {
		led_col_clr(0);
	}

	rx_ok++;

	w25qxx_WriteByte(romfs_waddr, buff, size);

	romfs_waddr += size;

	return 0;
}

void xmodem_init(u8* rx_buf) {
	struct xmodem_receiver xm_rx;

	xm_rx.get_char = xmodem_getchar;
	xm_rx.put_char = xmodem_putchar;
	xm_rx.get_first = xmodem_get_first;
	xm_rx.delay_1s = xmodem_delay1s;
	xm_rx.writer = xmodem_save;
	xm_rx.rx_buf = rx_buf;
	xm_rx.rx_ok_cnt = 0;
	romfs_waddr = 0;
	led_row_dis();
	led_col_dis();
	led_row_clr(0);

	//关闭中断，避免影响超时的精度
	EA = 0;

	if(0 == xmodem_rx(&xm_rx)) {
		xm_rx.delay_1s(); //延时等待退出。
		EA = 1;
		printk("\r\nXMODEM OK CNT: %d\r\n",xm_rx.rx_ok_cnt);
	} else {
		xm_rx.delay_1s(); //延时等待退出。
		EA = 1;
		printk("\r\nXMODEM RX ERROR\r\n");
	}
}

