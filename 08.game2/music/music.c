
#include "bsp/config.h"
#include "music/music.h"

//#include "music/music_dat1.c"
//#include "music/music_dat2.c"
//#include "music/music_dat3.c"
//#include "music/music_dat4.c"
//#include "music/music_dat5.c"

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

u8 prev = 0;
u32 err_cnt = 0;
u8 music_play() {
	u8 tmp;
	#if 1

	if(music_on) {
		if(music_len == 0 && fifo_level(&fifo_music_rd) == 0)
			music_on = 0;

		if(fifo_level(&fifo_music_rd) > 0) {
			fifo_rd_isr(&fifo_music_rd, &tmp, 1);

			if(prev != tmp)
				err_cnt++;
			prev++;

			return tmp;
		}
	}

	#else

	if(music_on) {
		if(music_addr > music_len)
			music_on = 0;

		return music_mofa[music_addr++];
	}

	#endif
	return 0x80;
}


void music_start(char* name, u8 on) {
	struct romfs_inode* file;
	file = romfs_namei(name);

	if(file == NULL) {
		printk("\r\nerror cnt: %d",(u32)err_cnt);
	} else {
		music_len = file->size - 32;
		music_addr = file->spec.file_data + 32;
		printk("\r\n0x%x,0x%x",(u32)music_addr,(u32)music_len);
		EA = 0;

		if(on) {
			music_on = 1;
		}

		#if 0
		music_len = 31782 - 48;
		music_addr = 0;
		#endif
		EA = 1;
	}
}



