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

// Simple examples of generating sine waves on each DAC.
// DAC1 drives output PA4 - Pin A2 of CN8
// DAC2 drives output PA5 - Pin SCK/D13 of CN9

#define ENABLE_DAC1 0x00010000
#define ENABLE_DAC2 0x00000001
#define ENABLE_DAC_CLOCK (1 << 29)
//#define ENABLE_PA4 0x00000300
//#define ENABLE_PA5 0x00000C00
//#define ENABLE_GPIOA_CLOCK 0x00000001

typedef struct 
{
	const uint32_t ENABLE_OTGHSULPI;
	const uint32_t ENABLE_OTGHS;
	const uint32_t ENABLE_ETHMACPTP;
	const uint32_t ENABLE_ETHMACRX;
	const uint32_t ENABLE_ETHMACTX;
	const uint32_t ENABLE_ETHMAC;
	const uint32_t ENABLE_DMA_2;
	const uint32_t ENABLE_DMA_1;
	const uint32_t ENABLE_CCM_DATA_RAM;
	const uint32_t ENABLE_BKP_SRAM;
	const uint32_t ENABLE_CRC;
	const uint32_t ENABLE_GPIOI_CLOCK;
	const uint32_t ENABLE_GPIOH_CLOCK;
	const uint32_t ENABLE_GPIOG_CLOCK;
	const uint32_t ENABLE_GPIOF_CLOCK;
	const uint32_t ENABLE_GPIOE_CLOCK;
	const uint32_t ENABLE_GPIOD_CLOCK;
	const uint32_t ENABLE_GPIOC_CLOCK;
	const uint32_t ENABLE_GPIOB_CLOCK;
	const uint32_t ENABLE_GPIOA_CLOCK;

} AHB1ENR_FLAGS;

extern  AHB1ENR_FLAGS AHB1ENR = 
{
	// reserved 1 bit1
	1 << 30,
	1 << 29,
	1 << 28,
	1 << 27,
	1 << 26,
	1 << 25,
	// reserved 2 bits
	1 << 22,
	1 << 21,
	1 << 20,	
	// reserved 1 bits
	1 << 18,
	// reserved 5 bits
	1 << 12,	
	// reserved 3 bits
	1 << 8,
	1 << 7,
	1 << 6,
	1 << 5,
	1 << 4,
	1 << 3,
	1 << 2,
	1 << 1,
	1 << 0
};

//typedef struct
//{
//	unsigned char INPUT;
//	unsigned char GENERAL_PURPOSE_OUTPUT;
//	unsigned char ALTERNATE_FUNCTION;
//	unsigned char ANALOG;
//} MODE_FLAGS;
//
//extern MODE_FLAGS MODES =
//{ 
//	0,
//	1,
//	2,
//	3
//};
//
//typedef struct
//{
//	uint32_t MODER_1;
//	uint32_t MODER_0;
//} MODER;
//
//extern 

typedef struct 
{
	const uint32_t P0;
	const uint32_t P1;
	const uint32_t P2;
	const uint32_t P3;
	const uint32_t P4;
	const uint32_t P5;
	const uint32_t P6;
	const uint32_t P7;
	const uint32_t P8;
	const uint32_t P9;
	const uint32_t P10;
	const uint32_t P11;
	const uint32_t P12;
	const uint32_t P13;
	const uint32_t P14;
	const uint32_t P15;
} MODER_PORTS;


typedef struct 
{
	const MODER_PORTS INPUT;
	const MODER_PORTS GENERAL_PURPOSE_OUTPUT;
	const MODER_PORTS ALTERNATE;
	const MODER_PORTS ANALOG;
} MODES;

extern MODES MODE =
{ 
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
	},
	
	{
		1 << 0,
		1 << 2,
		1 << 4,
		1 << 6,
		1 << 8,
		1 << 10,
		1 << 12,
		1 << 14,
		1 << 16,
		1 << 18,
		1 << 20,
		1 << 22,
		1 << 24,
		1 << 26,
		1 << 28,
		1 << 30,
	},

	
	{ 
		2 << 0,
		2 << 2,
		2 << 4,
		2 << 6,
		2 << 8,
		2 << 10,
		2 << 12,
		2 << 14,
		2 << 16,
		2 << 18,
		2 << 20,
		2 << 22,
		2 << 24,
		2 << 26,
		2 << 28,
		2 << 30,
	},
	{ 
		3 << 0,
		3 << 2,
		3 << 4,
		3 << 6,
		3 << 8,
		3 << 10,
		3 << 12,
		3 << 14,
		3 << 16,
		3 << 18,
		3 << 20,
		3 << 22,
		3 << 24,
		3 << 26,
		3 << 28,
		3 << 30,
	}
};



int main()
{

	
	RCC->AHB1ENR |= AHB1ENR.ENABLE_GPIOA_CLOCK;
	
	GPIOA->MODER |= MODE.ANALOG.P4 | MODE.ANALOG.P5;
	
	RCC->APB1ENR |= ENABLE_DAC_CLOCK;    // Enable DAC Clock
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
		
		for (int Phase = 0; Phase < 4096; Phase++)
		{
			Scan(Phase, &(DAC->DHR12R2), &(DAC->DHR12R1));
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