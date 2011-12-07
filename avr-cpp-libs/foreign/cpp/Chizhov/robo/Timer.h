/**********************************************************************************************************************\

	C++ library for Atmel AVR microcontrollers
	Copyright (C) 2007 Lauri Kirikal, Mikk Leini, MTÜ TTÜ Robotiklubi

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	See http://creativecommons.org/licenses/GPL/2.0/

	MTÜ TTÜ Robotiklubi  http://www.robotiklubi.ee robotiklubi@gmail.com
	Lauri Kirikal        laurikirikal@gmail.com
	Mikk Leini           mikk.leini@gmail.com

\**********************************************************************************************************************/

#ifndef __AVR_CPP_TIMER_H__
#define __AVR_CPP_TIMER_H__

#include "IO.h"


namespace AVRCpp
{
	namespace Timer
	{
		enum ClockA
		{
			NoClockA		= 0x00,
			NoPrescaleA		= 0x01,
			Prescale8A		= 0x02,
			Prescale32A		= 0x03,
			Prescale64A		= 0x04,
			Prescale128A	= 0x05,
			Prescale256A	= 0x06,
			Prescale1024A	= 0x07
			
		}; // enum ClockA
		
		enum ClockB
		{
			NoClockB		= 0x00,
			NoPrescaleB		= 0x01,
			Prescale8B		= 0x02,
			Prescale64B		= 0x03,
			Prescale256B	= 0x04,
			Prescale1024B	= 0x05,
			ExternalFall	= 0x06,
			ExternalRise	= 0x07
			
		}; // enum ClockB
		
		enum CompareOutputMode
		{
			NormalPortOperation	= 0x00,
			Toggle				= 0x10,
			Clear				= 0x20,
			Set					= 0x30
			
		}; // enum CompareOutputMode
	
		enum CompareOutputModeA
		{
			NormalPortOperationA	= 0x00,
			ToggleA					= 0x40,
			ClearA					= 0x80,
			SetA					= 0xC0
			
		}; // enum CompareOutputModeA
		
		enum CompareOutputModeB
		{
			NormalPortOperationB	= 0x00,
			ToggleB					= 0x10,
			ClearB					= 0x20,
			SetB					= 0x30
			
		}; // enum CompareOutputModeB
	
		enum CompareOutputModeC
		{
			NormalPortOperationC	= 0x00,
			ToggleC					= 0x04,
			ClearC					= 0x08,
			SetC					= 0x0C
			
		}; // CompareOutputModeC
		
		enum InputNoiseCanceler
		{
			On	= 0x80,
			Off	= 0x00
			
		}; // enum InputNoiseCanceler
		
		enum InputCaptureEdge
		{
			Rise	= 0x40,
			Fall	= 0x00
			
		}; // enum InputCaptureEdge
		
		enum Mode
		{
			Normal						= 0x00,
			ClearTimerOnCompareMatch	= 0x08,
			PhaseCorrectPWM				= 0x40,
			FastPWM						= 0x48
			
		}; // enum Mode;
		
		enum FixedTop16
		{
			Normal16						= 0x00,
			FastPWM16BitsCount8				= 0x09,
			FastPWM16BitsCount9				= 0x0A,
			FastPWM16BitsCount10			= 0x0B,
			PhaseCorrectPWM16BitsCount8		= 0x01,
			PhaseCorrectPWM16BitsCount9		= 0x02,
			PhaseCorrectPWM16BitsCount10	= 0x03
			
		}; // enum FixedTop16
		
		enum TopFromInputCapture16
		{
			ClearTimerOnCompareMatch16TopFromInputCapture		= 0x18,
			FastPWM16TopFromInputCapture						= 0x1A,
			PhaseCorrectPWM16TopFromInputCapture				= 0x12,
			PhaseAndFrequencyCorrectPWM16TopFromInputCapture	= 0x10
			
		}; // enum TopFromInputCapture16
		
		enum TopFromOutputCompareA16
		{
			ClearTimerOnCompareMatch16TopFromOutputCompareA		= 0x08,
			FastPWM16TopFromOutputCompareA						= 0x1B,
			PhaseCorrectPWM16TopFromOutputCompareA				= 0x13,
			PhaseAndFrequencyCorrectPWM16TopFromOutputCompareA	= 0x11
			
		}; // enum TopFromOutputCompareA16
	
		enum FixedTop8
		{
			Normal8				= 0x00,
			FastPWM8			= 0x03,
			PhaseCorrectPWM8	= 0x01
			
		}; // enum FixedTop8
		
		enum TopFromOutputCompareA8
		{
			ClearTimerOnCompareMatch8TopFromOutputCompareA	= 0x02,
			FastPWM8TopFromOutputCompareA					= 0x0B,
			PhaseCorrectPWM8TopFromOutputCompareA			= 0x09
			
		}; // enum TopFromOutputCompareA8
		
		
		namespace Internal
		{
			enum CommonConstants
			{
				ClockMask	= 0x03,
				Force		= 0x80,
				ForceA		= 0x80,
				ForceB		= 0x40,
				ForceC		= 0x20,
				OldForceA	= 0x08,
				OldForceB	= 0x04,
				TopMaskA8	= 0x03,
				TopMaskA16	= 0x03,
				TopMaskB8	= 0x08,
				TopMaskB16	= 0x18
				
			}; // enum CommonConstants
			
			enum BitFlags
			{
				AsynchronousFlagA			= 0x08,
				CounterUpdateFlagA			= 0x04,
				OutputCompareUpdateFlagA	= 0x02,
				ControlUpdateFlagA			= 0x01,
				ExternalClockEnableFlagB	= 0x40,
				AsynchronousFlagB			= 0x20,
				CounterUpdateFlagB			= 0x10,
				OutputCompareAUpdateFlagB	= 0x08,
				OutputCompareBUpdateFlagB	= 0x04,
				ControlAUpdateFlagB			= 0x02,
				ControlBUpdateFlagB			= 0x01
				
			}; // enum BitFlags
			
			
			template <class Register, class UpdateBit> struct AsyncRegister : Register
			{
				static inline void Set(typename Register::Type)
				{
					while (UpdateBit::IsSet() );
					Register::Set();
					
				} // Set
				
				static inline void SleepSafeSet(typename Register::Type value)
				{
					Set(value);
					while (UpdateBit::IsSet() );
					
				} // SleepSafeSet
				
			}; // struct AsyncRegister
			
			
			template <
					class CounterRegister,
					class ClockRegister,
					class ClockEnum >
			
			struct SimpleTimer
			{
				typedef CounterRegister Counter;
				
				static inline void SelectClock(ClockEnum clock) { ChangeBits<ClockRegister>(ClockMask, clock); }
				static inline uint8_t GetSelectedClock() { return SelectBits<ClockRegister>(ClockMask); }
				
			}; // struct SimpleTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegister,
					class ControlRegister,
					class ClockEnum,
					class ChannelOutputPin >
			
			struct OneChannel8BitTimer : SimpleTimer<CounterRegister, ControlRegister, ClockEnum>
			{
				typedef OutputCompareRegister OutputCompare;
				typedef ChannelOutputPin ChannelPin;
				
				static inline void ForceOutputCompare() { SetBits<ControlRegister>(Force); }
				
				static inline void SetUp (
						ClockEnum clock,
						Mode mode,
						CompareOutputMode compareOutputMode )
				{
					ControlRegister::Set(compareOutputMode | mode | clock);
					
				} // SetUp
				
			}; // struct OneChannel8BitTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegister,
					class ControlRegister,
					class AsyncStatusRegister,
					class InterruptEnableBits,
					class InterruptFlagBits,
					class ChannelOutputPin >
			
			class AsyncOneChannel8BitTimer : OneChannel8BitTimer <
					AsyncRegister<CounterRegister, Bits<AsyncStatusRegister, CounterUpdateFlagA> >,
					AsyncRegister<OutputCompareRegister, Bits<AsyncStatusRegister, OutputCompareUpdateFlagA> >,
					AsyncRegister<ControlRegister, Bits<AsyncStatusRegister, ControlUpdateFlagA> >,
					ClockA,
					ChannelOutputPin >
			{
			private:
				
				typedef Bits<AsyncStatusRegister, AsynchronousFlagA>		AsynchronousBit;
				typedef Bits<AsyncStatusRegister, CounterUpdateFlagA>		CounterUpdateBit;
				typedef Bits<AsyncStatusRegister, OutputCompareUpdateFlagA>	OutputCompareUpdateBit;
				typedef Bits<AsyncStatusRegister, ControlUpdateFlagA>		ControlUpdateBit;
				
				typedef AsyncRegister<CounterRegister, CounterUpdateBit>				AsyncCounterRegister;
				typedef AsyncRegister<OutputCompareRegister, OutputCompareUpdateBit>	AsyncOutputCompareRegister;
				typedef AsyncRegister<ControlRegister, ControlUpdateBit>				AsyncControlRegister;
				
			public:
				
				static inline bool IsSafeForSleepMode()
				{
					return !(CounterUpdateBit::IsSet()
							|| OutputCompareUpdateBit::IsSet()
							|| ControlUpdateBit::IsSet() );
					
				} // IsSafeForSleepMode
				
				static inline void WaitUntilSafeForSleepMode() { while (!IsSafeForSleepMode() ); }
				
				static void WaitMinimumTimeForReEnteringSleepMode()
				{
					AsyncControlRegister::Set(ControlRegister::Get() );
					WaitUntilSafeForSleepMode();
					
				} // WaitMinimumTimeForReEnteringSleepMode
				
				static inline uint8_t GetSafeCounterValue()
				{
					WaitMinimumTimeForReEnteringSleepMode();
					
					return CounterRegister::Get();
					
				} // GetSafeCounterValue
				
				static void AsynchronousOperation(bool enable)
				{
					uint8_t counter = CounterRegister::Get();
					uint8_t outputCompare = OutputCompareRegister::Get();
					uint8_t control = ControlRegister::Get();
					uint8_t interruptEnableBits = InterruptEnableBits::Select();
					
					InterruptEnableBits::Clear();
					
					AsynchronousBit::SetTo(enable);
						
					AsyncCounterRegister::Set(counter);
					AsyncOutputCompareRegister::Set(outputCompare);
					AsyncControlRegister::Set(control);
					
					WaitUntilSafeForSleepMode();
					
					InterruptFlagBits::Clear();
					InterruptEnableBits::Change(interruptEnableBits);
					
				} // EnableAsynchronous
				
			}; // class AsyncOneChannel8BitTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegister,
					class ControlRegister,
					class AsyncStatusRegister,
					class InterruptEnableBits,
					class InterruptFlagBits,
					class ChannelOutputPin >
			
			struct OneChannel8BitTimerWithAsynchronousOperation
			{
				typedef OneChannel8BitTimer <
					CounterRegister,
					OutputCompareRegister,
					ControlRegister,
					ClockA,
					ChannelOutputPin > Synchronous;
				
				typedef AsyncOneChannel8BitTimer <
					CounterRegister,
					OutputCompareRegister,
					ControlRegister,
					AsyncStatusRegister,
					InterruptEnableBits,
					InterruptFlagBits,
					ChannelOutputPin > Asynchronous;
				
			}; // struct OneChannel8BitTimerWithAsynchronousOperation
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class ControlRegisterA,
					class ControlRegisterB,
					class ClockEnum,
					class ChannelAOutputPin,
					class ChannelBOutputPin >
			
			struct TwoChannel8BitTimer : SimpleTimer<CounterRegister, ControlRegisterB, ClockEnum>
			{
				typedef OutputCompareRegisterA OutputCompareA;
				typedef OutputCompareRegisterB OutputCompareB;
				
				typedef ChannelAOutputPin ChannelAPin;
				typedef ChannelBOutputPin ChannelBPin;
				
				static inline void ForceOutputCompareA() { SetBits<ControlRegisterB>(ForceA); }
				static inline void ForceOutputCompareB() { SetBits<ControlRegisterB>(ForceB); }
				
				static inline void SetUp (
						ClockEnum clock,
						FixedTop8 fixedTop8,
						CompareOutputModeA compareOutputModeA,
						CompareOutputModeB compareOutputModeB )
				{
					ControlRegisterA::Set(compareOutputModeA | compareOutputModeB | (fixedTop8 & TopMaskA8) );
					ControlRegisterB::Set(clock | (fixedTop8 & TopMaskB8) );
					
				} // SetUp 1
				
				static inline void SetUp (
						ClockEnum clock,
						TopFromOutputCompareA8 topFromOutputCompareA8,
						CompareOutputModeB compareOutputModeB )
				{
					ControlRegisterA::Set(compareOutputModeB | (topFromOutputCompareA8 & TopMaskA8) );
					ControlRegisterB::Set(clock | (topFromOutputCompareA8 & TopMaskB8) );
					
				} // SetUp 2
				
			}; // struct TwoChannel8BitTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class ControlRegisterA,
					class ControlRegisterB,
					class InterruptMaskRegister,
					class InterruptFlagRegister,
					class AsyncStatusRegister,
					class ChannelAOutputPin,
					class ChannelBOutputPin >
			
			class AsyncTwoChannel8BitTimer : TwoChannel8BitTimer <
					AsyncRegister<CounterRegister, Bits<AsyncStatusRegister, CounterUpdateFlagB> >,
					AsyncRegister<OutputCompareRegisterA, Bits<AsyncStatusRegister, OutputCompareAUpdateFlagB> >,
					AsyncRegister<OutputCompareRegisterB, Bits<AsyncStatusRegister, OutputCompareBUpdateFlagB> >,
					AsyncRegister<ControlRegisterA, Bits<AsyncStatusRegister, ControlAUpdateFlagB> >,
					AsyncRegister<ControlRegisterB, Bits<AsyncStatusRegister, ControlBUpdateFlagB> >,
					ClockA,
					ChannelAOutputPin,
					ChannelBOutputPin >
			{
				
			private:
				
				typedef Bits<AsyncStatusRegister, ExternalClockEnableFlagB>		ExternalClockEnableBit;
				typedef Bits<AsyncStatusRegister, AsynchronousFlagB>			AsynchronousBit;
				typedef Bits<AsyncStatusRegister, CounterUpdateFlagB>			CounterUpdateBit;
				typedef Bits<AsyncStatusRegister, OutputCompareAUpdateFlagB>	OutputCompareAUpdateBit;
				typedef Bits<AsyncStatusRegister, OutputCompareBUpdateFlagB>	OutputCompareBUpdateBit;
				typedef Bits<AsyncStatusRegister, ControlAUpdateFlagB>			ControlAUpdateBit;
				typedef Bits<AsyncStatusRegister, ControlBUpdateFlagB>			ControlBUpdateBit;
				
				typedef	AsyncRegister<CounterRegister, CounterUpdateBit>				AsyncCounterRegister;
				typedef	AsyncRegister<OutputCompareRegisterA, OutputCompareAUpdateBit>	AsyncOutputCompareRegisterA;
				typedef	AsyncRegister<OutputCompareRegisterB, OutputCompareBUpdateBit>	AsyncOutputCompareRegisterB;
				typedef	AsyncRegister<ControlRegisterA, ControlAUpdateBit>				AsyncControlRegisterA;
				typedef	AsyncRegister<ControlRegisterB, ControlBUpdateBit>				AsyncControlRegisterB;
				
			public:
				
				static inline void EnableExternalClock() { ExternalClockEnableBit::Set(); }
				static inline void DisableExternalClock() { ExternalClockEnableBit::Clear(); }
				static inline bool IsExternalClockEnabled() { return ExternalClockEnableBit::IsSet(); }
				
				static inline bool IsSafeForSleepMode()
				{
					return !(CounterUpdateBit::IsSet()
							|| OutputCompareAUpdateBit::IsSet()
							|| OutputCompareBUpdateBit::IsSet()
							|| ControlAUpdateBit::IsSet()
							|| ControlBUpdateBit::IsSet() );
					
				} // IsSafeForSleepMode
				
				static inline void WaitUntilSafeForSleepMode() { while (!IsSafeForSleepMode() ); }
				
				static void WaitMinimumTimeForReEnteringSleepMode()
				{
					AsyncControlRegisterA::Set(ControlRegisterA::Get() );
					WaitUntilSafeForSleepMode();
					
				} // WaitMinimumTimeForReEnteringSleepMode
				
				static inline uint8_t GetSafeCounterValue()
				{
					WaitMinimumTimeForReEnteringSleepMode();
					
					return CounterRegister::Get();
					
				} // GetSafeCounterValue
				
				static void AsynchronousOperation(bool enable)
				{
					uint8_t counter = CounterRegister::Get();
					uint8_t outputCompareA = OutputCompareRegisterA::Get();
					uint8_t outputCompareB = OutputCompareRegisterB::Get();
					uint8_t controlA = ControlRegisterA::Get();
					uint8_t controlB = ControlRegisterB::Get();
					uint8_t interruptMask = InterruptMaskRegister::Get();
					
					InterruptMaskRegister::Set(0);
					
					AsynchronousBit::SetTo(enable);
					
					AsyncCounterRegister::Set(counter);
					AsyncOutputCompareRegisterA::Set(outputCompareA);
					AsyncOutputCompareRegisterB::Set(outputCompareB);
					AsyncControlRegisterA::Set(controlA);
					AsyncControlRegisterB::Set(controlB);
					
					WaitUntilSafeForSleepMode();
					
					InterruptFlagRegister::Set(0);
					InterruptMaskRegister::Set(interruptMask);
					
				} // EnableAsynchronous
				
			}; // class AsyncTwoChannel8BitTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class ControlRegisterA,
					class ControlRegisterB,
					class InterruptMaskRegister,
					class InterruptFlagRegister,
					class AsyncStatusRegister,
					class ChannelAOutputPin,
					class ChannelBOutputPin >
			
			struct TwoChannel8BitTimerWithAsynchronousOperation
			{
				typedef TwoChannel8BitTimer <
						CounterRegister,
						OutputCompareRegisterA,
						OutputCompareRegisterB,
						ControlRegisterA,
						ControlRegisterB,
						ClockA,
						ChannelAOutputPin,
						ChannelBOutputPin > Synchronous;
				
				typedef AsyncTwoChannel8BitTimer <
						CounterRegister,
						OutputCompareRegisterA,
						OutputCompareRegisterB,
						ControlRegisterA,
						ControlRegisterB,
						InterruptMaskRegister,
						InterruptFlagRegister,
						AsyncStatusRegister,
						ChannelAOutputPin,
						ChannelBOutputPin > Asynchronous;
				
			}; // struct TwoChannel8BitTimerWithAsynchronousOperation
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class InputCaptureRegister,
					class ControlRegisterA,
					class ControlRegisterB,
					class ClockEnum,
					class ChannelAOutputPin,
					class ChannelBOutputPin,
					class InputCaptureInputPin >
			
			struct TwoChannel16BitTimerBase : SimpleTimer<CounterRegister, ControlRegisterB, ClockEnum>
			{
				typedef OutputCompareRegisterA OutputCompareA;
				typedef OutputCompareRegisterB OutputCompareB;
				typedef InputCaptureRegister InputCapture;
				
				typedef ChannelAOutputPin ChannelAPin;
				typedef ChannelBOutputPin ChannelBPin;
				typedef InputCaptureInputPin InputCapturePin;
				
				static inline void SetUp (
						ClockEnum clock,
						FixedTop16 fixedTop16,
						CompareOutputModeA compareOutputModeA,
						CompareOutputModeB compareOutputModeB,
						InputNoiseCanceler inputNoiseCanceler,
						InputCaptureEdge inputCaptureEdge )
				{
					ControlRegisterA::Set(compareOutputModeA | compareOutputModeB | (fixedTop16 & TopMaskA16) );
					ControlRegisterB::Set(inputNoiseCanceler | inputCaptureEdge | clock | (fixedTop16 & TopMaskB16) );
					
				} // SetUp 1
				
				static inline void SetUp (
						ClockEnum clock,
						TopFromInputCapture16 topFromInputCapture16,
						CompareOutputModeA compareOutputModeA,
						CompareOutputModeB compareOutputModeB )
				{
					ControlRegisterA::Set(compareOutputModeA | compareOutputModeB | (topFromInputCapture16 & TopMaskA16) );
					ControlRegisterB::Set(clock | (topFromInputCapture16 & TopMaskB16) );
					
				} // SetUp 2
				
				static inline void SetUp (
						ClockEnum clock,
						TopFromOutputCompareA16 topFromOutputCompareA16,
						CompareOutputModeB compareOutputModeB,
						InputNoiseCanceler inputNoiseCanceler,
						InputCaptureEdge inputCaptureEdge )
				{
					ControlRegisterA::Set(compareOutputModeB | (topFromOutputCompareA16 & TopMaskA16) );
					ControlRegisterB::Set(inputNoiseCanceler | inputCaptureEdge | clock | (topFromOutputCompareA16 & TopMaskB16) );
					
				} // SetUp 3
				
			}; // struct TwoChannel16BitTimerBase
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class InputCaptureRegister,
					class ControlRegisterA,
					class ControlRegisterB,
					class ClockEnum,
					class ChannelAOutputPin,
					class ChannelBOutputPin,
					class InputCaptureInputPin >
			
			struct OldTwoChannel16BitTimer : TwoChannel16BitTimerBase <	CounterRegister,
																		OutputCompareRegisterA,
																		OutputCompareRegisterB,
																		InputCaptureRegister,
																		ControlRegisterA,
																		ControlRegisterB,
																		ClockEnum,
																		ChannelAOutputPin,
																		ChannelBOutputPin,
																		InputCaptureInputPin >
			{
				static inline void ForceOutputCompareA() { SetBits<ControlRegisterA>(OldForceA); }
				static inline void ForceOutputCompareB() { SetBits<ControlRegisterA>(OldForceB); }
				
			}; // struct OldTwoChannel16BitTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class InputCaptureRegister,
					class ControlRegisterA,
					class ControlRegisterB,
					class ControlRegisterC,
					class ClockEnum,
					class ChannelAOutputPin,
					class ChannelBOutputPin,
					class InputCaptureInputPin >
			
			struct NewTwoChannel16BitTimer : TwoChannel16BitTimerBase <	CounterRegister,
																		OutputCompareRegisterA,
																		OutputCompareRegisterB,
																		InputCaptureRegister,
																		ControlRegisterA,
																		ControlRegisterB,
																		ClockEnum,
																		ChannelAOutputPin,
																		ChannelBOutputPin,
																		InputCaptureInputPin >
			{
				static inline void ForceOutputCompareA() { SetBits<ControlRegisterC>(ForceA); }
				static inline void ForceOutputCompareB() { SetBits<ControlRegisterC>(ForceB); }
				
			}; // struct NewTwoChannel16BitTimer
			
			
			template <
					class CounterRegister,
					class OutputCompareRegisterA,
					class OutputCompareRegisterB,
					class OutputCompareRegisterC,
					class InputCaptureRegister,
					class ControlRegisterA,
					class ControlRegisterB,
					class ControlRegisterC,
					class ClockEnum,
					class ChannelAOutputPin,
					class ChannelBOutputPin,
					class ChannelCOutputPin,
					class InputCaptureInputPin >
			
			struct ThreeChannel16BitTimer : SimpleTimer<CounterRegister, ControlRegisterB, ClockEnum>
			{
				typedef OutputCompareRegisterA OutputCompareA;
				typedef OutputCompareRegisterB OutputCompareB;
				typedef OutputCompareRegisterC OutputCompareC;
				typedef InputCaptureRegister InputCapture;
				
				typedef ChannelAOutputPin ChannelAPin;
				typedef ChannelBOutputPin ChannelBPin;
				typedef ChannelCOutputPin ChannelCPin;
				typedef InputCaptureInputPin InputCapturePin;
				
				static inline void ForceOutputCompareA() { SetBits<ControlRegisterC>(ForceA); }
				static inline void ForceOutputCompareB() { SetBits<ControlRegisterC>(ForceB); }
				static inline void ForceOutputCompareC() { SetBits<ControlRegisterC>(ForceC); }
				
				static inline void SetUp (
						ClockEnum clock,
						FixedTop16 fixedTop16,
						CompareOutputModeA compareOutputModeA,
						CompareOutputModeB compareOutputModeB,
						CompareOutputModeC compareOutputModeC,
						InputNoiseCanceler inputNoiseCanceler,
						InputCaptureEdge inputCaptureEdge )
				{
					ControlRegisterA::Set(compareOutputModeA | compareOutputModeB | compareOutputModeC | (fixedTop16 & TopMaskA16) );
					ControlRegisterB::Set(inputNoiseCanceler | inputCaptureEdge | clock | (fixedTop16 & TopMaskB16) );
					
				} // SetUp 1
				
				static inline void SetUp (
						ClockEnum clock,
						TopFromInputCapture16 topFromInputCapture16,
						CompareOutputModeA compareOutputModeA,
						CompareOutputModeB compareOutputModeB,
						CompareOutputModeC compareOutputModeC )
				{
					ControlRegisterA::Set(compareOutputModeA | compareOutputModeB | compareOutputModeC | (topFromInputCapture16 & TopMaskA16) );
					ControlRegisterB::Set(clock | (topFromInputCapture16 & TopMaskB16) );
					
				} // SetUp 2
				
				static inline void SetUp (
						ClockEnum clock,
						TopFromOutputCompareA16 topFromOutputCompareA16,
						CompareOutputModeB compareOutputModeB,
						CompareOutputModeC compareOutputModeC,
						InputNoiseCanceler inputNoiseCanceler,
						InputCaptureEdge inputCaptureEdge )
				{
					ControlRegisterA::Set(compareOutputModeB | compareOutputModeC | (topFromOutputCompareA16 & TopMaskA16) );
					ControlRegisterB::Set(inputNoiseCanceler | inputCaptureEdge | clock | (topFromOutputCompareA16 & TopMaskB16) );
					
				} // SetUp 3
				
			}; // struct ThreeChannel16BitTimer
			
		} // namespace Internal
		
	} // namespace Timer

} // namespace AVRCpp
	
/* Include controller specific files */
#if defined(__AVR_AT90USB1287__)
#include "at90usb1287/Timer.h"
#elif defined(__AVR_AT90CAN128__)
#include "at90can128/Timer.h"
#elif defined(__AVR_ATmega128__)
#include "atmega128/Timer.h"
#elif defined(__AVR_ATmega64__)
#include "atmega64/Timer.h"
#elif defined(__AVR_ATmega8__)
#include "atmega8/Timer.h"
#elif defined(__AVR_ATmega8515__)
#include "atmega8515/Timer.h"
#elif defined(__AVR_ATmega88__)
#include "atmega88/Timer.h"
#elif defined(__AVR_ATmega48__)
#include "atmega48/Timer.h"
#elif defined(__AVR_ATmega168__)
#include "atmega168/Timer.h"
#elif defined(__AVR_ATmega164P__)
#include "atmega164p/Timer.h"
#elif defined(__AVR_ATmega324P__)
#include "atmega324p/Timer.h"
#elif defined(__AVR_ATmega644P__)
#include "atmega644p/Timer.h"
#elif defined(__AVR_ATmega644__)
#include "atmega644/Timer.h"
#else
#error "Device is not selected or selected device is not supported."
#endif

#endif // ifndef __AVR_CPP_TIMER_H__
