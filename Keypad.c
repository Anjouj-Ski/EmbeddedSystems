/*
 * Keybad.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Adam Aster
 */

#include "keypad.h"
#include "main.h"

void keypad()
 {
//Enabling Clock for Ports
	 RCC ->AHBENR|= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN| RCC_AHBENR_GPIOCEN;
//Configuring Input Pins

	 //Specifying Pin Type: INPUT

	 GPIOA -> MODER &= ~ (GPIO_MODER_MODER3_0|GPIO_MODER_MODER3_1|GPIO_MODER_MODER2_0|GPIO_MODER_MODER2_1|GPIO_MODER_MODER10_0|GPIO_MODER_MODER10_1);
	 GPIOB -> MODER &= ~ (GPIO_MODER_MODER3_0);
	 //Specifying Pin Type: Push-Pull

	 GPIOA -> OTYPER &= ~( GPIO_OTYPER_OT_3 | GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_10);
	 GPIOB -> OTYPER &= ~( GPIO_OTYPER_OT_3);
	 //Specifying Pin Speed

	 GPIOA-> OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEEDR3_0 | GPIO_OSPEEDR_OSPEEDR2_0 | GPIO_OSPEEDR_OSPEEDR10_0);
	 GPIOB-> OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEEDR3_0 );
	 //Specifying Pin: Pull Down

	 GPIOA->MODER &= ~(GPIO_MODER_MODER3_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER10_0);
	 GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR3_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR10_0);
	 GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR3_1 | GPIO_PUPDR_PUPDR2_1 | GPIO_PUPDR_PUPDR10_1);// Pull-down resistors
	 GPIOB->MODER &= ~(GPIO_MODER_MODER3_0);
	 GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_0;
	 GPIOB ->PUPDR &= ~GPIO_PUPDR_PUPDR3_1;

//Configuring Output Pins

	 //Specifying Pin Type: Output

	 GPIOA -> MODER |= (GPIO_MODER_MODER9_0|GPIO_MODER_MODER8_0|GPIO_MODER_MODER7_0);
	 GPIOA -> MODER &= ~(GPIO_MODER_MODER9_1|GPIO_MODER_MODER8_1|GPIO_MODER_MODER7_1);
	 GPIOB -> MODER |= (GPIO_MODER_MODER5_0|GPIO_MODER_MODER4_0|GPIO_MODER_MODER10_0|GPIO_MODER_MODER6_0);
	 GPIOB -> MODER &= ~(GPIO_MODER_MODER5_1|GPIO_MODER_MODER4_1|GPIO_MODER_MODER10_1|GPIO_MODER_MODER6_1);
	 GPIOC -> MODER |= (GPIO_MODER_MODER7_0);
	 GPIOC -> MODER &= ~(GPIO_MODER_MODER7_1);

	 //Specifying Pin Type: Push-Pull
	 GPIOA -> OTYPER &= ~( GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_7);
	 GPIOB -> OTYPER &= ~( GPIO_OTYPER_OT_4 | GPIO_OTYPER_OT_5 | GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_10);
	 GPIOC -> OTYPER &= ~( GPIO_OTYPER_OT_7);

	 //Specifying Pin Speed
	 GPIOA-> OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEEDR8_0 | GPIO_OSPEEDR_OSPEEDR7_0 | GPIO_OSPEEDR_OSPEEDR9_0);
	 GPIOB-> OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEEDR4_0 | GPIO_OSPEEDR_OSPEEDR5_0| GPIO_OSPEEDR_OSPEEDR6_0| GPIO_OSPEEDR_OSPEEDR10_0);
	 GPIOC-> OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEEDR7_0);


	 while(1){
		 // Set Row 1 (PA8) High, others Low
		 GPIOA->BSRR |= GPIO_BSRR_BR_8;    // Row 1 (PA8) High
		 GPIOA->BSRR |= GPIO_BSRR_BS_7 | GPIO_BSRR_BS_9; // Other rows Low
		 GPIOB->BSRR |= GPIO_BSRR_BS_6;

		         // Check if Column 1 (PB3) is high (key '1' pressed)
		 if(!(GPIOA -> ODR & GPIO_ODR_8)){
			 if (GPIOB->IDR & GPIO_IDR_3) { // If PB3 is high, key '1' is pressed
				 GPIOA->BSRR |= GPIO_BSRR_BS_9; // Turn on LED on PA9
			 } else {
				 GPIOA->BSRR |= GPIO_BSRR_BR_9; // Turn off LED on PA9
		         }

		         // Small delay for debouncing
		         delay(10);

		 }
	 }

	 }


