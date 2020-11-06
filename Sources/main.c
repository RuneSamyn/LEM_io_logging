#include "PJ_RPI.h"
#include <stdio.h>

int main()
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    }

	int gpioArray[27];

	while(1)
	{
		for(int x = 1; x <= 27; x++) {
			INP_GPIO(x);
			int value = GPIO_READ(x);
			value = value ? 1 : 0;
			if(gpioArray[x-1] != value) {
				usleep(100000);
				if(value) {
					printf("pin %d high\n", x);
				} else {
					printf("pin %d low\n", x);
				}
			}
			gpioArray[x-1] = value;
		}
	}

	return 0;	

}
