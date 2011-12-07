#ifndef __AVR_CPP_IO_H_CAN__
#define __AVR_CPP_IO_H_CAN__

#ifndef __AVR_CPP_IO_H__
#  error "Include <cpp/io.h> instead of this file."
#endif

union CanGeneralConfig
{
	struct
	{
		volatile uint8_t softwareReset				:1;
		volatile uint8_t enable						:1;
		volatile uint8_t testMode					:1;
		volatile uint8_t listeningMode				:1;
		volatile uint8_t ttcOnEof					:1;
		volatile uint8_t timeTriggerCommunication	:1;
		volatile uint8_t overloadFrame				:1;
		volatile uint8_t abort						:1;
	};
	struct
	{
		uint8_t softwareReset_				:1;
		uint8_t enable_						:1;
		uint8_t testMode_					:1;
		uint8_t listeningMode_				:1;
		uint8_t ttcOnEof_					:1;
		uint8_t timeTriggerCommunication_	:1;
		uint8_t overloadFrame_				:1;
		uint8_t abort_						:1;
	};
};

union CanGeneralStatus
{
	struct
	{
		volatile uint8_t errorPassiveMode	:1;
		volatile uint8_t busOff  			:1;
		volatile uint8_t enable				:1;
		volatile uint8_t receiverBusy		:1;
		volatile uint8_t transmitterBusy 	:1;
		volatile uint8_t 					:1;
		volatile uint8_t overloadFrame  	:1;
		volatile uint8_t 					:1;
	};
	struct
	{
		uint8_t errorPassiveMode_	:1;
		uint8_t busOff_  			:1;
		uint8_t enable_				:1;
		uint8_t receiverBusy_		:1;
		uint8_t transmitterBusy_ 	:1;
		uint8_t 					:1;
		uint8_t overloadFrame_  	:1;
		uint8_t 					:1;
	};
};

union CanGeneralInterruptFlag
{
	struct
	{
		volatile uint8_t acknowledgmentError	:1;
		volatile uint8_t formError				:1;
		volatile uint8_t crcError				:1;
		volatile uint8_t stuffError				:1;
		volatile uint8_t frameBufferReceive		:1;
		volatile uint8_t timerOverrun			:1;
		volatile uint8_t bussOff				:1;
		volatile uint8_t general				:1;
	};
	struct
	{
		uint8_t acknowledgmentError_	:1;
		uint8_t formError_				:1;
		uint8_t crcError_				:1;
		uint8_t stuffError_				:1;
		uint8_t frameBufferReceive_		:1;
		uint8_t timerOverrun_			:1;
		uint8_t bussOff_				:1;
		uint8_t general_				:1;
	};
};

union CanGeneralInterruptEnable
{
	struct
	{
		volatile uint8_t timerOverrun			:1;
		volatile uint8_t generalErrors			:1;
		volatile uint8_t frameBufferReceive		:1;
		volatile uint8_t mobErrors				:1;
		volatile uint8_t transmit				:1;
		volatile uint8_t receive				:1;
		volatile uint8_t bussOff				:1;
		volatile uint8_t general				:1;
	};
	struct
	{
		uint8_t timerOverrun_			:1;
		uint8_t generalErrors_			:1;
		uint8_t frameBufferReceive_		:1;
		uint8_t mobErrors_				:1;
		uint8_t transmit_				:1;
		uint8_t receive_				:1;
		uint8_t bussOff_				:1;
		uint8_t general_				:1;
	};
};

union CanMobEnable
{
	struct
	{
		volatile uint16_t mob0	:1;
		volatile uint16_t mob1	:1;
		volatile uint16_t mob2	:1;
		volatile uint16_t mob3	:1;
		volatile uint16_t mob4	:1;
		volatile uint16_t mob5	:1;
		volatile uint16_t mob6	:1;
		volatile uint16_t mob7	:1;
		volatile uint16_t mob8	:1;
		volatile uint16_t mob9	:1;
		volatile uint16_t mob10	:1;
		volatile uint16_t mob11	:1;
		volatile uint16_t mob12	:1;
		volatile uint16_t mob13	:1;
		volatile uint16_t mob14	:1;
		volatile uint16_t 		:1;
	};
	struct
	{
		 uint16_t mob0_		:1;
		 uint16_t mob1_		:1;
		 uint16_t mob2_		:1;
		 uint16_t mob3_		:1;
		 uint16_t mob4_		:1;
		 uint16_t mob5_		:1;
		 uint16_t mob6_		:1;
		 uint16_t mob7_		:1;
		 uint16_t mob8_		:1;
		 uint16_t mob9_		:1;
		 uint16_t mob10_	:1;
		 uint16_t mob11_	:1;
		 uint16_t mob12_	:1;
		 uint16_t mob13_	:1;
		 uint16_t mob14_	:1;
		 uint16_t 			:1;
	};
};

union CanMobInterruptEnable
{
	struct
	{
		volatile uint16_t mob0	:1;
		volatile uint16_t mob1	:1;
		volatile uint16_t mob2	:1;
		volatile uint16_t mob3	:1;
		volatile uint16_t mob4	:1;
		volatile uint16_t mob5	:1;
		volatile uint16_t mob6	:1;
		volatile uint16_t mob7	:1;
		volatile uint16_t mob8	:1;
		volatile uint16_t mob9	:1;
		volatile uint16_t mob10	:1;
		volatile uint16_t mob11	:1;
		volatile uint16_t mob12	:1;
		volatile uint16_t mob13	:1;
		volatile uint16_t mob14	:1;
		volatile uint16_t 		:1;
	};
	struct
	{
		 uint16_t mob0_		:1;
		 uint16_t mob1_		:1;
		 uint16_t mob2_		:1;
		 uint16_t mob3_		:1;
		 uint16_t mob4_		:1;
		 uint16_t mob5_		:1;
		 uint16_t mob6_		:1;
		 uint16_t mob7_		:1;
		 uint16_t mob8_		:1;
		 uint16_t mob9_		:1;
		 uint16_t mob10_	:1;
		 uint16_t mob11_	:1;
		 uint16_t mob12_	:1;
		 uint16_t mob13_	:1;
		 uint16_t mob14_	:1;
		 uint16_t 			:1;
	};
};

union CanMobInterruptFlag
{
	struct
	{
		volatile uint16_t mob0	:1;
		volatile uint16_t mob1	:1;
		volatile uint16_t mob2	:1;
		volatile uint16_t mob3	:1;
		volatile uint16_t mob4	:1;
		volatile uint16_t mob5	:1;
		volatile uint16_t mob6	:1;
		volatile uint16_t mob7	:1;
		volatile uint16_t mob8	:1;
		volatile uint16_t mob9	:1;
		volatile uint16_t mob10	:1;
		volatile uint16_t mob11	:1;
		volatile uint16_t mob12	:1;
		volatile uint16_t mob13	:1;
		volatile uint16_t mob14	:1;
		volatile uint16_t 		:1;
	};
	struct
	{
		 uint16_t mob0_		:1;
		 uint16_t mob1_		:1;
		 uint16_t mob2_		:1;
		 uint16_t mob3_		:1;
		 uint16_t mob4_		:1;
		 uint16_t mob5_		:1;
		 uint16_t mob6_		:1;
		 uint16_t mob7_		:1;
		 uint16_t mob8_		:1;
		 uint16_t mob9_		:1;
		 uint16_t mob10_	:1;
		 uint16_t mob11_	:1;
		 uint16_t mob12_	:1;
		 uint16_t mob13_	:1;
		 uint16_t mob14_	:1;
		 uint16_t 			:1;
	};
};

union CanTiming
{
	struct
	{
		volatile uint32_t 						:1;
		volatile uint32_t baudRatePrescaler		:6;
		volatile uint32_t 						:2;
		volatile uint32_t propagationTime		:3;
		volatile uint32_t 						:1;
		volatile uint32_t reSyncJumpWidth		:2;
		volatile uint32_t 						:1;
		volatile uint32_t threePointSampling	:1;
		volatile uint32_t phaseSegment1Time		:3;
		volatile uint32_t phaseSegment2Time		:3;
		volatile uint32_t 						:1;
	};
	struct
	{
		 uint32_t 						:1;
		 uint32_t baudRatePrescaler_	:6;
		 uint32_t 						:2;
		 uint32_t propagationTime_		:3;
		 uint32_t 						:1;
		 uint32_t reSyncJumpWidth_		:2;
		 uint32_t 						:1;
		 uint32_t threePointSampling_	:1;
		 uint32_t phaseSegment1Time_	:3;
		 uint32_t phaseSegment2Time_	:3;
		 uint32_t 						:1;
	};
};

union CanHighestPriorityMob
{
	struct
	{
		volatile uint8_t generalPurposeBits		:4;
		volatile uint8_t highestPriorityMob		:4;
	};
	struct
	{
		uint8_t generalPurposeBits_		:4;
		uint8_t highestPriorityMob_		:4;
	};
};

union CanPage
{
	struct
	{
		volatile uint8_t dataBufferIndex		:3;
		volatile uint8_t autoIncrementDisable	:1;
		volatile uint8_t mobNumber				:4;
	};
	struct
	{
		uint8_t dataBufferIndex_		:3;
		uint8_t autoIncrementDisable_	:1;
		uint8_t mobNumber_ 				:4;
	};
};

// ------------------------ MOb Registers --------------------------

union CanMobStatus
{
	struct
	{
		volatile uint8_t acknowledgmentError	:1;
		volatile uint8_t formError				:1;
		volatile uint8_t crcError				:1;
		volatile uint8_t stuffError				:1;
		volatile uint8_t bitError				:1;
		volatile uint8_t receiveFinish			:1;
		volatile uint8_t transmitFinish			:1;
		volatile uint8_t dataLengthWarning		:1;
	};
	struct
	{
		uint8_t acknowledgmentError_	:1;
		uint8_t formError_				:1;
		uint8_t crcError_				:1;
		uint8_t stuffError_				:1;
		uint8_t bitError_				:1;
		uint8_t receiveFinish_			:1;
		uint8_t transmitFinish_			:1;
		uint8_t dataLengthWarning_		:1;
	};
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

	union
	{
		struct
		{
			volatile uint8_t dataLength		:4;
			volatile uint8_t idExtension 	:1;
			volatile uint8_t automaticReply :1;
			volatile Type type 				:2;
		};
		struct
		{
			uint8_t dataLength_		:4;
			uint8_t idExtension_ 	:1;
			uint8_t automaticReply_ :1;
			Type type_ 				:2;
		};
	};
};

union CanMobId
{
	struct
	{
		volatile uint32_t rb0						:1;
		volatile uint32_t rb1						:1;
		volatile uint32_t remoteTransmissionRequest	:1;
		volatile uint32_t idB						:29;
	};
	struct
	{
		volatile uint32_t 							:21;
		volatile uint32_t idA						:11;
	};
	struct
	{
		uint32_t rb0_						:1;
		uint32_t rb1_						:1;
		uint32_t remoteTransmissionRequest_	:1;
		uint32_t idB_						:29;
	};
	struct
	{
		uint32_t 							:21;
		uint32_t idA_						:11;
	};
};

union CanMobMask
{
	struct
	{
		volatile uint32_t idExtension				:1;
		volatile uint32_t 							:1;
		volatile uint32_t remoteTransmissionRequest	:1;
		volatile uint32_t idB						:29;
	};
	struct
	{
		volatile uint32_t 							:21;
		volatile uint32_t idA						:11;
	};
	struct
	{
		uint32_t idExtension_				:1;
		uint32_t 							:1;
		uint32_t remoteTransmissionRequest_	:1;
		uint32_t idB_						:29;
	};
	struct
	{
		uint32_t 							:21;
		uint32_t idA_						:11;
	};
};

#endif // ifndef __AVR_CPP_IO_H_CAN__

