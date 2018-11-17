/*****************************************************************************************************
** Descriptions:sd �����������: Ӳ������� ---- SPI��������
********************************************************************************************************/
#include "sdhal.h"

// SPI transfer mode
#define TIMOD_RX		0x00
#define TIMOD_TX 		0x01
#define TIMOD_DMA_RX 	0x02
#define TIMOD_DMA_TX 	0x03
#define TIMOD_MASK 		0x03

	/**************************************************************

		��дSD����SPI�ӿں���: SPI�ӿ�����,����/�����ֽں���

	**************************************************************/
/*******************************************************************************************************************
** ��������: void SD_Power()					Name:	  void SD_Power()
** ��������: �Կ����µ�,���ϵ�					Function: turn off the card's power, and turn on
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SD_Power(void)
{
//	INT32U i;
//
//	SD_POWER_GPIO();
//	SD_POWER_OUT();
//	SD_POWER_OFF();								/* �ر� SD ����Դ  turn off power of sd card */
//	
//	SPI_SCK_GPIO();	
//	SPI_SCK_OUT();
//	SPI_SCK_CLR();								/* SCK  �����õ�   set SCK to zero */
//	
//	SPI_MISO_GPIO();
//	SPI_MISO_OUT();
//	SPI_MISO_CLR();								/* MISO �����õ�   set MISO to zero */
//	
//	SPI_MOSI_GPIO();		
//	SPI_MOSI_OUT();
//	SPI_MOSI_CLR();								/* MOSI �����õ�   set MOSI to zero */
//	
//	SPI_CS_GPIO();								
//   	SPI_CS_OUT();								
//	SPI_CS_CLR();								/* CS �����õ�	   set CS to zero */
//		
//	for(i = 0; i < 0x9000; i++);				/* �رյ�Դ��ʱ    delay after turn off power of sd card */
//	SD_POWER_ON();								/* �� SD ����Դ  turn on power of sd card */
}

/********************************************************************************************************
** �������ƣ�SPI_Init()
** �������ܣ���SSP����������Ϊ����SPI��
** ��ڲ�������
** ���ڲ�������
**********************************************************************************************************/
void  SPI_INIT(void)
{
	*pSPI_FLG	=0xFF10;		//PF4 as Chip Select
	*pSPI_BAUD	=0x0004;
	*pSPI_CTL	=0x5525;		//Enable SPI,Master,Enable MISO
}


/*******************************************************************************************************************
** ��������: void SD_HardWareInit()				Name:	  void SD_HardWareInit()
** ��������: ��ʼ������SD����Ӳ������			Function: initialize the hardware condiction that access sd card
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SD_HardWareInit(void)
{
	SPI_INIT();									/* ��ʼ��SPI�ӿ� */
	SPI_CS_SET();								/* CS�ø� */
}


/*******************************************************************************************************************
** ��������: void SPI_Clk400k()					Name:	  void SPI_Clk400k()
** ��������: ����SPI��ʱ��С��400kHZ			Function: set the clock of SPI less than 400kHZ
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_Clk400k(void)
{
//	*pSPI_BAUD	=0x00A1;   						/* ����SPIʱ�ӷ�ƵֵΪ161  Set the value of dividing frequency to 322 */
	*pSPI_BAUD	=0x00DE;   						/* ����SPIʱ�ӷ�ƵֵΪ222  Set the value of dividing frequency to 444 */
}


/*******************************************************************************************************************
** ��������: void SPI_ClkToMax()				Name:	  void SPI_ClkToMax()
** ��������: ����SPI��clock�����ֵ				Function: set the clock of SPI to maximum
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_ClkToMax(void)
{
	*pSPI_BAUD	=0x0005;					/* ����SPIʱ�ӷ�ƵֵΪ2*3  Set the value of dividing frequency to 2*3 */
}


/*******************************************************************************************************************
** ��������: void SPI_SendByte()				Name:	  void SPI_SendByte()
** ��������: ͨ��SPI�ӿڷ���һ���ֽ�			Function: send a byte by SPI interface
** �䡡  ��: INT8U byte: ���͵��ֽ�				Input:	  INT8U byte: the byte that will be send
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_SendByte(INT8U byte)
{
	*pSPI_STAT = TXCOL | RBSY | MODF | TXE;
	*pSPI_CTL =MSTR | TIMOD_TX | SPE;
	*pSPI_TDBR = byte;

	while(*pSPI_STAT & TXS);
	while(((*pSPI_STAT & SPIF)==0));
}


/*******************************************************************************************************************
** ��������: INT8U SPI_RecByte()				Name:	  INT8U SPI_RecByte()
** ��������: ��SPI�ӿڽ���һ���ֽ�				Function: receive a byte from SPI interface
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: �յ����ֽ�							Output:	  the byte that be received
********************************************************************************************************************/
INT8U SPI_RecByte(void)
{
	*pSPI_STAT = TXCOL | RBSY | MODF | TXE;
	*pSPI_CTL =MSTR | TIMOD_TX | SPE ;
	*pSPI_TDBR = 0xFF;

	while(*pSPI_STAT & TXS);
	while(((*pSPI_STAT & SPIF)==0));

	return (unsigned char)*pSPI_RDBR;
}


/*******************************************************************************************************************
** ��������: void SPI_CS_Assert()				Name:	  void SPI_CS_Assert()
** ��������: ƬѡSPI�ӻ�						Function: select the SPI slave
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_Assert(void)
{
	SPI_CS_CLR();			   					/* ƬѡSPI�ӻ�  select the SPI slave */
}


/*******************************************************************************************************************
** ��������: void SPI_CS_Deassert()				Name:	  void SPI_CS_Deassert()
** ��������: ��ƬѡSPI�ӻ�						Function: not select the SPI slave
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_Deassert(void)
{
	SPI_CS_SET();			    				/* ��ƬѡSPI�ӻ�  not select the SPI slave */
}


/*******************************************************************************************************************
** ��������: void SPI_CS_CLR()					Name:	  SPI_CS_CLR()
** ��������: ƬѡSPI�ӻ�						Function: select the SPI slave
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_CLR(void)
{
	*pSPI_FLG	=0xFF10;
}


/*******************************************************************************************************************
** ��������: void SPI_CS_SET()					Name:	  void SPI_CS_SET()
** ��������: ��ƬѡSPI�ӻ�						Function: not select the SPI slave
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_SET(void)
{
	*pSPI_FLG	=0xEF10;
}

/*******************************************************************************************************************
** ��������: void SD_ChkCard()					Name:	  void SD_ChkCard()
** ��������: ��⿨�Ƿ���ȫ����					Function: check weather card is insert entirely
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: 0: ����ȫ����	1: ��û����ȫ����   Output:	  1: insert entirely	0: not insert entirely
********************************************************************************************************************/
INT8U SD_ChkCard(void)
{
	if (SD_INSERT_STATUS() == PF10)
		return SD_ERR_NO_CARD;					/* δ��ȫ���� not insert entirely */
	else
		return SD_NO_ERR;						/* ��ȫ���� insert entirely */
}

/*******************************************************************************************************************
** ��������: void SD_ChkCardWP()				Name:	  void SD_ChkCardWP()
** ��������: ��⿨д����						Function: check weather card is write protect
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: 1: ����д����	0: ��δд����	    Output:	  1: insert write protect	0: not write protect
********************************************************************************************************************/
INT8U SD_ChkCardWP(void)
{
	if (SD_WP_STATUS() == PF9)
		return SD_ERR_WRITE_PROTECT;			/* ��д���� */
	else
		return SD_NO_ERR;						/* ��δд���� */
}
