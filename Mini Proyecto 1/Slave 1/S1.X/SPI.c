//Libreria extraida de https://electrosome.com/spi-pic-microcontroller-mplab-xc8/
//SPI Communication with PIC Microcontroller – MPLAB XC8 por Ligo George

#include "SPI.h"

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
  TRISC5 = 0;
  if(sType & 0b00000100) //If Slave Mode
  {
    SSPSTAT = sTransmitEdge;
    TRISC3 = 1;
  }
  else //If Master Mode
  {
    SSPSTAT = sDataSample | sTransmitEdge;
    TRISC3 = 0;
  }
  SSPCON = sType | sClockIdle;
}

// Funcion Wait
static void spiReceiveWait()
{
  while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
}

//Funcion Write
void spiWrite(char dat) //Write data to SPI bus
{
  SSPBUF = dat;
}

//Funcion Data Ready
unsigned spiDataReady() //Check whether the data is ready to read
{
  if(SSPSTATbits.BF)
    return 1;
  else
    return 0;
}

//Funcion Read
char spiRead()    // Read the received data
{
  spiReceiveWait();      // Wait until all bits receive
  return(SSPBUF); // Read the received data from the buffer
}