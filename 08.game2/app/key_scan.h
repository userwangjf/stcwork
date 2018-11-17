

#ifndef __KEY_SCAN_H__
#define __KEY_SCAN_H__


#define KEY_UP		0xf6
#define KEY_DOWN	0xee
#define KEY_LEFT	0xf5
#define KEY_RIGHT	0xf3
#define KEY_START	0xdb
#define KEY_Y		0xed
#define KEY_X		0xeb
#define KEY_A		0xdd
#define KEY_B		0xde

#define KEY_VALID(k)	(k!=0xff)


//������������ɨ��������������5�ζ���ɨ��Ķ�����ͬ��ֵ������Ϊ����Ч��ֵ���������󴥷�
#define KEYDEBOUNCE 		5
//�ظ��������
#define KEY_REPEAT_DLY	 	5
//�ظ������ȴ�
#define KEY_REPEAT_WAIT		20

//��������
extern u8 g_uiCurrKey;            //��ǰ����ֵ
extern u8 g_uiLastKey;            //�ϴΰ���ֵ
extern u8 g_uiKeyScanCount;       //����ɨ����������ã�������

extern u8 g_uiKeyDown;            //�������£����صļ�ֵ��       ���ã����ΰ��������η�����Ч��ֵ����ס���ţ�Ҳֻ���ر����µ�һ����ֵ
extern u8 g_uiKeyRelease;         //�����ͷź󣬷��صļ�ֵ��     ���ã�ֻ�а��µİ������ͷź󣬲ŷ��ذ��µļ�ֵ
extern u8 g_uiKeyContinue;        //�������������ظ����صļ�ֵ�� ���ã�ֻҪ��ס���ţ��ͻ��ظ��ط�����ͬ��ֵ

//��������
void key_scan ( void );
u8 key_get();

#endif
