#ifndef __AVR_CPP_IO_H_CAN__
#define __AVR_CPP_IO_H_CAN__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

struct CanGeneralConfig
{
	uint8_t softwareReset				:1;
	uint8_t enable						:1;
	uint8_t testMode					:1;
	uint8_t listeningMode				:1;
	uint8_t ttcOnEof					:1;
	uint8_t timeTriggerCommunication	:1;
	uint8_t overloadFrame				:1;
	uint8_t abort						:1;
};

struct CanGeneralStatus
{
	uint8_t errorPassiveMode	:1;
	uint8_t busOff	 			:1;
	uint8_t enable				:1;
	uint8_t receiverBusy		:1;
	uint8_t transmitterBusy		:1;
	uint8_t 					:1;
	uint8_t overloadFrame	 	:1;
	uint8_t 					:1;
};

struct CanGeneralInterruptFlag
{
	uint8_t acknowledgmentError	:1;
	uint8_t formError			:1;
	uint8_t crcError			:1;
	uint8_t stuffError			:1;
	uint8_t frameBufferReceive	:1;
	uint8_t timerOverrun		:1;
	uint8_t bussOff				:1;
	uint8_t general				:1;
};

struct CanGeneralInterruptEnable
{
	uint8_t timerOverrun		:1;
	uint8_t generalErrors		:1;
	uint8_t frameBufferReceive	:1;
	uint8_t mobErrors			:1;
	uint8_t transmit			:1;
	uint8_t receive				:1;
	uint8_t bussOff				:1;
	uint8_t general				:1;
};

struct CanMobEnable
{
	 uint16_t mob0		:1;
	 uint16_t mob1		:1;
	 uint16_t mob2		:1;
	 uint16_t mob3		:1;
	 uint16_t mob4		:1;
	 uint16_t mob5		:1;
	 uint16_t mob6		:1;
	 uint16_t mob7		:1;
	 uint16_t mob8		:1;
	 uint16_t mob9		:1;
	 uint16_t mob10		:1;
	 uint16_t mob11		:1;
	 uint16_t mob12		:1;
	 uint16_t mob13		:1;
	 uint16_t mob14		:1;
	 uint16_t 			:1;
};

struct CanMobInterruptEnable
{
	 uint16_t mob0		:1;
	 uint16_t mob1		:1;
	 uint16_t mob2		:1;
	 uint16_t mob3		:1;
	 uint16_t mob4		:1;
	 uint16_t mob5		:1;
	 uint16_t mob6		:1;
	 uint16_t mob7		:1;
	 uint16_t mob8		:1;
	 uint16_t mob9		:1;
	 uint16_t mob10		:1;
	 uint16_t mob11		:1;
	 uint16_t mob12		:1;
	 uint16_t mob13		:1;
	 uint16_t mob14		:1;
	 uint16_t 			:1;
};

struct CanMobInterruptFlag
{
	 uint16_t mob0		:1;
	 uint16_t mob1		:1;
	 uint16_t mob2		:1;
	 uint16_t mob3		:1;
	 uint16_t mob4		:1;
	 uint16_t mob5		:1;
	 uint16_t mob6		:1;
	 uint16_t mob7		:1;
	 uint16_t mob8		:1;
	 uint16_t mob9		:1;
	 uint16_t mob10		:1;
	 uint16_t mob11		:1;
	 uint16_t mob12		:1;
	 uint16_t mob13		:1;
	 uint16_t mob14		:1;
	 uint16_t 			:1;
};

struct CanTiming
{
	 uint32_t 						:1;
	 uint32_t baudRatePrescaler		:6;
	 uint32_t 						:2;
	 uint32_t propagationTime		:3;
	 uint32_t 						:1;
	 uint32_t reSyncJumpWidth		:2;
	 uint32_t 						:1;
	 uint32_t threePointSampling	:1;
	 uint32_t phaseSegment1Time		:3;
	 uint32_t phaseSegment2Time		:3;
	 uint32_t 						:1;
	 uint32_t timerPrescale			:8;
};

struct CanHighestPriorityMob
{
	uint8_t generalPurposeBits		:4;
	uint8_t highestPriorityMob		:4;
};

struct CanPage
{
	uint8_t dataBufferIndex			:3;
	uint8_t autoIncrementDisable	:1;
	uint8_t mobNumber				:4;
};

// ------------------------ MOb Registers --------------------------

struct CanMobStatus
{
	uint8_t acknowledgmentError		:1;
	uint8_t formError				:1;
	uint8_t crcError				:1;
	uint8_t stuffError				:1;
	uint8_t bitError				:1;
	uint8_t receiveFinish			:1;
	uint8_t transmitFinish			:1;
	uint8_t dataLengthWarning		:1;
};

struct CanMobControl
{
	enum Type
	{
		Disable,
		Transmit,
		Receive,
		FrameBufferReceive
	};

	uint8_t dataLength		:4;
	uint8_t idExtension		:1;
	uint8_t automaticReply	:1;
	Type type				:2;
};

struct CanMobId
{
	union
	{
		struct
		{
			uint32_t rb0						:1;
			uint32_t rb1						:1;
			uint32_t remoteTransmissionRequest	:1;
			uint32_t idB						:29;
		};
		struct
		{
			uint32_t 							:21;
			uint32_t idA						:11;
		};
	};
};

struct CanMobMask
{
	union
	{
		struct
		{
			uint32_t idExtension				:1;
			uint32_t 							:1;
			uint32_t remoteTransmissionRequest	:1;
			uint32_t idB						:29;
		};
		struct
		{
			uint32_t 							:21;
			uint32_t idA						:11;
		};
	};
};

#endif // ifndef __AVR_CPP_IO_H_CAN__

