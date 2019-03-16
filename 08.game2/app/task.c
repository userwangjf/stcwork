

#include "bsp/config.h"



typedef union {
	int i;
	char c;
}my_union;
 
int checkSystem1(void)
{
	my_union u;
	u.i = 1;
	return (u.i == u.c);
}


