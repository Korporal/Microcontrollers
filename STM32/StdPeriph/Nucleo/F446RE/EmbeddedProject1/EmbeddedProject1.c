
#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
#include <stm32f4xx_dac.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_rcc.h>

#include "SineTables.h"

#ifdef __cplusplus
extern "C"
#endif
	
uint32_t SINEWAVE_1[4096];
uint32_t SINEWAVE_2[4096];

#define MINV 0x032
#define MAXV 0xe1C
__IO uint32_t * FAL_GetDACPtr(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Alignment);
#define FAL_DACSetValue(P,V) (*P=V)
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
	
	GenerateSineTable(SINEWAVE_1, 0, 4095, &code);
	GenerateSineTable(SINEWAVE_2, 256, 2000, &code);

	HAL_Init();

	__GPIOA_CLK_ENABLE();
	
	__HAL_RCC_DAC_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	
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

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0);
	
	__IO uint32_t DAC_C1 = ((uint32_t)hdac.Instance) + DAC_DHR12R1_ALIGNMENT(DAC_ALIGN_12B_R);
	__IO uint32_t DAC_C2 = ((uint32_t)hdac.Instance) + DAC_DHR12R2_ALIGNMENT(DAC_ALIGN_12B_R);

	__IO uint32_t * DAC_P1 = FAL_GetDACPtr(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R);
	__IO uint32_t * DAC_P2 = FAL_GetDACPtr(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R);
	
	while (1)
	{
		
		for (int X = 0; X < 4096; X++)
		{
			FAL_DACSetValue(DAC_P1, SINEWAVE_1[X]);
			FAL_DACSetValue(DAC_P2, SINEWAVE_2[X]);

//			*DAC_P1 = SINEWAVE_1[X];
//			*DAC_P2 = SINEWAVE_2[X];
//			HAL2_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, SINEWAVE_1[X]);
//			HAL2_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, SINEWAVE_2[X]);
		}
		
	}
}

__IO uint32_t * FAL_GetDACPtr(DAC_HandleTypeDef* hdac, uint32_t Channel, uint32_t Alignment)
{  
	__IO uint32_t tmp = 0U;
  
  
    tmp = (uint32_t)hdac->Instance; 
	
	if (Channel == DAC_CHANNEL_1)
	{
		tmp += DAC_DHR12R1_ALIGNMENT(Alignment);
	}
	else
	{
		tmp += DAC_DHR12R2_ALIGNMENT(Alignment);
	}

	/* Set the DAC channel1 selected data holding register */
	return ((__IO uint32_t *) tmp);
}

