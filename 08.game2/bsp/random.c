
#include "bsp/config.h"
#include "bsp/bsp.h"

//ʹ�ü�����0��1�����������
u8 random()
{
	u8 temp[2];

	temp[0] = TL0 + TL1;
	temp[1] = TH0 + TH1;
	
	return crc8(temp,2);
}

