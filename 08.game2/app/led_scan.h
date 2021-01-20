
#ifndef __LED_SCAN_H__
#define __LED_SCAN_H__


#define LED_WX		11
#define LED_WY		21


extern u16 xdata disp_buf[21];

void disp_clear();
void disp_open(u8 delay);
void led_scan(void);
void disp_on(u8 x,u8 y);
void disp_off(u8 x, u8 y);
void disp_clear_row(u8 start,u8 end);
void disp_dec(u8 x, u8 y, u8 dec);
void disp_row(u8 y,u16 row);
void led_row_set(u8 set);
void led_row_clr(u8 clr);
void led_col_clr(u8 clr);
void led_col_set(u8 set);
void led_row_dis();
void led_col_dis();

#endif

