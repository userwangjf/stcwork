

#include "bsp/config.h"
#include "xmodem/xmodem.h"

//暂不使用。
u16 xmodem_crc16(const u8 *buf, int sz) {
	u16 crc = 0;

	while(--sz >= 0) {
		u8 i;
		crc ^= ((u16) * buf++) << 8;

		for(i = 0; i < 8; i++) {
			if(crc & 0x8000) {
				crc = crc << 1 ^ 0x1021;
			} else {
				crc <<= 1;
			}
		}
	}

	return crc;
}

//计算校验和
u8 xmodem_sum(const u8 *buf, int sz) {
	u8 sum = 0;

	for(; sz > 0; sz--) {
		sum += *buf++;
	}

	return sum;
}

//检查包是否正确，正确返回1。
u8 xmodem_check(u8* buff, u8 pkt_num) {
	//包序号检查
	if(pkt_num != buff[1])
		return 0;

	//包序号反码检查
	if(buff[1] + buff[2] != 0xFF)
		return 0;

	//检查包的sum
	if(buff[131] != xmodem_sum(&buff[3], 128))
		return 0;

	return 1;
}

u32 xm_rx_ok_cnt = 0;

//接收
s8 xmodem_start(char *xm_rx_buf) {
	u8 cur_char = 0;
	u8 wrong_char = 0;
	u8 cur_packet = 1;
	s16 ch;
	u8 *prx;
	prx = xm_rx_buf;

	while(1) {

		while(cur_char < XMODEM_BUF_LEN) {
			ch = xm_getchar();

			if(ch == -1)
				return -2; //超时

			prx[cur_char] = (u8)ch;

			if(cur_char == 0) {
				switch(prx[cur_char]) {
				case SOH: {
					cur_char++;
					break;
				}

				case EOT: {
					xm_putchar(ACK);
					xm_putchar(ACK);
					return 0;
				}

				default: {
					wrong_char++;

					if(wrong_char >= 5) {
						return -1;
					}

					xm_putchar(NAK);
					break;
				}
				}
			} else {
				cur_char++;
			}
		}

		if(xmodem_check(prx, cur_packet)) {
			cur_packet++;
			//回调函数
			xm_save(&prx[3], 128);
			xm_rx_ok_cnt++;
			cur_char = 0;
			xm_putchar(ACK);
		} else {
			cur_char = 0;
			xm_putchar(NAK);
		}
	}
}

//0: receive ok
//-1: retry over
s8 xmodem_rx(char* xm_buf) {
	u8 retry_count = 0;

	while(retry_count < XMODEM_MAX_RETRY) {
		retry_count++;

		//CRC方式不行,校验和方式兼容性好。
		//xm_putchar('C');
		xm_putchar(NAK);

		//超级终端/CRT都会多发一个0x01，需要先剔除。
		if(xm_get_first()) {
			break;
		}

		xm_delay1s();
	}

	return xmodem_start(xm_buf);
}



