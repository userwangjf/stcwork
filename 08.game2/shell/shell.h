
#ifndef __SHELL_H__
#define __SHELL_H__

#include "bsp/config.h"

#define SHELL_CMD_MAX_LEN		140
#define SHELL_ECHO_ON			1

#define SHELL_ECHO(dat)		Uart1_Echo(dat)
#define SHELL_TX(dat)		Uart1_Tx(dat)

extern u8 hex_str[11];


void shell_rx_dat(u8 dat);
void shell_init(void);
void shell_run(fifo_ctrl* fifo);

int mini_snprintf(char* buffer, unsigned int buffer_len, const char *fmt, ...);

#endif

