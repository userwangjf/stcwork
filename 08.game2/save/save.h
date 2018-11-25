
#ifndef __SAVE_H__
#define __SAVE_H__

//每个sector的字节长度
#define SECTOR_SIZE		512

//需要定义这6个回调函数,完成移植
void erase_sector_a();
void erase_sector_b();
void write_sector_a(u16 index,u32 wdata);
void write_sector_b(u16 index,u32 wdata);
u32 read_sector_a(u16 index);
u32 read_sector_b(u16 index);

void save_init();
s32 get_save(u8 pos);
u8 save_read(u16 sav_index, u32* sav_data, u32 def_data);
void save_write(u16 sav_index,u32 sav_data);
void save_start();

void save_test();

extern u16 save_wptr;
//存储参数index的最大值
extern u16 save_max;
extern u8 save_select;


#endif

