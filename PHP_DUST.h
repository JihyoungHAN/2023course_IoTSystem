#include <stdio.h>
#include <wiringPi.h>

#define D_SPI_CH 0
#define D_ADC_CH 3
#define D_ADC_CS 29
#define SPI_SPEED 500000
#define OUT 4

int dust(void){
        int value=0, i;
        unsigned char buf[3];

        pinMode(D_ADC_CS,OUTPUT);
        pinMode(OUT,OUTPUT);
        
        while(1){
			digitalWrite(OUT,LOW);
			delayMicroseconds(280);
			
			buf[0] = 0x06 | ((D_ADC_CH & 0x04)>>2);
			buf[1] = ((D_ADC_CH & 0x03)<<6);
			buf[2] = 0x00;

			digitalWrite(D_ADC_CS,0);

			wiringPiSPIDataRW(D_SPI_CH,buf,3);
	
			buf[1]=0x0F & buf[1];

			value = (buf[1]<<8) | buf[2];

			digitalWrite(D_ADC_CS,1);

			delayMicroseconds(40);
			digitalWrite(OUT,HIGH);
			delayMicroseconds(9680);
			
			return(value); 

		}
}

