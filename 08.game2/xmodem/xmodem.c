

#include "bsp/config.h"
#include "xmodem/xmodem.h"

//�ݲ�ʹ�á�
u16 xmodem_crc16(const u8 *buf, int sz)
{
	u16 crc = 0;
	while (--sz >= 0)
	{
		u8 i;
		crc ^= ((u16)*buf++) << 8;
		for (i = 0; i < 8; i++)
		{
			if (crc & 0x8000)
			{
				crc = crc << 1 ^ 0x1021;
			}
			else
			{
				crc <<= 1;
			}
        }
	}
	return crc;
}

//����У���
u8 xmodem_sum(const u8 *buf, int sz)
{
	u8 sum = 0;
	for(;sz>0;sz--)
	{
	 	sum += *buf++;
	}
	return sum;
}

//�����Ƿ���ȷ����ȷ����1��
u8 xmodem_check(u8* buff, u8 pkt_num)
{
	//����ż��
	if (pkt_num != buff[1])return 0;

	//����ŷ�����
	if(buff[1] + buff[2] != 0xFF)return 0;

	//������sum
	if(buff[131] != xmodem_sum(&buff[3], 128))return 0;

	return 1;
}

//����
s8 xmodem_start(struct xmodem_receiver *rx)
{	
	u8 cur_char = 0;
	u8 wrong_char = 0;
	u8 cur_packet = 1;
	s16 ch;
	u8 i;
	u8 *prx;

	prx = rx->rx_buf;
	while(1)
	{
		while(cur_char < XMODEM_BUF_LEN)
		{
			ch = rx->get_char();
			if(ch == -1)return -2;//��ʱ
			prx[cur_char] = (u8)ch;
			if(cur_char == 0)
			{
				switch(prx[cur_char])
				{
					case SOH:
					{
						cur_char++;
						break;
					}
					case EOT:
					{
						rx->put_char(ACK);
						rx->put_char(ACK);
						return 0;
					}
					default:
					{
						wrong_char++;
						if (wrong_char >= 5)
						{
							return -1;
						}
						rx->put_char(NAK);
						break;
					}
				}
			}
			else
			{
				cur_char++;
			}
		}
			  
		if(xmodem_check(prx, cur_packet))
		{
			cur_packet++;	
			//�ص�����
			rx->writer(&prx[3],128);
			#if 1
			for(i=0;i<cur_char;i++)
			{
				Uart2_Tx(byte2str(prx[i]));
				Uart2_Tx(",");
			}
			Uart2_Tx("\r\n");
			#endif
			rx->rx_ok_cnt++;
			cur_char = 0;
			rx->put_char(ACK);
		}
		else
		{
			cur_char = 0;
			rx->put_char(NAK);
		}
	}
}

//0: receive ok
//-1: retry over
s8 xmodem_rx(struct xmodem_receiver *rx)
{
	u8 retry_count = 0;

	while(retry_count < XMODEM_MAX_RETRY)
	{
		retry_count++;

		//CRC��ʽ����,У��ͷ�ʽ�����Ժá�
		//rx->put_char('C');
		rx->put_char(NAK);
		
		//�����ն�/CRT����෢һ��0x01����Ҫ���޳���
		if(rx->get_first())
		{
			break;	
		}
		rx->delay_1s();
	}

	return xmodem_start(rx);
}



