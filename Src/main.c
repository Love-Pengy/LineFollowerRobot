#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor.h"

#define LED_PIN    5
#define BUTTON_PIN 13
volatile int d;
int main(void){
  
	initMotors();
	d = 0;
	while(1);
}
