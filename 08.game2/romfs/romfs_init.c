
#include "bsp/config.h"

//
u8 romfs_rd_block(u32 addr, u8* buf, u16 len) {
	w25qxx_ReadBytes(addr, buf, len);
	return 0;
}


void romfs_init()
{

}


