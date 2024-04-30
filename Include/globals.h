#ifndef GLOBALS_H
#define GLOBALS_H

//gen defs
	//TIM4 = motor left
	//TIM3 = motor right
	//TIM2 = delay timer 

	//this must be calibrated 
	#define SENSOR_PULSE_THRESHOLD_RIGHT 500
	#define SENSOR_PULSE_THRESHOLD_LEFT 500
		#define SENSOR_PULSE_THRESHOLD_MIDDLE 500
	//delay between motor pulses
	#define DELAY_VAL 1000

//pin defs
	//front right motor PB1 
	#define FTIM3_PIN 1
	
	//back right motor PB0
	#define BTIM3_PIN 0
	
	//front left motor PB7
	#define FTIM4_PIN 7
	
	//back right motor PB6 
	#define BTIM4_PIN 6
	
	//these sensor pins are in places to try to make it easier for wiring they can be changed
	
	//left sensor pin PC10
	#define LEFT_SENSOR_PIN 10
	
	//right sensor pin PC8 
	#define RIGHT_SENSOR_PIN 8
	
	//middle sensor pin PC11 
	#define MIDDLE_SENSOR_PIN 11
#endif
