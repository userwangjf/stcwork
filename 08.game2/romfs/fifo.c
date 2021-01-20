

#include "bsp/config.h"
#include "romfs/fifo.h"

//FIFO总长度,必须是2的幂
#define FIFO_LEN    0x80

u8 fifo_waddr = 0;
u8 fifo_raddr = 0;
u8 fifo_dat_buf[FIFO_LEN];

//#define is_power_of_2(x) 	((x) != 0 && (((x) & ((x) - 1)) == 0))
#define fifo_min(x,y) 		((x) > (y)) ? (y) : (x)


//fifo初始化,size必须为2的幂
u8 fifo_init(fifo_ctrl* fifo, u8* buffer, u8 size) {
	fifo->waddr = 0;
	fifo->raddr = 0;
	fifo->buffer = buffer;
	fifo->size = size;

	return size;
}

//从FIFO申请一定长度的空间,如果有空间,则返回该长度,否则返回0
// u8 fifo_get(fifo_ctrl* fifo, u8 len) {
// 	if(len == fifo_min(len, fifo->size - fifo->waddr - fifo->raddr))
// 		return len;
// 	else
// 		return 0;
// }

//获得fifo的数据深度
u8 fifo_level(fifo_ctrl* fifo) {
	return (u8)(fifo->waddr - fifo->raddr);
}

//获得fifo的剩余空间
u8 fifo_remain(fifo_ctrl* fifo) {
	return fifo->size - (u8)(fifo->waddr - fifo->raddr);
}

//写数据到FIFO,返回写入的真实长度
u8 fifo_wr(fifo_ctrl* fifo, u8* wdata, u8 len) {
	u8 i;
	u8 high;
	u8* dst;
	u8 mask;

	mask = fifo->size - 1;

	//fifo剩余的总长度
	len = fifo_min(len, fifo->size - (u8)(fifo->waddr - fifo->raddr));
	//fifo高地址剩余的长度
	high = fifo_min(len, fifo->size - (fifo->waddr & mask));

	//拷贝数据到FIFO高地址
	dst = fifo->buffer + (fifo->waddr & mask);
	for(i=0;i<high;i++) {
		*dst++ = *wdata++;
	}

	//拷贝数据到FIFO低地址
	dst = fifo->buffer;
	high = len-high;
	for(i=0;i<high;i++) {
		*dst++ = *wdata++;
	}
	
	fifo->waddr += len;

	return len;
}

//从FIFO中读出一定长度的数据,返回实际的长度
u8 fifo_rd(fifo_ctrl* fifo, u8* rdata, u8 len)
{
	u8 i;
	u8 low;
	u8* src;
	u8 mask;

	mask = fifo->size - 1;

	len = fifo_min(len, (u8)(fifo->waddr - fifo->raddr));
	low = fifo_min(len, fifo->size - (fifo->raddr & mask));

	src = fifo->buffer + (fifo->raddr & mask);
	for(i=0;i<low;i++) {
		*rdata++ = *src++;
	}

	src = fifo->buffer;
	low = len - low;
	for(i=0;i<low;i++) {
		*rdata++ = *src++;
	}

	fifo->raddr += len;

	return len;
}

//写数据到FIFO,返回写入的真实长度
u8 fifo_wr_isr(fifo_ctrl* fifo, u8* wdata, u8 len) {
	u8 i;
	u8 high;
	u8* dst;
	u8 mask;

	mask = fifo->size - 1;

	//fifo剩余的总长度
	len = fifo_min(len, fifo->size - (u8)(fifo->waddr - fifo->raddr));
	//fifo高地址剩余的长度
	high = fifo_min(len, fifo->size - (fifo->waddr & mask));

	//拷贝数据到FIFO高地址
	dst = fifo->buffer + (fifo->waddr & mask);
	for(i=0;i<high;i++) {
		*dst++ = *wdata++;
	}

	//拷贝数据到FIFO低地址
	dst = fifo->buffer;
	high = len-high;
	for(i=0;i<high;i++) {
		*dst++ = *wdata++;
	}
	
	fifo->waddr += len;

	return len;
}

//从FIFO中读出一定长度的数据,返回实际的长度
u8 fifo_rd_isr(fifo_ctrl* fifo, u8* rdata, u8 len)
{
	u8 i;
	u8 low;
	u8* src;
	u8 mask;

	mask = fifo->size - 1;

	len = fifo_min(len, (u8)(fifo->waddr - fifo->raddr));
	low = fifo_min(len, fifo->size - (fifo->raddr & mask));

	src = fifo->buffer + (fifo->raddr & mask);
	for(i=0;i<low;i++) {
		*rdata++ = *src++;
	}

	src = fifo->buffer;
	low = len - low;
	for(i=0;i<low;i++) {
		*rdata++ = *src++;
	}

	fifo->raddr += len;

	return len;
}

void fifo_test() {
	u8 ww[17];
	u8 wdata;
	u8 rr[17];
	u8 i;

	fifo_ctrl test;

	printk("\r\n: start fifo test:");

	fifo_init(&test,ww,16);
	ww[16] = 0;

	for(i = 0; i < 20; i++) {
		wdata = '1' + i;
		if(0 == fifo_wr(&test,&wdata, 1))break;
	}
	printk("\r\nWR%d,%d",test.raddr,test.waddr);
	printk("\r\nDATA:%s",ww);

	rr[16] = 0;
	fifo_rd(&test,rr,20);
	printk("\r\nRD%d,%d",test.raddr,test.waddr);
	printk("\r\n%s",rr);

	for(i = 0; i < 20; i++) {
		wdata = 'A' + i;
		if(0 == fifo_wr(&test,&wdata, 1))break;
	}
	printk("\r\nWR%d,%d",test.raddr,test.waddr);
	printk("\r\nDATA:%s",ww);

	rr[16] = 0;
	fifo_rd(&test,rr,20);
	printk("\r\nRD%d,%d",test.raddr,test.waddr);

	printk("\r\n%s",rr);


}


#ifdef UNIT_TEST

//增加依赖文件,以冒号结尾
//#DEP_FILE: :
//添加编译文件需要的gcc参数
//#CMP_FLAG: -I. -I..:

#include "unit_test.h"

char* ut_wr_byte()
{
	int i;
	char byte;
	fifo_ctrl fifo;
	char fifo_buf[16] = {0,};
	char fifo_cmp[16] = {0,};
	fifo_init(&fifo, fifo_buf, 16);

	for(i=0;i<16;i++) {
		byte = 'A' + i;
		fifo_wr(&fifo, &byte, 1);
		fifo_cmp[i] = byte;
		
	}

    return 0;
}


//定义自己的ut_all_tests
char* ut_all_tests()
{
    UT_TEST(ut_wr_byte);

    return 0;
}

#endif


