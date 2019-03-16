
#ifndef __XMODEM_H__
#define __XMODEM_H__

#define XMODEM_MAX_RETRY 	30
#define XMODEM_BUF_LEN 		132		//使用校验和方式

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A

s8 xmodem_rx(char* rx);
u8 xm_save(u8* buff, u8 size);
s8 xmodem_start(char *xm_rx_buf);
u8 xmodem_check(u8* buff, u8 pkt_num);
u8 xmodem_sum(const u8 *buf, int sz);


void xmodem_init(u8* rx_buf);
u8 xm_save(u8* buff, u8 size);
void xm_delay1s();
u8 xm_get_first();
void xm_putchar(u8 ch);
s16 xm_getchar();


extern u32 xm_rx_ok_cnt;


#endif

