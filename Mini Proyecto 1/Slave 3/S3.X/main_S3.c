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

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ADC.h"
#include "SPI.h"

//----------------  -----Variables, valores y banderas--------------------------
#define _XTAL_FREQ 8000000

void Setup(void);
void __interrupt() ISR(void);

char TEMP;
unsigned char FLG0;
//------------------------------Prototipos--------------------------------------


//------------------------Configuracion de puertos-----------------------------

void Setup(void) {
    //Configuracion de puertos analogicos
    ANSEL = 0b00000001;
    ANSELH = 0x00;
    //Seteo de puertos como entrada y salida
    TRISA = 0x01;
    TRISD = 0x00;
    //Limpiar puertos 
    PORTA = 0x00;
    PORTD = 0x00;
    //Habilitacion del ADC
    ADCON0 = 0b01000001;
    OPTION_REG = 0x87;
    INTCON = 0xE8;
    TMR0 = 15;
    //Habilitar interrupciones de puerto B para pushes
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
        SPI_IDLE_2_ACTIVE);
}

void __interrupt() ISR(void) {
        if (INTCONbits.T0IF == 1) {
        TMR0 = 15;
        //Se apaga la bandera del timer 0
        INTCONbits.T0IF = 0;
    }
    //-------------------------Interrupcion ADC-------------------------------------
    if (PIR1bits.ADIF == 1) {
        TEMP = ADRESH;
        PIR1bits.ADIF = 0;
    }
    if(SSPIF==1){
        spiWrite(TEMP);
        SSPIF = 0;
    }
}

void main(void) {
    Setup();
    FLG0=1;
    while (1) {
        ADC(FLG0);
        if (TEMP<=12){
            PORTD = 0x01;
        }else if(12<=TEMP & TEMP<=18){
            PORTD = 0x02;
        }else{
            PORTD = 0x04;
        }
    }
}
