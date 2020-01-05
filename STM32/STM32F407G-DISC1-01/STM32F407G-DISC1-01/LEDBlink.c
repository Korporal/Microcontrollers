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

void LED_LIT(uint16_t, uint32_t);
void LED_OFF(uint16_t , uint32_t);




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
		LED_LIT(GREEN,0);
		LED_LIT(ORANGE,0);
		LED_LIT(RED,0);
		LED_LIT(BLUE,100);
		
		LED_OFF(GREEN,0);
		LED_OFF(ORANGE,0);
		LED_OFF(RED,0);
		LED_OFF(BLUE,100);
		
		LED_LIT(GREEN, 100);
		LED_OFF(GREEN, 100);
		
		LED_LIT(ORANGE, 100);
		LED_OFF(ORANGE, 100);

		LED_LIT(RED, 100);
		LED_OFF(RED, 100);

		LED_LIT(BLUE, 100);
		LED_OFF(BLUE, 100);
	}
}

void LED_LIT(uint16_t ID, uint32_t Delay)
{
	HAL_GPIO_WritePin(GPIOD, ID, GPIO_PIN_SET);
	
	if (Delay > 0)
		HAL_Delay(Delay);
}
void LED_OFF(uint16_t ID, uint32_t Delay)
{
	HAL_GPIO_WritePin(GPIOD, ID, GPIO_PIN_RESET);

	if (Delay > 0)
		HAL_Delay(Delay);
}
