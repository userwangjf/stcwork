

#include "bsp/config.h"
#include "save/save.h"

//移植下面6个函数


//2个sector的地址
#define SECTOR_A		0xE200
#define SECTOR_B		0xE400

void erase_sector_a() {
	EEPROM_SectorErase(SECTOR_A);
}

void erase_sector_b() {
	EEPROM_SectorErase(SECTOR_B);
}

//按4B写
void write_sector_a(u16 index, u32 wdata)
{
	EEPROM_write_n(SECTOR_A + (index << 2), (u8*)&wdata, 4);
}

//按4B写
void write_sector_b(u16 index, u32 wdata)
{
	EEPROM_write_n(SECTOR_B + (index << 2), (u8*)&wdata, 4);
}

u32 read_sector_a(u16 index)
{
	u32 CODE * psave;
	u32 temp;

	psave = (u32 CODE *)(SECTOR_A + (index << 2));
	temp = *psave;
	return temp;
}

u32 read_sector_b(u16 index)
{
	u32 CODE * psave;
	u32 temp;

	psave = (u32 CODE *)(SECTOR_B + (index << 2));
	temp = *psave;
	return temp;
}

void save_init()
{
	s16 i;

#if 1
	u32 CODE * psave;
	printk("\r\n");
	psave = (u32 CODE *)SECTOR_A;
	for (i = 0; i < 1; i++) {
		printk("0x%x,",*psave);
		psave++;
	}

	//读最后一个sector的校验码
	printk("\r\n");
	psave = (u32 CODE *)0xE700;
	for (i = 0; i < 0x40; i++) {
		printk("0x%x,",*psave);
		psave++;
	}

#endif

	save_start();


#if 1
	printk("\r\nsave_wptr: 0x%x",(u32)save_wptr);
	printk("\r\nsave_max : 0x%x",(u32)save_max);
	printk("\r\nsave_select: 0x%x",(u32)save_select);
#endif

}


void save_test() {
	u32 mysave1 = 0;
	u32 mysave2 = 0;

	save_init();
	save_read(1, &mysave1, 0x5511);
	save_read(2, &mysave2, 0x5522);
	printk("\r\nmysave1: 0x%x", (u32)mysave1);
	printk("\r\nmysave2: 0x%x", (u32)mysave2);
	mysave1 += 2;
	mysave2 += 3;
	save_write(1, mysave1);
	save_write(2, mysave2);
}




