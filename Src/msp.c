/*
 * msp.c
 *
 *  Created on: 23/01/2021
 *      Author: PC
 */

#include "main.h"
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer);

void HAL_MspInit(void){
	//Low level initializations

	//1. Set up priority grouping
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions
	SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exception

	//3. Configure the priority for the system exception
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer){

	__HAL_RCC_TIM5_CLK_ENABLE();

	HAL_NVIC_EnableIRQ(TIM5_IRQn);

	HAL_NVIC_SetPriority(TIM5_IRQn, 15, 0);

}

