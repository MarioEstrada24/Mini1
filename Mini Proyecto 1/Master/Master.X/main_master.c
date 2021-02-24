
//-------------------------Configuracion inicial--------------------------------
#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

//-------------------------Librerias--------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f887.h>
#include "LCD.h"
#include "USART.h"
#include "SPI.h"
#define _XTAL_FREQ 4000000

//-------------------------Funciones y variables--------------------------------
void setup(void);
uint8_t cont0=0;
char V_ADC;
float TEMP;
char LEDS;
char data[20];

void setup(void);
void Slave1(void);
void Slave2(void);
float Slave3(void);
//-----------------------------Setup--------------------------------------------
void setup(){
    //Indicamos entradas analogicas
    ANSEL=0;
    ANSELH=0;
    //Definimos entradas y salidas
    TRISA=0x00;
    TRISB=0x00;
    TRISD=0x00;
    TRISE=0x00;
    TRISC=0;

    //Limpiamos los puertos
    PORTA=0;
    PORTB=0;
    PORTD=0;
    PORTE=0;
    PORTCbits.RC0=1;
    PORTCbits.RC1=1;
    PORTCbits.RC2=1;
    PORTCbits.RC7=1;
    //Configuramos las interrupciones generales del sistema
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    PIE1bits.RCIE=1;
    PIR1bits.RCIF=0;
    TXSTAbits.CSRC = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 0;
    TXSTAbits.TRMT = 0;
    TXSTAbits.TX9D = 0;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.SREN = 0;
    RCSTAbits.CREN = 1;
    RCREG = 0;  

}
//------------------------------Interrupciones----------------------------------

void Slave1(void){
    PORTCbits.RC0 = 0
    spiWrite(1);;       
    __delay_ms(1);
    spiWrite(1);
    //Tomamos la variable V_ADC y la colocamos en el spi read
    V_ADC = spiRead();
    __delay_ms(1);
    PORTCbits.RC0 = 1;      
    __delay_ms(1);
}    
    
void Slave2(void){
    PORTCbits.RC1 = 0;
    __delay_ms(1);
    spiWrite(1);
    //Tomamos la variable LEDS y la colocamos en el spi read
    LEDS = spiRead();
    __delay_ms(1);
    PORTCbits.RC1 = 1; 
    __delay_ms(1);
}   

float Slave3(void){
    PORTCbits.RC2 = 0;
    __delay_ms(1);   
    spiWrite(1);
    //Tomamos la variable TEMP y la colocamos en el spi read
    TEMP = spiRead();
    __delay_ms(1);
    PORTCbits.RC2 = 1; 
    __delay_ms(1);
    return TEMP;
}

//---------------------------------Codigo Principal----------------------------
void main(void){
    setup();
    LCD_Init();
    LCD_clear();
    while(1){
        Slave1();
        Slave2();
        Slave3();
        
        USART_Write_String("S1:    S2:    S3:");
        USART_Write(13);
        USART_Write(10);
        USART_Write_String(data);
        USART_Write(13);
        USART_Write(10);
        __delay_ms(500);
        
        LCD_clear();
        LCD_Cursor(1,1);
        LCD_Texto("S1:    S2:    S3:");
        TEMP = Slave3();
        sprintf(data, "%1.0f   %d   %3.0f" ,V_ADC,LEDS,TEMP);
        LCD_Cursor(2,1);
        LCD_Texto(data);
        

    }
}

