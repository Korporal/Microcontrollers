#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_flash.h"
#include <stm32f4xx_gpio.h>

void Delay()
{
	int i;
	for (i = 0; i < 2; i++)
		asm("nop");
}

void XGPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
	/* Check the parameters */
//	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
//	assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
//	assert_param(IS_GPIO_BIT_ACTION(BitVal));

	if (BitVal != Bit_RESET)
	{
		GPIOx->BSRRL = GPIO_Pin;
	}
	else
	{
		GPIOx->BSRRH = GPIO_Pin;
	}
}

int main(void)
{
	// Resets the clock configuration to the default reset state
	RCC_DeInit();

	// Enable external crystal (HSE)
	RCC_HSEConfig(RCC_HSE_ON);
	// Wait until HSE ready to use or not
	ErrorStatus errorStatus = RCC_WaitForHSEStartUp();
	
	int32_t H = HSE_VALUE;

	if (errorStatus == SUCCESS)
	{
		// Configure the PLL for 168MHz SysClk and 48MHz for USB OTG, SDIO
		RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
		// Enable PLL
		RCC_PLLCmd(ENABLE);
		// Wait until main PLL clock ready
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		// Set flash latency
		FLASH_SetLatency(FLASH_Latency_5);

		// AHB 168MHz
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// APB1 42MHz
		RCC_PCLK1Config(RCC_HCLK_Div4);
		// APB2 84 MHz
		RCC_PCLK2Config(RCC_HCLK_Div2);

		// Set SysClk using PLL
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	}
	else
	{
		// Do something to indicate that error clock configuration
		while(1);
	}

	SystemCoreClockUpdate();
	
	uint32_t ccc = SystemCoreClock;

	while (1) 
	{
		
		GPIO_InitTypeDef GPIO_InitStructure;
  
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		int X = 0;
		
		for (;;)
		{
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
			XGPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
		}
	}
}