
#include "bsp/config.h"


//带超时串口接收，在12M时，大约3秒，需要关闭中断。
//使用查询方式,需要关闭中断
//超时返回-1
s16 xm_getchar() {
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
}

void xm_putchar(u8 ch) {
	SBUF = ch;

	while(!TI);

	TI = 0;
}

u8 xm_get_first() {
	if(RI) {
		RI = 0;//清除第一个字符
		return 1;
	} else
		return 0;
}

void xm_delay1s() {
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
}


u32 write_addr = 0;

//保存从xmodem获取的信息，
//size <= 128
u8 xm_save(u8* buff, u8 size) {

	if((xm_rx_ok_cnt & 0x001f) == 0x00) {
		led_col_set(0);
	} else if((xm_rx_ok_cnt & 0x001f) == 0x10) {
		led_col_clr(0);
	}

	w25qxx_WriteByte(write_addr, buff, size);

	write_addr += size;

	return 0;
}

void xmodem_init(u8* xm_rx_buf) {
	write_addr = 0;
	led_row_dis();
	led_col_dis();
	led_row_clr(0);

	//关闭中断，避免影响超时的精度
	EA = 0;

	if(0 == xmodem_rx(xm_rx_buf)) {
		xm_delay1s(); //延时等待退出。
		EA = 1;
		printk("\r\nXMODEM OK CNT: %d\r\n", (u32)xm_rx_ok_cnt);
	} else {
		xm_delay1s(); //延时等待退出。
		EA = 1;
		printk("\r\nXMODEM RX ERROR\r\n");
	}
}

