

#include "bsp/config.h"


void task_ds3231(u8 task_id)
{
	os_addPeriod(task_id,1000000);
	ds3231_updateTime();
	
	ds3231_print_time();
	
	os_debug(task_id);
	
}



