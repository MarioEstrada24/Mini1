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
#include "SPI.h"
#define _XTAL_FREQ 8000000

void Setup(void);
char LEDS;

//------------------------Configuracion de puertos-----------------------------
void Setup(void) {
    //Configuracion de puertos analogicos
    ANSEL = 0b00000001;
    ANSELH = 0x00;
    //Seteo de puertos como entrada y salida
    TRISB = 0x03;
    TRISD = 0x00;
    //Limpiar puertos 
    PORTB = 0x00;
    PORTD = 0x00;
    //Habilitar interrupciones de puerto B para pushes
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    INTCON = 0xE8;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
        SPI_IDLE_2_ACTIVE);
}


void main(void) {
    Setup();
    while (1) {
            if (INTCONbits.RBIF == 1) {
        if (PORTBbits.RB0 == 0) {
            LEDS++;
        } else if (PORTBbits.RB1 == 0) {
            LEDS--;
        }
        INTCONbits.RBIF = 0;
    }
    if(SSPIF==1){
        spiWrite(LEDS);
        SSPIF = 0;
    }
        PORTD = LEDS;
        }
    }
