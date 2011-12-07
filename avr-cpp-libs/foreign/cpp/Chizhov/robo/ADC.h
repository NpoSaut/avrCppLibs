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

#ifndef __AVR_CPP_ADC_H__
#define __AVR_CPP_ADC_H__

#define __ADC_SIMPLE__			0x00
#define __ADC_DIFFERENTIAL__	0x01
#define __ADC_DIGITAL_INPUT__	0x02
#define __ADC_AUTO_TRIGGER__	0x04
#define __ADC_INTERNAL_REF1__	0x08
#define __ADC_HIGH_SPEED__		0x10


#if defined(__AVR_ATmega8__)

#define __ADC_PROPERTIES__		(__ADC_SIMPLE__)

#elif defined(__AVR_ATmega128__)

#define __ADC_PROPERTIES__		(__ADC_SIMPLE__ | __ADC_DIFFERENTIAL__)

#elif defined(__AVR_ATmega64__)

#define __ADC_PROPERTIES__		(__ADC_SIMPLE__ | __ADC_DIFFERENTIAL__ | __ADC_AUTO_TRIGGER__)

#elif defined(__AVR_AT90USB1287__)

#define __ADC_PROPERTIES__		(__ADC_SIMPLE__ | __ADC_DIFFERENTIAL__ | __ADC_AUTO_TRIGGER__ | __ADC_DIGITAL_INPUT__ | __ADC_HIGH_SPEED__)

#elif defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)

#define __ADC_PROPERTIES__		(__ADC_SIMPLE__ | __ADC_DIFFERENTIAL__ | __ADC_AUTO_TRIGGER__ | __ADC_DIGITAL_INPUT__ | __ADC_INTERNAL_REF1__)

#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)

#define __ADC_PROPERTIES__		(__ADC_SIMPLE__ | __ADC_AUTO_TRIGGER__ | __ADC_DIGITAL_INPUT__)

#else

#error "Device is not selected or selected device is not supported."

#endif

#ifdef __ADC_PROPERTIES__

#include "IO.h"
#include "Assembler.h"

#define ADC_ns		AnalogToDigital
#define ADC_struct	AnalogToDigital::ConversionCompleteInterrupt


/**********************************************************************************************************************\

	Analog to digital converter

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace AnalogToDigital
	{
		typedef _ADC Result;
		
#if __ADC_PROPERTIES__ & __ADC_INTERNAL_REF1__

		enum Reference
		{
			AREF		= 0x00,
			AVCC		= _REFS0,
			Internal1V	= _REFS1,
			InternalRef	= _REFS1 | _REFS0
			
		}; // enum Reference

#else // if __ADC_PROPERTIES__ & __ADC_INTERNAL_REF1__

		enum Reference
		{
			AREF		= 0x00,
			AVCC		= _REFS0,
			InternalRef	= _REFS1 | _REFS0
			
		}; // enum Reference

#endif // if __ADC_PROPERTIES__ & __ADC_INTERNAL_REF1__

		
		enum Adjustment
		{
			AlignRight	= 0x00,
			AlignLeft	= _ADLAR
			
		}; // enum Adjustment
		
		enum InterruptEnableFlag
		{
			InterruptEnable	= _ADIE,
			InterruptDisable = 0x00
			
		}; // enum InterruptEnableFlag
		
		enum EnableFlag
		{
			ADCEnable	= _ADEN,
			ADCDisable	= 0x00
			
		}; // enum EnableFlag
		
		enum ConversionStart
		{
			StartNow	= _ADSC,
			StartLater	= 0x00
			
		}; // enum ConversionStart
		
		enum FreeRunning
		{
			FreeRunMode		= 0x20,
			FreeRunStopped	= 0x00
			
		}; // enum FreeRunning
		
		enum Prescaler
		{
			Div2	= 0x01,
			Div4	= 0x02,
			Div8	= 0x03,
			Div16	= 0x04,
			Div32	= 0x05,
			Div64	= 0x06,
			Div128	= 0x07
			
		}; // enum Prescaler
		

#if __ADC_PROPERTIES__ & __ADC_DIFFERENTIAL__
		
		enum AnalogChannel
		{
			ADC0		= 0x00,
			ADC1		= 0x01,
			ADC2		= 0x02,
			ADC3		= 0x03,
			ADC4		= 0x04,
			ADC5		= 0x05,
			ADC6		= 0x06,
			ADC7		= 0x07,
			Vbandgap	= 0x1E,
			GND			= 0x1F
			
		}; // enum AnalogChannel

		enum Gain
		{
			Gain1x		= 0x10,
			Gain10x		= 0x08,
			Gain200x	= 0x0a

		}; // enum Gain
		
#else // if __ADC_PROPERTIES__ & __ADC_DIFFERENTIAL__
		
		enum AnalogChannel
		{
			ADC0		= 0x00,
			ADC1		= 0x01,
			ADC2		= 0x02,
			ADC3		= 0x03,
			ADC4		= 0x04,
			ADC5		= 0x05,
			ADC6		= 0x06,
			ADC7		= 0x07,
			Vbandgap	= 0x0E,
			GND			= 0x0F

		}; // enum AnalogChannel
		
#endif // if __ADC_PROPERTIES__ & __ADC_DIFFERENTIAL__
		
		
#if __ADC_PROPERTIES__ & __ADC_AUTO_TRIGGER__
		
		enum AutoTriggerSource
		{
			FreeRunningMode				= 0x00,
			AnalogComparator			= 0x01,
			ExternalInterruptRequest0	= 0x02,
			Counter0CompareMatch		= 0x03,
			Counter0Overflow			= 0x04,
			Counter1CompareMatchB		= 0x05,
			Counter1Overflow			= 0x06,
			Counter1CaptureEvent		= 0x07
			
		}; // enum AutoTriggerSource

#endif
		
		struct ConversionCompleteInterrupt : Interrupt<Bits<_ADCSRA, _ADIE>, Bits<_ADCSRA, _ADIF> > { __INTERRUPT_HANDLER_SUPPORT__ };
		
		inline bool IsConverting() { return IsBitsSet<_ADCSRA>(_ADSC); }
		inline void WaitWhileConverting() { while (IsConverting() ); }
		
		inline void EnsureChangeSafety()
		{
			if (IsConverting() )
				Assembler::NOP();
			
		} // EnsureChangeSafety
		
		
		inline void SelectionSetUp (
				Reference reference,
				Adjustment adjustment,
				AnalogChannel channel )
		{
			EnsureChangeSafety();
			ADMUX = reference | adjustment | channel;
			
		} // SelectionSetUp
		
		
		inline void ControlSetUp (
				EnableFlag enableFlag,
				ConversionStart conversionStart,
				FreeRunning freeRunning,
				InterruptEnableFlag interruptEnableFlag,
				Prescaler prescaler )
		{
			ADCSRA = enableFlag
					| conversionStart
					| freeRunning
					| interruptEnableFlag
					| prescaler;
			
		} // ControlSetUp
		
		
		inline void SetChannel(AnalogChannel channel)
		{
			EnsureChangeSafety();
			ChangeBits<_ADMUX>(_MUX0 | _MUX1 | _MUX2 | _MUX3, channel);
			
		} // SetChannel
		
		
		inline void SelectPrescaler(Prescaler prescaler)
		{
			ChangeBits<_ADCSRA>(_ADPS0 | _ADPS1 | _ADPS2, prescaler);
			
		} // SelectPrescaler

		
		inline void Enable() { SetBits<_ADCSRA>(_ADEN); }
		inline void Disable() { ClearBits<_ADCSRA>(_ADEN); }
		inline bool IsEnabled() { return IsBitsSet<_ADCSRA>(_ADEN); }
		
		inline void StartConversion() { SetBits<_ADCSRA>(_ADSC); }		
		
#if __ADC_PROPERTIES__ & __ADC_HIGH_SPEED__
		
		inline void EnableHighSpeedMode() { SetBits<_ADCSRB>(_ADHSM); }
		inline void DisableHighSpeedMode() { ClearBits<_ADCSRB>(_ADHSM); }
		inline bool IsHighSpeedModeEnabled() { return IsBitsSet<_ADCSRB>(_ADHSM); }
		
#endif // if __ADC_PROPERTIES__ & __ADC_HIGH_SPEED__
		
		
#if __ADC_PROPERTIES__ & __ADC_DIFFERENTIAL__
		
		inline void SetDifferentialChannels(AnalogChannel positive, AnalogChannel negative, Gain gain)
		{
			if(gain == Gain1x)
			{
				ChangeBits<_ADMUX>(_MUX0 | _MUX1 | _MUX2 | _MUX3 | _MUX4, gain | positive | ((negative << 2) & 0x08));
			}
			else
			{
				ChangeBits<_ADMUX>(_MUX0 | _MUX1 | _MUX2 | _MUX3, gain | (negative << 1) | (positive & 0x01));
			}
			
		} // SetDifferentialChannels
		
#endif // if __ADC_PROPERTIES__ & __ADC_DIFFERENTIAL__
		
		
#if __ADC_PROPERTIES__ & __ADC_AUTO_TRIGGER__
		
		inline void EnableAutoTrigger() { SetBits<_ADCSRA>(_ADATE); }
		inline void DisableAutoTrigger() { ClearBits<_ADCSRA>(_ADATE); }
		inline bool IsAutoTriggerEnabled() { return IsBitsSet<_ADCSRA>(_ADATE); }
		
		inline void SetAutoTriggerSource(AutoTriggerSource source) { ChangeBits<_ADCSRB>(_ADTS2 | _ADTS1 | _ADTS0, source); }
		
		inline void EnableFreeRun() { EnableAutoTrigger(); SetAutoTriggerSource(FreeRunningMode); }
		inline void DisableFreeRun() { DisableAutoTrigger(); }
		inline bool IsFreeRunEnabled() { return !IsBitsSet<_ADCSRB>(_ADTS2 | _ADTS1 | _ADTS0); }
		
		inline void StartFreeRun() { EnableFreeRun(); EnableAutoTrigger(); }
		inline void StopFreeRun() { DisableFreeRun(); }
		
#else // if __ADC_PROPERTIES__ & __ADC_AUTO_TRIGGER__
		
		inline void EnableFreeRun() { SetBits<_ADCSRA>(_ADFR); }
		inline void DisableFreeRun() { ClearBits<_ADCSRA>(_ADFR); }
		inline bool IsFreeRunEnabled() { return IsBitsSet<_ADCSRA>(_ADFR); }
		
		inline void StartFreeRun() { SetBits<_ADCSRA>(_ADSC | _ADFR); }
		inline void StopFreeRun() { DisableFreeRun(); }
		
#endif // if __ADC_PROPERTIES__ & __ADC_AUTO_TRIGGER__
		
		
#if __ADC_PROPERTIES__ & __ADC_DIGITAL_INPUT__
		
		/**
		* Disables the digital input buffers of the pins specified. It is used to reduce power consumption
		* in the digital input buffer because you do not need digital input buffers when you use these pins
		* as an analog input port. Note that ADC7 and ADC6 do not have digital inputs, so for example the
		* instruction DigitalInputDisable(ADC7 | ADC6 | ADC5) only switches off the fifth pin's buffer.
		*/
		inline void DigitalInputDisable(uint8_t pins) { SetBits<_DIDR0>(pins); }
		/// Enables the digital input buffers for the specified pins
		inline void DigitalInputEnable(uint8_t pins) { ClearBits<_DIDR0>(pins); }
		/// Enables the digital input buffers for the specified pins, disables for others.
		inline void SetDigitalInput(uint8_t pins) { DIDR0 = ~pins; }
		
#endif // if __ADC_PROPERTIES__ & __ADC_DIGITAL_INPUT__
		
	} // namespace AnalogToDigital
	
} // namespace AVRCpp

/**********************************************************************************************************************/

#endif // ifdef __ADC_PROPERTIES__

#endif // ifndef __AVR_CPP_ADC_H__
