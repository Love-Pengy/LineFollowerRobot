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
	 RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
}

void initMotorPins(void){
	
	//PIN PB7 uses Timer 4 Channel 2: Front LEFT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*FTIM4_PIN));
	GPIOB->MODER |= 0x02 << (2*FTIM4_PIN);
	GPIOB->AFR[0] |= 0x2<<(4*FTIM4_PIN); //I believe its four because we shift 4 for moving over one and the offset is 9-8
	GPIOB->OSPEEDR |= 0x03<<(2*FTIM4_PIN);
	GPIOB->OTYPER &= ~(1<<FTIM4_PIN);
	GPIOB->PUPDR &= ~(0x03<<(2*FTIM4_PIN));
	
	//PIN PB6 uses Timer 4 Channel 1: Back LEFT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*BTIM4_PIN));
	GPIOB->MODER |= 0x02 << (2*BTIM4_PIN);
	GPIOB->AFR[0] |= 0x2<<(4*BTIM4_PIN); //I believe its four because we shift 4 for moving over one and the offset is 9-8
	GPIOB->OSPEEDR |= 0x03<<(2*BTIM4_PIN);
	GPIOB->OTYPER &= ~(1<<BTIM4_PIN);
	GPIOB->PUPDR &= ~(0x03<<(2*BTIM4_PIN));
	
	//PIN PB1 uses Timer 3 Channel 4: Front RIGHT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*FTIM3_PIN));
	GPIOB->MODER |= 0x02 << (2*FTIM3_PIN);
	GPIOB->AFR[0] |= 0x2<<(4*FTIM3_PIN);
	GPIOB->OSPEEDR |= 0x03<<(2*FTIM3_PIN);
	GPIOB->OTYPER &= ~(1<<FTIM3_PIN);
	GPIOB->PUPDR &= ~(0x03<<(2*FTIM3_PIN));
	
	//PIN PB0 uses Timer 3 Channel 3: Back RIGHT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*BTIM3_PIN));
	GPIOB->MODER |= 0x02 << (2*BTIM3_PIN);
	GPIOB->AFR[0] |= 0x2<<(4*BTIM3_PIN);
	GPIOB->OSPEEDR |= 0x03<<(2*BTIM3_PIN);
	GPIOB->OTYPER &= ~(1<<BTIM3_PIN);
	GPIOB->PUPDR &= ~(0x03<<(2*BTIM3_PIN));
}

void initMotorTimers(void){
	
  //TIM4 part >>>>>>
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	TIM4->PSC = 63;
	TIM4->ARR = MAX_COUNT;
	//enable preload
	TIM4->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; //pwm mode 1
	//auto preload
	TIM4->CR1 |= TIM_CR1_ARPE; 
	//upcounting
	TIM4->CR1 &= ~TIM_CR1_DIR;
	//enable capture/compare register
	TIM4->CCER |= TIM_CCER_CC2E | TIM_CCER_CC1E ;	
	TIM4->CCER &= ~ (TIM_CCER_CC2P |TIM_CCER_CC1P);
	TIM4->EGR |= TIM_EGR_UG;
	//clear interrupt flag
	TIM4->SR &= ~TIM_SR_UIF;
	TIM4->DIER |= TIM_DIER_UIE;
	//enable the counter
	TIM4->CR1 = TIM_CR1_CEN;
	//default pwm value
	TIM4->CCR2 = 0; 
	TIM4->CCR1 = 0; 
  // ============  
    
  //TIM3 part >>>>>>>>>>>>>
	
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
	TIM3->PSC = 63;
	TIM3->ARR = MAX_COUNT;
	//enable preload
	TIM3->CCMR2 &= ~TIM_CCMR2_OC4M;
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE; //pwm mode 1
	//auto preload
	TIM3->CR1 |= TIM_CR1_ARPE; 
	//upcounting
	TIM3->CR1 &= ~TIM_CR1_DIR;
	//enable capture/compare register
	TIM3->CCER |= TIM_CCER_CC4E | TIM_CCER_CC3E;	
	TIM3->CCER &= ~ (TIM_CCER_CC4P | TIM_CCER_CC3P);
	TIM3->EGR |= TIM_EGR_UG;
	//clear interrupt flag
	TIM3->SR &= ~TIM_SR_UIF;
	TIM3->DIER |= TIM_DIER_UIE;
	//enable the counter
	TIM3->CR1 = TIM_CR1_CEN;
	//default pwm value
	TIM3->CCR4 = 0; 
	TIM3->CCR3 = 0; 
  // ==============
}

void initMotors(void){
	initMotorClocks();
  initMotorPins();
  initMotorTimers();
}

void setLeftPWMForward(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if((val < 38) && (val != 0)){
		TIM4->CCR2 = 38;
		TIM4->CCR1 = 0;
	}
	else{
		TIM4->CCR2 = val;
		TIM4->CCR1 = 0;
	}
}

void setLeftPWMBackward(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if((val < 38) && (val != 0)){
		TIM4->CCR1 = 38;
		TIM4->CCR2 = 0;
	}
	else{
		TIM4->CCR1 = val;
		TIM4->CCR2 = 0;
	}
}

void setRightPWMForward(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if((val < 38) && (val != 0)){
		TIM3->CCR4 = 38;
		TIM3->CCR3 = 0;
	}
	else{
		TIM3->CCR4 = val;
		TIM3->CCR3 = 0;
	}
}

void setRightPWMBackward(float pwm){
	int val = (int)(MAX_COUNT * pwm);
	if((val < 38) && (val != 0)){
		TIM3->CCR3 = 38;
		TIM3->CCR4 = 0;
	}
	else{
		TIM3->CCR3 = val;
		TIM3->CCR4 = 0;
	}
}

