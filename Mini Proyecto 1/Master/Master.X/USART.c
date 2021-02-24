//Libreria extraida de: https://electrosome.com/uart-pic-microcontroller-mplab-xc8/
//Using UART of PIC microcontroller by Ligo George
#include <xc.h>
#include <pic16f887.h>
#include "USART.h"

void USART_Write(uint8_t a){
    while(!TRMT);
    TXREG=a;
}
void USART_Write_String(char *a){
    uint8_t i;
    for(i=0;a[i]!='\0';i++){
        USART_Write(a[i]);
    }
}
uint8_t USART_Read(){
  while(!RCIF);
  return RCREG;
} 