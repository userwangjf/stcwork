

#include "bsp/config.h"

#define IO_595_RSTn		P20
#define IO_595_LOAD 	P22
#define IO_595_OEn		P23
#define IO_595_SCK		P21
#define IO_595_SI_0		P24
#define IO_595_SI_1		P25
#define IO_595_SI_2		P26
#define IO_595_SI_3		P27
#define IO_595_POWER_OFF	P37

const u8 seg_char[18] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF,0xbf};//0-9,A-F,灭,-

void data_out_595(u8 d0, u8 d1, u8 d2, u8 d3)
{
	u8 i;

	for(i=0;i<8;i++) {
		IO_595_SI_0 = d0 >> 7;
		IO_595_SI_1 = d1 >> 7;
		IO_595_SI_2 = d2 >> 7;
		IO_595_SI_3 = d3 >> 7;
		IO_595_SCK = 0;
		IO_595_SCK = 0;
		IO_595_SCK = 1;
		IO_595_SCK = 1;
		d0 = d0 << 1;
		d1 = d1 << 1;
		d2 = d2 << 1;
		d3 = d3 << 1;
	}
	IO_595_LOAD = 0;
	IO_595_LOAD = 0;
	IO_595_LOAD = 1;
	IO_595_LOAD = 1;
}
	
void init_595()
{

	GPIO_InitTypeDef	GPIO_Init;		//结构定义
	GPIO_Init.Pin  = GPIO_Pin_All;		//指定要初始化的IO, GPIO_Pin_0 | GPIO_Pin_7, 或操作
	GPIO_Init.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2,&GPIO_Init);
	
	GPIO_Init.Pin = GPIO_Pin_7;
	GPIO_Inilize(GPIO_P3,&GPIO_Init);
	
	IO_595_RSTn = 0;
	IO_595_LOAD = 0;
	IO_595_OEn = 1;
	IO_595_SCK = 0;
	IO_595_POWER_OFF = 0;
	
	IO_595_RSTn = 1;
	IO_595_OEn = 0;
	
	data_out_595(0, 0, 0, 0);
}



void seg_disp_num(u8 d0,u8 d1,u8 d2,u8 d3) {
	data_out_595(seg_char[d0%16],seg_char[d1%16],seg_char[d2%16],seg_char[d3%16]);
}

u8 bright_curr = 0;

//通过开关595的oe来控制数码管的亮度
void bright_595() {
	if(bright_curr < 2)
		IO_595_OEn = 0;
	else
		IO_595_OEn = 1;

	if(bright_curr++ >= 9)
		bright_curr = 0;	
}

//依次循环点亮0的6个段码
void loop_zero_595() {
	u8 i;
	u8 show;
	for(i=0;i<6;i++) {
		show = ~(0x1<<i);
		data_out_595(show,show,show,show);
		delay_ms(100);
	}
}

//依次
void loop_eight_595() {
	u8 show;

	show = ~(0x40);
	data_out_595(show,show,show,show);
	delay_ms(100);
	show = ~(0x30);
	data_out_595(show,show,show,show);
	delay_ms(100);
	show = ~(0x09);
	data_out_595(show,show,show,show);
	delay_ms(100);
	show = ~(0x06);
	data_out_595(show,show,show,show);
	delay_ms(100);
}


void test_595() {
	u8 i,j;
	u32 cnt = 0;

	for(j=0;j<5;j++) {
		loop_zero_595();
	}

	for(i=0;i<18;i++) {
		data_out_595(seg_char[i%18],seg_char[i%18],seg_char[i%18],seg_char[i%18]);
		os_delayTick(500000);
	}
	
	for(cnt=0;;cnt++) {
		
		data_out_595(seg_char[cnt%10],seg_char[cnt/10%10],seg_char[cnt/100%10],seg_char[cnt/1000%10]);
		cnt++;
		os_delayTick(100000);
	}
}


