#ifndef _w25qxx_H
#define _w25qxx_H

typedef enum {
	W25Q10 = 1,
	W25Q20,
	W25Q40,
	W25Q80,
	W25Q16,
	W25Q32,
	W25Q64,
	W25Q128,
	W25Q256,
	W25Q512,

} w25qxx_ID_t;

typedef struct {
	w25qxx_ID_t	ID;
	u8	UniqID[8];

	u16 PageSize;
	u32	PageCount;
	u32	SectorSize;
	u32	SectorCount;
	u32	BlockSize;
	u32	BlockCount;

	u32	CapacityInKiloByte;

	u8 StatusRegister1;
	u8 StatusRegister2;
	u8 StatusRegister3;

} w25qxx_t;

extern w25qxx_t	w25qxx;
//############################################################################
// in Page,Sector and block read/write functions, can put 0 to read maximum bytes
//############################################################################

u8 w25qxx_Spi(u8 dat);
u32 w25qxx_ReadID(void);
void w25qxx_WaitBusy(void);
bool w25qxx_Init(void);
void w25qxx_WaitForWriteEnd(void);

void w25qxx_ReadBytes(u32 ReadAddr, u8* pBuffer, u16 NumByte);
void w25qxx_WriteByte(u32 WriteAddr, u8* pBuffer, u16 numByte);
void w25qxx_EraseSector(u32 SectorAddr);
void w25qxx_EraseChip();

void w25qxx_ReadUniqID(void);
u8 w25qxx_ReadStatusRegister(u8	SelectStatusRegister_1_2_3);

void w25qxx_test();

/*
void w25qxx_EraseChip(void);
void w25qxx_EraseBlock(u32 BlockAddr);

void w25qxx_WritePage(u8 *pBuffer, u32 Page_Address, u32 NumByteToWrite_up_to_PageSize);
void w25qxx_WriteSector(u8 *pBuffer, u32 Sector_Address, u32 NumByteToWrite_up_to_SectorSize);
void w25qxx_WriteBlock(u8* pBuffer, u32 Block_Address, u32 NumByteToWrite_up_to_BlockSize);


void w25qxx_ReadPage(u8 *pBuffer, u32 Page_Address, u32 NumByteToRead_up_to_PageSize);
void w25qxx_ReadSector(u8 *pBuffer, u32 Sector_Address, u32 NumByteToRead_up_to_SectorSize);
void w25qxx_ReadBlock(u8* pBuffer, u32 Block_Address, u32 NumByteToRead_up_to_BlockSize);
*/

#define W25Q_FAST_READ			0x0B
#define W25Q_DUMMY_BYTE         0xA5
#define W25Q_WRITE_BYTE         0xA5

#endif

