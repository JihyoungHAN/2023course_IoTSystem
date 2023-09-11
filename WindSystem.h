#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include "PHP_DUST.h"
#include "PHP_GAS.h"
#include "SMART_SWITCH.h"
#include "SMART_DCMOTOR.h"


#define R 27
#define REED 9
#define PIR 2
#define BUZ 15

//void sf_edge_rise(void);
//void sf_edge_fall(void);

int winOpen(void);
void* waitThread(void *argu);
void* safetyThread(void *argu); 


int cancle = 0;
int w_stop;
    



int WindSystem(void){
	
	if(wiringPiSetup() == -1) return 1;
	if(wiringPiSPISetup() == -1) return -1;
	
	int gasValue=0;
	int dustValue=0;
			
	gasValue = gas();
	dustValue = dust();
	if (gasValue >=100 || dustValue > 10) // Atmosphere in the car is bad
	{ 
		printf("gas: %d, dust: %d\n", gasValue, dustValue);
		printf("---------------------------------------------\n");
		delay(1000); // 3s
		winOpen();
	}
	digitalWrite(R, LOW);
	
}


int winOpen(void){
	int open = 0;
	int safe = 0; 
	int reed = 1;
	int i; 

 

		pinMode(R,OUTPUT);
		digitalWrite(R,HIGH);
		
        pinMode(REED,INPUT);
        reed = digitalRead(REED);
        if(reed == 0) // checking windows are open (0 : close, 1: open)  
        {
			printf("Door is closed\n");
			printf("Do you want to open the windows?\n");
			open = Switch(); // 1 : accept, 0 : no 
			printf("open num: %d\n", open);
			printf("-------------------------------------------\n");
			delay(1000); //3s
			
			printf("Do you want to run [safety mode]?\n");
			safe = Switch(); // 1: accept, 0 : no
			printf("safety num: %d\n", safe);
			delay(1000); //3s
			
			if(open == 1 && safe == 1){
				printf("open the window\n");
				DCmotor(0); // DCmotor(0) : open the window, DCmotor(1) : close the window  
				pthread_t wait_id;
				pthread_create(&wait_id, NULL, waitThread, NULL);
				pthread_t safety_id;
				pthread_create(&safety_id, NULL, safetyThread, NULL);
				pthread_join(wait_id, NULL); 
				cancle = 1; 
				printf("close the window\n");
				DCmotor(1); // close the window
				pthread_join(safety_id, NULL); 
				printf("safety mode turns off\n");
			}
			else if(open == 1 && safe == 0){
				printf("open the window\n");
				DCmotor(0); // DCmotor(0) : open the window, DCmotor(1) : close the window  
				pthread_t wait_id;
				pthread_create(&wait_id, NULL, waitThread, NULL);
				pthread_join(wait_id, NULL); 
				printf("close the window\n");
				DCmotor(1); // close the window
			}
			
		}
		else if (reed == 1){ // windows are open, don't need to open the window 
			printf("Door is open\n");
			delay(5000); // 10s 
		}
		
}

void* waitThread(void *argu){
	printf("waitThread is running\n");
	int gas_value, dust_value;
	
	while(1){
		delay(5000); //3s
		gas_value = gas();
		dust_value = dust();
		printf("gas: %d, dust: %d\n", gas_value, dust_value);
		if(gas_value < 400 && dust_value < 3000) // Atmosphere in the car is clean now 
		{
			printf("gas: %d, dust: %d\n", gas_value, dust_value);
			printf("turn off the light\n");
			digitalWrite(R, LOW); 
			break;
		}
	} 
}

void* safetyThread(void *argu){
	printf("safety mode turns on\n");
	pinMode(PIR, INPUT);
	pinMode(PIR, OUTPUT);
	//wiringPiISR(PIR, INT_EDGE_RISING, sf_edge_rise);
	while(cancle == 0){
		if(digitalRead(PIR) == 1){
			digitalWrite(BUZ, HIGH);
			delay(2000);
			digitalWrite(BUZ, LOW);
		}
	}
	printf("safetyThread is discared\n");
}

/*void sf_edge_rise(void){
	pinMode(BUZ, OUTPUT);
	digitalWrite(BUZ, HIGH);
	printf("WARNING!! Don't stick your body out the window!\n");
	delay(1000); // Buzzer is ringing for 2 second. 
	if (cancle == 0) {
		wiringPiISR(PIR, INT_EDGE_FALLING, sf_edge_fall);
	}		
	digitalWrite(BUZ, LOW);

} 
	

void sf_edge_fall(void){
	pinMode(BUZ, OUTPUT);
	digitalWrite(BUZ, LOW);
	delay(1000);
	if(cancle == 0){
	wiringPiISR(PIR, INT_EDGE_RISING, sf_edge_rise);
	}
	digitalWrite(BUZ, LOW);

}*/




