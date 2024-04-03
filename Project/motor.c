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



int main (void){
    System_Clock_Init();
	
	// Enable the clock to GPIO Port C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	
    while(1);
}