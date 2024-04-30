#include "stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/motor.h"

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5
#define BUTTON_PIN 13
	
void switchinit(void){

System_Clock_Init(); // Switch System Clock = 80 MHz

// Enable the clock to GPIO Port C
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  


//Program GPIOC->MODER to set the mode of Pin PC 13 as input (by default, they are analog).
GPIOC->MODER &= ~GPIO_MODER_MODE13;
GPIOC->MODER |= 0x0;
	
//Program GPIOC->PUPDR to set the pull-up/pull-down setting of Pin PC 13 as no pull-up no pull-down
GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
GPIOC->PUPDR |= 0x0;
	
}

int enableswitch(int *eligChange){
	while(GPIOC->IDR & GPIO_IDR_IDR_13){
		if(*eligChange){
			setLeftPWMBackward(0.5);
			*eligChange = 0;
		}
	}
	setLeftPWMBackward(0);
	*eligChange = 1;
}


