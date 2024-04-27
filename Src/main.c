#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor.h"
#include "../Include/sensor.h"
#include "../Include/delay.h"
#include "../Include/globals.h"

volatile int rightSensorVal;
volatile int leftSensorVal;
volatile int i;
int main(void){
  
	initMotors();
	initSensors();
	
	while(1){
		
		leftSensorVal = pulseLeftSensor();
		rightSensorVal = pulseRightSensor();
		

	//if both white go forward
		setLeftPWM(0.8);
		setRightPWM(0.8);
		 	//if black on left
		if(!leftSensorVal && rightSensorVal){
			setLeftPWM(0);
			setRightPWM(0.5);
		}
		
	//if black on right
		if(leftSensorVal && !rightSensorVal){
			setLeftPWM(0.5);
			setRightPWM(0);
		}
		delayMs(500);
	
/*
	//if both white go forward
		 if((rightSensorVal && leftSensorVal)){
			setLeftPWM(0.8);
			setRightPWM(0.8);
		}
		//if black on right
		if(leftSensorVal && !rightSensorVal){
			setLeftPWM(0.6);
			setRightPWM(0);
		}
			//if both white go forward
		else if((rightSensorVal && leftSensorVal)){
			setLeftPWM(0.8);
			setRightPWM(0.8);
		}
	*/
		
	}
}


