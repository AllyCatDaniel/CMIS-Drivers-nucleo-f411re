#include "timebase.h"
#include "stm32f4xx.h"


#define CTRL_ENABLE   (1U<<0)
#define CTRL_TICKINT   (1U<<1)
#define CTRL_CLKSRC   (1U<<2)
#define CTRL_COUNTFLAG   (1U<<16)

#define ONE_SEC_LOAD    16000000
#define ONE_MSEC_LOAD    16000


#define MAX_DELAY 0xFFFFFFFF
#define TICK_FREQ  1

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;



void delay(uint32_t delay)
{  uint32_t tickstart = get_tick();
   uint32_t   wait =delay;


	if(wait < MAX_DELAY )
	{

		wait +=(uint32_t) TICK_FREQ;
	}
	while (( get_tick() - tickstart)<wait){}


}
uint32_t get_tick(void)
{
	__disable_irq();

	g_curr_tick_p =g_curr_tick;

	 __enable_irq();

     return g_curr_tick_p;

}


static void tick_increment(void)
{

	g_curr_tick += TICK_FREQ;
}


void timebase_init(void){
	//disable globe interupt
	__disable_irq();
	//reload timer clock cycles per second
	SysTick->LOAD = ONE_MSEC_LOAD-1;
	//clear clock register
	SysTick->VAL=0;

	//select internal clock source
	SysTick->CTRL = CTRL_CLKSRC;
	// enable interupt
	SysTick->CTRL |= CTRL_TICKINT;
	// enable systick

      SysTick->CTRL |= CTRL_ENABLE;
	// enable global interupt
      __enable_irq();

}
 void SysTick_Handler(void){

	tick_increment();

}
