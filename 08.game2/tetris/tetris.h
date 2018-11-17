
#ifndef _TETRIS_H_
#define _TETRIS_H_

#define MAP_WIDTH                   10  // ��ͼ��,��ҪС��16
#define MAP_HEIGHT                  21  // ��ͼ��


typedef struct
{
    s8 x;               //!< brick�ڵ�ͼ�е�x����
    s8 y;               //!< brick�ڵ�ͼ�е�y����
    s8 index;           //!< ��������, ��4λ��¼����, ��4λ��¼����
    u16 brick;         		//!< ��������,16��bit���4*4��bitmap
} brick_t;

#define BRICK_TYPE                  7   // һ��7�����͵ķ���
#define BRICK_NUM_OF_TYPE           4   // ÿһ��������4�ֱ���

#define BRICK_HEIGHT                4   // һ��brick��4*4��box���
#define BRICK_WIDTH                 4

#define BRICK_START_X               ((MAP_WIDTH / 2) - (BRICK_WIDTH / 2))

#ifndef NULL
    #define NULL    ((void *)0)
#endif

/* Private macro -------------------------------------------------------------*/
// �Ե�ͼ�������λ������֧�ֺ�
#define     SET_BIT(dat, bit)      ((dat) |= (0x0001 << (bit)))
#define     CLR_BIT(dat, bit)      ((dat) &= ~(0x0001 << (bit)))
#define     GET_BIT(dat, bit)      (((dat) & (0x0001 << (bit))) >> (bit))

/* Private variables ---------------------------------------------------------*/
// �ص�����ָ��, ����������(x, y)��һ��brick
static void (*draw_box)(u8 x, u8 y, u8 color) = NULL;
// �ص�����ָ��, ��ȡһ�������
static u8 (*get_random_num)(void) = NULL;
// �ص�����ָ��, ��������ʱ����
static void (*return_remove_line_num)(u8 line) = NULL;

extern u16 map[MAP_HEIGHT];

// direction
typedef enum
{
    dire_left,      //!< ����
    dire_right,     //!< ����
    dire_down,      //!< ����
    dire_rotate,    //!< ��ת
} dire_t;

void tetris_run(u8 key);
s8 tetris_init(void);

extern u8   tetris_move(dire_t direction);
extern void tetris_sync(void);
extern void tetris_sync_all(void);
extern u8   tetris_is_game_over(void);
void create_new_brick(brick_t* brick);
void draw_brick(const brick_t* brick);
void clear_brick ( const brick_t* brick );

// ��ʼ��, ��Ҫ�Ļص�����˵��:
// ��(x, y)��һ��box, colorΪ��ɫ, ע��0��ʾ���, ����ʾ�κ���ɫ
// draw_box_to_map(u8 x, u8 y, u8 color)

// �����뷵��һ�������, �����·���ʹ��
// get_random(void)

// �������·����ص��˺���, ����Ϊ�·��������
// ��ǰ�汾 *info Ϊuint16_t������, �����·���ĵ�������
// next_brick_info(const void *info)

// ����������ʱ�ص��˺���, ����Ϊ����������
// remove_line_num(u8 line)
extern void tetris_start(
    void (*draw_box_to_map)(u8 x, u8 y, u8 color),
    u8 (*get_random)(void),
    void (*remove_line_num)(u8 line)
    );

#endif

