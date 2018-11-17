
#include "bsp/config.h"
#include "music/music.h"

u32 mucis_ptr_play = 0;
u8 music_play_on = 0;
u8 music_type = 0;

typedef struct 
{
	u8* music_dat;
	u16 music_len;
}music_list;

music_list music_rom[10] = {{music_line,6268},};

u8 music_play()
{
	u8 tmp;
	if(music_play_on)
	{
		if(mucis_ptr_play >= music_rom[music_type].music_len)
		{
			mucis_ptr_play = 0;
			music_play_on--;
		}
		tmp = music_rom[music_type].music_dat[mucis_ptr_play++];
		return tmp;

		//增加、减少音量，no use
		if(tmp > 0x80)
			return 0x80 + (tmp - 0x80) /2;
		else
			return 0x80 - (0x80 - tmp) / 2;
	}
	
	return 0x80;
}

void music_on(u8 type,u8 times)
{
	music_play_on = times;
	music_type = type;
}


