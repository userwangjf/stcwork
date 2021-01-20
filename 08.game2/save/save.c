
#include "bsp/config.h"
#include "save/save.h"

//持久化数据
//每个数据带一个唯一的index,从1开始.
//使用2个扇区持久化数据
//每个数据固定占用8B,其中前4B为flag,后4B为有效数据.
//按增量方式存储数据，写满一个sector后，
//写下一个sector前需要将前一个sector的最新数据拷贝过来
//第一个4B存储数据有效标记，0x55aaxxxx为有效数据
//其中xxxx为数据的序列号
//只有一个sector存在有效数据。另一个sector必须是被擦除状态.
//STC15最后一个sector,编程后会自动生成一个校验码


u16 save_wptr = 0;
//存储参数index的最大值
u16 save_max = 0;
u8 save_select = 0;

typedef struct {
	u32 save_flag;
	u32 save_data;
} save_st;


void save_start() {
	u16 i;
	u32 rdata;
	save_max = 0;
	//先搜索SECTOR_A
	save_wptr = 0;
	save_select = 0;

	for(i = 0; i < SECTOR_SIZE / 8; i++) {
		rdata = read_sector_a(save_wptr);

		if((rdata & 0xffff0000) == 0x55aa0000) {
			rdata &= 0x0000ffff;

			if(rdata > save_max)
				save_max = (u16)rdata;

			save_wptr += 2;
		} else
			break;
	}

	//已经找到,则返回
	if(save_wptr > 0)
		return;

	//再搜索SECTOR_B
	save_wptr = 0;
	save_select = 1;

	for(i = 0; i < SECTOR_SIZE / 8; i++) {
		rdata = read_sector_b(save_wptr);

		if((rdata & 0xffff0000) == 0x55aa0000) {
			rdata &= 0x0000ffff;

			if(rdata > save_max)
				save_max = (u16)rdata;

			save_wptr += 2;
		} else
			break;
	}
}

void save_write(u16 sav_index, u32 sav_data) {
	save_st save;
	u16 i;

	if(sav_index < 1 || sav_index > 10000)
		return;

	//如果超过一个sector,则先搬移数据
	if(save_wptr >= SECTOR_SIZE / 4) {
		save_wptr = 0;

		for(i = 1; i <= save_max; i++) {
			if(save_read(i, &(save.save_data), 0xffffffff)) {
				save.save_flag = 0x55aa0000 | i;

				if(save_select) {
					write_sector_a(save_wptr++, save.save_flag);
					write_sector_a(save_wptr++, save.save_data);
				} else {
					write_sector_b(save_wptr++, save.save_flag);
					write_sector_b(save_wptr++, save.save_data);
				}
			}
		}

		//擦除当前sector的数据
		if(save_select) {
			erase_sector_b();
			save_select = 0;
		} else {
			erase_sector_a();
			save_select = 1;
		}
	}

	//写入当前数据
	save.save_flag = 0x55aa0000 | sav_index;
	save.save_data = sav_data;

	if(save_select) {
		write_sector_b(save_wptr++, save.save_flag);
		write_sector_b(save_wptr++, save.save_data);
	} else {
		write_sector_a(save_wptr++, save.save_flag);
		write_sector_a(save_wptr++, save.save_data);
	}

	if(sav_index > save_max)
		save_max = sav_index;
}

//按sav_index从持久化空间读取数据到sav_data,如果没有找到,则保存def_data.
//成功,返回1,否则返回0
u8 save_read(u16 sav_index, u32* sav_data, u32 def_data) {
	u32 rdata;
	s16 i;
	u8 ret = 0;
	*sav_data = def_data;

	if(sav_index < 1 || sav_index > 10000)
		return 0;

	//超过范围
	if(sav_index > save_max) {
		return ret;
	}

	//没有存储数据
	if(save_wptr < 2)
		return ret;

	//从后向前搜索,后面的数据是最新的
	i = save_wptr - 2;

	for(; i >= 0; i--) {
		if(save_select)
			rdata = read_sector_b(i);
		else
			rdata = read_sector_a(i);

		if(rdata == 0xffffffff) {
			return ret;
		} else if((rdata & 0xffff0000) != 0x55aa0000)
			continue;
		else if((rdata & 0x0000ffff) == sav_index) {
			if(save_select)
				rdata = read_sector_b(i + 1);
			else
				rdata = read_sector_a(i + 1);

			*sav_data = rdata;
			ret = 1;
			break;
		}
	}

	return ret;
}

