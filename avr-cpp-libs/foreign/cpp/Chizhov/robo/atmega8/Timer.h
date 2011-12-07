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

#ifndef __AVR_CPP_ATMEGA8_TIMER_H__
#define __AVR_CPP_ATMEGA8_TIMER_H__

/* This file should only be included from <avr/cpp/Timer.h>, never directly. */

#ifndef __AVR_CPP_TIMER_H__
#ifdef __DOXYGEN__
#include <avr/cpp/Timer.h>
#else
#error "Include <avr/cpp/Timer.h> instead of <avr/cpp/atmega8/Timer.h>."
#endif
#endif // ifdef __AVR_CPP_TIMER_H__

#ifndef __AVR_CPP_XXX_TIMER_H__
#define __AVR_CPP_XXX_TIMER_H__ "atmega8/Timer.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/Timer.h> file."
#endif

#define TIMER0_OVF_ns	Timer
#define TIMER1_OVF_ns	Timer
#define TIMER1_COMPA_ns	Timer
#define TIMER1_COMPB_ns	Timer
#define TIMER1_CAPT_ns	Timer
#define TIMER2_COMP_ns	Timer
#define TIMER2_OVF_ns	Timer

#define TIMER0_OVF_struct	Timer::TimerCounter0::OverflowInterrupt
#define TIMER1_OVF_struct	Timer::TimerCounter1::OverflowInterrupt
#define TIMER1_COMPA_struct	Timer::TimerCounter1::CompareMatchAInterrupt
#define TIMER1_COMPB_struct	Timer::TimerCounter1::CompareMatchBInterrupt
#define TIMER1_CAPT_struct	Timer::TimerCounter1::InputCaptureInterrupt
#define TIMER2_COMP_struct	Timer::TimerCounter2::CompareMatchInterrupt
#define TIMER2_OVF_struct	Timer::TimerCounter2::OverflowInterrupt


namespace AVRCpp
{
	namespace Timer
	{
		inline void PrescalerReset10() { SetBits<_SFIOR>(_PSR10); }
		inline void PrescalerReset2() { SetBits<_SFIOR>(_PSR2); }
		
		
		struct TimerCounter0 : Internal::SimpleTimer <
				_TCNT0,				/* CounterRegister */
				_TCCR0,				/* ClockRegister */
				ClockB >			/* ClockEnum */
		{
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE0>, Bits<_TIFR, _TOV0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // TimerCounter0
		
		
		struct TimerCounter1 : Internal::OldTwoChannel16BitTimer <
				_TCNT1,				/* CounterRegister */
				_OCR1A,				/* OutputCompareRegisterA */
				_OCR1B,				/* OutputCompareRegisterB */
				_ICR1,				/* InputCaptureRegister */
				_TCCR1A,			/* ControlRegisterA */
				_TCCR1B,			/* ControlRegisterB */
				ClockB,				/* ClockEnum */
				OutputPin1<PortB>,	/* ChannelAOutputPin */
				OutputPin2<PortB>,	/* ChannelBOutputPin */
				InputPin0<PortB> >	/* InputCaptureInputPin */
		{
			struct InputCaptureInterrupt : Interrupt<Bits<_TIMSK, _TICIE1>, Bits<_TIFR, _ICF1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchAInterrupt : Interrupt<Bits<_TIMSK, _OCIE1A>, Bits<_TIFR, _OCF1A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_TIMSK, _OCIE1B>, Bits<_TIFR, _OCF1B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE1>, Bits<_TIFR, _TOV1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter1
		
		
		struct TimerCounter2 : Internal::OneChannel8BitTimerWithAsynchronousOperation <
				_TCNT2,							/* CounterRegister */
				_OCR2,							/* OutputCompareRegister */
				_TCCR2,							/* ControlRegister */
				_ASSR,							/* AsyncStatusRegister */
				Bits<_TIMSK, _OCIE2 | _TOIE2>,	/* InterruptEnableBits */
				Bits<_TIFR, _OCF2 | _TOV2>,		/* InterruptFlagBits */
				OutputPin3<PortB> >				/* ChannelOutputPin */
		{
			struct CompareMatchInterrupt : Interrupt<Bits<_TIMSK, _OCIE2>, Bits<_TIFR, _OCF2> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE2>, Bits<_TIFR, _TOV2> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter2
		
	} // namespace Timer
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA8_TIMER_H__
