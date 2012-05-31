#ifndef __AVR_CPP_IO_H_USART__
#define __AVR_CPP_IO_H_USART__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif


struct UsartControl
{
	uint32_t multiProcessorCommunicationMode	:1;
	uint32_t doubleSpeed						:1;
	uint32_t parityError						:1;
	uint32_t dataOverRunError					:1;
	uint32_t frameError							:1;
	uint32_t dataRegEmpty						:1;
	uint32_t txComplete							:1;
	uint32_t rxComplete							:1;
	uint32_t txDataBit8							:1;
	uint32_t rxDataBit8							:1;
	uint32_t charSize2bit						:1;
	uint32_t txEnable							:1;
	uint32_t rxEnable							:1;
	uint32_t dataRegEmptyInterrupt				:1;
	uint32_t txCompleteInterrupt				:1;
	uint32_t rxCompleteInterrupt				:1;
	uint32_t clockPolaritySyncMode				:1;
	uint32_t charSize0bit						:1;
	uint32_t charSize1bit						:1;
	uint32_t stopBitDouble						:1;
	uint32_t parityOdd							:1;
	uint32_t parityGeneration					:1;
	uint32_t synchronous						:1;
	uint32_t 									:9;
};


struct UsartBaudRate
{
	uint16_t baudRate	:12;
	uint16_t 			:4;
};


#endif // ifndef __AVR_CPP_IO_H_USART__

