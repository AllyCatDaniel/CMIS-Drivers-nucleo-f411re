#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H


#include "uart.h"

#include <stdio.h>
#include <string.h>
typedef enum
{
   DEBUG_PORT = 0,
   SLAVE_DEV_PORT

}portType;


#define UART_BUFFER_SIZE 100
#define INIT_VAL           0
typedef struct
{
      unsigned char buffer[UART_BUFFER_SIZE];
    __IO uint32_t head;
    __IO uint32_t tail;

}circular_buffer;
void buffer_send_string(const char *s , portType uart);
void circular_buffer_init(void);
void buffer_send_byte(const uint8_t *data, int length, portType uart);
void buffer_send_string(const char *s , portType uart);
void buffer_clear(portType uart);


#endif
