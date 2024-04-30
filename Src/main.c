#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor.h"
#include "../Include/sensor.h"
#include "../Include/delay.h"
#include "../Include/globals.h"
#include "../Include/oled.h"
volatile int rightSensorVal;
volatile int leftSensorVal;
volatile int middleSensorVal;
volatile int i;
int main(void){
  
	initMotors();
	initSensors();
	//initOled();
	
	
	while(1){
		
		//0 is black 1 is white
		leftSensorVal = pulseLeftSensor();
		rightSensorVal = pulseRightSensor();	
		middleSensorVal = pulseMiddleSensor();
		
		//setRightPWMForward(0.5);
		//setLeftPWMForward(0.5);
		
		setRightPWMBackward(0.5);
		setLeftPWMBackward(0.5);
		
		/*
		//if black on left
		if(!leftSensorVal && rightSensorVal){
			setLeftPWM(0);
			setRightPWM(.6);
			//updateOled("0     1");
			delayMs(10);
		}
		//if black on right
		if(leftSensorVal && !rightSensorVal){
			setLeftPWM(.6);
			setRightPWM(0);
			//updateOled("1     0");
			delayMs(10);
		}
		//if both white go forward
		if((!middleSensorVal && rightSensorVal && leftSensorVal)||(!middleSensorVal && !rightSensorVal && !leftSensorVal)){
			setLeftPWM(.6);
			setRightPWM(.6);
			//updateOled("0     0");
			delayMs(10);
		}
		if((middleSensorVal && rightSensorVal && !leftSensorVal)){
			setLeftPWM(0);
			setRightPWM(.6);
			//updateOled("0     1");
			delayMs(10);
		}
		if((middleSensorVal && !rightSensorVal && leftSensorVal)){
			setLeftPWM(0.6);
			setRightPWM(0);
			//updateOled("1     0");
			delayMs(10);
		}
		if((!middleSensorVal && !rightSensorVal && leftSensorVal)){
			setLeftPWM(0.6);
			setRightPWM(0.6);
			//updateOled("1     0");
			delayMs(10);
		}
		if((!middleSensorVal && rightSensorVal && !leftSensorVal)){
			setLeftPWM(0.6);
			setRightPWM(0.6);
			//updateOled("0     1");
			delayMs(10);
		}*/
	}
}


