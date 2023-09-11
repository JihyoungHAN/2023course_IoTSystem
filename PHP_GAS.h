#include <stdio.h>
#include <wiringPi.h>

#define G_SPI_CH 0
#define G_ADC_CH 4
#define G_ADC_CS 29
#define SPI_SPEED 500000

int gas(void){
        int value=0, i;
        unsigned char buf[3];

        pinMode(G_ADC_CS,OUTPUT);
        
        while(1){
			buf[0] = 0x06 | ((G_ADC_CH & 0x04)>>2);
			buf[1] = ((G_ADC_CH & 0x03)<<6);
			buf[2] = 0x00;

			digitalWrite(G_ADC_CS,0);

			wiringPiSPIDataRW(G_SPI_CH,buf,3);

			buf[1]=0x0F & buf[1];

			value=(buf[1] << 8) | buf[2];

			digitalWrite(G_ADC_CS,1);
			
			return(value); 

		}
		
}
