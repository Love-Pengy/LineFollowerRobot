#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/globals.h"
#include "../Include/delay.h"

//ARR value
#define MAX_COUNT 199
#define LEFT_MOTOR_PIN 3
#define RIGHT_MOTOR_PIN 9

void initMotorClocks(void){
   //init GPIO A and B 
   RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	 RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
}

void initMotorPins(void){
	
	//PIN PB9 LEFT MOTOR
	GPIOB->MODER &= ~(0x03 << (2*RIGHT_MOTOR_PIN));
	//set moder to output
	GPIOB->MODER |= 0x01 << (2*RIGHT_MOTOR_PIN);
	GPIOB->OSPEEDR |= 0x03<<(2*RIGHT_MOTOR_PIN);
	//pushpull
	GPIOB->OTYPER &= ~(1<<RIGHT_MOTOR_PIN);
	//no pupdr
	GPIOB->PUPDR &= ~(0x03<<(2*RIGHT_MOTOR_PIN));
	//turn off pin
	GPIOB->ODR &= ~(1<<RIGHT_MOTOR_PIN);
	
	//PIN PA3 RIGHT MOTOR
	GPIOA->MODER &= ~(0x03 << (2*LEFT_MOTOR_PIN));
	//set moder to output
	GPIOA->MODER |= 0x01 << (2*LEFT_MOTOR_PIN);
	GPIOA->OSPEEDR |= 0x03<<(2*LEFT_MOTOR_PIN);
	//pushpull
	GPIOA->OTYPER &= ~(1<<LEFT_MOTOR_PIN);
	//no pupdr
	GPIOA->PUPDR &= ~(0x03<<(2*LEFT_MOTOR_PIN));
	//turn off pin
  GPIOA->ODR &= ~(GPIO_ODR_OD3);
}

void initMotors(void){
    initMotorClocks();
    initMotorPins();
}

void pulseLeftMotor(void){
	GPIOB->ODR |= 1<<RIGHT_MOTOR_PIN;
	delayMs(DELAY_VAL);
	GPIOB->ODR &= ~(1<<RIGHT_MOTOR_PIN);
}

void pulseRightMotor(void){
	GPIOA->ODR |= 1<<LEFT_MOTOR_PIN;
	delayMs(DELAY_VAL);
	GPIOA->ODR &= ~(1<<LEFT_MOTOR_PIN);
}

