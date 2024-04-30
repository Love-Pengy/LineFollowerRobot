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
	#define DELAY_VAL 0
	
	//speed value for motors
	#define SPEED_VAL .35
	
	
//pin defs
	//PIN PB1 uses Timer 3 Channel 4: Front RIGHT MOTOR
	#define FTIM3_PIN 1
	
	//PIN PB0 uses Timer 3 Channel 3: Back RIGHT MOTOR
	#define BTIM3_PIN 0
	
	//PIN PB7 uses Timer 4 Channel 2: Front LEFT MOTOR
	#define FTIM4_PIN 7
	
	//PIN PB6 uses Timer 4 Channel 1: Back LEFT MOTOR
	#define BTIM4_PIN 6
	
	//these sensor pins are in places to try to make it easier for wiring they can be changed
	
	//left sensor pin PC10
	#define LEFT_SENSOR_PIN 10
	
	//right sensor pin PC8 
	#define RIGHT_SENSOR_PIN 8
	
	//middle sensor pin PC11 
	#define MIDDLE_SENSOR_PIN 11
#endif
