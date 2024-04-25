#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/globals.h"
#include "../Include/delay.h"
#include "../Include/motor2.h"

//ARR value
#define MAX_COUNT 199
#define LEFT_MOTOR_PIN 1
#define RIGHT_MOTOR_PIN 9

void initMotorClocks(void){
   //init GPIO A and B 
   RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	 RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
}

void initMotorPins(void){
	
	//PIN PB9 LEFT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*TIM4_PIN));
	GPIOB->MODER |= 0x02 << (2*TIM4_PIN);
	GPIOB->AFR[1] |= 0x2<<(4); //I believe its four because we shift 4 for moving over one and the offset is 9-8
	GPIOB->OSPEEDR |= 0x03<<(2*TIM4_PIN);
	GPIOB->OTYPER &= ~(1<<TIM4_PIN);
	GPIOB->PUPDR &= ~(0x03<<(2*TIM4_PIN));
	
	//PIN PB1 RIGHT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*TIM3_PIN));
	GPIOB->MODER |= 0x02 << (2*TIM3_PIN);
	GPIOB->AFR[0] |= 0x2<<(4*TIM3_PIN);
	GPIOB->OSPEEDR |= 0x03<<(2*TIM3_PIN);
	GPIOB->OTYPER &= ~(1<<TIM3_PIN);
	GPIOB->PUPDR &= ~(0x03<<(2*TIM3_PIN));
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

void pulseLeftMotor(void){
	GPIOB->ODR |= 1<<RIGHT_MOTOR_PIN;
	delayMs(DELAY_VAL);
	GPIOB->ODR &= ~(1<<RIGHT_MOTOR_PIN);
}

void pulseRightMotor(void){
	GPIOB->ODR |= 1<<LEFT_MOTOR_PIN;
	delayMs(DELAY_VAL);
	GPIOB->ODR &= ~(1<<LEFT_MOTOR_PIN);
}
