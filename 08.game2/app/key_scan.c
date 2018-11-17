
#include "bsp/config.h"

//======================================================
//KeyScan.c
//======================================================
//ע�⣺�ú궨�壬������keyscan.h�ļ���
//#define KEYDEBOUNCE 0x05             //������������ɨ��������������5�ζ���ɨ��Ķ�����ͬ��ֵ������Ϊ����Ч��ֵ���������󴥷�

u8 		g_uiCurrKey;            //��ǰ����ֵ
u8 		g_uiLastKey = 0xff;            //�ϴΰ���ֵ
u8 		g_uiKeyScanCount;       //����ɨ����������ã�������

u8 		g_uiKeyDown = 0xff;            //�������£����صļ�ֵ��       ���ã����ΰ��������η�����Ч��ֵ����ס���ţ�Ҳֻ���ر����µ�һ����ֵ
u8 		g_uiKeyRelease;         //�����ͷź󣬷��صļ�ֵ��     ���ã�ֻ�а��µİ������ͷź󣬲ŷ��ذ��µļ�ֵ
u8 		g_uiKeyContinue;        //�������������ظ����صļ�ֵ�� ���ã�ֻҪ��ס���ţ��ͻ��ظ��ط�����ͬ��ֵ
u8		g_repeatDly;

u8		g_repeatWait = 0;

//P3�ڵĵ�6λ��Ϊ����
//û�а���ʱ�����ص���0xff��
void key_scan ( void )
{
	static u8 LastReadKey;        //�ϴδ�IO�ڶ�ȡ�ļ�ֵ ,ע���Ǿ�̬����
	u8 	CurrReadKey;               //��ǰ��IO�ڶ�ȡ�ļ�ֵ

//---------------------- ��Ҫ�޸ĵĵط� --------------------------------------//
	u8  KeyRow,KeyColumn;

	//��ȡ����������
	P3 &= 0xf8;
	P3 |= 0x38;
	KeyRow = P3 | 0xc0;

	//��ȡ����������
	P3 &= 0xc7;
	P3 |= 0x07;
	KeyColumn = P3 | 0xc0;

	//��ȡ�����������ǵ�ǰ��ֵ��
	CurrReadKey = KeyRow|KeyColumn;         //��ȡ��ǰ�ļ�ֵ

	//�����ǰ��ȡ�ļ�ֵ���ϴδ�IO�ڶ�ȡ�ļ�ֵ��ͬ
	if ( CurrReadKey == LastReadKey )
	{
		//�����ж��Ƿ���ڵ���debounce���趨ֵ(���ǣ��Ƿ���ڵ����趨�Ĳ�������)
		if ( g_uiKeyScanCount >= KEYDEBOUNCE )
		{
			//��ס����,�����Ӧ
			g_uiCurrKey = CurrReadKey;                //�����,����ǰ�Ķ�ȡֵ�ж�Ϊ��Ч����ֵ(����ǣ��ڲ��������У��������ֵ�����ж�Ϊ��Ч����ֵ)

			//��ס����ֻ��Ӧһ��
			if ( g_uiLastKey == g_uiCurrKey )
			{
				//�ظ�����ǰ�ȴ�
				if(g_repeatWait++ >= KEY_REPEAT_WAIT)
				{
					//�ظ���������
					if ( g_repeatDly++ >= KEY_REPEAT_DLY )
					{
						g_uiKeyDown = g_uiCurrKey;
						g_repeatDly = 0;
					}
					else
					{
						g_uiKeyDown = 0xff;    //û�м�ֵ
					}
				}
			}
			else
			{
				g_uiKeyDown = g_uiCurrKey;             //�����ͬ��������Ч,(���ǵ�һ����Чֵʱ)
				g_repeatDly = 0;
				g_repeatWait = 0;
			}

			//�����ͷ�ʱ������ֵ����Ч
			if ( g_uiCurrKey == 0xff )               //����Ч����ֵ�ӷ�0��0��״̬ʱ(���ǣ����а������ް�������ʾ�Ѿ��ͷ���)����ʾ֮ǰ�����Ѿ��ͷ���
			{
				g_uiKeyRelease = g_uiLastKey;
			}

			g_uiLastKey = g_uiCurrKey;               //��¼�ϴ���Ч����ֵ
		}
		else                                       //�������debounce��һ(����������������ֵ)
		{
			g_uiKeyScanCount++;
		}
	}
	else                                          //�����ǰ��ȡ�ļ�ֵ���ϴδ�IO�ڶ�ȡ�ļ�ֵ��ͬ��˵�������Ѿ��仯
	{
		g_uiKeyDown = 0xff;                       //�ſ��������һ�ν���ɨ���������g_uiKeyDown.���ã�����һ��BUG�����BUG��ʲô����
		g_uiKeyScanCount = 0;                     //����֮ǰ�İ�����debounce����
		LastReadKey = CurrReadKey;                //����ǰ��ȡ�ļ�ֵ��¼Ϊ�ϴζ�ȡ�İ���ֵ
		g_repeatDly = 0;
		g_repeatWait = 0;
	}
}

u8 key_get()
{
	u8 tmp;
	if ( g_uiKeyDown != 0xff )
	{
		tmp = g_uiKeyDown;
		g_uiKeyDown = 0xff;
		return tmp;
	}
	return 0xff;
}

