#ifndef __AVR_CPP_IO_H_TIMERS__
#define __AVR_CPP_IO_H_TIMERS__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

#include <cpp/io/hole-field.h>

struct TimerControl8
{
	enum ClockType
	{
		NoClock 	= 0,
		Prescale1 	= 1,
		Prescale8 	= 2,
		Prescale64 	= 3,
		Prescale256	= 4,
		Prescale1024= 5,
		ExtPinFall	= 6,
		ExtPinRise	= 7
	};
	enum OutputMode
	{
		OutPinDisconnect	= 0,
		TogglePin			= 1,
		ClearPin			= 2,
		SetPin				= 3
	};
	enum Waveform
	{
		Normal				= 0b00000000,
		PwmPhaseCorrect		= 0b01000000,
		ClearOnCompare		= 0b00001000,
		PwmFast				= 0b01001000
	};

	union
	{
		struct
		{
			 ClockType		clockType		:3;
			 uint8_t						:1;
			 OutputMode		outputMode		:2;
			 uint8_t						:1;
			 uint8_t		forceCompare	:1;

		};
		HoleField<Waveform, 0b01001000>	waveform;
	};
};

struct TimerControl8_2
{
	enum ClockType
	{
		NoClock 	= 0,
		Prescale1 	= 1,
		Prescale8 	= 2,
		Prescale32	= 3,
		Prescale64 	= 4,
		Prescale128	= 5,
		Prescale256	= 6,
		Prescale1024= 7
	};
	enum OutputMode
	{
		OutPinDisconnect	= 0,
		TogglePin			= 1,
		ClearPin			= 2,
		SetPin				= 3
	};
	enum Waveform
	{
		Normal				= 0b00000000,
		PwmPhaseCorrect		= 0b01000000,
		ClearOnCompare		= 0b00001000,
		PwmFast				= 0b01001000
	};

	union
	{
		struct
		{
			 ClockType		clockType		:3;
			 uint8_t						:1;
			 OutputMode		outputMode		:2;
			 uint8_t						:1;
			 uint8_t		forceCompare	:1;

		};
		HoleField<Waveform, 0b01001000>	waveform;
	};
};


struct TimerInterruptMask8
{
	uint8_t OverflowInterrupt	:1;
	uint8_t CompInterrupt			:1;
	uint8_t 					:6;
};

struct TimerInterruptFlag8
{
	uint8_t OverflowOccur	:1;
	uint8_t CompOccur		:1;
	uint8_t 				:6;
};




struct TimerControl16
{
	enum ClockType
	{
		NoClock 	= 0,
		Prescale1 	= 1,
		Prescale8 	= 2,
		Prescale64 	= 3,
		Prescale256	= 4,
		Prescale1024= 5,
		ExtPinFall	= 6,
		ExtPinRise	= 7
	};
	enum OutputMode
	{
		OutPinDisconnect	= 0,
		TogglePin			= 1,
		ClearPin			= 2,
		SetPin				= 3
	};
	enum Waveform
	{
		Normal					= 0b0000000000000,
		PwmPhaseCorrect			= 0b0000000000001,
		PwmPhaseCorrect8bit		= 0b0000000000001,
		PwmPhaseCorrect9bit		= 0b0000000000010,
		PwmPhaseCorrect10bit	= 0b0000000000011,
		PwmPhaseCorrectIcr		= 0b1000000000010,
		PwmPhaseCorrectOcr		= 0b1000000000011,
		PwmPhaseFreqCorrectIcr	= 0b1000000000000,
		PwmPhaseFreqCorrectOcr	= 0b1000000000001,
		ClearOnCompare			= 0b0100000000000,
		ClearOnCompareOcr		= 0b0100000000000,
		ClearOnCompareIcr		= 0b1100000000000,
		PwmFast					= 0b0100000000001,
		PwmFast8bit				= 0b0100000000001,
		PwmFast9bit				= 0b0100000000010,
		PwmFast10bit			= 0b0100000000011,
		PwmFastIcr				= 0b1100000000010,
		PwmFastOcr				= 0b1100000000011,
	};
	enum InputEdge
	{
		Fall = 0,
		Negative = 0,
		Rise = 1,
		Positive = 1
	};

	union
	{
		HoleField<Waveform,0b1100000000011> waveform;
		struct
		{
			 uint32_t						:6;
			 OutputMode		outputMode		:2;
			 uint32_t						:15;
			 uint8_t		forceCompare	:1;
		};
		struct
		{
			 uint32_t						:2;
			 OutputMode		outputModeC		:2;
			 OutputMode		outputModeB		:2;
			 OutputMode		outputModeA		:2;
			 ClockType		clockType		:3;
			 uint32_t						:3;
			 InputEdge		inputEdge		:1;
			 uint8_t		noiseFilter		:1;
			 uint32_t						:5;
			 uint8_t		forceComareC	:1;
			 uint8_t		forceComareB	:1;
			 uint8_t		forceComareA	:1;
		};
	};
};

struct TimerInterruptFlag16
{
	union
	{
		struct
		{
			uint8_t 					:1;
			uint8_t CompOccur			:1;
			uint8_t 					:6;
		};
		struct
		{
			uint8_t OverflowOccur		:1;
			uint8_t CompAOccur			:1;
			uint8_t CompBOccur			:1;
			uint8_t CompCOccur			:1;
			uint8_t 					:1;
			uint8_t InputCaptureOccur	:1;
			uint8_t 					:2;
		};
	};
};

struct TimerInterruptMask16
{
	union
	{
		struct
		{
			uint8_t 					:1;
			uint8_t CompInterrupt		:1;
			uint8_t 					:6;
		};
		struct
		{
			uint8_t OverflowInterrupt		:1;
			uint8_t CompAInterrupt			:1;
			uint8_t CompBInterrupt			:1;
			uint8_t CompCInterrupt			:1;
			uint8_t 						:1;
			uint8_t InputCaptureInterrupt	:1;
			uint8_t 						:2;
		};
	};
};


#endif // ifndef __AVR_CPP_IO_H_TIMERS__

