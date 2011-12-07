#ifndef __AVR_CPP_IO_H_SPI__
#define __AVR_CPP_IO_H_SPI__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

union SpiStatusControl
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

	volatile HoleField<Prescale,0b100000011> prescale;
	struct
	{
		volatile uint16_t							:2;
		volatile Phase			phase				:1;
		volatile LeadingEdge	leadingEdge			:1;
		volatile uint16_t		master				:1;
		volatile DataOrder		dataOrder			:1;
		volatile uint16_t		enable				:1;
		volatile uint16_t		interruptEnable		:1;
		volatile uint16_t							:6;
		volatile uint16_t		writeCollision		:1;
		volatile uint16_t		transferComplete	:1;
	};
	HoleField<Prescale,0b100000011> prescale_;
	struct
	{
		uint16_t							:2;
		Phase			phase_				:1;
		LeadingEdge		leadingEdge_		:1;
		uint16_t		master_				:1;
		DataOrder		dataOrder_			:1;
		uint16_t		enable_				:1;
		uint16_t		interruptEnable_	:1;
		uint16_t							:6;
		uint16_t		writeCollision_		:1;
		uint16_t		transferComplete_	:1;
	};
};


#endif // ifndef __AVR_CPP_IO_H_SPI__

