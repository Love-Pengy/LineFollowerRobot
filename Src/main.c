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

		
		//if black on left
		if(!leftSensorVal && rightSensorVal){
			setLeftPWMForward(0);
			setRightPWMForward(0.5);
			//updateOled("0     1");
			delayMs(DELAY_VAL);
		}
		//if black on right
		if(leftSensorVal && !rightSensorVal){
			setLeftPWMForward(.5);
			setRightPWMForward(0);
			//updateOled("1     0");
			delayMs(DELAY_VAL);
		}
		//if both white go forward
		if((!middleSensorVal && rightSensorVal && leftSensorVal)||(!middleSensorVal && !rightSensorVal && !leftSensorVal)){
			setLeftPWMForward(.5);
			setRightPWMForward(.5);
			//updateOled("0     0");
			delayMs(DELAY_VAL);
		}
		if((middleSensorVal && rightSensorVal && !leftSensorVal)){
			setLeftPWMForward(0);
			setRightPWMForward(.5);
			//updateOled("0     1");
			delayMs(DELAY_VAL);
		}
		if((middleSensorVal && !rightSensorVal && leftSensorVal)){
			setLeftPWMForward(0.5);
			setRightPWMForward(0);
			//updateOled("1     0");
			delayMs(DELAY_VAL);
		}
		if((!middleSensorVal && !rightSensorVal && leftSensorVal)){
			setLeftPWMForward(0.5);
			setRightPWMForward(0.5);
			//updateOled("1     0");
			delayMs(DELAY_VAL);
		}
		if((!middleSensorVal && rightSensorVal && !leftSensorVal)){
			setLeftPWMForward(0.5);
			setRightPWMForward(0.5);
			//updateOled("0     1");
			delayMs(DELAY_VAL);
		}
	}
}


