/******************************************************************************
** Descriptions:		sd ������������: Ӳ������� ---- SPI��������ͷ�ļ�
******************************************************************************/

#ifndef __SDHAL_H__
#define __SDHAL_H__

#include "sdconfig.h"
#include "sddriver.h"
#include "sdcmd.h"
#include "sdcrc.h"

/*��ʼ��SPI����	init SPI BUS*/
void SPI_INIT(void);

/* ��⿨�Ƿ���ȫ����  check weather card is insert entirely */
extern INT8U SD_ChkCard(void);

/* ��⿨�Ƿ�д����  check weather card is write protect */
extern INT8U SD_ChkCardWP(void);

/* ��ʼ������SD����Ӳ����ʼ�� initialize the hardware that access sd card */
extern void SD_HardWareInit(void);

/* ����SPI��ʱ��С��400kHZ set the clock of SPI less than 400kHZ */
extern void SPI_Clk400k(void);

/* ����SPI��clock�����ֵ set the clock of SPI to maximum */
extern void SPI_ClkToMax(void);

/* ͨ��SPI�ӿڷ���һ���ֽ� send a byte by SPI interface */
extern void SPI_SendByte(INT8U byte);

/* ��SPI�ӿڽ���һ���ֽ� receive a byte from SPI interface */
extern INT8U SPI_RecByte(void);

/* ƬѡSPI�ӻ� select the SPI slave */
extern void SPI_CS_Assert(void);

/* ��ƬѡSPI�ӻ� not select the SPI slave */
extern void SPI_CS_Deassert(void);

#endif