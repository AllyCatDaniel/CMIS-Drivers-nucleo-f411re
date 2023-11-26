#include "adc.h"

#define GPIOAEN (1U<<0)
#define ADC1EN  (1U<<8)
#define ADC_CH1 (1U<<0)
#define ADC_SEQ_LEN 0x00
#define ADC_CR2 (1U<<0)
#define CR2_CONT (1U<<1)
#define CR2_SWSRT (1U<<30)
#define SR_EOC (1U<<1)


void pa1_adc_init(void){
	//gPIO for adc
	// enable clock access
	RCC->AHB1ENR|=GPIOAEN;
	//set PA1 mode to analog mode
	GPIOA->MODER |=(1U<<2);
	GPIOA->MODER |=(1U<<3);

	//configure adc module
	//clock access to module
	RCC->APB2ENR  |= ADC1EN;
	// set conversion sequence start
	ADC1->SQR3 =ADC_CH1;
	// set conversion sequence length.
	ADC1->SQR1=ADC_SEQ_LEN;

	// enable adc
	ADC1->CR2|=ADC_CR2;



}

void start_conversion(void){

	//enable continuous conversion
	ADC1->CR2|=CR2_CONT;
	// start ad conversion
	ADC1->CR2|=CR2_SWSRT;

}


uint32_t adc_read(void){

	//wait for version to be complete.
      while(!(ADC1->SR & SR_EOC)){

      }
      return (ADC1->DR);
}
