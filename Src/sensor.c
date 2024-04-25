#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/globals.h"
#include "../Include/delay.h"

//counter for length of time for pulse 
static volatile int timeCounter = 0;


/*
Set sensor port to digital output ;
Set voltage high on port;
Wait for a couple clock cycles to be sure that capacitor on sensor is charged;
*/

//set to charging
void initSensors(void){
	// LEFT SENSOR PART >>>>>>>>>>>>>
	
	//enable clock 
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	//set to output 
	GPIOC->MODER &= ~(0x3 << (2*LEFT_SENSOR_PIN));
	GPIOC->MODER |= (0x1 << (2*LEFT_SENSOR_PIN));
	
	//set value to high 
	GPIOC->ODR |= (0x1 << LEFT_SENSOR_PIN);

	
	//===============================
	
	// RIGHT SENSOR PART >>>>>>>>>>>>
	
	//set to output 
	GPIOC->MODER &= ~(0x3 << (2*RIGHT_SENSOR_PIN));
	GPIOC->MODER |= (0x1 << (2*RIGHT_SENSOR_PIN));
	
	//set value to high 
	GPIOC->ODR |= (0x1 << RIGHT_SENSOR_PIN);
	
	//sanity check 
	timeCounter = 0;
	
	//let capacitor charge
	delayMs(1);
}

void chargeSensorLeft(void){
	GPIOC->MODER &= ~(0x3 << (2*LEFT_SENSOR_PIN));
	GPIOC->MODER |= (0x1 << (2*LEFT_SENSOR_PIN));
	GPIOC->ODR |= (0x1 << LEFT_SENSOR_PIN);
}

void chargeSensorRight(void){
	GPIOC->MODER &= ~(0x3 << (2*RIGHT_SENSOR_PIN));
	GPIOC->MODER |= (0x1 << (2*RIGHT_SENSOR_PIN));
	GPIOC->ODR |= (0x1 << RIGHT_SENSOR_PIN);
}

/*
Set integer variable “counter” to 0;
Set sensor port to digital input;
While (Value on digital input port is 1)
{
increment counter by 1;
}
If counter is greater than some calibrated threshold value, then the surface is black.
Otherwise, the surface is white.
*/

//returns 0 for black 1 for white 
int pulseLeftSensor(void){
	timeCounter = 0;
	
	chargeSensorLeft();
	
	//set to input
	GPIOC->MODER &= ~(0x3 << (2*LEFT_SENSOR_PIN));
	GPIOC->MODER |= (0x0 << (2*LEFT_SENSOR_PIN));
	
	while(GPIOC->IDR & (0x1 << LEFT_SENSOR_PIN)){
		timeCounter++;
	}
	
	if(timeCounter > SENSOR_PULSE_THRESHOLD_LEFT){
		return(0);
	}
	
	return(1);
}

int pulseRightSensor(void){
	timeCounter = 0;
	
	chargeSensorRight();
	
	//set to input
	GPIOC->MODER &= ~(0x3 << (2*RIGHT_SENSOR_PIN));
	GPIOC->MODER |= (0x0 << (2*RIGHT_SENSOR_PIN));
	
	while(GPIOC->IDR & (0x1 << RIGHT_SENSOR_PIN)){
		timeCounter++;
	}
	
	if(timeCounter > SENSOR_PULSE_THRESHOLD_RIGHT){
		return(0);
	}
	
	return(1);
}


