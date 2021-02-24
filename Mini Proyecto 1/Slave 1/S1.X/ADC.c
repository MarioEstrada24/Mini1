#include <xc.h>
#define _XTAL_FREQ 8000000
void ADC(unsigned char FLG0) {
    //Se configura la interrupcion del ADC y se justifican los bits a la izquierda
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    ADCON1bits.ADFM = 0;
    
    //Al encender la bandera se tiene un delay para tener completa la conversion ADC y se vuelve a apagar
    if(FLG0 == 1){
        __delay_us(20);
        ADCON0bits.GO = 1;
        FLG0 = 0;
    }
}