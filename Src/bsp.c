#include "bsp.h"
#include "stm32f4xx.h"

#define GPIOAEN   (1U<<0)
#define GPIOCEN   (1U<<2)
#define PIN5    (1U<<5)
#define LED_PIN5   (1U<<5)
#define BTN_PIN13 (1U<<13)

void led_init(void){


//	Enable Clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//PA5 set to output mode
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
}

void led_on(void){
	GPIOA->ODR |= LED_PIN5;

}

void led_off(void){
	GPIOA->ODR &= ~LED_PIN5;

}

void button_init(void){


	RCC->AHB1ENR|= GPIOCEN;
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);


}

bool get_btn_state(void){

	if (GPIOC->IDR & BTN_PIN13)
	{
		return false;

	}
	else{
		return true;
	}

}
