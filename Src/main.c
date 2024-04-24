#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor2.h"
#include "../Include/sensor.h"
#include "../Include/delay.h"
#include "../Include/globals.h"

volatile int d;
volatile int rightSensorVal;
volatile int leftSensorVal;
volatile int i;
int main(void){
  
	//initMotors();
	//initSensors();
	rightSensorVal = 0;
	leftSensorVal = 0;
	
	while(1);
		//setLeftPWM(.5);
		//setRightPWM(0);
		/*
		rightSensorVal = pulseRightSensor();
		leftSensorVal = pulseLeftSensor();
		//if both black or both white go forward
		if((!rightSensorVal && !leftSensorVal) || (rightSensorVal && leftSensorVal)){
			setLeftPWM(1);
			setRightPWM(1);
			delayMs(DELAY_VAL);
			setLeftPWM(0);
			setRightPWM(0);
		}
		//if black on left
		else if(!leftSensorVal && rightSensorVal){
			setRightPWM(1);
			delayMs(DELAY_VAL);
			setRightPWM(0);
		}
		//if black on right
		else if(leftSensorVal && !rightSensorVal){
			setLeftPWM(1);
			delayMs(DELAY_VAL);
			setLeftPWM(0);
		}
		else{
			//error
		}	
		
	}
	*/
	
}


