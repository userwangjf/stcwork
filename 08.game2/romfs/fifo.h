
#ifndef __FIFO_H__
#define __FIFO_H__

typedef struct {
	u8 waddr;
	u8 raddr;
	u8* buffer;
	u8 size;
} fifo_ctrl ;

u8 fifo_init(fifo_ctrl* fifo, u8* buffer, u8 size);
u8 fifo_get(fifo_ctrl* fifo, u8 len);
u8 fifo_wr(fifo_ctrl* fifo, u8* wdata, u8 len) ;
u8 fifo_rd(fifo_ctrl* fifo, u8* rdata, u8 len) ;
u8 fifo_wr_isr(fifo_ctrl* fifo, u8* wdata, u8 len) ;
u8 fifo_rd_isr(fifo_ctrl* fifo, u8* rdata, u8 len) ;
u8 fifo_level(fifo_ctrl* fifo);
u8 fifo_remain(fifo_ctrl* fifo);

void fifo_test();


#endif
