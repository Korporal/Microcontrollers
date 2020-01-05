#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>

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
	HAL_Init();

	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	
	GPIO_InitStructure.Pin = GPIO_PIN_12;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_14;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);


	for (;;)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(100);
		
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(100);
		
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
		HAL_Delay(100);
	}
}
