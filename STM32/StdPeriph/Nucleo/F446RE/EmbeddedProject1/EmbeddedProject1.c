
#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
#include <stm32f4xx_dac.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_rcc.h>

#include "SineTables.h"

#ifdef __cplusplus
extern "C"
#endif
	
	int32_t SINEWAVE[4096];

#define MINV 0x032
#define MAXV 0xe1C

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int main(void)
{
	uint16_t code = 0;
	HAL_StatusTypeDef status;
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_ChannelConfTypeDef sConfig;
	DAC_HandleTypeDef hdac;
	
	GenerateSineTable(SINEWAVE, MINV, MAXV, &code);
	
	HAL_Init();

	__GPIOA_CLK_ENABLE();
	
	__HAL_RCC_DAC_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	hdac.Instance = (DAC_TypeDef*)DAC1;
	
	status = HAL_DAC_Init(&hdac);
	
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
	
	status = HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1);
	status = HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2);

	uint32_t v = 0;
	
	status = HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	status = HAL_DAC_Start(&hdac, DAC_CHANNEL_2);

	for (;;)
	{
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, v);
		//HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, v);
		v++;
	}
}
