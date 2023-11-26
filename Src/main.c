
#include <stdio.h>
#include "stm32f4xx.h"
#include "FPU.h"
#include <stdbool.h>
#include "uart.h"
#include "circular_buffer.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"
#include "dfplayer_lib.h"

    uint32_t sensor;
    bool btn_state;
int main()
{
	fpu_enable();
	//
	debug_uart_int();

	slave_uart_int();
	circular_buffer_init();

	timebase_init();
	led_init();
	button_init();
	 pa1_adc_init();
	 delay(200);

	 dfplayer_init();
	 dfplayer_play_first_track();
		int toggle=1;

	while(1)
	{
		btn_state=get_btn_state();
		if(btn_state==true){
			led_on();

			 while  (btn_state==true){

				 btn_state=get_btn_state();
				 delay(10);
						 }

			if (toggle==1){
					dfplayer_play_pause_track();
					toggle=0;
			}
			else
			if (toggle==0){
				 dfplayer_play_first_track();
							toggle=1;
			}

		}
		led_off();
		//buffer_send_string("Dog is not bad\n\r",DEBUG_PORT);
 		//led_on();
		//delay(1);
//		buffer_send_string("Rodger Witiker\n\r",DEBUG_PORT);
		//buffer_send_string("Rogr is  bad\n\r",SLAVE_DEV_PORT);

    	//led_off();
	//	delay(3);

	}
    /* Loop forever */

}
