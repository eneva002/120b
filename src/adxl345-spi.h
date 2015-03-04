#ifndef _ADXL345_H_
#define _ADXL345_H_

/*
 *  This library is intended for use with the adafruit ADXL345 Digital
 *  Accelerometer in conjunction with the atmega1284
 */


//TODO - rewrite timer to handle multiple bits
//handle the interrupt
//define protocol as described in adxl documentation

void spiInit(){
  void SPI_MasterInit(void)
  {
    //set MOSI (B5) to output
    //set SCK (B7) to output
    DDRB = (1<<5)|(1<<7);

    /* 
     * Enable SPI (SPE == 1) 
     * set as Master (MSTR == 1) 
     * set clock rate based on prescaler 
     * clock rate == fck/16 (SPR1 == 0, SPR0 == 1)
     * enable interrupgs (SPIE)
     */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);

    sei();
  }

  void SPI_Transmit(unsigned char cData)
  {
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
  }

  unsigned char SPI_Receive(){
    //wait for transmission complete
    while(!(SPSR & (1<<SPIF)));
    //return data
    return SPDR;
  }
}

#endif
