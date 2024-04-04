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
			
	NOTES:
		https://deepbluembedded.com/stm32-pwm-example-timer-pwm-mode-tutorial/#stm32-pwm-example-led-dimmer
		There are 8 timer registers that can be used (1-8)
		relavent TIMER struct{
			CCR1 -> start of pulse time
			ARR -> end of pulse
		}
		Duty cycle (in percent) = CCR/ARR
		Fpwm = (Fclk/((ARR + 1) * (PSC + 1)))
		
		80 Mhz
		
		*/

//float randing from 0 - 1; 0 being off 1 being max speed
static float pwmRatio = 1;

static int MINDELAYVAL = 1000;

/*

void initTimerLeft(void){
    //enable clock for TIM2
    RCC->APB1ENR1 |= (1<<0);
    //set prescaler value for 1000hz (1ms)
    TIM2->PSC = 80000 - 1;
    //set auto reset value to max
    TIM2->ARR = 0xFFFF;
    //reset the counter registers 
    TIM2->EGR |= (1<<0);
    //reset the actual count value | this holds the amoutn of times reset
    TIM2->CNT = 0x0;
    //enable the timer 
    TIM2->CR1 |= (1<<0);
}



void initTimerLeft(void){
    //enable clock for TIM2
    RCC->APB1ENR1 |= (1<<0);
    //set prescaler value for 1000hz (1ms)
    TIM2->PSC = 80000 - 1;
    //set auto reset value to max
    TIM2->ARR = 0xFFFF;
    //reset the counter registers 
    TIM2->EGR |= (1<<0);
    //reset the actual count value | this holds the amoutn of times reset
    TIM2->CNT = 0x0;
    //enable the timer 
    TIM2->CR1 |= (1<<0);
}

//delay assuming clock is set to 80 Mhz
void updateMotorLeft(void){
    initTimer();
	if(pwmRatio == 0){
		//set motor to off and reset timer value
	}
	
	
	//while count is not greater than the delay val continue 
	if(TIM2->CNT < (MINDELAYVAL/pwmRatio)){
	
	}
	//if count is greater than delay val then swap 
	
    while(TIM2->CNT < timeInMs){
    }

}


void initMotor(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	//set MODER for pin 0 and 1 to output
	GPIOC->MODER &= ~((0x3 << 2) | (0x3));
	GPIOC->MODER |= (0x5);
	
	//set gpio speed to fast or w/e
	GPIOC->OSPEEDR |= 0xF;

	
}

*/