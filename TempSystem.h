#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include "calcTemp.h"
#include "SMART_TOUCH.h"


#define G 0
#define B 1

int t_mode; 
 
int touch_value; 
int carMode; 

void aircon(void);
void heater(void);


int TempSystem(int arg){
	
	if(wiringPiSetup() == -1) return 1;
	
	int carMode = arg;
	
	float curTemp; // current temparature

	if(carMode == 10) // parking mode 
	{
		curTemp = calcTemp();
		printf("Current temperatur is %f.\n", curTemp); 

		if ( curTemp >= 21 && curTemp <= 23) // proper temparature is between 21 and 23. 
		{
			printf("The temperature in the car is proper.\n"); 
			return(0);
		}
		else if (curTemp > 23) 
		{
			printf("The temparture in the car is high.\n");
			printf("The air conditional will be turned on.\n");
			aircon();
		}
		else if (curTemp < 21)
		{
			printf("The temprature in the car is low.\n");
			printf("The heater will be turned on.\n");
			heater();
		}
	 }
	 
	 else if(carMode == 11) //driving mode 
	{  
		touch_value = 0;
		while(0){ 
			curTemp = calcTemp();
			if (curTemp > 23 || curTemp < 21) break; 
		}
		printf("Current temperature is %f.\n", curTemp);
		if(curTemp > 23)
		{
			printf("Do you want to turn on the air conditional?\n");
			touch_value = touch();
			if(touch_value == 1)
			{
				printf("Airconditional is running\n");
				aircon();
			}
		}
		else if(curTemp < 21)
		{
			printf("Do you want to turn on the heater?\n");
			touch_value = touch();
			printf("%d\n", touch_value);
			if(touch_value == 1)
			{	
				printf("Heater is running\n");
				heater();
			}
		}
	}	
 }
 
void aircon(void){
	 pinMode(B, OUTPUT);
	 digitalWrite(B, HIGH);
	 delay(3000);
	 digitalWrite(B,LOW);
}

void heater(void){
	pinMode(G, OUTPUT);
	digitalWrite(G, HIGH);
	delay(3000);
	digitalWrite(G, LOW);
}


		
        
