#include "stm32l4xx.h"

int main(){
	RCC_TypeDef *clock; // pointer to RXX
	GPIO_TypeDef *gpio;
	clock = RCC;
	gpio = GPIOA;
	
	clock->CR &= 0x000000000; // clock register reset bit
	clock->CR |= (1<<16); // clock source is ON and 8Mhz crystal
	
	while(!((clock->CR)&(1<<17))){ // Wait till HSERDY flag is set
		clock->CFGR &= 0x00000000;
		clock->CFGR |= 0x0A; // AHB1 1Mhz set in RCC, clock divider is 8
		
		clock->AHB2ENR &= 0x00000000;
		clock->AHB2ENR |= 0x01; // Clock port GPIOA enable
		
		gpio->MODER &= (1<<10);
		gpio->OTYPER &= (0x00);
		gpio->OSPEEDR &= (0x1100);
		gpio->PUPDR &= (0x00000000);
		gpio->ODR &= (0x00000000);
		
		while(1){
			for(long unsigned int i=0;i<1000000;i++) __nop(); // delay 1 second, 1Mhz clock to the port A --> 10^-6*10^6 = 1 second
		}
	}
	return 0;
}