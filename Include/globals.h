#ifndef GLOBALS_H
#define GLOBALS_H

//gen defs
	//TIM4 = motor left
	//TIM3 = motor right
	//TIM2 = delay timer 

	//this must be calibrated 
	#define SENSOR_PULSE_THRESHOLD_RIGHT 200
	#define SENSOR_PULSE_THRESHOLD_LEFT 200
	//delay between motor pulses
	#define DELAY_VAL 1000

//pin defs
	//right motor PA3 
	#define TIM3_PIN 1
	
	//left motor PB9
	#define TIM4_PIN 9
	
	//these sensor pins are in places to try to make it easier for wiring they can be changed
	
	//left sensor pin PC10
	#define LEFT_SENSOR_PIN 10
	
	//right sensor pin PC8 
	#define RIGHT_SENSOR_PIN 8
	
#endif
