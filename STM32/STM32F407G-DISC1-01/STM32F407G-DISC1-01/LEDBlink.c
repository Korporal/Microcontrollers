/*----------------------------------------------------------*/
/* Simple LED example for the STM32F407G-DISC1 board.		*/
/* Some of the info for this was obtained here				*/
/* https://visualgdb.com/tutorials/arm/stm32/f4_discovery/	*/
/*----------------------------------------------------------*/

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

static TIM_HandleTypeDef s_TimerInstance = { 
	.Instance = TIM2
};
 
void InitializeTimer()
{
	__TIM2_CLK_ENABLE();
	s_TimerInstance.Init.Prescaler = 2;
	s_TimerInstance.Init.CounterMode = TIM_COUNTERMODE_UP;
	s_TimerInstance.Init.Period = 64;
	s_TimerInstance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	s_TimerInstance.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&s_TimerInstance);
	HAL_TIM_Base_Start_IT(&s_TimerInstance);
}
 
extern void TIM2_IRQHandler()
{
	HAL_TIM_IRQHandler(&s_TimerInstance);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
}
int main(void)
{
	HAL_Init();
	
	InitializeTimer();
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	
	__GPIOD_CLK_ENABLE();
	
	uint32_t c = HAL_RCC_GetHCLKFreq();
	
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

	int timerValue;
	
	while (1)
	{
		; // do nothing here, the interrupt handler does all the work.
	}
}

void LED(LedArgs_ptr Args_ptr)
{
	HAL_GPIO_WritePin(GPIOD, Args_ptr->color, Args_ptr->state);

//	if (Args_ptr->delay > 0)
//		HAL_Delay(Args_ptr->delay);
}

