#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"

/*
	PINS: 
        Lab: 
            PC0 = A
            PC1 = C
            PC2 = B
            PC3 = D
        Project: 
            PC0 = Right Motor 
            PC1 = Left Motor
*/


void initMotor(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	//set MODER for pin 0 and 1 to output
	GPIOC->MODER &= ~((0x3 << 2) | (0x3));
	GPIOC->MODER |= (0x5);
	
}