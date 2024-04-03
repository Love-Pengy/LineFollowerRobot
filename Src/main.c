#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"

#define LED_PIN    5
#define BUTTON_PIN 13

int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	  // Enable the clock to GPIO Port B	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;   
	
	// MODE: 00: Input mode, 01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
  GPIOB->MODER &= ~(0x03<<(2*2)) ;   // Clear bit 13 and bit 12 for Port B
  GPIOB->MODER |= (1<<4);
		
	GPIOB->ODR |= GPIO_ODR_ODR_2;
  // Dead loop & program hangs here
	
	while(1);
}
