#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <math.h>

#include <peripherals.h>

#define PI 3.14159265358979323846
#define RAD (double)(PI/180.0)
#define DPB (double)(360.0 / 4096.0)

#define MINV 0x032
#define MAXV 0xe1C

int32_t SINEWAVE[4096];
void Scan(int Offset, uint32_t * DACAReg, uint32_t * DACBReg);

// Simple examples of generating sine waves on each DAC.
// DAC1 drives output PA4 - Pin A2 of CN8
// DAC2 drives output PA5 - Pin SCK/D13 of CN9

#define ENABLE_DAC1 0x00010000
#define ENABLE_DAC2 0x00000001

int main()
{

	RCC->AHB1ENR |= AHB1ENR.ENABLE_GPIOA_CLOCK | AHB1ENR.ENABLE_DMA_1;
	
	GPIOA->MODER |= MODER.ANALOG.P4 | MODER.ANALOG.P5; // Expecting this to be optimized and gen same code as line below
	
	RCC->APB1ENR |= APB1ENR.ENABLE_DAC_CLOCK;    // Enable DAC Clock
	
	DAC->CR |= ENABLE_DAC1 | ENABLE_DAC2;      // Enable each DAC
	
	// DMA1 can use DAC1 and DAC2 on DMA channel 7, streams 5 & 6 respectively.
	
	int32_t value;
	int32_t min = 0x7FFF;
	int32_t max = 0;
	
	double angle;
	
	// Calculate a table of Sine values adjusted to be in
	// increments of 360/4096 of a degree. We also compensate 
	// for the fact that DAC ouput can't reach ground or the +ve rail.
	
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
	

	// Repeatedly scan the sinewave table. One call to 'Scan'
	// will generate one cycle and the phase of the signal
	// written to DAC2 relative to DAC1 is dictated by the 
	// 'Phase' value.
	// A Phase of 4096 corresponds to 360 degrees.
	
	while (1)
	{
		for (int Phase = 0; Phase < 4096; Phase++)
		{
			Scan(Phase, &(DAC->DHR12R1), &(DAC->DHR12R2));
		}
		
//		for (int Phase = 0; Phase < 4096; Phase++)
//		{
//			Scan(Phase, &(DAC->DHR12R2), &(DAC->DHR12R1));
//		}

	}
	
}

/*-----------------------------------------------------------*/
/* This function 'plays' the entire digitized sinewave table */
/* to each DAC in an interleaved manner. The phase of the    */
/* the second wave relative to the first is dictated by the  */
/* Offset argument.                                          */
/*-----------------------------------------------------------*/

void Scan(int Offset, uint32_t * DACAReg, uint32_t * DACBReg)
{
	int B = 0; // Always start at 0 for DAC B
	
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