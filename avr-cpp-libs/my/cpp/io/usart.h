#ifndef __AVR_CPP_IO_H_USART__
#define __AVR_CPP_IO_H_USART__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif


struct UsartControl
{
	union
	{
		struct
		{
			volatile uint8_t multiProcessorCommunicationMode	:1;
			volatile uint8_t doubleSpeed						:1;
			volatile uint8_t parityError						:1;
			volatile uint8_t dataOverRunError					:1;
			volatile uint8_t frameError							:1;
			volatile uint8_t dataRegEmpty						:1;
			volatile uint8_t txComplete							:1;
			volatile uint8_t rxComplete							:1;
			volatile uint8_t txDataBit8							:1;
			volatile uint8_t rxDataBit8							:1;
			volatile uint8_t charSize2bit						:1;
			volatile uint8_t txEnable							:1;
			volatile uint8_t rxEnable							:1;
			volatile uint8_t dataRegEmptyInterrupt				:1;
			volatile uint8_t txCompleteInterrupt				:1;
			volatile uint8_t rxCompleteInterrupt				:1;
			volatile uint8_t clockPolaritySyncMode				:1;
			volatile uint8_t charSize0bit						:1;
			volatile uint8_t charSize1bit						:1;
			volatile uint8_t stopBitDouble						:1;
			volatile uint8_t parityOdd							:1;
			volatile uint8_t parityGeneration					:1;
			volatile uint8_t synchronous						:1;
			volatile uint8_t 									:1;
		};
		struct
		{
			uint8_t multiProcessorCommunicationMode_	:1;
			uint8_t doubleSpeed_						:1;
			uint8_t parityError_						:1;
			uint8_t dataOverRunError_					:1;
			uint8_t frameError_							:1;
			uint8_t dataRegEmpty_						:1;
			uint8_t txComplete_							:1;
			uint8_t rxComplete_							:1;
			uint8_t txDataBit8_							:1;
			uint8_t rxDataBit8_							:1;
			uint8_t charSize2bit_						:1;
			uint8_t txEnable_							:1;
			uint8_t rxEnable_							:1;
			uint8_t dataRegEmptyInterrupt_				:1;
			uint8_t txCompleteInterrupt_				:1;
			uint8_t rxCompleteInterrupt_				:1;
			uint8_t clockPolaritySyncMode_				:1;
			uint8_t charSize0bit_						:1;
			uint8_t charSize1bit_						:1;
			uint8_t stopBitDouble_						:1;
			uint8_t parityOdd_							:1;
			uint8_t parityGeneration_					:1;
			uint8_t synchronous_						:1;
			uint8_t 									:1;
		};
	};
};


struct UsartBaudRate
{
	union
	{
		struct
		{
			volatile uint16_t baudRate	:12;
			volatile uint16_t 	:4;
		};
		struct
		{
			uint16_t baudRate_	:12;
			uint16_t 	:4;
		};
	};
};


#endif // ifndef __AVR_CPP_IO_H_USART__

