#include <wiringPi.h>
#include <stdio.h>

#define TOUCH 6

void t_edge_rise(void);
void t_edge_fall(void);

int t_value;

int touch(void){
	
		printf("If you want, please touch the sensor\n");
		
		t_value = 0;
		
        if(wiringPiSetup() == -1) return 1;
        pinMode(TOUCH,INPUT);
	
		wiringPiISR(TOUCH, INT_EDGE_RISING, t_edge_rise);
		delay(2000); //3s
		printf("touch value: %d\n", t_value);
		return(t_value);
}

void t_edge_rise(void){
	t_value = 1;
	wiringPiISR(TOUCH, INT_EDGE_FALLING, t_edge_fall);
	//printf("Touch!\n");
}

void t_edge_fall(void){
	t_value = 1;
	wiringPiISR(TOUCH, INT_EDGE_RISING, t_edge_rise);
	//printf("Touch! Touch!\n");
}
