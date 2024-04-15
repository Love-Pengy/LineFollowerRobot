#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"

//left motor
#define TIM2_PIN 0
//right motor
#define TIM3_PIN 7
//ARR value
#define MAX_COUNT 199

/*			
    PINS: 
        AF1 = 0001
        AF2 = 0010
        PA0 -> TIM2_CH1 -> AF1
        PA7 -> TIM3_CH2 -> AF2
        PB9 -> TIM4_CH2 -> AF2
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

void initMotorClocks(void){
    //init GPIO A and TIM2/TIM3
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |=  RCC_AHB2ENR_GPIOBEN;
}

void initMotorPins(void){
    //init pins PA0 and PA7 
    //PB9 -> TIM4_CH1 -> AF2
    //PA7 -> TIM3_CH2 -> AF2
    //AFR[0] is for pins 0-7
	
	//PIN PB9
	GPIOB->MODER &= ~(0x03 << (2*9));
	GPIOB->MODER |= 0x02 << (2*9);
	GPIOB->AFR[1] |= 0x2<<(4);
	GPIOB->OSPEEDR |= 0x03<<(2*9);
	GPIOB->OTYPER &= ~(1<<9);
	GPIOB->PUPDR &= ~(0x03<<(2*9));
	
   
}

void initMotorTimers(void){
    //TIM2 part >>>>>>
    //set to up counting
	
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	TIM4->PSC = 63;
	TIM4->ARR = MAX_COUNT;
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; //pwm mode 1
	//enable preload
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE;
	//auto preload
	TIM4->CR1 |= TIM_CR1_ARPE; 
	//upcounting
	TIM4->CR1 &= ~TIM_CR1_DIR;
	//enable capture/compare register
	TIM4->CCER |= TIM_CCER_CC4E;
	TIM4->EGR |= TIM_EGR_UG;
	//clear interrupt flag
	TIM4->SR &= ~TIM_SR_UIF;
	
	TIM4->DIER |= TIM_DIER_UIE;
	//enable the counter
	TIM4->CR1 = TIM_CR1_CEN;
	//default pwm value
	TIM4->CCR4 = 50; 
	
    // ============  
    
    //TIM3 part >>>>>>>>>>>>>
    
    // ==============
}

void initMotors(void){
    initMotorClocks();
    initMotorPins();
    initMotorTimers();
}


void setLeftPWM(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if(val < 38){
		TIM4->CCR4 = 38;
	}
	else{
		TIM4->CCR4 = val;
	}
}

void setRightPWM(float pwm);

