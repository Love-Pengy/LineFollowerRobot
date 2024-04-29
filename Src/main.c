#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor.h"
#include "../Include/sensor.h"
#include "../Include/delay.h"
#include "../Include/globals.h"

volatile int rightSensorVal;
volatile int leftSensorVal;
volatile int middleSensorVal;
volatile int i;
int main(void){
  
	initMotors();
	initSensors();
	
	while(1){
		leftSensorVal = pulseLeftSensor();
		rightSensorVal = pulseRightSensor();	
		middleSensorVal = pulseMiddleSensor();

		//if black on left
		if(!leftSensorVal && rightSensorVal){
			setLeftPWM(0);
			setRightPWM(.4);
			delayMs(25);
		}
		//if black on right
		if(leftSensorVal && !rightSensorVal){
			setLeftPWM(.4);
			setRightPWM(0);
			delayMs(25);
		}
		//if both white go forward
		if((!middleSensorVal && rightSensorVal && leftSensorVal)||(!middleSensorVal && !rightSensorVal && !leftSensorVal)){
			setLeftPWM(.4);
			setRightPWM(.4);
		}
	}
}


