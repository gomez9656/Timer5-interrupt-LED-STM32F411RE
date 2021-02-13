/*
 * main.c
 *
 *  Created on: 23/01/2021
 *      Author: PC
 */

#include "stm32f4xx.h"
#include "main.h"
#include <string.h>

/*
 * Functions prototypes
 */
void SystemCoreClockConfig();
void Error_handler();
void TIMER5_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer5;


int main(){

	/* Basic initialization  */
	HAL_Init();
	SystemCoreClockConfig();
	GPIO_Init();
	TIMER5_Init();

	HAL_TIM_Base_Start_IT(&htimer5);

	while(1);

	return 0;
}

/*
 * You can use it when you need an specific clock
 * By default will be internal clock
 */
void SystemCoreClockConfig(){

}

void TIMER5_Init(void){

	htimer5.Instance = TIM5;
	htimer5.Init.Prescaler = 24;
	htimer5.Init.Period = 120000 - 1 ;

	if (HAL_TIM_Base_Init(&htimer5) != HAL_OK){
		Error_handler();
	}

}

void GPIO_Init(void){

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void Error_handler(void){
	while(1);
}
