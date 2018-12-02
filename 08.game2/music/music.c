
#include "bsp/config.h"
#include "music/music.h"

u32 music_addr = 0;
u32 music_len = 0;
u8 music_on = 0;

//"/wav/backgangqin.wav"
//"/wav/daojishi.wav"
//"/wav/dingling.wav"
//"/wav/dushen.wav"
//"/wav/endmusic.wav"
//"/wav/faguang.wav"
//"/wav/guzhang.wav"
//"/wav/kaichang.wav"
//"/wav/kaichang2.wav"
//"/wav/kehuanclick.wav"
//"/wav/kuaimen.wav"
//"/wav/malifail.wav"
//"/wav/mofa.wav"
//"/wav/qiaoluo.wav"
//"/wav/qqmess.wav"
//"/wav/shuidi.wav"
//"/wav/sysfail.wav"
//"/wav/tupaopao.wav"
//"/wav/zhuangchang.wav"

u8 pi = 0;
u8 pbuf[128];

u8 music_play() {
	u8 tmp;

	if(music_on) {
		if(music_len > 0) {
			music_len--;

			if(fifo_get(1) > 0) {
				fifo_rd(&tmp, 1);
				if(pi < 128) {
					pbuf[pi++] = tmp;
				}
				
				return tmp;
			}
		} else {
			music_on = 0;
		}

		//增加、减少音量，no use
		// if(tmp > 0x80)
		// 	return 0x80 + (tmp - 0x80) /2;
		// else
		// 	return 0x80 - (0x80 - tmp) / 2;
	}

	return 0x80;
}

void music_start(char* name, u8 times) {
	struct romfs_inode* file;
	file = romfs_namei(name);

	Uart1_Tx("\r\n");
	for(pi=0;pi<128;pi++) {
		Uart1_Tx(byte2str(pbuf[pi]));
		Uart1_Tx(",");
	}
	Uart1_Tx("\r\n");
	pi = 0;

	if(file == NULL) {
		Uart1_Tx("\r\nNO FIND: ");
		Uart1_Tx(name);
		Uart1_Tx("\r\n");
		return;
	}

	music_len = file->size;
	music_addr = file->spec.file_data;
	Uart1_Tx("\r\n");
	Uart1_Tx(hex2str(music_addr));
	Uart1_Tx(",");
	Uart1_Tx(hex2str(music_len));
	Uart1_Tx("\r\n");
	EA = 0;
	music_on = times;
	EA = 1;
}


//#include "music/music_dat1.c"
//#include "music/music_dat3.c"
