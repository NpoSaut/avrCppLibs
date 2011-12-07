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

#ifndef __AVR_CPP_ATMEGA324P_TIMER_H__
#define __AVR_CPP_ATMEGA324P_TIMER_H__

/* This file should only be included from <avr/cpp/Timer.h>, never directly. */

#ifndef __AVR_CPP_TIMER_H__
#ifdef __DOXYGEN__
#include <avr/cpp/Timer.h>
#else
#error "Include <avr/cpp/Timer.h> instead of <avr/cpp/atmega324p/Timer.h>."
#endif
#endif // ifdef __AVR_CPP_TIMER_H__

#ifndef __AVR_CPP_XXX_TIMER_H__
#define __AVR_CPP_XXX_TIMER_H__ "atmega324p/Timer.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/Timer.h> file."
#endif

#define TIMER0_COMPA_ns	Timer
#define TIMER0_COMPB_ns	Timer
#define TIMER0_OVF_ns	Timer
#define TIMER1_OVF_ns	Timer
#define TIMER1_COMPA_ns	Timer
#define TIMER1_COMPB_ns	Timer
#define TIMER1_CAPT_ns	Timer
#define TIMER2_COMPA_ns	Timer
#define TIMER2_COMPB_ns	Timer
#define TIMER2_OVF_ns	Timer

#define TIMER0_COMPA_struct	Timer::TimerCounter0::CompareMatchAInterrupt
#define TIMER0_COMPB_struct	Timer::TimerCounter0::CompareMatchBInterrupt
#define TIMER0_OVF_struct	Timer::TimerCounter0::OverflowInterrupt
#define TIMER1_OVF_struct	Timer::TimerCounter1::OverflowInterrupt
#define TIMER1_COMPA_struct	Timer::TimerCounter1::CompareMatchAInterrupt
#define TIMER1_COMPB_struct	Timer::TimerCounter1::CompareMatchBInterrupt
#define TIMER1_CAPT_struct	Timer::TimerCounter1::InputCaptureInterrupt
#define TIMER2_COMPA_struct	Timer::TimerCounter2::CompareMatchAInterrupt
#define TIMER2_COMPB_struct	Timer::TimerCounter2::CompareMatchBInterrupt
#define TIMER2_OVF_struct	Timer::TimerCounter2::OverflowInterrupt


namespace AVRCpp
{
	namespace Timer
	{
		
		inline void StartSynchronization() { SetBits<_GTCCR>(_TSM); }
		inline void EndSynchronization() { ClearBits<_GTCCR>(_TSM); }
		
		inline void PrescalerReset10() { SetBits<_GTCCR>(_PSRSYNC); }
		
		
		struct TimerCounter0 : Internal::TwoChannel8BitTimer <
				_TCNT0,				/* CounterRegister */
				_OCR0A,				/* OutputCompareRegisterA */
				_OCR0B,				/* OutputCompareRegisterB */
				_TCCR0A,			/* ControlRegisterA */
				_TCCR0B,			/* ControlRegisterB */
				ClockB,				/* ClockEnum */
				OutputPin3<PortB>,	/* ChannelAOutputPin */
				OutputPin4<PortB> >	/* ChannelBOutputPin */
		{
			struct CompareMatchAInterrupt : Interrupt<Bits<_TIMSK0, _OCIE0A>, Bits<_TIFR0, _OCF0A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_TIMSK0, _OCIE0B>, Bits<_TIFR0, _OCF0B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK0, _TOIE0>, Bits<_TIFR0, _TOV0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter0
		
		
		struct TimerCounter1 :  Internal::NewTwoChannel16BitTimer <
				_TCNT1,				/* CounterRegister */
				_OCR1A,				/* OutputCompareRegisterA */
				_OCR1B,				/* OutputCompareRegisterB */
				_ICR1,				/* InputCaptureRegister */
				_TCCR1A,			/* ControlRegisterA */
				_TCCR1B,			/* ControlRegisterB */
				_TCCR1C,			/* ForceOutputCompare */
				ClockB,				/* ClockEnum */
				OutputPin5<PortD>,	/* ChannelAOutputPin */
				OutputPin4<PortD>,	/* ChannelBOutputPin */
				InputPin6<PortD> >	/* InputCaptureInputPin */
		{
			struct InputCaptureInterrupt : Interrupt<Bits<_TIMSK1, _ICIE1>, Bits<_TIFR1, _ICF1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchAInterrupt : Interrupt<Bits<_TIMSK1, _OCIE1A>, Bits<_TIFR1, _OCF1A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_TIMSK1, _OCIE1B>, Bits<_TIFR1, _OCF1B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK1, _TOIE1>, Bits<_TIFR1, _TOV1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter1
		
		
		struct TimerCounter2 : Internal::TwoChannel8BitTimerWithAsynchronousOperation <
				_TCNT2,					/* CounterRegister */
				_OCR2A,					/* OutputCompareRegisterA */
				_OCR2B,					/* OutputCompareRegisterB */
				_TCCR2A,				/* ControlRegisterA */
				_TCCR2B,				/* ControlRegisterB */
				_TIMSK2,				/* InterruptMaskRegister */
				_TIFR2,					/* InterruptFlagRegister */
				_ASSR,					/* AsyncStatusRegister */
				OutputPin7<PortD>,		/* ChannelAOutputPin */
				OutputPin6<PortD> >		/* ChannelBOutputPin */
		{
			struct CompareMatchAInterrupt : Interrupt<Bits<_TIMSK2, _OCIE2A>, Bits<_TIFR2, _OCF2A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_TIMSK2, _OCIE2B>, Bits<_TIFR2, _OCF2B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK2, _TOIE2>, Bits<_TIFR2, _TOV2> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter2
		
	} // namespace Timer
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA324P_TIMER_H__
