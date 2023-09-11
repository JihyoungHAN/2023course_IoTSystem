#include <wiringPi.h>

#define PIN_INA 26
#define PIN_INB 23

int DCmotor(int arg){

        pinMode(PIN_INA,OUTPUT);
        pinMode(PIN_INB,OUTPUT);
        
        if(arg == 0) // open the window 
		{	digitalWrite(PIN_INA,HIGH);
			delay(2000);
			digitalWrite(PIN_INA,LOW);
		}
		else if(arg == 1) // close the window 
		{	digitalWrite(PIN_INB,HIGH);
			delay(2000);
			digitalWrite(PIN_INB,LOW);
		}	
}
		
        
        
