#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#define PI 3.14159265358979323846
#define RAD (double)(PI/180.0)
#define DPB (double)(360.0 / 4096.0)

// The max DAC output voltage is reached before we reach 0x0FFF
// The min DAC output voltage is reached before we reach 0x0000

#define MINV 0x032
#define MAXV 0xF3C

void Delay()
{
	int i;
	for (i = 0; i < 10; i++)
		asm("nop");
}

int main()
{
	
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x00000300;
	RCC->APB1ENR |= 1 << 29;
	DAC->CR |= 1;
	
	int32_t value;
	int32_t min = 0x7FFF;
	int32_t max = 0;
	
	int32_t SINEWAVE[4096];
	double angle;
	// 0, 1, -1, 0
	
	for(int I = 0 ; I < 4096 ; I++)
	{
		angle = DPB * I;
		value = 60 + (MAXV / 2.0 * (1.0 + sin(angle * RAD)));
		
		if (value > max)
			max = value;
		
		if (value < min)
			min = value;
		
		SINEWAVE[I] = value;
	}
	
		while (1)
		{
			for (int X = 0; X < 4096; X++)
			{
				DAC->DHR12R1 = SINEWAVE[X];
			}
		}
	
//		while(1)
//	{
//		DAC->DHR12R1 = 0x0FFF;
////		DAC->DHR12R1 = 0x0FEF;
////		DAC->DHR12R1 = 0x0FDF;
////		DAC->DHR12R1 = 0x0FCF;
////		DAC->DHR12R1 = 0x0FBF;
//		DAC->DHR12R1 = 0x0FAF;
//	
//	}
	
	return 0;
	
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//  
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//  for (;;)
//  {
//	  GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
//	  //Delay();
//	  GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
//	  //Delay();
//  }
}