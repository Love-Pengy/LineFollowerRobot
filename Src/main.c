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
volatile int last; 
int main(void){
  
	initMotors();
	initSensors();
	//initOled();
	//0 is straight
	//1 is right
	//2 is left 
	last = 0;
	while(1){
		
		//0 is black 1 is white
		leftSensorVal = pulseLeftSensor();
		rightSensorVal = pulseRightSensor();	
		middleSensorVal = pulseMiddleSensor();

		
		//if black on left 
		if(!leftSensorVal && rightSensorVal){
			setLeftPWMForward(0);
			setRightPWMForward(SPEED_VAL);
			//updateOled("0     1");
			delayMs(DELAY_VAL);
			last = 2;
		}
		//if black on right
		if(leftSensorVal && !rightSensorVal){
			setLeftPWMForward(SPEED_VAL);
			setRightPWMForward(0);
			//updateOled("1     0");
			delayMs(DELAY_VAL);
			last = 1;
		}
		//if both white go forward
		if((!middleSensorVal && rightSensorVal && leftSensorVal)||(!middleSensorVal && !rightSensorVal && !leftSensorVal)){
			setLeftPWMForward(SPEED_VAL);
			setRightPWMForward(SPEED_VAL);
			//updateOled("0     0");
			delayMs(DELAY_VAL);
			last = 0;
		}
		if((middleSensorVal && rightSensorVal && !leftSensorVal)){
			setLeftPWMForward(0);
			setRightPWMForward(SPEED_VAL);
			//updateOled("0     1");
			delayMs(DELAY_VAL);
			last = 2;
		}
		if((middleSensorVal && !rightSensorVal && leftSensorVal)){
			setLeftPWMForward(SPEED_VAL);
			setRightPWMForward(0);
			//updateOled("1     0");
			delayMs(DELAY_VAL);
			last = 1;
		}
		if((!middleSensorVal && !rightSensorVal && leftSensorVal)){
			setLeftPWMForward(SPEED_VAL);
			setRightPWMForward(SPEED_VAL);
			//updateOled("1     0");
			delayMs(DELAY_VAL);
			last = 0;
		}
		if((!middleSensorVal && rightSensorVal && !leftSensorVal)){
			setLeftPWMForward(SPEED_VAL);
			setRightPWMForward(SPEED_VAL);
			//updateOled("0     1");
			delayMs(DELAY_VAL);
			last = 0;
		}
		/*
		if(middleSensorVal && rightSensorVal && leftSensorVal){
			switch(last){
				case 0: 
					setLeftPWMForward(.5);
					setRightPWMForward(0.5);
					break;
				case 1: 
					setLeftPWMForward(.5);
					setRightPWMForward(0);
					break;
				default: 
					setLeftPWMForward(0);
					setRightPWMForward(.5);
					break;
			}
		}
		*/

	}
}


