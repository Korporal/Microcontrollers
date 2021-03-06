#include "SineTables.h"
#include "math.h"

#define PI 3.14159265358979323846
#define RAD (double)(PI/180.0)
//#define DPB (double)(360.0 / 4096.0)

//#define MINV 0x032
//#define MAXV 0xe1C


void GenerateSineTable(uint32_t table[], uint32_t MinVoltage, uint32_t MaxVoltage, uint16_t  Granularity, uint16_t * Status)
{

	*Status = 0;	
	
	// Calculate a table of Sine values adjusted to be in
	// increments of 360/4096 of a degree. We also compensate 
	// for the fact that DAC ouput can't reach ground or the +ve rail.
	// A Phase of 4096 corresponds to 360 degrees.
	
	
	uint32_t value;
	uint32_t min = 0x7FFF;
	uint32_t max = 0;
	double angle;
	double degreesPerBit = (double)(360.0 / Granularity);
	
	for (uint16_t I = 0; I < Granularity; I++)
	{
		angle = degreesPerBit * I;
		
		// the way we use Min or Max is not quite correct yet...
		
		value = MinVoltage + ((MaxVoltage-MinVoltage) / 2.0 * (1.0 + sin(angle * RAD)));
		
		if (value > max)
			max = value;
		
		if (value < min)
			min = value;
		
		table[I] = value;
	}
}

