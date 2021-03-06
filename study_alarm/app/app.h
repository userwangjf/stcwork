

#ifndef __APP_H__
#define __APP_H__

void GPIO_Config(void);

void UART_config(u8 int_en,u32 rate);
void PCA_config(void);
void EXTI_config(void);

void task_keyScan(u8 task_id);
void task_pwm(u8 task_id);
void task_shell(u8 task_id);

void task_cnt0(u8 task_id);
void task_cnt1(u8 task_id);
void task_cnt2(u8 task_id);
void task_cnt3(u8 task_id);
void task_cnt4(u8 task_id);
void task_cnt5(u8 task_id);
void task_cnt6(u8 task_id);
void task_cnt7(u8 task_id);

void init_595();
void test_595();

void task_ds3231(u8 task_id);


#endif

