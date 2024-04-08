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
        TIMERS THAT SHOULD BE USED: 2, 3, 4, 5
        Also can use 15, 16, 17 but use 2, 3, 4, 5 first these are the all purpose ones

		relavent TIMER struct{
			CCR1 -> start of pulse time
			ARR -> end of pulse
		}
		Duty cycle (in percent) = CCR/ARR
		Fpwm = (Fclk/((ARR + 1) * (PSC + 1)))
        PSC in this case will be 0 
	    ARR can be set to 10 to give us 10 percent duty cycles	
		80 Mhz
        
        sum: 
            timer = PWM mode
            prescaler = 0;
            counter = up;
            8 bit resolution 
            (ARR of 255);
            change CCR1 based on desired duty cycle
            look at page 1071 for information on how to enable to registers for pwm mode
		
		*/

//float randing from 0 - 1; 0 being off 1 being max speed
static float pwmRatio = 1;

static int MINDELAYVAL = 1000;


//https://community.st.com/t5/stm32-mcus-products/how-to-start-pwm-without-using-hal/td-p/84397
void initTimerLeft(void){
    //enable clock, set to PWM mode
    /*
    enable GPIOx and TIMx clock in RCC
    set the appropriate pin's GPIOx_MODER to AF, and GPIOx_AFR to appropriate value; set also GPIOx_OSPEEDR if there's a need for higher slew rates
    set TIMx_CCMRx to set given channel to Output Compare, and one of the PWM modes
    set TIMx_CCRx to set duty cycle
    enable given channel in TIMx_CCER
    in Advanced timers, set TIMx_BDTR.MOE
    set TIMx_PSC/TIMx_ARR to set period
    set TIMx_CR1.CEN to start timer's counter  
    */ 
    /*
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
    */
}

void initTimerRight(void){
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

/*
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
