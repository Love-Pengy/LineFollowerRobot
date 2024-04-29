#include "../Include/stm32l476xx.h"
#include "../Include/SysClock.h"
#include "../Include/globals.h"
#include "../Lib/OLED/ssd1306.h"
#include "../Lib/OLED/ssd1306_tests.h"
#include "../Lib/OLED/I2C.h"

void initOled(void){
	//SETS CLOCK TO 80 MHZ
	System_Clock_Init();
	I2C_GPIO_init();
	I2C_Initialization(I2C1);
	ssd1306_Init();
}


void updateOled(char* input){
	ssd1306_Fill(White);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString(input, Font_11x18, Black);
	ssd1306_UpdateScreen();	
}
