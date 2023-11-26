#include "circular_buffer.h"

#define CR1_RXNEIE (1U<<5)
#define CR1_TXEIE (1U<<7)

#define SR1_RXNE (1U<<5)
#define SR1_TXE (1U<<7)

portType  debug_port =0;
portType slave_devPort=1;

//Slave buffer//
circular_buffer  rx_buffer1 = {{INIT_VAL}, INIT_VAL, INIT_VAL};
circular_buffer  tx_buffer1 = {{INIT_VAL}, INIT_VAL, INIT_VAL};


//Debug buffer
circular_buffer rx_buffer2={{INIT_VAL},INIT_VAL,INIT_VAL};
circular_buffer tx_buffer2={{INIT_VAL},INIT_VAL,INIT_VAL};

circular_buffer *_rx_buffer1;
circular_buffer *_tx_buffer1;

circular_buffer *_rx_buffer2;
circular_buffer *_tx_buffer2;
void circular_buffer_init(void){

	//Init buff pointers
	_rx_buffer1 = &rx_buffer1;
	_tx_buffer1 = &rx_buffer2;

	_tx_buffer1 = &tx_buffer1;
	_tx_buffer2 = &tx_buffer2;
   //initial RX interrupt
    USART1->CR1 |=CR1_RXNEIE;
    USART2->CR1 |=CR1_RXNEIE;

}

static void buff_store_char(unsigned char c, circular_buffer *buffer)
{
	int loc;
	 loc = (uint32_t)(buffer->head + 1 )% UART_BUFFER_SIZE;
	if(loc != buffer->tail)
	{
    buffer->buffer[buffer->head]=c;
    buffer->head = loc;
	}
}

void buffer_clear(portType uart){
    switch(uart)
    {
    case SLAVE_DEV_PORT:

		memset(_rx_buffer1->buffer,'\0',UART_BUFFER_SIZE);
		_rx_buffer1->head=0;
	     break;
		case DEBUG_PORT:

			memset(_rx_buffer2->buffer,'\0',UART_BUFFER_SIZE);
			_rx_buffer2->head=0;
		break;

   }
}


int buffer_peek(portType uart){

	switch(uart){

	case SLAVE_DEV_PORT:

           if(_rx_buffer1->head ==_rx_buffer1->tail){


        	   return -1;
           }
           else
           {
        	   return _rx_buffer1->buffer[_rx_buffer1->tail];
           }
           break;
	case DEBUG_PORT:

           if(_rx_buffer2->head ==_rx_buffer2->tail){


        	   return -1;
           }
           else
           {
        	   return _rx_buffer2->buffer[_rx_buffer2->tail];
           }
           break;
	 default:

		       return -1;

	}
 }


int buffer_read(portType uart)
{
	int ret;
     switch(uart){
 	case SLAVE_DEV_PORT:

	           if(_rx_buffer1->head ==_rx_buffer1->tail)
	           {


	        	   return -1;
	           }
	           else
	           {
                unsigned char c= _rx_buffer1->buffer [_rx_buffer1->tail];
                _rx_buffer1->tail =(uint32_t)(_rx_buffer1->tail+1)%UART_BUFFER_SIZE;
                ret= c;
	           }
		       break;
 	case DEBUG_PORT:
		           if(_rx_buffer2->head ==_rx_buffer2->tail)
		           {


		        	   return -1;
		           }
		           else
		           {
	                unsigned char c= _rx_buffer2->buffer [_rx_buffer2->tail];
	                _rx_buffer2->tail =(uint32_t)(_rx_buffer2->tail+1) % UART_BUFFER_SIZE;
	                ret = c;
		           }
			     break;
 	default:
		ret = -1;
	    break;

     }
   return ret;
}


void buffer_write(unsigned char c ,  portType uart)
{
	int loc=0;
	switch(uart)
	{
	case SLAVE_DEV_PORT:
		 loc =(uint32_t)(_tx_buffer1->head + 1 )% UART_BUFFER_SIZE;
		while (loc == _tx_buffer1->tail ){}
		_tx_buffer1->buffer[_tx_buffer1->head]=c;
		_tx_buffer1->head=loc;

		   USART1->CR1 |=CR1_TXEIE;
		  // USART1->DR=c;
			break;
	case DEBUG_PORT:
		 loc =(uint32_t)( _tx_buffer2->head + 1 )% UART_BUFFER_SIZE;
		while (loc == _tx_buffer2->tail ){}
		_tx_buffer2->buffer[_tx_buffer2->head]=c;
		_tx_buffer2->head=loc;
		   USART2->CR1 |=CR1_TXEIE;
	break;

	default:
		break;
	}

}
void buffer_send_byte(const uint8_t *data, int length, portType uart)
{


	for(int i=0;i<length; ++i)
	{
		buffer_write(data[i],uart);
	}
}

int is_data( portType uart){
	int ret;

	switch(uart){

	case SLAVE_DEV_PORT:
		ret=	(uint32_t)(UART_BUFFER_SIZE+_rx_buffer1->head-_rx_buffer1->tail)%UART_BUFFER_SIZE;
		break;
	case DEBUG_PORT:
		ret =	(uint32_t)(UART_BUFFER_SIZE+_rx_buffer2->head-_rx_buffer2->tail)%UART_BUFFER_SIZE;
			break;

		return ret;
}
}
static void get_first_char(char *str){

	 while(!is_data(SLAVE_DEV_PORT)){}

	while(buffer_peek(SLAVE_DEV_PORT)!=str[0])
	{
		_rx_buffer1->tail=(uint16_t)(_rx_buffer1->tail+1)%UART_BUFFER_SIZE;
		while (!is_data(SLAVE_DEV_PORT)){}

	}

}

int is_response(char *str)
{
	int curr_pos =0;
	int len=strlen(str);

	while(curr_pos !=len){
		curr_pos=0;
		get_first_char(str);
	while (buffer_peek(SLAVE_DEV_PORT)==str[curr_pos])
	{

		curr_pos++;
		buffer_read(SLAVE_DEV_PORT);
		if (curr_pos !=len)
		{
			return 1 ;

		}

	}

		while(!is_data(SLAVE_DEV_PORT)){}
	}
	return -1;
}
void get_string(uint8_t num_of_chars, char *dest_buffer)
{

	int indx;
	for(indx=0; indx<num_of_chars; indx++)
	{
		for(int i=0; i<9000; i++){}
		dest_buffer[indx] = buffer_read(SLAVE_DEV_PORT);


	}





}


void buffer_send_string(const char *s , portType uart)
{
	while(*s !='\0'){
		buffer_write(*s++,uart);

	}

}


void slave_dev_uart_callback(void)
{
	if(((USART1->SR & SR1_RXNE) !=0) && ((USART1->CR1 & CR1_RXNEIE)!=0))
		{
		unsigned char c = USART1->DR;
		buff_store_char (c,_rx_buffer1);

	    }
	if(((USART1->SR & SR1_TXE) !=0) && ((USART1->CR1 & CR1_TXEIE)!=0)){

		if (tx_buffer1.head== tx_buffer1.tail )
		{
			USART1->CR1 &= ~CR1_TXEIE;

		}
		else{
			unsigned char c = tx_buffer1.buffer[tx_buffer1.tail];
			tx_buffer1.tail=(uint32_t)(tx_buffer1.tail+1)% UART_BUFFER_SIZE;
			USART1->DR=c;
		}
	}


}




void debug_uart_callback(void)
{
	if(((USART2->SR & SR1_RXNE) !=0) && ((USART2->CR1 & CR1_RXNEIE)!=0))
		{
		unsigned char c = USART2->DR;
		buff_store_char (c,_rx_buffer2);

	    }
	if(((USART2->SR & SR1_TXE) !=0) && ((USART2->CR1 & CR1_TXEIE)!=0)){

		if (tx_buffer2.head== tx_buffer2.tail )
		{
			USART2->CR1 &= ~CR1_TXEIE;

		}
		else{
			unsigned char c = tx_buffer2.buffer[tx_buffer2.tail];
			tx_buffer2.tail=(uint32_t)(tx_buffer2.tail+1)%UART_BUFFER_SIZE;
			USART2->DR=c;
		}
	}


}



void USART2_IRQHandler (void){
	debug_uart_callback();


}
void USART1_IRQHandler (void){
	slave_dev_uart_callback();


}
