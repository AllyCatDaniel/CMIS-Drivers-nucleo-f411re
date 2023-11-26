#include <stdio.h>
#include <stdint.h>

#include "uart.h"

#define GPIOENA (1U<<0);
#define UART2EN (1U<<17);
#define UART1EN (1U<<4);

#define DBG_UART_BAUDRATE  9600
#define UART1_BAUDRATE  9600
#define SYS_FREQ 16000000

#define APB1_CLK SYS_FREQ
#define APB2_CLK SYS_FREQ

#define CR1_TE (1U<<3)
#define CR1_RE (1U<<2)

#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)
static uint16_t slave_uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);

//static void slave_uart_write(int ch);
//static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static uint16_t uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void slave_uart_write(int ch);
static void uart_write(int ch);

int __io_putchar(int ch)
{
	//uart_write(ch);
	slave_uart_write(ch);
	return ch;
}
void debug_uart_int(void)
{
	/* Enable clock access to GPIOA*/
	 RCC->AHB1ENR |=GPIOENA;
	/*Set Pin A2 to alternate function Mode*/

     GPIOA->MODER &=~(1U<<4);
     GPIOA->MODER |=(1U<<5);


 	/*Set Pin A3 to alternate function Mode*/
     GPIOA->MODER &=~(1U<<6);
        GPIOA->MODER |=(1U<<7);

 	/* Set function to AF7 for UART2*/

     GPIOA->AFR[0]  &=~(1U<<11);
     GPIOA->AFR[0] |=(1U<<10);
     GPIOA->AFR[0] |=(1U<<9);
     GPIOA->AFR[0] |=(1U<<8);

     //AF7 to be set for Tx

     GPIOA->AFR[0]  &=~(1U<<15);
     GPIOA->AFR[0] |=(1U<<14);
     GPIOA->AFR[0] |=(1U<<13);
     GPIOA->AFR[0] |=(1U<<12);
 	/* Enable clock to UART2*/
     RCC->APB1ENR |= UART2EN;

     USART2->CR1 &= ~CR1_UE;
  	/*Set baudrate*/

     uart_set_baudrate(APB1_CLK , DBG_UART_BAUDRATE);

   	/*Transfer Direction*/

     USART2->CR1 = CR1_TE | CR1_RE;
     // Enable NVIC USART2_IRQn
     NVIC_EnableIRQ(USART2_IRQn);

    	/*Enable*/

     USART2->CR1 |= CR1_UE;

}



void slave_uart_int(void)
{
	/* Enable clock access to GPIOA*/
	 RCC->AHB1ENR |=GPIOENA;
	/*Set Pin A9 to alternate function Mode*/

     GPIOA->MODER &=~(1U<<18);
     GPIOA->MODER |=(1U<<19);


 	/*Set Pin A10 to alternate function Mode*/
     GPIOA->MODER &=~(1U<<20);
     GPIOA->MODER |=(1U<<21);

 	/* Set function to AF7 for UART1*/

     GPIOA->AFR[1]  &=~(1U<<7);
     GPIOA->AFR[1] |=(1U<<6);
     GPIOA->AFR[1] |=(1U<<5);
     GPIOA->AFR[1] |=(1U<<4);

     //AF7 to be set for Tx

     GPIOA->AFR[1]  &=~(1U<<11);
     GPIOA->AFR[1] |=(1U<<10);
     GPIOA->AFR[1] |=(1U<<9);
     GPIOA->AFR[1] |=(1U<<8);
 	/* Enable clock to UART1*/
     RCC->APB2ENR |= UART1EN;

     USART1->CR1 &= ~CR1_UE;
  	/*Set baudrate*/

     slave_uart_set_baudrate(APB2_CLK , DBG_UART_BAUDRATE);
   	/*Transfer Direction*/
     USART1->CR1 = CR1_TE|CR1_RE;
     // Enable NVIC USART1_IRQn
     NVIC_EnableIRQ(USART1_IRQn);

    	/*Enable*/

     USART1->CR1 |= CR1_UE;

}


static void uart_write(int ch){
	/* make sure empty*/
	while(!(USART1->SR & SR_TXE)){}
		USART1->DR= (ch & 0xFF);

}


static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate){


	return ((periph_clk + (baudrate/2U))/baudrate);

}
static void slave_uart_write(int ch){
	/* make sure empty*/
	while(!(USART1->SR & SR_TXE)){}

	USART1->DR=(ch & 0xFF);

}

static uint16_t uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate){
	/*Clock set to 16MHz*/

	USART2->BRR = compute_uart_bd(periph_clk,baudrate);


}
static uint16_t slave_uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate){
	/*Clock set to 16MHz*/

	USART1->BRR = compute_uart_bd(periph_clk,baudrate);


}
