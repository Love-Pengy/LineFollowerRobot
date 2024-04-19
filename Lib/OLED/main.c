#include <string.h>
#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"
#include "I2C.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"
	
int main(void){
	volatile int i;
	int count = 0;
	char message[64]="";
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	I2C_GPIO_init();
	I2C_Initialization(I2C1);

	ssd1306_Init();
	
	while(1){
		for(i=0; i<100000; i++);
		sprintf(message, "%d", count);
		ssd1306_Fill(White);
		ssd1306_SetCursor(2,0);
		ssd1306_WriteString(message, Font_11x18, Black);
		ssd1306_UpdateScreen();	
		count++;
	}
}

