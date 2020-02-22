
#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
#include <stm32f4xx_dac.h>
#include <stm32f4xx.h>

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	DAC_HandleTypeDef DACH_Struc;
	
	HAL_Init();

	__GPIOA_CLK_ENABLE();
	//__DAC1_CLK_ENABLE();

	GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	DAC_InitStructure.DAC_Trigger = DAC_TRIGGER_NONE;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WAVEGENERATION_NONE;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	
	DACH_Struc.Instance = (DAC_TypeDef*)DAC1;
	HAL_DAC_Init(&DACH_Struc);
	
	
	for (;;)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		//HAL_Delay(5);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		//HAL_Delay(5);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		//HAL_Delay(5);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		//HAL_Delay(5);

	}
}
