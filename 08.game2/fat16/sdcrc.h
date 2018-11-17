/******************************************************************************************************
** Descriptions:		sd �����������: SD����ع��ߺ��� ---- CRCУ��ͷ�ļ�
********************************************************************************************************/

#ifndef 	__sdcrc_h
#define 	__sdcrc_h

#include "sdconfig.h"
#include "sddriver.h"
#include "sdhal.h"
#include "sdcmd.h"

extern INT16U SD_GetCRC16(INT8U *pSource,INT16U len);	//�õ�len���ֽڵ�CRC16

extern INT8U SD_GetCmdByte6(INT8U cmd,INT8U *param);	//�õ�SD����ĵ�6���ֽ�: CRC7 + ֹͣλ1

extern INT8U SD_GetCRC7(INT8U *pSource,INT16U len);		//�õ�len���ֽڵ�CRC7

#endif
