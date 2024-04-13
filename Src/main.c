#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor.h"

#define LED_PIN    5
#define BUTTON_PIN 13

int main(void){
    initMotors();
    setLeftPWM(.75);
	while(1);
	
}
