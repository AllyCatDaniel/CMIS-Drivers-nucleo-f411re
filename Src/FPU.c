#include "stm32f4xx.h"



void fpu_enable(void)
{
	/*Enable CP10 and CP11*/
		SCB->CPACR |=(1<<20);
		SCB->CPACR |=(1<<21);
		SCB->CPACR |=(1<<22);
		SCB->CPACR |=(1<<23);
}
