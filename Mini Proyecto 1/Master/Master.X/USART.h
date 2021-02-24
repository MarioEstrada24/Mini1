//Prototipos del archivo USART.c
#ifndef USART_H
#define	USART_H

#include <xc.h> 
#include <stdint.h>

uint8_t USART_Read();
void USART_Write_String(char *a);
void USART_Write(uint8_t a);

#endif	

