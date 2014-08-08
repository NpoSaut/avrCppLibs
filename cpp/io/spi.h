#ifndef __AVR_CPP_IO_H_SPI__
#define __AVR_CPP_IO_H_SPI__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

#include <cpp/io/hole-field.h>

struct SpiStatusControl
{
	enum Prescale : uint16_t
	{
		F2		= 0b100000000,
		F4		= 0b000000000,
		F8		= 0b100000001,
		F16		= 0b000000001,
		F32		= 0b100000010,
		F64		= 0b100000011,
		F128	= 0b000000011
	};
	enum Phase
	{
		DataSampleOnLeadingEdge		= 0,
		DataSampleOnTrailingEdge	= 1
	};
	enum LeadingEdge
	{
		Rising		= 0,
		Falling		= 1
	};
	enum DataOrder
	{
		MsbFirst		= 0,
		LsbFirst		= 1
	};

	union
	{
		HoleField<Prescale,0b100000011> prescale;
		struct
		{
			uint16_t							:2;
			Phase			phase				:1;
			LeadingEdge		leadingEdge			:1;
			uint16_t		master				:1;
			DataOrder		dataOrder			:1;
			uint16_t		enable				:1;
			uint16_t		interruptEnable		:1;
			uint16_t							:6;
			uint16_t		writeCollision		:1;
			uint16_t		transferComplete	:1;
		};
	};
};


#endif // ifndef __AVR_CPP_IO_H_SPI__

