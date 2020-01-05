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

#define GREEN GPIO_PIN_12
#define ORANGE GPIO_PIN_13
#define RED GPIO_PIN_14
#define BLUE GPIO_PIN_15

void LED_ON(uint16_t ID);
void LED_OFF(uint16_t ID);


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
		LED_ON(GREEN);
		LED_ON(ORANGE);
		LED_ON(RED);
		LED_ON(BLUE);
		
		HAL_Delay(100);
		
		LED_OFF(GREEN);
		LED_OFF(ORANGE);
		LED_OFF(RED);
		LED_OFF(BLUE);
		
		HAL_Delay(100);
		
		LED_ON(GREEN);
		HAL_Delay(100);
		LED_OFF(GREEN);
		HAL_Delay(100);
		
		LED_ON(ORANGE);
		HAL_Delay(100);
		LED_OFF(ORANGE);
		HAL_Delay(100);

		LED_ON(RED);
		HAL_Delay(100);
		LED_OFF(RED);
		HAL_Delay(100);

		LED_ON(BLUE);
		HAL_Delay(100);
		LED_OFF(BLUE);
		HAL_Delay(100);
	}
}

void LED_ON(uint16_t ID)
{
	HAL_GPIO_WritePin(GPIOD, ID, GPIO_PIN_SET);
}

void LED_OFF(uint16_t ID)
{
	HAL_GPIO_WritePin(GPIOD, ID, GPIO_PIN_RESET);
}
