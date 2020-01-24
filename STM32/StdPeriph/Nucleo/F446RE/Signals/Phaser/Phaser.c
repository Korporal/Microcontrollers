#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <math.h>

#define PI 3.14159265358979323846
#define RAD (double)(PI/180.0)
#define DPB (double)(360.0 / 4096.0)

#define MINV 0x032
#define MAXV 0xe1C

int32_t SINEWAVE[4096];
void Scan(int Offset, uint32_t * DACAReg, uint32_t * DACBReg);

int main()
{
	
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x00000F00; // PA4, PA5 Analog
	RCC->APB1ENR |= 1 << 29;    // Enable DAC Clock
	DAC->CR |= 0x00010001;      // Enable each DAC
	
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
	
	while (1)
	{
		for (int Phase = 0; Phase < 4096; Phase++)
		{
			Scan(Phase, &(DAC->DHR12R1), &(DAC->DHR12R2));
		}
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