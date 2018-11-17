
#include "bsp/config.h"
#include "music/music.h"

//����ʹ�õİ���
#define JK_PAUSE	KEY_Y
#define JK_ROTATE	KEY_A
#define JK_DOWN		KEY_DOWN
#define JK_LEFT		KEY_LEFT
#define JK_RIGHT	KEY_RIGHT
#define JK_RESET		KEY_START


static u8   pause = 0;  		// ��Ϸ��ͣ
static u8   tetris_level = 1;          // ����
static u16  lines = 0;          // ����������
static u16  tetris_score = 0;          // ����
static u16  time_count = 0;


//���´�ӡ
void game_info_update()
{
	disp_dec(0,0,(tetris_score/100)%10);
	disp_dec(4,0,(tetris_score/10)%10);
	disp_dec(8,0,tetris_score%10);
	//L-level
	disp_row(6,0x00);
	disp_row(7,0x00);
	disp_row(8,0x00);
	disp_row(9,0x00);
	disp_row(10,0x00);
	disp_row(11,0x00);
	disp_on(0,6);
	disp_on(0,7);
	disp_on(0,8);
	disp_on(0,9);
	disp_on(0,10);
	disp_on(1,10);
	disp_on(2,10);
	disp_on(4,8);
	disp_on(5,8);
	disp_on(6,8);
	disp_dec(8,6,tetris_level);
}

void tetris_pause ( void )
{
	pause = !pause;

	if ( pause )
		game_info_update();
	else
	{
		tetris_sync_all();    // ��Ϊ��ӡ��ͣ�ƻ��˵�ͼ����ʾ
	}
	// �����˳�ʱҪˢ��������ͼ��
	return;
}

//�ص��������������
void tetris_get_score ( u8 line )
{
	u16 i;
	u16 j;
	lines += line;

	switch ( line )
	{
		case 1:
			tetris_score += 1;
			music_on(0,1);
			break;
		case 2:
			tetris_score += 3;
			music_on(0,2);
			break;
		case 3:
			tetris_score += 5;
			music_on(0,3);
			break;
		case 4:
			tetris_score += 12;
			music_on(0,2);
			break;
		default:
			break;
	}

	

	// ÿ25����һ��
	if(tetris_level < 10)
		tetris_level = lines / 25;

	return;
}

//�ص���������������Ļ�ϻ���box
//colorΪ0ʱ����������ϵ�box
void tetris_draw_box ( u8 x, u8 y, u8 color )
{
	if ( color == 0 )
	{
		disp_off ( x,y );
	}
	else
	{
		disp_on ( x,y );
	}

	return;
}

u8 rand_times = 0;
//�ص��������������������
u8 tetris_random()
{
	if(rand_times++ > 5)
	{
		rand_times = 0;
		return 4;
	}
	return random();
}

//������һ�����飬����Ԥ����ʾ
void tetris_preview_brick ( const void* info )
{

	return;
}



brick_t brick;
//��ʱ���ô˺���
void tetris_run ( u8 key )
{
	static u8 refresh = 0;

	if(key == JK_RESET)
	{
		tetris_init();
		return;
	}
	
	//��Ϸ����
	if ( tetris_is_game_over() )
	{
		game_info_update();
		return;
	}

	if ( !pause )
	{
		time_count++;
	}
	else
		refresh = 0;

	// ���������ƶ�������Խ���ٶ�Խ��
	if ( time_count >= ( 100 - tetris_level*5 ) )
	{
		time_count = 0;

		refresh = 1;
		tetris_move ( dire_down );
	}

	//�а�������
	if ( KEY_VALID ( key ) )
	{
		// ��ͣʱֻ��Ӧ�س���
		if ( pause && key != JK_PAUSE )
		{
			return;
		}

		switch ( key )
		{
			case JK_ROTATE:
				tetris_move ( dire_rotate );
				break;
			case JK_DOWN:
				tetris_move ( dire_down );
				break;
			case JK_LEFT:
				tetris_move ( dire_left );
				break;
			case JK_RIGHT:
				tetris_move ( dire_right );
				break;
			case JK_PAUSE:
				tetris_pause();
				return;
				break;
			default:
				break;
		}

		refresh = 1;
	}

	if ( refresh )
	{
		refresh = !refresh;
		//tetris_sync();
		tetris_sync_all();
		// ��������, ��������Ϣ
		//game_info_update();
	}

	return;
}


s8 tetris_init ( void )
{

	// ����������ʱ�ص��˺���, ����Ϊ����������
	// remove_line_num(uint8_t line)
	tetris_start ( tetris_draw_box, tetris_random, tetris_get_score );

	tetris_pause();

	tetris_score = 0;
	tetris_level = 0;

	return 0;
}