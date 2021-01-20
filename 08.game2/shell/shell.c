

#include "bsp/config.h"
#include "shell/shell.h"

extern s16 pos_x ;
extern s16 pos_y ;

bool shell_rx_ok;
u8 shell_rx_ptr = 0;
//用于共享的缓存
u8 shell_rx_buf[SHELL_CMD_MAX_LEN];
u8 shell_tx_buf[SHELL_CMD_MAX_LEN];
//char data shell_rx_buf[SHELL_CMD_MAX_LEN];
u8 shell_tx_ptr = 0;

s8 is_blank(u8 ch) {
	if(ch == ' ')
		return 1;
	else if(ch == 0)
		return 1;
	else if(ch == '\t')
		return 1;
	else if(ch == '\r')
		return 1;
	else if(ch == '\n')
		return 1;
	else
		return 0;
}

u8* get_param(s8 num) {
	u8 i;
	u8* param = NULL;
	u8 prev = ' ';

	for(i = 0; i < SHELL_CMD_MAX_LEN; i++) {
		if(num < 0) {
			if(is_blank(shell_rx_buf[i])) {
				shell_rx_buf[i] = 0;
				break;
			}
		} else if(prev == 0 && shell_rx_buf[i] == 0)
			break;
		else if(is_blank(prev) && !is_blank(shell_rx_buf[i])) {
			if(num-- == 0) {
				param = &shell_rx_buf[i];
			}
		}

		prev = shell_rx_buf[i];
	}

	return param;
}

void list_param() {
	u8 i;
	char* param;

	for(i = 0; i < 10; i++) {
		param = get_param(i);

		if(param == NULL) {
			printk("\r\nparam finish");
			break;
		} else {
			printk("\r\nparam%d: %s", (u32)i, param);
		}
	}
}

//周期性的调用此函数，处理shell命令
void shell_run(fifo_ctrl* fifo) {
	u8 rdata[128];
	u32 addr = 0;
	u8 i;
	u8 uart_rx;
	struct romfs_inode* file;

	//从串口缓冲区读出数据
	for(;;) {
		if(fifo_rd(fifo, &uart_rx, 1) == 0)
			break;

		shell_rx_dat(uart_rx);
	}

	if(!shell_rx_ok)
		return;

	shell_rx_ok = 0;
	printk("\r\n%s", shell_rx_buf);
	list_param();

	if(shell_rx_buf[0] == 'X' && shell_rx_buf[1] == 'M') {
		printk("\r\nStart XModem:\r\n");
		delay_ms(200);
		xmodem_init(shell_rx_buf);
	} else if(shell_rx_buf[0] == 'E' && shell_rx_buf[1] == 'A') {
		addr = str2hex(&shell_rx_buf[3]);

		if(addr == 0xffffffff)
			w25qxx_EraseChip();
		else
			w25qxx_EraseSector(addr);

		printk("\r\nErase Sector:");
		printk(hex2str(addr));
		printk("\r\n");
	} else if(shell_rx_buf[0] == 'R' && shell_rx_buf[1] == 'D') {
		addr = str2hex(&shell_rx_buf[3]);
		w25qxx_ReadBytes(addr, rdata, 16);
		printk("\r\nRead Addr:");
		printk(hex2str(addr));
		printk("\r\n");

		for(i = 0; i < 16; i++) {
			printk(byte2str(rdata[i]));
			printk(" ");
		}

		printk("\r\n");
	} else if(shell_rx_buf[0] == 'W' && shell_rx_buf[1] == 'R') {
		addr = str2hex(&shell_rx_buf[3]);

		for(i = 0; i < 128; i++) {
			rdata[i] = (u8)addr + i;
		}

		w25qxx_WriteByte(addr, rdata, 128);
		printk("\r\nwrite Addr:");
		printk(hex2str(addr));
		printk("\r\n");
	} else if(shell_rx_buf[0] == 'L' && shell_rx_buf[1] == 'S') {
		//list file addr
		for(i = 0; i < SHELL_CMD_MAX_LEN; i++)
			if(shell_rx_buf[i] == '\n' || shell_rx_buf[i] == '\r')
				shell_rx_buf[i] = 0;

		file = romfs_namei(&shell_rx_buf[3]);
		printk("\r\nFile addr: ");
		printk(hex2str(file->spec.file_data));
		printk("\r\n");
	} else if(shell_rx_buf[0] == 'P' && shell_rx_buf[1] == 'L') {
		//play music
		for(i = 0; i < SHELL_CMD_MAX_LEN; i++)
			if(shell_rx_buf[i] == '\n' || shell_rx_buf[i] == '\r')
				shell_rx_buf[i] = 0;

		music_start(&shell_rx_buf[3], 1);
	}

	printk("\r\n>>>");
}

void shell_init(void) {
	shell_rx_ptr = 0;
}

//接收字符，需要在uart中断函数中调用。
void shell_rx_dat(u8 dat) {
	u8 echo[3];

	if(dat == '\n' || dat == '\r') {
		shell_rx_ok = 1;
		shell_rx_buf[shell_rx_ptr] = 0;
		shell_rx_buf[shell_rx_ptr + 1] = 0;
		shell_rx_ptr = 0;
	} else if(dat == 0x08) {//backspace
		if(shell_rx_ptr > 0) {
			shell_rx_ptr--;
			echo[0] = '\b';
			echo[1] = ' ';
			echo[2] = 0;
			printk(echo);
		}
	} else if(dat == 0x03) {//ctrl-c
		shell_rx_buf[0] = 0;
		shell_rx_ptr = 0;
		shell_rx_ok = 1;
		return ;
	} else if(shell_rx_ptr < (SHELL_CMD_MAX_LEN - 1)) {
		shell_rx_buf[shell_rx_ptr++] = dat;
		shell_tx_ptr++;
	} else {
		shell_rx_buf[shell_rx_ptr] = 0;
		shell_rx_buf[shell_rx_ptr + 1] = 0;
		shell_rx_ptr = 0;
		shell_tx_ptr = 0;
		shell_rx_ok = 1;
	}

	#if SHELL_ECHO_ON
	echo[0] = dat;
	echo[1] = 0;
	printk(echo);
	#endif
}



