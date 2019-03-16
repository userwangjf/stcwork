
#include "bsp/config.h"



#define MODE_SELECT 0
#define MODE_SNAKE 	1
#define MODE_TETRIS 2

u8 mode = 0;
u8 mode_pre = 0;

void mode_select(u8 key) {
	//选择mode
	if(key == KEY_UP) {
		if(mode_pre < 5)
			mode_pre++;
	} else if(key == KEY_DOWN) {
		if(mode_pre > 0)
			mode_pre--;
	}

	disp_dec(1, 10, mode_pre);
	disp_dec(6, 10, mode_pre);

	//确定按键
	if(key == KEY_A) {
		mode = mode_pre;
		disp_clear();

		if(mode == MODE_SNAKE)
			snake_init();

		if(mode == MODE_TETRIS)
			tetris_init();
	}
}

//
fifo_ctrl fifo_uart1_rx;
fifo_ctrl fifo_uart1_tx;
fifo_ctrl fifo_music_rd;
u8 uart1_rx_buf[32];
u8 uart1_tx_buf[128];
u8 music_buf[32];
u8 music_rd_buf[128];

extern u32 tx_cnt;

void main() {
	u8 idle_cnt = 0;
	bit uart1_ren = 0;
	u8 key = 0xff;
	u8 xon = 0;
	//u8 i,j = 0;
	//u8 rbuf[32];
	u8 shine_cnt = 0;
	//初始化
	GPIO_Config();
	fifo_init(&fifo_uart1_rx, uart1_rx_buf, 32);
	fifo_init(&fifo_uart1_tx, uart1_tx_buf, 128);
	fifo_init(&fifo_music_rd, music_rd_buf, 128);
	UART_config(1, 115200);
	EA = 1;

	printk("\r\nhello world");

	Timer_config();
	PCA_config();
	disp_clear();
	w25qxx_Init();
	//测试使用STC的内部EEPROM保存掉电不丢失的数据
	//save_test();
	//fifo_test();
	printk("\r\nstart shell\r\n>>>");

	while(1) {
		#if 1

		if(cur_task_id == 0) {
			cur_task_id = 0xff;
			shell_run(&fifo_uart1_rx);
			shine_cnt++;

			if(shine_cnt >= 200)
				shine_cnt = 0;

			if(shine_cnt == 0)
				disp_on(0, 0);
			else if(shine_cnt == 50)
				disp_off(0, 0);
		}

		#endif
		#if 1

		//键盘扫描
		if(cur_task_id == 1) {
			cur_task_id = 0xff;
			uart1_ren = REN;
			REN = 0;//关闭串口
			key_scan();
			key = key_get();

			if(key == KEY_START) {
				disp_clear();
				mode = 0;
				mode_pre = 0;
				key = 0xff;
			}

			#if 0

			//显示按键编码
			if(key != 0xff) {
				disp_dec(0, 0, key >> 4);
				disp_dec(4, 0, key & 0x0f);
			}

			#endif
			P3 |= 0x3f;//恢复端口
			REN = uart1_ren;
		}

		#endif
		#if 1

		//选择工作模式
		if(cur_task_id == 2) {
			cur_task_id = 0xff;

			if(mode == 0) {
				mode_select(key);
			} else if(mode == MODE_SNAKE) {
				snake_game(key);
			} else if(mode == MODE_TETRIS) {
				tetris_run(key);
			}
		}

		#endif
		#if 1

		//从文件系统读数据
		if(cur_task_id == 3) {
			cur_task_id = 0xff;

			if(music_on) {
				for(;;) {
					if(music_len > 0 && fifo_remain(&fifo_music_rd) >= 0x20) {
						if(music_len > 32) {
							w25qxx_ReadBytes(music_addr, music_buf, 32);
							fifo_wr(&fifo_music_rd, music_buf, 32);
							music_addr += 32;
							music_len -= 32;
						} else {
							w25qxx_ReadBytes(music_addr, music_buf, music_len);
							fifo_wr(&fifo_music_rd, music_buf, music_len);
							music_len = 0;
						}
					}
					else
						break;
				}
			}
		}

		#endif
	}
}


void GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_Init;		//结构定义
	GPIO_Init.Pin  = GPIO_Pin_All;		//指定要初始化的IO, GPIO_Pin_0 ! GPIO_Pin_7, 或操作
	GPIO_Init.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	P5 = 0xff;
	#if 1
	//配置键盘扫描,P3.0~P3.5
	GPIO_Init.Pin = 0x3f;
	GPIO_Init.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3, &GPIO_Init);
	#endif
	#if 1
	//配置BEEP输出
	GPIO_Init.Pin = GPIO_Pin_6;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P3, &GPIO_Init);
	#endif
	#if 1
	//LED列驱动，正极
	GPIO_Init.Pin = 0xff;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P2, &GPIO_Init);
	GPIO_Init.Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P4, &GPIO_Init);
	#endif
	#if 1
	//LED行驱动，负极，P0.0~P0.7
	GPIO_Init.Pin = 0xff;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P0, &GPIO_Init);
	//P1.0~P1.6
	GPIO_Init.Pin = 0x7f;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P1, &GPIO_Init);
	//P4.0~P4.4/P4.7
	GPIO_Init.Pin = 0x9f;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P4, &GPIO_Init);
	#endif
	#if 1
	//W25Q64
	GPIO_Init.Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P5, &GPIO_Init);
	GPIO_Init.Pin = GPIO_Pin_4;
	GPIO_Init.Mode = GPIO_OUT_OD;
	GPIO_Inilize(GPIO_P5, &GPIO_Init);
	#endif
}


void UART_config(u8 int_en, u32 rate) {
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
	COMx_InitStructure.UART_Interrupt = ENABLE;
	COMx_InitStructure.UART_P_SW = UART2_SW_P10_P11;
	USART_Configuration(USART2, &COMx_InitStructure);
	#endif
}

void PCA_config(void) {
	PCA_InitTypeDef		PCA_InitStructure;
	#if 1
	//配置作为高速PWM模式，用于8bit pcm数据播放
	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_IoUse    = PCA_P34_P35_P36_P37;	//PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//ENABLE, DISABLE
	PCA_InitStructure.PCA_Polity   = PolityLow;			//优先级设置	PolityHigh,PolityLow
	//PCA_InitStructure.PCA_RUN      = DISABLE;			//ENABLE, DISABLE
	PCA_Init(PCA_Counter, &PCA_InitStructure);
	PCA_InitStructure.PCA_Mode     = PCA_Mode_PWM;		//PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_HighPulseOutput
	PCA_InitStructure.PCA_PWM_Wide = 0;					//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
	PCA_InitStructure.PCA_Interrupt_Mode = DISABLE;		//PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
	PCA_InitStructure.PCA_Value    = 0x8080;				//对于软件定时, 为匹配比较值
	PCA_Init(PCA1, &PCA_InitStructure);
	#endif
}


