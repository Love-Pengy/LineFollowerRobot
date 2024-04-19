#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/globals.h"

//ARR value
#define MAX_COUNT 199

void initMotorClocks(void){
   //init GPIO A and B 
   RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
   RCC->AHB2ENR |=  RCC_AHB2ENR_GPIOBEN;
}

void initMotorPins(void){
    //init pins PA0 and PA7 
    //PB9 -> TIM4_CH1 -> AF2
    //PA7 -> TIM3_CH2 -> AF2
    //AFR[0] is for pins 0-7
	
	//PIN PB9
	GPIOB->MODER &= ~(0x03 << (2*TIM4_PIN));
	GPIOB->MODER |= 0x02 << (2*TIM4_PIN);
	GPIOB->AFR[1] |= 0x2<<(4);
	GPIOB->OSPEEDR |= 0x03<<(2*TIM4_PIN);
	GPIOB->OTYPER &= ~(1<<9);
	GPIOB->PUPDR &= ~(0x03<<(2*TIM4_PIN));
	
	//PIN PA7
	GPIOA->MODER &= ~(0x03 << (2*TIM3_PIN));
	GPIOA->MODER |= 0x02 << (2*TIM3_PIN);
	GPIOA->AFR[0] |= 0x2<<(4);
	GPIOA->OSPEEDR |= 0x03<<(2*TIM3_PIN);
	GPIOA->OTYPER &= ~(1<<9);
	GPIOA->PUPDR &= ~(0x03<<(2*TIM3_PIN));
   
}

void initMotorTimers(void){
  //TIM4 part >>>>>>
	
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
	TIM4->CCR4 = 0; 
	
  // ============  
    
  //TIM3 part >>>>>>>>>>>>>
	
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
	TIM3->PSC = 63;
	TIM3->ARR = MAX_COUNT;
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; //pwm mode 1
	//enable preload
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE;
	//auto preload
	TIM3->CR1 |= TIM_CR1_ARPE; 
	//upcounting
	TIM3->CR1 &= ~TIM_CR1_DIR;
	//enable capture/compare register
	TIM3->CCER |= TIM_CCER_CC4E;
	TIM3->EGR |= TIM_EGR_UG;
	//clear interrupt flag
	TIM3->SR &= ~TIM_SR_UIF;
	
	TIM3->DIER |= TIM_DIER_UIE;
	//enable the counter
	TIM3->CR1 = TIM_CR1_CEN;
	//default pwm value
	TIM3->CCR4 = 0; 
	
  // ==============
}

void initMotors(void){
    initMotorClocks();
    initMotorPins();
    initMotorTimers();
}


void setLeftPWM(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if((val < 38) && (val != 0)){
		TIM4->CCR4 = 38;
	}
	else{
		TIM4->CCR4 = val;
	}
}

void setRightPWM(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if((val < 38) && (val != 0)){
		TIM3->CCR4 = 38;
	}
	else{
		TIM3->CCR4 = val;
	}
}

