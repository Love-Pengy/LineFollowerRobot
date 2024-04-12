#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"

#define TIM2_PIN 0
#define TIM3_PIN 7

/*			
    PINS: 
        AF1 = 0001
        AF2 = 0010
        PA0 -> TIM2_CH1 -> AF1
        PA7 -> TIM3_CH2 -> AF2
        PB7 -> TIM4_CH2 -> AF2
        PA1 -> TIM5_CH2 -> AF2
        
	NOTES:
		https://deepbluembedded.com/stm32-pwm-example-timer-pwm-mode-tutorial/#stm32-pwm-example-led-dimmer
        16 bit gen purpose timers (2-5)
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

//float ranging from 0 - 1; 0 being off 1 being max speed
static float pwmRatio = 1;

static int MINDELAYVAL = 1000;



void initMotorClocks(void){
    //init GPIO A and TIM2/TIM3
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
}

void initMotorPins(void){
    //init pins PA0 and PA7 
    //PA0 -> TIM2_CH1 -> AF1
    //PA7 -> TIM3_CH2 -> AF2
    //AFR[0] is for pins 0-7

    //TIM2 part
    GPIOA->AFR[0] &= ~(0xF<<(4*TIM2_PIN));
    GPIOA->AFR[0] |= 1<<(4*TIM2_PIN);

    //get gpio speed to fast 
    GPIOA->OSPEEDR &= (0x2 << (2*TIM2_PIN)); 

    //set pin to no pupd
    GPIOA->PUPDR &= ~(0x3<<(2*TIM2_PIN));    

}

void initMotorTimers(void){
    //set to up counting
    TIM2->CR1 &= ~TIM_CR1_DIR;

    //set prescaler 
    TIM2->PSC = 0;

    //set auto reload
    TIM2->ARR = 65535;

    //set initial duty cycle to 50%
    TIM2->CCR1 = ((int)65535/2);

    //clear current compare bits 
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;

    //set to PWM Mode 1 output on channel 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;

    //enable preload for output 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;


    //select output polarity 0 = active high 1 = active low
    TIM2->CCER &= ~TIM_CCER_CC1P;


    //enable output of ch1
    TIM2->CCER |= TIM_CCER_CC1E;


    //main output enable 
    TIM2->BDTR |= TIM_BDTR_MOE;

    //finally start the counter
    TIM2->CR1 |= TIM_CR1_CEN;

}

void initMotors(void){
    initMotorClocks();
    initMotorPins();
    initMotorTimers();
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
