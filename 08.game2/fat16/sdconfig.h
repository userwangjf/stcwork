/******************************************************************************************************
** Descriptions:		sd �����������: �����ļ�
********************************************************************************************************/
#ifndef __SDCONFIG_H__
#define __SDCONFIG_H__

#include <cdefBF533.h>
#include <defBF533.h>

typedef unsigned char  INT8U;                   /* �޷���8λ���ͱ���                        */
typedef signed   char  INT8;                    /* �з���8λ���ͱ���                        */
typedef unsigned short INT16U;                  /* �޷���16λ���ͱ���                       */
typedef signed   short INT16;                   /* �з���16λ���ͱ���                       */
typedef unsigned int   INT32U;                  /* �޷���32λ���ͱ���                       */
typedef signed   int   INT32;                   /* �з���32λ���ͱ���                       */
typedef float          FP32;                    /* �����ȸ�������32λ���ȣ�                 */
typedef double         FP64;                    /* ˫���ȸ�������64λ���ȣ�                 */

#define SPI_CLOCK			400000		/* ����ͨ��ʱ,SPIʱ��Ƶ�� frequency (Hz) */
#define SD_BLOCKSIZE		512			//SD����ĳ���
#define SD_BLOCKSIZE_NBITS	9

/*�Ƿ���ϵͳ*/
#define SD_UCOSII_EN			0			/* �Ƿ���UCOS-II�����б�ģ�� */

/* �������ݴ���ʱ�Ƿ�ʹ��CRC */
#define SD_CRC_EN		   		0

/* ���溯��������,����û�����Ҫ,����Ϊ 0 �ü�ָ������ */
#define SD_ReadMultiBlock_EN    1			/* �Ƿ�ʹ�ܶ���麯�� */
#define SD_WriteMultiBlock_EN   1			/* �Ƿ�ʹ��д��麯�� */
#define SD_EraseBlock_EN		1			/* �Ƿ�ʹ�ܲ������� */
#define SD_ProgramCSD_EN   		0			/* �Ƿ�ʹ��дCSD�Ĵ������� */
#define SD_ReadCID_EN	   		1			/* �Ƿ�ʹ�ܶ�CID�Ĵ������� */
#define	SD_ReadSD_Status_EN		0			/* �Ƿ�ʹ�ܶ�SD_Status�Ĵ������� */
#define	SD_ReadSCR_EN			0			/* �Ƿ�ʹ�ܶ�SCR�Ĵ������� */

/* ����ȫ���뿨��������� */	//SD_INSERT_STATUS==1	Insert			SD_WP_STATUS==1	Unlock
#define  SD_INSERT_STATUS()  	(*pFIO_FLAG_D & PF10)			/* ��ȡ INSERT �ڵ�״̬ */

/* ��д����������� */
#define  SD_WP_STATUS()  		(*pFIO_FLAG_D & PF9)			/* ��ȡ WP �ڵ�״̬ */

#endif
