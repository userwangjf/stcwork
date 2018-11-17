/*******************************************************************************************************
** Descriptions:		sd ������������: SD�������� �û�API����
********************************************************************************************************/
#include "sddriver.h"

extern bool	SanDisk;

/* SD����Ϣ�ṹ����� the information structure variable of SD Card */
sd_struct sds;

/* ��ʱʱ�䵥λ��(��λ:0.000000001ns) timeout unit table */
const INT32U time_unit[8] = {1000000000,100000000,10000000,1000000,100000,10000,1000,100};

/* ��ʱʱ��� timeout value table */
const INT8U time_value[16] = {0,10,12,13,15,20,25,30,35,40,45,50,55,60,70,80};

/* ��ʱʱ�������� timeout factor table */
const INT8U r2w_fator[6] = {1,2,4,8,16,32};

/********************************************************************************************

�û�API����:  ��ʼ��,��,д,�� SD��  User API Function: Initialize,read,write,erase SD Card

********************************************************************************************/


/*******************************************************************************************************************
** ��������: INT8U SD_Initialize()				Name:	  INT8U SD_Initialize()
** ��������: ��ʼ��SD��							Function: initialize sd card
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: 0:   ��ȷ    >0:   ������		  	Output:	  0:  right		>0:  error code
********************************************************************************************************************/
INT8U SD_Initialize(void)
{
	INT8U recbuf[4],ret;

	//test
	DelayX(100);
	
	SD_HardWareInit();					    		/* ��ʼ����дSD����Ӳ������ Initialize the hardware that access SD Card */

	SPI_Clk400k();
	
	SD_StartSD();									/* ��OS������ʿ��ź��� request semaphore acessed SD/MMC to OS */
	
    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
//    	printf("card is not inserted entirely!\n");
    	return SD_ERR_NO_CARD;   					/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	SPI_CS_Assert();								/* 1. ��CSΪ�� assert CS */

	//test
	DelayX(30);
//	SD_SPIDelay(30);								/* 2. ������ʱ 74 clock delay more than 74 clock */
	SPI_CS_Deassert();								/* 3. ��CSΪ�� dessert CS */

	//test
	DelayX(8);
//	SD_SPIDelay(8);									/* 4. ��ʱ2(8 clock) delay 2(8 clock) */
	SPI_CS_Assert();

	ret = SD_ResetSD();								/* 5. ����CMDO���λSD�� send CMD0 command to reset sd card */

//	printf("SD Reset ret=0x%x\n",ret);

    if (ret != SD_NO_ERR)
        return ret;

 	ret = SD_ActiveInit();							/* 6. ��������ʼ������. active card initialize process */

//	printf("SD ActiveInit ret=0x%x\n",ret);

 	if (ret != SD_NO_ERR)
 		return ret;

   	ret = SD_ReadOCR(4, recbuf);  					/* 7. ��OCR�Ĵ���,��ѯ��֧�ֵĵ�ѹֵ read OCR register,get the supported voltage */

//	printf("SD Read OCR ret=0x%x\n",ret);
//	printf("OCR[]=%x %x %x %x\n",recbuf[0],recbuf[1],recbuf[2],recbuf[3]);

	if (ret != SD_NO_ERR)
	    return ret;
	
	if ((recbuf[1] & MSK_OCR_33) != MSK_OCR_33)
	{
		printf("do not support 3.3V\n");
	    return SD_ERR_VOL_NOTSUSP;					/* ��֧��3.3V,���ش�����  not support 3.3V,return error code */
	}

    SPI_ClkToMax();									/* 8. ����SPIʱ�ӵ����ֵ set SPI clock to maximum */

	#if SD_CRC_EN
	    ret = SD_EnableCRC(1);						/* ʹ��CRCУ�� enable CRC check */

//		printf("SD Enable CRC ret=0x%x\n",ret);

		if (ret != SD_NO_ERR)
		  	return ret;
	#endif

    ret = SD_SetBlockLen(SD_BLOCKSIZE);				/* 9. ���ÿ�ĳ���: 512Bytes Set the block length: 512Bytes */

//	printf("SD SetBlockLen ret=0x%x\n",ret);

	if (ret != SD_NO_ERR)
	    return ret;

	ret=SD_GetCardInfo();							/* 10. ��CSD�Ĵ���,��ȡSD����Ϣ read CSD register, get the information of SD card */
	
	SD_EndSD();										/* �黹���ʿ��ź��� return semaphore acessed SD/MMC to OS */
	
	SPI_ClkToMax();
	
	return ret;
}

/********************************************************************************************************************
** ��������: INT8U SD_ReadBlock()					Name:	  INT8U SD_ReadBlock()
** ��������: ��SD/MMC���ж�һ����					Function: read a single block from SD/MMC card
** �䡡  ��: INT32U blockaddr: ���ַ				Input:    INT32U blockaddr: address of block
			 INT8U *recbuf   : ���ջ�����,����512Bytes	 	  INT8U *recbuf   : the buffer of receive,length is 512Bytes
** ��    ��: 0:   �ɹ�    >0:  ������				Output:	  0:  right			>0:  error code
*********************************************************************************************************************/
INT8U SD_ReadBlock(INT32U blockaddr, INT8U *recbuf)
{
	INT8U ret;

    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
    	printf("card is not inserted entirely\n");
    	return SD_ERR_NO_CARD;   					/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	if (blockaddr > sds.block_num)
	{
		SD_EndSD();
		printf("SD ReadBlock\nblockaddr=0x%x sds.block_num=0x%x\n",blockaddr,sds.block_num);
		printf("operate over the card range\n");
		return SD_ERR_OVER_CARDRANGE;				/* ����������������Χ operate over the card range */
	}

 	ret = SD_ReadSingleBlock(blockaddr);			/* ���������� read single blocks command */
 	if (ret != SD_NO_ERR)
 	{
 		printf("SD Read Single Block Address Error!\n");
 		SD_EndSD();
 		return ret;
 	}

  	ret = SD_ReadBlockData(SD_BLOCKSIZE, recbuf);	/* �������� read data from sd card */
	SD_EndSD();										/* �黹���ʿ��ź��� return semaphore acessed SD/MMC to OS */

	return ret;
}

/********************************************************************************************************************
** ��������: INT8U SD_ReadMultiBlock()				Name:	  INT8U SD_ReadMultiBlock()
** ��������: ��SD/MMC���ж������					Function: read multi blocks from SD/MMC card
** �䡡  ��: INT32U blockaddr: ���ַ				Input:	  INT32U blockaddr: address of block
			 INT32U blocknum : ������						  INT32U blocknum : the numbers of block
			 INT8U *recbuf   : ���ջ�����,ÿ��512�ֽ�		  INT8U *recbuf   : the buffer of receive,each block length is 512Bytes
** ��    ��: 0:   �ɹ�    >0:  ������				Output:	  0:  right			>0:  error code
*********************************************************************************************************************/
#if SD_ReadMultiBlock_EN
INT8U SD_ReadMultiBlock(INT32U blockaddr, INT32U blocknum, INT8U *recbuf)
{
    INT32U i;
    INT8U ret;

//	printf("SD ReadMultiBlock Start!\n");
	
    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
    	printf("card is not inserted entirely\n");
    	return SD_ERR_NO_CARD;   					/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	if ((blockaddr + blocknum) > sds.block_num)
	{
		SD_EndSD(); 
		printf("blockaddr=0x%x\nblocknum=0x%x sds.block_num=0x%x\n",blockaddr,blocknum,sds.block_num);
		printf("operate over the card range\n");
		return SD_ERR_OVER_CARDRANGE;				/* ����������������Χ operate over the card range */
	}

	ret = SD_ReadMultipleBlock(blockaddr);			/* ��������� read multiple blocks command */
	if (ret != SD_NO_ERR)
	{
		SD_EndSD();									/* �黹���ʿ��ź��� return semaphore acessed SD/MMC to OS */
		return ret;
    }

    for (i = 0; i < blocknum; i++)
    {												/* �������� read data from SD/MMC card */
    	ret = SD_ReadBlockData(SD_BLOCKSIZE, recbuf);
    	if (ret == SD_NO_ERR)
    	{
       		recbuf = recbuf + SD_BLOCKSIZE;
      	}	
    	else
    	{
    		SD_EndSD();
    		printf("read data error\n");
    		return ret;
    	}
    }

 	ret = SD_StopTransmission();				    /* �������ݴ��� stop transmission operation */

 	SD_EndSD();
 	
//	printf("SD ReadMultiBlock Done!\n");
	return ret;
}
/********************************************************************************************************************
** ��������: INT8U SD_ReadMultiBlockSanDisk()				Name:	  INT8U SD_ReadMultiBlockSanDisk()
** ��������: ��SD/MMC���ж������					Function: read multi blocks from SD/MMC card
** �䡡  ��: INT32U blockaddr: ���ַ				Input:	  INT32U blockaddr: address of block
			 INT32U blocknum : ������						  INT32U blocknum : the numbers of block
			 INT8U *recbuf   : ���ջ�����,ÿ��512�ֽ�		  INT8U *recbuf   : the buffer of receive,each block length is 512Bytes
** ��    ��: 0:   �ɹ�    >0:  ������				Output:	  0:  right			>0:  error code
*********************************************************************************************************************/
INT8U SD_ReadMultiBlockSanDisk(INT32U blockaddr, INT32U blocknum, INT8U *recbuf)
{
    INT32U i;
    INT8U ret;

//	printf("SanDisk ReadMultiBlock\n");
	
    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
    	printf("card is not inserted entirely\n");
    	return SD_ERR_NO_CARD;   					/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	if ((blockaddr + blocknum) > sds.block_num)
	{
		SD_EndSD(); 
		printf("blocknum=0x%x sds.block_num=0x%x\n",blocknum,sds.block_num);
		printf("operate over the card range\n");
		return SD_ERR_OVER_CARDRANGE;				/* ����������������Χ operate over the card range */
	}

    for (i = 0; i < blocknum; i++)
    {												/* �������� read data from SD/MMC card */
		ret=SD_ReadBlock(blockaddr,recbuf);
    	if (ret == SD_NO_ERR)
    	{
    		blockaddr++;
       		recbuf = recbuf + SD_BLOCKSIZE;
    	}
    	else
    	{
    		SD_EndSD();
    		printf("read data error\n");
    		return ret;
    	}
    }

// 	ret = SD_StopTransmission();				    /* �������ݴ��� stop transmission operation */

 	SD_EndSD();
 	
//	printf("SD ReadMultiBlock Done!\n");
	return ret;
}
#endif

/********************************************************************************************************************
** ��������: INT8U SD_WriteBlock()					Name:	  INT8U SD_WriteBlock()
** ��������: ��SD/MMC����д��һ����					Function: write a block to SD/MMC card
** �䡡  ��: INT32U blockaddr: ���ַ				Input: 	  INT32U blockaddr: address of block
			 INT8U *sendbuf  : ���ͻ�����,����512Bytes	  	  INT8U *sendbuf  : the buffer of send,length is 512Bytes
** ��    ��: 0:   �ɹ�    >0:  ������				Output:	  0:  right			>0:  error code
*********************************************************************************************************************/
INT8U SD_WriteBlock(INT32U blockaddr, INT8U *sendbuf)
{
	INT8U ret,tmp[2];

    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
    	printf("card is not inserted entirely\n");
    	return SD_ERR_NO_CARD;   								/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	if (blockaddr > sds.block_num)
	{
		SD_EndSD();
		printf("operate over the card range\n");
		return SD_ERR_OVER_CARDRANGE;							/* ����������������Χ operate over the card range */
	}

	if (SD_ChkCardWP() != 0)
	{
		SD_EndSD();
    	printf("\ncard write protect\n");		
		return SD_ERR_WRITE_PROTECT;							/* ����д���� card write protect*/
	}

	ret = SD_WriteSingleBlock(blockaddr);						/* д�������� write single block */
	if (ret != SD_NO_ERR)
	{
		SD_EndSD();
		printf("SD Write Single Block Address Error!\n");
		return ret;
	}

	ret = SD_WriteBlockData(0, SD_BLOCKSIZE, sendbuf);			/* д������ write data */
 	if (ret == SD_NO_ERR)										/* ��Card Status�Ĵ���, ���д���Ƿ�ɹ� */
 	{															/* read Card Status register to check write wheather sucessfully */
 		ret = SD_ReadCard_Status(2, tmp);
 		if (ret != SD_NO_ERR)
 		{
 			SD_EndSD();
 			printf("read register fail\n");
 			return ret;											/* ���Ĵ���ʧ�� read register fail */
		}

 		if((tmp[0] != 0) || (tmp[1] != 0))
 		{
 			SD_EndSD();
			ret = SD_ERR_WRITE_BLK; 			     			/* ��Ӧָʾдʧ�� response indicate write fail */
 		}
 	}

    SD_EndSD();
 	return ret;													/* ����д���� return the result of writing */
}

/**********************************************************************************************************************
** ��������: INT8U SD_WriteMultiBlock()				Name:	  INT8U SD_WriteMultiBlock()
** ��������: ��SD/MMC����д������					Function: write multi blocks to SD/MMC card
** �䡡  ��: INT32U blockaddr: ���ַ				Input:	  INT32U blockaddr: address of block
			 INT32U blocknum : ������						  INT32U blocknum : the numbers of block
			 INT8U *sendbuf  : ���ͻ�����ÿ��512�ֽ�    	  INT8U *sendbuf  : the send buffer,each block length is 512Bytes
** ��    ��: 0:   �ɹ�    >0:  ������				Output:	  0:  right			>0:  error code
***********************************************************************************************************************/
#if SD_WriteMultiBlock_EN
INT8U SD_WriteMultiBlock(INT32U blockaddr, INT32U blocknum, INT8U *sendbuf)
{
	INT32U i;
	INT8U ret,tmp[2];

//	printf("SD WriteMultiBlock Start!\n");
//	printf("\n\n\n\nblockaddr=0x%x SD WriteMultiBlock blocknum=%d\n",blockaddr,blocknum);

    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
    	printf("card is not inserted entirely\n");
    	return SD_ERR_NO_CARD;   								/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	if ((blockaddr + blocknum) > sds.block_num)
	{
		SD_EndSD();
		printf("operate over the card range\n");
		return SD_ERR_OVER_CARDRANGE;							/* ����������������Χ operate over the card range */
	}

	if (SD_ChkCardWP() != 0)
	{
		SD_EndSD();
    	printf("\ncard write protect\n");		
		return SD_ERR_WRITE_PROTECT;							/* ����д���� card write protect*/
	}

	ret = SD_WriteMultipleBlock(blockaddr);						/* д������� write multiple blocks command */
	if (ret != SD_NO_ERR)
	{
		printf("SD Write MultipleBlock Address Error!\n");
		SD_EndSD();
		return ret;
	}

	
    for (i = 0; i < blocknum; i++)
    {
 		ret = SD_WriteBlockData(1, SD_BLOCKSIZE, sendbuf);		/* д������ write data */
 		if (ret == SD_NO_ERR)
 			sendbuf = sendbuf + SD_BLOCKSIZE;
 		else
 		{														/* дʧ�� write fail */
			SD_StopTransmission();								/* ֹͣ���ݴ��� stop data transmission */
			SD_WaitBusy(SD_WAIT_WRITE);							/* �ȴ� waiting */
			SD_EndSD();
			return ret;
		}
	}

    SD_StopMultiToken();										/* ��������ֹͣ���� send data stop token */

    ret = SD_WaitBusy(SD_WAIT_WRITE);							/* �ȴ�д������ wait for finishing writing */
//    if (ret != SD_NO_ERR)
//    {
//    	SD_EndSD();
//    	printf("wait for finishing writing\n\n");
//    	return SD_ERR_TIMEOUT_WRITE;
//    }
//
//    if (sds.card_type == CARDTYPE_SD)
//    {
//   		ret = SD_GetNumWRBlcoks(&i);							/* ����ȷд��Ŀ��� read the blocks that be written correctly */
//   		if (ret != SD_NO_ERR)
//   		{
//   			SD_EndSD();
//   			printf("read the blocks that be written correctly\n\n");
//   		  	return ret;
//   		}
//   		if(i != blocknum)
//   		{
//   			printf("the blocks that be written correctly is error\n\n");
//			ret =  SD_ERR_WRITE_BLKNUMS;						/* ��ȷд��������� the blocks that be written correctly is error */
//		}
//   	}
//   	else
//   	{
//   	 	ret = SD_ReadCard_Status(2, tmp);
// 		if (ret != SD_NO_ERR)
// 		{
// 			SD_EndSD();
// 			printf("read register fail\n");
// 			return ret;											/* ���Ĵ���ʧ�� read register fail */
//		}
// 		if((tmp[0] != 0) || (tmp[1] != 0))
// 		{
// 			printf("response indicate write fail\n");
//			ret = SD_ERR_WRITE_BLK; 			     			/* ��Ӧָʾдʧ�� response indicate write fail */
//		}
//   	}
//
   	SD_EndSD();
   	
//	printf("SD WriteMultiBlock Done!\n");
	return ret;													/* ����д��ɹ� return write sucessfully */
}
#endif

/*********************************************************************************************************************
** ��������: INT8U SD_EraseBlock()					Name:	  INT8U SD_EraseBlock()
** ��������: ����SD/MMC���еĿ�						Function: Erase the block of SD/MMC card
** �䡡  ��: INT32U startaddr: ��ʼ��ַ				Input:    INT32U startaddr: start address
			 INT32U endaddr  : ��ֹ��ַ						  INT32U endaddr  : end address
** ��    ��: 0:   �ɹ�    >0:  ������				Output:	  0:  right			>0:  error code
** ע    ��: startaddr �� blocknum ����Ϊ sds.erase_unit ��������, ��Ϊ�еĿ�ֻ���� sds.erase_unit Ϊ��λ���в���
*********************************************************************************************************************/
#if SD_EraseBlock_EN
INT8U SD_EraseBlock(INT32U startaddr, INT32U blocknum)
{
	INT32 tmp;
	INT8U ret;

    if (SD_ChkCard() != 0)
    {
    	SD_EndSD();
    	printf("card is not inserted entirely\n");
    	return SD_ERR_NO_CARD;   								/* ��û��ȫ���뿨�� card is not inserted entirely */
	}

	if ((startaddr + blocknum) > sds.block_num)
	{
		SD_EndSD();
		printf("operate over the card range\n");
		return SD_ERR_OVER_CARDRANGE;							/* ����������������Χ operate over the card range */
	}

	if (SD_ChkCardWP() != 0)
	{
		SD_EndSD();
    	printf("\ncard write protect\n");		
		return SD_ERR_WRITE_PROTECT;							/* ����д���� card write protect*/
	}

	tmp = blocknum*512/sds.erase_unit;
	while(tmp >= 0)												/* ÿ�β������� once erase is sector size */
	{
		ret = SD_EraseStartBlock(startaddr);					/* ѡ����ʼ���ַ select start address */
		if (ret != SD_NO_ERR)
		{
			printf("tmp=%d\nSD Erase Start Block Address Error!\n",tmp);
			SD_EndSD();
			return ret;
		}

		ret = SD_EraseEndBlock(startaddr + sds.erase_unit - 1);		/* ѡ����ֹ���ַ select end address */
		if (ret != SD_NO_ERR)
		{
			printf("tmp=%d\nSD Erase End Block Address Error!\n",tmp);
			SD_EndSD();
			return ret;
		}

		ret = SD_EraseSelectedBlock();							/* ������ѡ�Ŀ� erase blocks selected */
		if (ret != SD_NO_ERR)
		{
			printf("tmp=%d\nSD Erase Selected Block Error!\n",tmp);
			SD_EndSD();
			return ret;
		}

		startaddr += sds.erase_unit;								/* ��ʼ��ַ���� */
//		blocknum  -= sds.erase_unit;
		tmp--;
//		tmp = blocknum - sds.erase_unit;
	}

	if (blocknum*512%sds.erase_unit > 0)											/* ��������once_erase�� */
	{															/* erase blocks that numbers is not enough once_erase */
		ret = SD_EraseStartBlock(startaddr);
		if (ret != SD_NO_ERR)
		{
			printf("blocknum=%d\nSD Erase Start Block Error!\n",blocknum);
			SD_EndSD();
			return ret;
		}

		ret = SD_EraseEndBlock(startaddr);
		if (ret != SD_NO_ERR)
		{
			printf("blocknum=%d\nSD Erase End Block Error!\n",blocknum);
			SD_EndSD();
			return ret;
		}

		ret = SD_EraseSelectedBlock();
		if (ret != SD_NO_ERR)
		{
			printf("blocknum=%d\nSD Erase Selected Block Error!\n",blocknum);
			SD_EndSD();
			return ret;
		}
	}

	SD_EndSD();
	return SD_NO_ERR;											/* ���ز����ɹ� return erase sucessfully */
}
#endif

/*******************************************************************************************************************
** ��������: INT8U SD_GetCardInfo()				Name:	  INT8U SD_GetCardInfo()
** ��������: ���SD������Ϣ						Function: get the information of SD card
** �䡡  ��: INT8U cardtype: ������				Input:    INT8U cardtype: card type
** �� �� ��: 0:   ��ȷ    >0:   ������		  	Output:	  0:  right		>0:  error code
*******************************************************************************************************************/
INT8U SD_GetCardInfo()
{
	INT32U tmp;
	INT8U cidbuf[16],csdbuf[16],ret,i;
	
	ret = SD_ReadCID(16,cidbuf);
	
//	printf("SD Read CID ret=%d\n",ret);
	
	if (ret != SD_NO_ERR)
		return ret;
	
	if(cidbuf[0]==0x03)
		SanDisk	=true;
		
	ret = SD_ReadCSD(16,csdbuf);	 								    		/* ��CSD�Ĵ���    read CSD register */

//	printf("SD Read CSD ret=%d\n",ret);
	
	if (ret != SD_NO_ERR)
		return ret;
	
	SD_CalTimeout(csdbuf);														/* ���㳬ʱʱ��ֵ calculate timeout value */

	/* ��������󳤶�  */														/* calculate the size of a sector */
	sds.block_len = 1 << (csdbuf[READ_BL_LEN_POS] & READ_BL_LEN_MSK);  			/* (2 ^ READ_BL_LEN) */

	/* ���㿨�п�ĸ��� */														/* calculate the sector numbers of the SD Card */
	sds.block_num = ((csdbuf[C_SIZE_POS1] & C_SIZE_MSK1) << 10) +
	      			 (csdbuf[C_SIZE_POS2] << 2) +
	 	 			((csdbuf[C_SIZE_POS3] & C_SIZE_MSK3) >> 6) + 1;				/* (C_SIZE + 1)*/

	tmp = ((csdbuf[C_SIZE_MULT_POS1] & C_SIZE_MULT_MSK1) << 1) +
	      ((csdbuf[C_SIZE_MULT_POS2] & C_SIZE_MULT_MSK2) >> 7) + 2;				/* (C_SIZE_MULT + 2) */

    /* ��ÿ��п������ */														/* get the block numbers in card */
	sds.block_num = sds.block_num * (1 << tmp);									/* (C_SIZE + 1) * 2 ^ (C_SIZE_MULT + 2) */

	/* ����������С */															/*calculate the size of sector */
	sds.erase_unit = ((csdbuf[SECTOR_SIZE_POS1] & SECTOR_SIZE_MSK1) << 1) +
	                 ((csdbuf[SECTOR_SIZE_POS2] & SECTOR_SIZE_MSK2) >> 7) + 1; /* SD (SECTOR_SIZE + 1) */

	#define GetCardCISD

	#ifdef GetCardCISD
		printf("CID[]=");
		for(i=0;i<16;i++)
			printf("%x ",cidbuf[i]);
		printf("\n");	
		printf("CSD[]=");
		for(i=0;i<16;i++)
			printf("%x ",csdbuf[i]);
		printf("\n");
	#endif

	#define GetCardInfo
	
	#ifdef GetCardInfo
		printf("block len=%d\n",sds.block_len);
		printf("card size mult=%d\n",1<<tmp);
		printf("block num=%d\n",sds.block_num);
		printf("memory capacity=%d\n",sds.block_num*sds.block_len);
		printf("card erase unit=%d\n\n\n",sds.erase_unit);
	#endif
	
	if(sds.block_len==1024)
		sds.block_num=sds.block_num*2;
	
	return SD_NO_ERR;															/* ����ִ�гɹ� return perform sucessfully */
}

/*******************************************************************************************************************
** ��������: INT8U SD_CalTimeout()				Name:	  INT8U SD_CalTimeout()
** ��������: �����/д/����ʱʱ��				Function: get the information of SD card
** �䡡  ��: INT8U cardtype: ������				Input:    INT8U cardtype: card type
			 INT8U *csdbuf : CSD�Ĵ�������		 	      INT8U *csdbuf : CSD register content
** �� �� ��: 0:   ��ȷ    >0:   ������		  	Output:	  0:  right		>0:  error code
*******************************************************************************************************************/
void SD_CalTimeout(INT8U *csdbuf)
{
	INT32U tmp;
	INT8U time_u,time_v,fator;

	sds.timeout_read = READ_TIMEOUT_100MS;								/* Ĭ�϶���ʱΪ100ms */
	sds.timeout_write = WRITE_TIMEOUT_250MS;							/* Ĭ��д��ʱΪ250ms */
	sds.timeout_erase = WRITE_TIMEOUT_250MS;

	time_u = (csdbuf[TAAC_POS] & TAAC_MSK);								/* ����ʱʱ�䵥λ read timeout unit */
	time_v = (csdbuf[TAAC_POS] & NSAC_MSK) >> 3;						/* ����ʱʱ��ֵ   read timeout value */
	fator = (csdbuf[R2WFACTOR_POS] & R2WFACTOR_MSK) >> 2;				/* д��ʱʱ������ write timeout factor */

	if(time_v == 0)	return;
	if(fator >= 6) return;

	tmp = SPI_CLOCK * time_value[time_v] / 10 / time_unit[time_u];		/* TACC * f (��λ unit: clock) */
	tmp = tmp + csdbuf[NSAC_POS] * 100;									/* TACC * f + NSAC * 100 (��λ unit: clock) */

	/* ����õ��ĳ�ʱֵ the timeout value of being calculated */
	sds.timeout_read = tmp;
	sds.timeout_write = tmp * r2w_fator[fator];							/* (TACC * f + NSAC * 100) * R2WFACTOR (��λ unit:clock)*/

	sds.timeout_read  = sds.timeout_read * 100 / 8;						/* ʵ��ֵΪ����ֵ��100�� */
	sds.timeout_write = sds.timeout_write * 100 / 8;

	if (sds.timeout_read > READ_TIMEOUT_100MS)							/* ȡ����ֵ��Ĭ��ֵ�е���Сֵ */
		sds.timeout_read = READ_TIMEOUT_100MS;

	if (sds.timeout_write > WRITE_TIMEOUT_250MS)
		sds.timeout_write = WRITE_TIMEOUT_250MS;

	sds.timeout_erase = sds.timeout_write;    
}

/*******************************************************************************************************************
** ��������: INT8U SD_ActiveInit()				Name:	  INT8U SD_ActiveInit()
** ��������: �����/д/����ʱʱ��				Function: get the Idle state of SD card
** �䡡  ��: void							 	Input:    void
** �� �� ��: 0:   ��ȷ    >0:   ������		  	Output:	  0:  right		>0:  error code
** ����˵��: ��������ظ����͵�SD����ֱ����ӦR1��Bit0(Idle)λΪ0����ʾSD���ڲ���ʼ��������ɡ�
		     ����Ӧ��IdleλΪ0ʱ��SD������ȫ����SPIģʽ�ˡ���Ȼ�ظ���������CMD1���д������Ƶģ�
		     ������Ϊ�궨��SD_IDLE_WAIT_MAX.
*******************************************************************************************************************/
INT8U SD_ActiveInit(void)
{
	INT8U param[4] = {0,0,0,0},resp[5],ret;
	INT32U i = 0;

	do
	{													/* ����CMD1, ��ѯ����״̬, send CMD1 to poll card status */
		ret = SD_SendCmd(CMD1, param, CMD1_R, resp);
		if (ret != SD_NO_ERR)
			return ret;

		i++;
		
		//test
		DelayX(10);
//		printf("CMD1 resp[0]=0x%x\n",resp[0]);
//		SD_SPIDelay(10);
	}
	while (((resp[0] & MSK_IDLE) == MSK_IDLE) && (i < SD_IDLE_WAIT_MAX)); 		/* �����ӦR1�����λIdleλΪ1,�����ѭ�� */
	
	if (i >= SD_IDLE_WAIT_MAX)
		return SD_ERR_TIMEOUT_WAITIDLE;					/* ��ʱ,���ش��� time out,return error */

    ret = SD_SendCmd(CMD55, param, CMD55_R, resp);

//	printf("SD ActiveInit CMD55 ret=0x%x\n",ret);

	if(ret != SD_NO_ERR)
		return ret;

    ret = SD_SendCmd(ACMD41, param, ACMD41_R, resp);		/* �����ڲ���ʼ������ active card to initialize process internal */

//	printf("SD ActiveInit ACMD41 ret=0x%x\n",ret);

	if (ret != SD_NO_ERR)
		return SD_ERR_UNKNOWN_CARD;
	
	if ((resp[0] & 0xFE) == 0)
	{
	  	sds.card_type = CARDTYPE_SD;						/* ��SD�� the card is SD card */
	  	printf("the card is SD card\n");
	}
	else
	{
		sds.card_type = CARDTYPE_MMC;						/* ��MMC�� the card is MMC card */
		printf("the card is MMC card\n");
	}

	return SD_NO_ERR;
}

/*******************************************************************************************************************
** ��������: void SD_StartSD()					Name:	  INT8U SD_StartSD()
** ��������: �����ϵͳ�������SD����Ȩ��		Function: request the right of operating sd to OS
** �䡡  ��: ��									Input:	  NULL
** ��	 ��: ��									return:	  NULL
********************************************************************************************************************/
void SD_StartSD(void)
{
	#if SD_UCOSII_EN
		INT8U ret;

		OSSemPend(pSemSD, 0, &ret);					/* �ȴ����ʿ��ź������� wait for semaphore that accessed Card */
	#endif
}

/*******************************************************************************************************************
** ��������: void SD_EndSD()					Name:	  INT8U SD_EndSD()
** ��������: ����SD����Ȩ�޹黹����ϵͳ			Function: return the right of operating sd to OS
** �䡡  ��: ��									Input:	  NULL
** ��	 ��: ��									return:	  NULL
********************************************************************************************************************/
void SD_EndSD(void)
{
	#if SD_UCOSII_EN
		OSSemPost(pSemSD);							/* �����ʿ��ź�����������ϵͳ return the semaphore accessing Card to OS */
	#endif
}