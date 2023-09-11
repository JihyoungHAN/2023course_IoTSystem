#include <wiringPi.h>
#include <stdio.h>

#define SWITCH 3

void s_edge_rise(void);
void s_edge_fall(void);
int button;

int Switch(void){
	button = 0;
	pinMode(SWITCH, INPUT);
	wiringPiISR(SWITCH, INT_EDGE_RISING, s_edge_rise);
	delay(3000); // 3s
	return(button);
}

void s_edge_rise(void){
	wiringPiISR(SWITCH, INT_EDGE_FALLING, s_edge_fall);
	button = 1;
}
void s_edge_fall(void){
	wiringPiISR(SWITCH, INT_EDGE_RISING, s_edge_rise);
	button = 1;
}
