typedef 	unsigned char	u8;
typedef 	         char	s8;
typedef 	unsigned int	u16;
typedef 	         int	s16;
typedef 	unsigned long	u32;
typedef 			 long	s32;


#define OS_TSK_MAX  8
u32 os_taskTick[OS_TSK_MAX] = {10,20,30,40,50,60,70,80};
u8 os_taskFindGt(u32 tick)
{
	u8 low = 0;
	u8 high = OS_TSK_MAX-1;
	u8 mid;

    if(tick < os_taskTick[low])return 0;
    if(tick > os_taskTick[high])return OS_TSK_MAX;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(tick < os_taskTick[mid])
            high = mid-1;
		else
			low = mid+1;
        printf("%d,",mid);
	}

	return high+1;
}

int main()
{
    /*
    os_taskFindGt
    */
    int i;
    for(i=0;i<9;i++) {
        printf("  %d\n",os_taskFindGt(i*10+2));
    }

    for(i=0;i<9;i++) {
        printf("  %d\n",os_taskFindGt(i*10));
    }



}


