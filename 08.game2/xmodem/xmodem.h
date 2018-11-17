
#ifndef __XMODEM_H__
#define __XMODEM_H__

#define XMODEM_MAX_RETRY 	60
#define XMODEM_BUF_LEN 		132		//ʹ��У��ͷ�ʽ

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A

struct xmodem_receiver {
	s16 (*get_char)(void); 	 	//�����ַ�����������ʱ
	void (*put_char)(u8 c);		//�����ַ�
	u8 (*get_first)(void);		//���յ�һ���ַ���
	void (*delay_1s)(void); 	//��ʱ1�롣
	u8 (*writer)(u8* buff, u8 size);	//����һ֡���ݺ󱣴�
	u8* rx_buf;							//��ʱ���ջ��棬��Ҫ����132.
	u32 rx_ok_cnt;						//���ճɹ���֡����
};

s8 xmodem_rx(struct xmodem_receiver *rx);

void xmodem_init(u8* rx_buf);

#endif

