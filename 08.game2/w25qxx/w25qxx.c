
#include "bsp/config.h"
#include "w25qxx/w25qxx.h"
#include "w25qxx/w25qxxConfig.h"


w25qxx_t	w25qxx;

void w25qxx_Delay(u8 delay) {
	for(; delay > 0; delay--);
}

//SPI收发一个字节
u8 w25qxx_Spi(u8 dat) {
	u8 ret;
	u8 i;
	ret = 0;

	for(i = 0; i < 8; i++) {
		ret <<= 1;

		if(dat & 0x80)
			w25qxx_DI_SET;
		else
			w25qxx_DI_CLR;

		w25qxx_CLK_SET;

		//
		if(w25qxx_DO_GET)
			ret |= 0x01;
		else
			ret &= 0xfe;

		w25qxx_CLK_CLR;
		dat <<= 1;
	}

	return ret;
}

//
u32 w25qxx_ReadID(void) {
	u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
	w25qxx_CS_CLR;
	w25qxx_Spi(0x9F);
	Temp0 = w25qxx_Spi(W25Q_DUMMY_BYTE);
	Temp1 = w25qxx_Spi(W25Q_DUMMY_BYTE);
	Temp2 = w25qxx_Spi(W25Q_DUMMY_BYTE);
	w25qxx_CS_SET;
	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
	return Temp;
}

//
bool w25qxx_Init(void) {
	u32	id;
	u8 i;

	for(i = 0; i < 10; i++) {
		id = w25qxx_ReadID();

		if((id & 0x00ffff00) == 0x00ef4000)
			break;
	}

	SHELL_TX("\r\n");
	SHELL_TX(hex2str(id));

	if(i >= 10)
		return 0;

	switch(id & 0x0000FFFF) {
	case 0x401A:	// 	w25q512
		w25qxx.ID = W25Q512;
		w25qxx.BlockCount = 1024;
		break;

	case 0x4019:	// 	w25q256
		w25qxx.ID = W25Q256;
		w25qxx.BlockCount = 512;
		break;

	case 0x4018:	// 	w25q128
		w25qxx.ID = W25Q128;
		w25qxx.BlockCount = 256;
		break;

	case 0x4017:	//	w25q64
		w25qxx.ID = W25Q64;
		w25qxx.BlockCount = 128;
		break;

	case 0x4016:	//	w25q32
		w25qxx.ID = W25Q32;
		w25qxx.BlockCount = 64;
		break;

	case 0x4015:	//	w25q16
		w25qxx.ID = W25Q16;
		w25qxx.BlockCount = 32;
		break;

	case 0x4014:	//	w25q80
		w25qxx.ID = W25Q80;
		w25qxx.BlockCount = 16;
		break;

	case 0x4013:	//	w25q40
		w25qxx.ID = W25Q40;
		w25qxx.BlockCount = 8;
		break;

	case 0x4012:	//	w25q20
		w25qxx.ID = W25Q20;
		w25qxx.BlockCount = 4;
		break;

	case 0x4011:	//	w25q10
		w25qxx.ID = W25Q10;
		w25qxx.BlockCount = 2;
		break;

	default:
		return 0;
	}

	w25qxx.PageSize = 256;
	w25qxx.SectorSize = 0x1000;
	w25qxx.SectorCount = w25qxx.BlockCount * 16;
	w25qxx.PageCount = (w25qxx.SectorCount * w25qxx.SectorSize) / w25qxx.PageSize;
	w25qxx.BlockSize = w25qxx.SectorSize * 16;
	w25qxx.CapacityInKiloByte = (w25qxx.SectorCount * w25qxx.SectorSize) / 1024;
	w25qxx_ReadUniqID();
	w25qxx_ReadStatusRegister(1);
	w25qxx_ReadStatusRegister(2);
	w25qxx_ReadStatusRegister(3);
	return 1;
}


void w25qxx_ReadUniqID(void) {
	u8 i;
	w25qxx_CS_CLR;
	w25qxx_Spi(0x4B);

	for(i = 0; i < 4; i++)
		w25qxx_Spi(W25Q_DUMMY_BYTE);

	for(i = 0; i < 8; i++)
		w25qxx.UniqID[i] = w25qxx_Spi(W25Q_DUMMY_BYTE);

	w25qxx_CS_SET;
}

void w25qxx_WaitBusy(void) {
	w25qxx_Delay(1);
	w25qxx_CS_CLR;
	w25qxx_Spi(0x05);

	do {
		w25qxx.StatusRegister1 = w25qxx_Spi(W25Q_DUMMY_BYTE);
		w25qxx_Delay(1);
	} while((w25qxx.StatusRegister1 & 0x01) == 0x01);

	w25qxx_CS_SET;
}

u8 w25qxx_ReadStatusRegister(u8	SelectStatusRegister_1_2_3) {
	u8	status = 0;
	w25qxx_CS_CLR;

	if(SelectStatusRegister_1_2_3 == 1) {
		w25qxx_Spi(0x05);
		status = w25qxx_Spi(W25Q_DUMMY_BYTE);
		w25qxx.StatusRegister1 = status;
	} else if(SelectStatusRegister_1_2_3 == 2) {
		w25qxx_Spi(0x35);
		status = w25qxx_Spi(W25Q_DUMMY_BYTE);
		w25qxx.StatusRegister2 = status;
	} else {
		w25qxx_Spi(0x15);
		status = w25qxx_Spi(W25Q_DUMMY_BYTE);
		w25qxx.StatusRegister3 = status;
	}

	w25qxx_CS_SET;
	return status;
}

void w25qxx_WaitForWriteEnd(void) {
	w25qxx_Delay(1);
	w25qxx_CS_CLR;
	w25qxx_Spi(0x05);

	do {
		w25qxx.StatusRegister1 = w25qxx_Spi(W25Q_DUMMY_BYTE);
		w25qxx_Delay(1);
	} while((w25qxx.StatusRegister1 & 0x01) == 0x01);

	w25qxx_CS_SET;
}

void w25qxx_WriteEnable(void) {
	w25qxx_CS_CLR;
	w25qxx_Spi(0x06);
	w25qxx_CS_SET;
	w25qxx_Delay(1);
}

void w25qxx_WriteDisable(void) {
	w25qxx_CS_CLR;
	w25qxx_Spi(0x04);
	w25qxx_CS_SET;
	w25qxx_Delay(1);
}

void w25qxx_EraseChip(void) {
	w25qxx_WriteEnable();
	w25qxx_CS_CLR;
	w25qxx_Spi(0xC7);
	w25qxx_CS_SET;
	w25qxx_WaitForWriteEnd();
	w25qxx_Delay(10);
}

void w25qxx_EraseSector(u32 SectorAddr) {
	w25qxx_WaitForWriteEnd();
	SectorAddr = SectorAddr * w25qxx.SectorSize;
	w25qxx_WriteEnable();
	w25qxx_CS_CLR;
	w25qxx_Spi(0x20);

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((SectorAddr & 0xFF000000) >> 24);

	w25qxx_Spi((SectorAddr & 0xFF0000) >> 16);
	w25qxx_Spi((SectorAddr & 0xFF00) >> 8);
	w25qxx_Spi(SectorAddr & 0xFF);
	w25qxx_CS_SET;
	w25qxx_WaitForWriteEnd();
	w25qxx_Delay(1);
}

void w25qxx_ReadBytes(u32 ReadAddr, u8* pBuffer, u16 NumByte) {
	u16 i;
	w25qxx_CS_CLR;
	w25qxx_Spi(W25Q_FAST_READ);

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((ReadAddr & 0xFF000000) >> 24);

	w25qxx_Spi((u8)((ReadAddr) >> 16));
	w25qxx_Spi((u8)((ReadAddr) >> 8));
	w25qxx_Spi((u8)ReadAddr);
	w25qxx_Spi(0xFF);//dummy clock

	for(i = 0; i < NumByte; i++) {
		pBuffer[i] = w25qxx_Spi(0xFF);
	}

	w25qxx_CS_SET;
}

void w25qxx_WriteByte(u32 WriteAddr, u8* pBuffer, u16 numByte) {
	u16 i;
	w25qxx_WaitForWriteEnd();
	w25qxx_WriteEnable();
	w25qxx_CS_CLR;
	#if 1
	w25qxx_Spi(0x02);

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((WriteAddr & 0xFF000000) >> 24);

	w25qxx_Spi((WriteAddr & 0xFF0000) >> 16);
	w25qxx_Spi((WriteAddr & 0xFF00) >> 8);
	w25qxx_Spi(WriteAddr & 0xFF);

	if(numByte > 0xff)
		numByte = 0x100;

	for(i = 0; i < numByte; i++) {
		w25qxx_Spi(pBuffer[i]);
	}
	#endif

	w25qxx_CS_SET;
	w25qxx_WaitForWriteEnd();
}


void w25qxx_test() {
	u8 i;
	u8 rdata[8];

	w25qxx_Init();

	w25qxx_ReadBytes(0, rdata, 16);

	SHELL_TX("\r\n");
		for(i = 0; i < 8; i++) {
		SHELL_TX(byte2str(rdata[i]));
		SHELL_TX(",");
	}

	w25qxx_ReadBytes(0x80, rdata, 8);

	SHELL_TX("\r\n");
		for(i = 0; i < 8; i++) {
		SHELL_TX(byte2str(rdata[i]));
		SHELL_TX(",");
	}

#if 0
	for(i=0;i<8;i++)
		rdata[i] = 0x55 +i;

	w25qxx_WriteByte(0,rdata,8);
	for(i=0;i<8;i++)
		rdata[i] = 0;

	w25qxx_ReadBytes(0, rdata, 8);

	SHELL_TX("\r\n");
	for(i = 0; i < 8; i++) {
		SHELL_TX(byte2str(rdata[i]));
		SHELL_TX(",");
	}

	w25qxx_EraseSector(0);
#endif

}


#if 0

//
void w25qxx_EraseBlock(u32 BlockAddr) {
	w25qxx_WaitForWriteEnd();
	BlockAddr = BlockAddr * w25qxx.SectorSize * 16;
	w25qxx_WriteEnable();
	w25qxx_CS_CLR;
	w25qxx_Spi(0xD8);

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((BlockAddr & 0xFF000000) >> 24);

	w25qxx_Spi((BlockAddr & 0xFF0000) >> 16);
	w25qxx_Spi((BlockAddr & 0xFF00) >> 8);
	w25qxx_Spi(BlockAddr & 0xFF);
	w25qxx_CS_SET;
	w25qxx_WaitForWriteEnd();
	w25qxx_Delay(1);
}

//###################################################################################################################
void w25qxx_WriteStatusRegister(u8 SelectStatusRegister_1_2_3, u8 dat) {
	w25qxx_CS_CLR;

	if(SelectStatusRegister_1_2_3 == 1) {
		w25qxx_Spi(0x01);
		w25qxx.StatusRegister1 = dat;
	} else if(SelectStatusRegister_1_2_3 == 2) {
		w25qxx_Spi(0x31);
		w25qxx.StatusRegister2 = dat;
	} else {
		w25qxx_Spi(0x11);
		w25qxx.StatusRegister3 = dat;
	}

	w25qxx_Spi(dat);
	w25qxx_CS_SET;
}
//##########################################################################
//#####################################################

//###################################################################################################################

//###################################################################################################################

//###################################################################################################################
void w25qxx_WritePage(u8 *pBuffer	, u32 Page_Address, u32 NumByteToWrite_up_to_PageSize) {
	if((NumByteToWrite_up_to_PageSize > w25qxx.PageSize) || (NumByteToWrite_up_to_PageSize == 0))
		NumByteToWrite_up_to_PageSize = w25qxx.PageSize;

	w25qxx_WaitForWriteEnd();
	w25qxx_WriteEnable();
	w25qxx_CS_CLR;
	w25qxx_Spi(0x02);
	Page_Address = Page_Address * w25qxx.PageSize;

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((Page_Address & 0xFF000000) >> 24);

	w25qxx_Spi((Page_Address & 0xFF0000) >> 16);
	w25qxx_Spi((Page_Address & 0xFF00) >> 8);
	w25qxx_Spi(Page_Address & 0xFF);
	HAL_SPI_Transmit(&_w25qxx_SPI, pBuffer, NumByteToWrite_up_to_PageSize, 100);
	w25qxx_CS_SET;
	w25qxx_WaitForWriteEnd();
	w25qxx_Delay(1);
}
//###################################################################################################################
void  w25qxx_WriteSector(u8 *pBuffer	, u32 Sector_Address	, u32 NumByteToWrite_up_to_SectorSize) {
	#if (_w25qxx_DEBUG==1)
	printf("w25qxx WriteSector %d begin...\r\n", Sector_Address);
	printf("w25qxx Split to %d Page...\r\n", w25qxx.SectorSize / w25qxx.PageSize);
	w25qxx_Delay(100);
	#endif
	u8	inSectorIndex = 0;

	if((NumByteToWrite_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToWrite_up_to_SectorSize == 0))
		NumByteToWrite_up_to_SectorSize = w25qxx.SectorSize;

	do {
		w25qxx_WritePage(pBuffer, (Sector_Address * w25qxx.SectorSize / w25qxx.PageSize) + inSectorIndex, NumByteToWrite_up_to_SectorSize);

		if(NumByteToWrite_up_to_SectorSize <= w25qxx.PageSize) {
			#if (_w25qxx_DEBUG==1)
			printf("w25qxx WriteSector done\r\n");
			w25qxx_Delay(100);
			#endif
			return;
		}

		inSectorIndex++;
		NumByteToWrite_up_to_SectorSize -= w25qxx.PageSize;
		pBuffer += w25qxx.PageSize;
	} while(NumByteToWrite_up_to_SectorSize > 0);
}
//###################################################################################################################
void 	w25qxx_WriteBlock(u8* pBuffer, u32 Block_Address		, u32	NumByteToWrite_up_to_BlockSize) {
	u8	inBlockIndex = 0;
	#if (_w25qxx_DEBUG==1)
	printf("w25qxx WriteSector %d begin...\r\n", Block_Address);
	printf("w25qxx Split to %d Page...\r\n", w25qxx.BlockSize / w25qxx.PageSize);
	w25qxx_Delay(100);
	#endif

	if((NumByteToWrite_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToWrite_up_to_BlockSize == 0))
		NumByteToWrite_up_to_BlockSize = w25qxx.BlockSize;

	do {
		w25qxx_WritePage(pBuffer, (Block_Address * w25qxx.BlockSize / w25qxx.PageSize) + inBlockIndex, NumByteToWrite_up_to_BlockSize);

		if(NumByteToWrite_up_to_BlockSize <= w25qxx.PageSize) {
			#if (_w25qxx_DEBUG==1)
			printf("w25qxx WriteSector done\r\n");
			w25qxx_Delay(100);
			#endif
			return;
		}

		inBlockIndex++;
		NumByteToWrite_up_to_BlockSize -= w25qxx.PageSize;
		pBuffer += w25qxx.PageSize;
	} while(NumByteToWrite_up_to_BlockSize > 0);
}
//###################################################################################################################
void 	w25qxx_ReadByte(u8 *pBuffer	, u32 Bytes_Address) {
	#if (_w25qxx_DEBUG==1)
	u32	StartTime = HAL_GetTick();
	printf("w25qxx ReadByte at address %d begin...\r\n", Bytes_Address);
	#endif
	HAL_GPIO_WritePin(_w25qxx_CS_GPIO, _w25qxx_CS_PIN, GPIO_PIN_RESET);
	w25qxx_Spi(0x0B);

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((Bytes_Address & 0xFF000000) >> 24);

	w25qxx_Spi((Bytes_Address & 0xFF0000) >> 16);
	w25qxx_Spi((Bytes_Address & 0xFF00) >> 8);
	w25qxx_Spi(Bytes_Address & 0xFF);
	w25qxx_Spi(0);
	*pBuffer = w25qxx_Spi(w25qxx_DUMMY_BYTE);
	HAL_GPIO_WritePin(_w25qxx_CS_GPIO, _w25qxx_CS_PIN, GPIO_PIN_SET);
	#if (_w25qxx_DEBUG==1)
	printf("w25qxx ReadByte 0x%02X done after %d ms\r\n", *pBuffer, HAL_GetTick() - StartTime);
	#endif
}
//###################################################################################################################


//###################################################################################################################
void 	w25qxx_ReadPage(u8 *pBuffer	, u32 Page_Address		, u32 NumByteToRead_up_to_PageSize) {
	if((NumByteToRead_up_to_PageSize > w25qxx.PageSize) || (NumByteToRead_up_to_PageSize == 0))
		NumByteToRead_up_to_PageSize = w25qxx.PageSize;

	#if (_w25qxx_DEBUG==1)
	printf("w25qxx ReadPage %d begin...\r\n", Page_Address);
	w25qxx_Delay(100);
	u32	StartTime = HAL_GetTick();
	#endif
	Page_Address = Page_Address * w25qxx.PageSize;
	HAL_GPIO_WritePin(_w25qxx_CS_GPIO, _w25qxx_CS_PIN, GPIO_PIN_RESET);
	w25qxx_Spi(0x0B);

	if(w25qxx.ID >= W25Q256)
		w25qxx_Spi((Page_Address & 0xFF000000) >> 24);

	w25qxx_Spi((Page_Address & 0xFF0000) >> 16);
	w25qxx_Spi((Page_Address & 0xFF00) >> 8);
	w25qxx_Spi(Page_Address & 0xFF);
	w25qxx_Spi(0);
	HAL_SPI_Receive(&_w25qxx_SPI, pBuffer, NumByteToRead_up_to_PageSize, 100);
	HAL_GPIO_WritePin(_w25qxx_CS_GPIO, _w25qxx_CS_PIN, GPIO_PIN_SET);
	#if (_w25qxx_DEBUG==1)
	StartTime = HAL_GetTick() - StartTime;

	for(u32 i = 0; i < NumByteToRead_up_to_PageSize ; i++) {
		if((i % 8 == 0) && (i > 2)) {
			printf("\r\n");
			w25qxx_Delay(10);
		}

		printf("0x%02X,", pBuffer[i]);
	}

	printf("\r\n");
	printf("w25qxx ReadPage done after %d ms\r\n", StartTime);
	w25qxx_Delay(100);
	#endif
	w25qxx_Delay(1);
}
//###################################################################################################################
void 	w25qxx_ReadSector(u8 *pBuffer	, u32 Sector_Address	, u32 NumByteToRead_up_to_SectorSize) {
	u8	inSectorIndex = 0;
	#if (_w25qxx_DEBUG==1)
	printf("w25qxx ReadSector %d begin...\r\n", Sector_Address);
	printf("w25qxx Split to %d Page...\r\n", w25qxx.SectorSize / w25qxx.PageSize);
	w25qxx_Delay(100);
	#endif

	if((NumByteToRead_up_to_SectorSize > w25qxx.SectorSize) || (NumByteToRead_up_to_SectorSize == 0))
		NumByteToRead_up_to_SectorSize = w25qxx.SectorSize;

	do {
		w25qxx_ReadPage(pBuffer, (Sector_Address * w25qxx.SectorSize / w25qxx.PageSize) + inSectorIndex, NumByteToRead_up_to_SectorSize);

		if(NumByteToRead_up_to_SectorSize <= w25qxx.PageSize) {
			#if (_w25qxx_DEBUG==1)
			printf("w25qxx ReadSector done\r\n");
			w25qxx_Delay(100);
			#endif
			return;
		}

		inSectorIndex++;
		NumByteToRead_up_to_SectorSize -= w25qxx.PageSize;
		pBuffer += w25qxx.PageSize;
	} while(NumByteToRead_up_to_SectorSize > 0);
}
//###################################################################################################################
void 	w25qxx_ReadBlock(u8* pBuffer, u32 Block_Address		, u32	NumByteToRead_up_to_BlockSize) {
	u8	inBlockIndex = 0;
	#if (_w25qxx_DEBUG==1)
	printf("w25qxx ReadSector %d begin...\r\n", Block_Address);
	printf("w25qxx Split to %d Page...\r\n", w25qxx.BlockSize / w25qxx.PageSize);
	w25qxx_Delay(100);
	#endif

	if((NumByteToRead_up_to_BlockSize > w25qxx.BlockSize) || (NumByteToRead_up_to_BlockSize == 0))
		NumByteToRead_up_to_BlockSize = w25qxx.BlockSize;

	do {
		w25qxx_ReadPage(pBuffer, (Block_Address * w25qxx.BlockSize / w25qxx.PageSize) + inBlockIndex, NumByteToRead_up_to_BlockSize);

		if(NumByteToRead_up_to_BlockSize <= w25qxx.PageSize) {
			#if (_w25qxx_DEBUG==1)
			printf("w25qxx ReadSector done\r\n");
			w25qxx_Delay(100);
			#endif
			return;
		}

		inBlockIndex++;
		NumByteToRead_up_to_BlockSize -= w25qxx.PageSize;
		pBuffer += w25qxx.PageSize;
	} while(NumByteToRead_up_to_BlockSize > 0);
}
//###################################################################################################################

#endif

