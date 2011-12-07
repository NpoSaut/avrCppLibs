#ifndef __AVR_CPP_IO_H_WATCHDOG__
#define __AVR_CPP_IO_H_WATCHDOG__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

union WatchdogControl
{
	enum TimeOut
	{
		t16ms	= 0b000,
		t32ms	= 0b001,
		t64ms	= 0b010,
		t128ms	= 0b011,
		t256ms	= 0b100,
		t520ms	= 0b101,
		t1s		= 0b110,
		t2s		= 0b111
	};
	struct
	{
		volatile TimeOut timeOut	:3;
		volatile uint8_t enable		:1;
		volatile uint8_t change		:1;
		volatile uint8_t 			:3;
	};
	struct
	{
		TimeOut timeOut_	:3;
		uint8_t enable_		:1;
		uint8_t change_		:1;
		uint8_t 			:3;
	};
};


#endif // ifndef __AVR_CPP_IO_H_WATCHDOG__

