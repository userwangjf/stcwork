
#include "bsp/config.h"
#include "tetris/tetris.h"


u8 is_game_over = 0;


// 为了preview brick显示美观, 将方块在4 * 4 的点阵中居中
// 实际上这个是可以直接使用方块数据表的, 但要略做更改, 懒得再算表了
const u16 preview_brick_table[BRICK_TYPE] =
{
	0x0360,     // S
	0x0C60,     // Z
	0x0446,     // L
	0x0226,     // J
	0x2222,     // I
	0x0660,     // O
	0x0E40,     // T
};


// 方块数据表
const u16 brick_table[BRICK_TYPE][BRICK_NUM_OF_TYPE] =
{
	{ 0x6C00, 0x4620, 0x06C0, 0x8C40 },     // S
	{ 0xC600, 0x2640, 0x0C60, 0x4C80 },     // Z
	{ 0x88C0, 0xE800, 0x6220, 0x02E0 },     // L
	{ 0x2260, 0x08E0, 0xC880, 0xE200 },     // J
	{ 0x4444, 0x0F00, 0x2222, 0x00F0 },     // I
	{ 0xCC00, 0xCC00, 0xCC00, 0xCC00 },     // O
	{ 0xE400, 0x2620, 0x04E0, 0x8C80 }      // T
};


// 旋转掩码表
const u16 rotate_mask[BRICK_TYPE][BRICK_NUM_OF_TYPE] =
{
	{ 0xEE20, 0x66E0, 0x8EE0, 0xECC0 },     // S
	{ 0xE660, 0x2EE0, 0xEE80, 0xCCE0 },     // Z
	{ 0xECC0, 0xEE20, 0x66E0, 0x8EE0 },     // L
	{ 0x2EE0, 0xCCE0, 0xEE80, 0xE660 },     // J
	{ 0x7FCC, 0xEF33, 0x33FE, 0xCCF0 },     // I
	{ 0xCC00, 0xCC00, 0xCC00, 0xCC00 },     // O
	{ 0xE620, 0x26E0, 0x8CE0, 0xEC80 }      // T
};

// 下一个方块的y坐标初始值
const s8 brick_start_y[BRICK_TYPE] =
{
//   S   Z   L   J   I   O   T
	1, 1, 1, 1, 1, 1, 1
};

// 地图数组
// map[0]是地图的最上方
u16 map[MAP_HEIGHT];
// 地图备份, 保存上一次的数据, 解决屏幕闪烁问题
u16 map_backup[MAP_HEIGHT];

brick_t curr_brick;              // 当前方块
//brick_t next_brick;              // 下一个方块

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



//创建一个新的方块
void create_new_brick ( brick_t* brick )
{
	//随机的方块类型
	u8 bt = get_random_num() % BRICK_TYPE;

	// 初始坐标
	brick->x = BRICK_START_X;
	brick->y = brick_start_y[bt];

	// 记录种类
	brick->index = bt << 4;
	// 方块的bitmap信息
	brick->brick = brick_table[bt][0];
}


/**
 * \brief  将地图数组中的内容同步到屏幕, 只同步改变的部分
 */
void tetris_sync ( void )
{
	u8 x, y;

	// 为了解决全图更新时屏幕闪烁的问题
	// 新增一个备份区, 每次只更新不一样的部分
	for ( y = 0; y < MAP_HEIGHT; y++ )
	{
		// 只更新不一样的部分
		if ( map[y] != map_backup[y] )
		{
			for ( x = 0; x < MAP_WIDTH; x++ )
			{
				if ( GET_BIT ( map[y], x ) != GET_BIT ( map_backup[y], x ) )
				{
					draw_box ( x, y, ( u8 ) GET_BIT ( map[y], x ) );
				}
			}
		}
	}

	for ( y = 0; y < MAP_HEIGHT; y++ )
	{
		map_backup[y] = map[y];
	}

	return;
}



//按行同步显示缓存
void tetris_sync_all ( void )
{
	u8 y;

	for ( y = 0; y < MAP_HEIGHT; y++ )
	{
		disp_row ( y, map[y] );
	}

	return;
}



/**
 * \brief  game over?
 *
 * \return
 */
u8 tetris_is_game_over ( void )
{
	return is_game_over;
}

/**
 * \brief  在地图数组中画指定方块
 *
 * \param  brick
 */
void draw_brick ( const brick_t* brick )
{
	u8 box_x, box_y;

	for ( box_y = 0; box_y < BRICK_HEIGHT; box_y++ )
	{
		for ( box_x = 0; box_x < BRICK_WIDTH; box_x++ )
		{
			// 保证在地图区域内, 因为SET_BIT()只是一个宏, 对数组边界不会进行检查
			// 所以在这里检查数组(地图)边界是必须的, 但是只要检查上边界就可以
			// 因为如果要调用此函数时已经经过冲突检测, 所以其它条件必然符合
			if ( brick->y + box_y >= 0
			        // && brick.y < MAP_HEIGHT
			        && GET_BIT ( brick->brick, 15 - ( box_y * BRICK_WIDTH + box_x ) ) )
			{
				SET_BIT ( map[box_y + brick->y], box_x + brick->x );
			}
		}
	}

	return;
}




/**
 * \brief  在方块数组中清除指定方块
 *
 * \param  brick
 */
void clear_brick ( const brick_t* brick )
{
	u8 box_x, box_y;

	for ( box_y = 0; box_y < BRICK_HEIGHT; box_y++ )
	{
		for ( box_x = 0; box_x < BRICK_WIDTH; box_x++ )
		{
			// 保证在地图区域内
			if ( brick->y + box_y >= 0
			        // && brick.y < MAP_HEIGHT
			        && GET_BIT ( brick->brick, 15 - ( box_y * BRICK_WIDTH + box_x ) ) )
			{
				CLR_BIT ( map[box_y + brick->y], box_x + brick->x );
			}
		}
	}

	return;
}


/**
 * \brief  冲突检测, 检测之前要将当前方块从地图数组中清掉.
 *
 * \param  dest 目标位
 *
 * \retval 1 方块在目标位有冲突
 *         0 方块在目标位无冲突
 */
u8 is_conflict ( const brick_t dest )
{
	s8 box_y, box_x;
	u8 exp = 1;

	for ( box_y = 0; box_y < BRICK_HEIGHT; box_y++ )
	{
		for ( box_x = 0; box_x < BRICK_WIDTH; box_x++ )
		{
			// 依次检测每一个box
			if ( ( GET_BIT ( dest.brick, ( 15 - ( box_y * BRICK_WIDTH + box_x ) ) ) ) )
			{
				// box在地图外的情况(只存在新方块刚被创建时)
				// 这时不用检测地图部分(因为没在地图内)
				// 只需要检查左右边界就可以了, 下边界也没必要检查, 因为肯定不会越界
				if ( ( dest.y + box_y ) < 0 )
				{
					exp = ( ( ( box_x + dest.x ) > ( MAP_WIDTH - 1 ) ) // 右边界
					        || ( ( box_x + dest.x ) < 0 ) );                      // 左边界
					// || ((box_y + dest.y) > (MAP_HEIGHT - 1)));  // 下边界
				}
				else
				{
					// 此时box在地图内, 检查下边界, 还要检测box在地图内是否有冲突
					exp = ( ( ( box_x + dest.x ) > ( MAP_WIDTH - 1 ) ) // 右边界
					        || ( ( box_x + dest.x ) < 0 )                         // 左边界
					        || ( ( box_y + dest.y ) > ( MAP_HEIGHT - 1 ) ) // 下边界
					        || ( GET_BIT ( map[box_y + dest.y], ( box_x + dest.x ) ) ) ); // 地图内
				}
				if ( exp )
				{
					return 1;
				}
			}
		}
	}

	return 0;
}


/**
 * \brief
 *
 * \param  draw_box_to_map
 * \param  get_random
 * \param  next_brick_info
 * \param  remove_line_num
 */
void tetris_start ( void ( *draw_box_to_map ) ( u8 x, u8 y, u8 color ),
                    u8 ( *get_random ) ( void ),
                    void ( *remove_line_num ) ( u8 line ) )
{
	u8 i;

	draw_box = draw_box_to_map;
	get_random_num = get_random;
	return_remove_line_num = remove_line_num;
	is_game_over = 0;

	// 初始化地图
	for ( i = 0; i < MAP_HEIGHT; i++ )
	{
		map[i] = 0;
		map_backup[i] = 0;
	}

	create_new_brick ( &curr_brick );

	draw_brick ( &curr_brick );
	tetris_sync_all();

	return;
}

/**
 * \brief  消行
 */
void line_clear_check ( void )
{
	u8 row, line;
	u8 i;

	line = 0;

	// FIXME
	// 消行, map[0]实际上是地图的顶端
	// 从顶端开始向下扫, 每遇到一行满的
	// 就以此开始替换
	for ( row = 0; row < MAP_HEIGHT; row++ )
	{
		if ( map[row] >= (0xffff >> (16-MAP_WIDTH )))
		{
			line++;

			for ( i = row; i > 0; i-- )
			{
				map[i] = map[i - 1];
			}
			map[0] = 0;
		}
	}

	// 有消行, 返回消行数
	if ( return_remove_line_num != NULL )
	{
		return_remove_line_num ( line);
	}

	return;
}



/**
 * \brief  移动方块
 *
 * \param  direction
 *
 * \retval 1 移动失败
 *         0 移动成功
 */
u8 tetris_move ( dire_t direction )
{
	brick_t dest_brick;
	u8 is_move = 0;

	dest_brick.x = curr_brick.x;
	dest_brick.y = curr_brick.y;
	dest_brick.index = curr_brick.index;
	dest_brick.brick = curr_brick.brick;

	switch ( ( u8 ) direction )
	{
		case dire_left:
			dest_brick.x--;
			break;
		case dire_right:
			dest_brick.x++;
			break;
		case dire_down:
			dest_brick.y++;
			break;
		case dire_rotate:
		{
			// 低8位记录变形
			u8 i = dest_brick.index & 0x0F;
			i++;
			dest_brick.index = ( dest_brick.index & 0xF0 ) | ( i % 4 );
			dest_brick.brick = rotate_mask[dest_brick.index >> 4][dest_brick.index & 0x0F];

			break;
		}
		default:
			break;
	}

	// 在检测之前先将当前方块从地图中清掉
	clear_brick ( &curr_brick );

	// 无冲突, 更改之
	if ( !is_conflict ( dest_brick ) )
	{
		// 旋转, 要方块信息从旋转mask改回来
		if ( direction == dire_rotate )
		{
			dest_brick.brick = brick_table[dest_brick.index >> 4][dest_brick.index & 0x0F];
		}
		curr_brick = dest_brick;
		is_move = 1;
	}
	else
	{
		// 不可移动, 且向下不可移动
		if ( direction == dire_down )
		{
			// 先将当前方块画到地图中
			draw_brick ( &curr_brick );
			// 如果下落完成时当前方块还有部分在地图外
			// 或者下一个方块无法再放进地图, 游戏结束
			if ( curr_brick.y + 1 <= 0 )
			{
				is_game_over = 1;
			}
			// 消行
			line_clear_check();
			// 产生新方块
			//curr_brick = next_brick;
			create_new_brick ( &curr_brick );
		}
		is_move = 0;
	}

	draw_brick ( &curr_brick );

	return is_move;
}

