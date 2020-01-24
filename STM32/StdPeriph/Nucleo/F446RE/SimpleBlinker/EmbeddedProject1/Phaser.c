#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <math.h>

#define PI 3.14159265358979323846
#define RAD (double)(PI/180.0)
#define DPB (double)(360.0 / 4096.0)

typedef struct MODE_Pair_Struct
{
	unsigned int RW0 : 1;
	unsigned int RW1 : 1;
} __attribute__((packed)) MODE_Pair;

typedef struct MODER_Struct
{
	MODE_Pair PAIR[16];
} __attribute__((packed)) MODER;

typedef struct OTYPER_Struct
{
	
} OTYPER;
typedef struct GPIO_Struct
{
	MODER MODER;
	OTYPER OTYPER;
} GPIO;

typedef struct AHB1_Struct
{
	GPIO GPIO[8];
} * AHB1_Ptr;

static AHB1_Ptr AHB1 = (AHB1_Ptr )(0x40020000);

// The max DAC output voltage is reached before we reach 0x0FFF
// The min DAC output voltage is reached before we reach 0x0000

#define MINV 0x032
#define MAXV 0xe1C

void Delay()
{
	int i;
	for (i = 0; i < 10; i++)
		asm("nop");
}
	int32_t SINEWAVE[4096];
void Scan(int Offset, uint32_t * DACAReg, uint32_t * DACBReg);

int main()
{
	
	#define MODE_RESET 0;
	#define MODE_GP_OUTPUT 1
	#define MODE_ALTERNATE 2
	#define MODE_ANALOG 3
	

	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x00000F00; // PA4, PA5 Analog
	RCC->APB1ENR |= 1 << 29;    // Enable DAC Clock
	DAC->CR |= 0x00010001;      // Enable each DAC
	
	int32_t value;
	int32_t min = 0x7FFF;
	int32_t max = 0;
	
	double angle;
	
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
		for (int Phase = 0; Phase < 4096; Phase++)
		{
			Scan(Phase, &(DAC->DHR12R1), &(DAC->DHR12R2));
		}
	}
	
}

void Scan(int Offset, uint32_t * DACAReg, uint32_t * DACBReg)
{
	int B = 0;
	
	for (int I = Offset; I < 4096; I++)
	{
		(*DACAReg) = SINEWAVE[I];
		(*DACBReg) = SINEWAVE[B++];
	}
	
	for (int I = 0; I < Offset; I++)
	{
		(*DACAReg) = SINEWAVE[I];
		(*DACBReg) = SINEWAVE[B++];
	}
}