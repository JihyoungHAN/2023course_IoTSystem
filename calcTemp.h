#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>

#define MAX_TIME 100
#define TEMP 25

int val[5] = {0,0,0,0,0};

float calcTemp(void){
		int currentTemp;
        uint8_t lststate = 1;
        uint8_t cnt = 0;
        uint8_t j=0,i;

        pinMode(TEMP,OUTPUT);

        digitalWrite(TEMP,LOW);
        delay(18);
        digitalWrite(TEMP,HIGH);
        delayMicroseconds(40);
        pinMode(TEMP,INPUT);

        for(i=0;i<MAX_TIME;i++){
                cnt=0;

                while(digitalRead(TEMP) == lststate){
                        cnt++;
                        delayMicroseconds(1);
                        if(cnt == 255) break;
                }

                lststate = digitalRead(TEMP);

                if(cnt == 255) break;

                if((i>=4) && (i%2==0)){
                        val[j/8]<<=1;
                        if(cnt>16) val[j/8]|=1;
                        j++;
                }
        }
        //printf("current temp is %d.%d *C\n", val[2], val[3]);
        currentTemp = val[2] + val[3]*0.1;
		return(currentTemp);
}
