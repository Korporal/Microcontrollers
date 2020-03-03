#pragma once
#include <_stdint.h>
typedef struct 
{
	const uint32_t CTCIF;
	const uint32_t CHTIF;
	const uint32_t CTEIF;
	const uint32_t CDMEIF;
	const uint32_t CFEIF;

} DMA_HIFCR_STREAM;
typedef struct
{
	DMA_HIFCR_STREAM Stream7;
	DMA_HIFCR_STREAM Stream6;
	DMA_HIFCR_STREAM Stream5;
	DMA_HIFCR_STREAM Stream4;
} DMA_HIFCR_FLAGS;
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
typedef struct 
{
	const uint32_t ENABLE_DAC_CLOCK;
	const uint32_t ENABLE_POWER_CLOCK;
	const uint32_t ENABLE_CEC_CLOCK;
	const uint32_t ENABLE_CAN2_CLOCK;
	const uint32_t ENABLE_CAN1_CLOCK;
	const uint32_t ENABLE_FMPI2C1_CLOCK;
	const uint32_t ENABLE_I2C3_CLOCK;
	const uint32_t ENABLE_I2C2_CLOCK;
	const uint32_t ENABLE_I2C1_CLOCK;
	const uint32_t ENABLE_UART5_CLOCK;
	const uint32_t ENABLE_UART4_CLOCK;
	const uint32_t ENABLE_USART3_CLOCK;
	const uint32_t ENABLE_USART2_CLOCK;
	const uint32_t ENABLE_SPDIFRX_CLOCK;
	const uint32_t ENABLE_SPI3_CLOCK;
	const uint32_t ENABLE_SPI2_CLOCK;
	const uint32_t ENABLE_WWDG_CLOCK;
	const uint32_t ENABLE_TIM14_CLOCK;
	const uint32_t ENABLE_TIM13_CLOCK;
	const uint32_t ENABLE_TIM12_CLOCK;
	const uint32_t ENABLE_TIM7_CLOCK;
	const uint32_t ENABLE_TIM6_CLOCK;
	const uint32_t ENABLE_TIM5_CLOCK;
	const uint32_t ENABLE_TIM4_CLOCK;
	const uint32_t ENABLE_TIM3_CLOCK;
	const uint32_t ENABLE_TIM2_CLOCK;

} APB1ENR_FLAGS;
// Defines the GPIO ports available.
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
// Defines the available modes for a GPIO port.
typedef struct 
{
	const MODER_PORTS INPUT;
	const MODER_PORTS GENERAL_PURPOSE_OUTPUT;
	const MODER_PORTS ALTERNATE;
	const MODER_PORTS ANALOG;
} MODES;
extern DMA_HIFCR_FLAGS DMA_HIFCR =
{ 
		// Stream 7
        // reserved 4 bits
		1 << 27,
		1 << 26,
		1 << 25,
		1 << 24,
		// reserved 1 bit
		1 << 22,
	
		1 << 21,
		1 << 20,
		1 << 19,
		1 << 18,
		// reserved 1 bit
		1 << 16,

	    // reserved 4 bits

		1 << 11,
		1 << 10,
		1 << 9,
		1 << 8,
		// reserved 1 bit
		1 << 6,

		1 << 5,
		1 << 4,
		1 << 3,
		1 << 2,
		// reserved 1 bit
		1 << 0
		
};
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
extern  APB1ENR_FLAGS APB1ENR = 
{
	// reserved 2 bit1
	1 << 29,
	1 << 28,
	1 << 27,
	1 << 26,
	1 << 25,
	1 << 24,
	1 << 23,
	1 << 22,
	1 << 21,
	1 << 20,
	1 << 19,
	1 << 18,
	1 << 17,
	1 << 16,
	1 << 15,	
	1 << 14,
	// reserved 2 bits
	1 << 11,	
	// reserved 2 bits
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
// Defines the IO direction and modes for GPIO ports.
extern MODES MODER =
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