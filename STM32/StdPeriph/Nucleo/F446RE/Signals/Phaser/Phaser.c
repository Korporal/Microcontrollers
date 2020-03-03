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

#define ENABLE_DAC1     0x00000001 // DAC1 is PA4 = 
#define ENABLE_DAC2     0x00010000 // DAC2 is PA5
#define ENABLE_DAC2_DMA 0x10000000
#define ENABLE_DAC1_DMA 0x00001000

void DMA1_Stream5_IRQHandler();
void PopulateTable();

uint32_t interrupts = 0;

int main()
{
	
	uint32_t looper = 0;
	uint32_t dummy;
	
	PopulateTable();
	
	RCC->AHB1ENR |= AHB1ENR.ENABLE_GPIOA_CLOCK | AHB1ENR.ENABLE_DMA_1;
	dummy = RCC->AHB1ENR; // SEE: https://www.st.com/content/ccc/resource/technical/document/errata_sheet/38/e6/37/64/08/38/45/67/DM00068628.pdf/files/DM00068628.pdf/jcr:content/translations/en.DM00068628.pdf
	GPIOA->MODER |= MODER.ANALOG.P4 | MODER.ANALOG.P5; // Expecting this to be optimized and gen same code as line below
	RCC->APB1ENR |= APB1ENR.ENABLE_DAC_CLOCK;    // Enable DAC Clock
	DAC->CR |= ENABLE_DAC1 | ENABLE_DAC1_DMA; 
	
	// DMA1, S5, C7 -> DAC1 -> 
	// DMA1, S6, C7 -> DAC2
	
	DMA1->HIFCR = DMA_HIFCR.Stream5.CDMEIF | DMA_HIFCR.Stream5.CFEIF | DMA_HIFCR.Stream5.CHTIF | DMA_HIFCR.Stream5.CTCIF | DMA_HIFCR.Stream5.CTEIF;
	
	DMA1_Stream5->CR = 0;

	while (DMA1_Stream5->CR & 1)
	{
		looper++;
	}
	
	DMA1_Stream5->PAR  = (uint32_t)&(DAC->DHR12R1);
	DMA1_Stream5->M0AR = (uint32_t)(SINEWAVE);
	DMA1_Stream5->NDTR = 4096;
	DMA1_Stream5->CR  = 0x0E000000;  // Channel 7
	DMA1_Stream5->CR |= 0x00005440;
	DMA1_Stream5->CR |= 0x00000016;
	DMA1_Stream5->FCR = 0;
	
	NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	
	DMA1_Stream5->CR |= 1;  // enable the dma stream
	
	while (1)
	{
		looper++;
	}
	
}

void PopulateTable()
{
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

void DMA1_Stream5_IRQHandler()
{
	interrupts++;
}