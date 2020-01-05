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
#define LIT GPIO_PIN_SET
#define OFF GPIO_PIN_RESET


typedef struct led_arguments
{
	GPIO_PinState state;
	uint16_t color;
	uint32_t delay;
} LedArgs, * LedArgs_ptr;

#define lengthof(X) (sizeof((X))/sizeof(*(X)))


LedArgs argstable[] = 
{ 
	{LIT, GREEN, 0}, 
	{LIT, RED, 0},
	{LIT, BLUE, 100},
	{OFF, BLUE, 2},
	{LIT, GREEN, 100},
	{LIT, RED, 0},
	{LIT, GREEN, 100},
	{OFF, GREEN, 0},
	{LIT, GREEN, 0 }, 
	{LIT, ORANGE, 100},
	{OFF, ORANGE, 45},
	{LIT, RED, 100},
	{OFF, ORANGE, 0},
	{OFF, GREEN, 100},
	{OFF, RED, 100},
	{OFF, GREEN, 100},
	{LIT, BLUE, 100},
	{OFF, BLUE, 100},
	{OFF, RED, 0},
	{LIT, ORANGE, 0},
	{OFF, BLUE, 100},
	{OFF, GREEN, 0},
	{LIT, ORANGE, 100},
	{LIT, RED, 69},
	{OFF, ORANGE, 100},
	{LIT, RED, 100},
	{LIT, RED, 0},
	{LIT, BLUE, 100},
	{LIT, GREEN, 100},
	{OFF, GREEN, 0},
	{LIT, ORANGE, 100},
	{OFF, ORANGE, 100},
	{LIT, GREEN, 0 }, 
	{OFF, ORANGE, 0},
	{OFF, RED, 23},
	{OFF, GREEN, 100},
	{LIT, BLUE, 100},
	{OFF, BLUE, 63},
	{OFF, RED, 0},
	{LIT, ORANGE, 0},
	{OFF, BLUE, 49},
	{OFF, ORANGE, 0},
	{LIT, GREEN, 0 }, 
	{LIT, RED, 0},
	{LIT, BLUE, 100},
	{OFF, RED, 42},
	{LIT, GREEN, 100},
	{OFF, GREEN, 0},
	{LIT, ORANGE, 100},
	{OFF, ORANGE, 100},
	{LIT, RED, 38},
	{OFF, ORANGE, 0},
	{OFF, RED, 100},
	{LIT, ORANGE, 0},
	{OFF, GREEN, 100},
	{LIT, BLUE, 100},
	{OFF, BLUE, 33},
	{OFF, RED, 0},
	{OFF, BLUE, 100},
	{LIT, BLUE, 22},
	{OFF, BLUE, 100},
	{OFF, RED, 0},
	{LIT, ORANGE, 0},
	{OFF, BLUE, 100}
};


void LED(LedArgs_ptr);

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

	while (1)
	{
		for (int I = 0; I < lengthof(argstable); I++)
		{
			LED(&argstable[I]);
		}
	}
}

void LED(LedArgs_ptr Args_ptr)
{
	HAL_GPIO_WritePin(GPIOD, Args_ptr->color, Args_ptr->state);

	if (Args_ptr->delay > 0)
		HAL_Delay(Args_ptr->delay);
}
