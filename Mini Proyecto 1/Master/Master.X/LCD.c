/* 
 * File:   LCD.c
 * Author: Mario Andres
 *
 * Created on 7 de febrero de 2021, 10:47 PM
 */

#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#define _XTAL_FREQ 8000000

void Pines(uint8_t x){
	if(x & 1){D0 = 1;}else{D0 = 0;}
    if(x & 2){D1 = 1;}else{D1 = 0;}
    if(x & 4){D2 = 1;}else{D2 = 0;}
    if(x & 8){D3 = 1;}else{D3 = 0;}
    if(x & 16){D4 = 1;}else{D4 = 0;}
    if(x & 32){D5 = 1;}else{D5 = 0;}
    if(x & 64){D6 = 1;}else{D6 = 0;}
    if(x & 128){D7 = 1;}else{D7 = 0;}
}

void LCD_Caracter(char a){
    Reset = 1;
    Pines(a);
    Enable = 1;
    __delay_us(5);
    Enable = 0;
    __delay_us(5);
    __delay_us(50);
}
void LCD_Comandos(uint8_t x){
    Reset = 0;
    Pines(x);
    Enable = 1;
    __delay_us(5);
    Enable = 0;
    __delay_us(5);
    __delay_ms(2);   
}
void LCD_clear(void){
    LCD_Comandos(0);
    LCD_Comandos(1);
}
void LCD_Init(){
    __delay_ms(20);
    LCD_Comandos (0x30);
    __delay_ms(5);
    LCD_Comandos (0x30);
    __delay_us(100);
    LCD_Comandos (0x30);
    __delay_us(100);
    LCD_Comandos (0x38);
    __delay_us(60);
    LCD_Comandos (0x08);
    __delay_us(60);
    LCD_Comandos (0x01);
    __delay_ms(5);
    LCD_Comandos (0x06);
    __delay_us(60);
    LCD_Comandos (0x0C);     
    __delay_us(60);
}
//Funcion para configurar el cursor
void LCD_Cursor(uint8_t x, uint8_t y){
	uint8_t a;
	if(x == 1){
	  a = 0x80 + y;
                       
		LCD_Comandos(a);
    }
	else if(x == 2){
	  a = 0xC0 + y;
                       
		LCD_Comandos(a);
    }
}
void LCD_Texto(char *a){
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_Caracter(a[i]);
}
