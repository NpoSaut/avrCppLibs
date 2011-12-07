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

#ifndef __AVR_CPP_ATMEGA8515_TIMER_H__
#define __AVR_CPP_ATMEGA8515_TIMER_H__

/* This file should only be included from <avr/cpp/Timer.h>, never directly. */

#ifndef __AVR_CPP_TIMER_H__
#ifdef __DOXYGEN__
#include <avr/cpp/Timer.h>
#else
#error "Include <avr/cpp/Timer.h> instead of <avr/cpp/atmega8515/Timer.h>."
#endif
#endif // ifdef __AVR_CPP_TIMER_H__

#ifndef __AVR_CPP_XXX_TIMER_H__
#define __AVR_CPP_XXX_TIMER_H__ "atmega8515/Timer.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/Timer.h> file."
#endif

#define TIMER0_COMP_ns	Timer
#define TIMER0_OVF_ns	Timer
#define TIMER1_OVF_ns	Timer
#define TIMER1_COMPA_ns	Timer
#define TIMER1_COMPB_ns	Timer
#define TIMER1_CAPT_ns	Timer

#define TIMER0_COMP_struct	Timer::TimerCounter0::CompareMatchInterrupt
#define TIMER0_OVF_struct	Timer::TimerCounter0::OverflowInterrupt
#define TIMER1_OVF_struct	Timer::TimerCounter1::OverflowInterrupt
#define TIMER1_COMPA_struct	Timer::TimerCounter1::CompareMatchAInterrupt
#define TIMER1_COMPB_struct	Timer::TimerCounter1::CompareMatchBInterrupt
#define TIMER1_CAPT_struct	Timer::TimerCounter1::InputCaptureInterrupt


namespace AVRCpp
{
	namespace Timer
	{
		inline void PrescalerReset10() { SetBits<_SFIOR>(_PSR10); }
		
		
		struct TimerCounter0 : Internal::OneChannel8BitTimer <
				_TCNT0,				/* CounterRegister */
				_OCR0,				/* OutputCompareRegister */
				_TCCR0,				/* ControlRegister */
				ClockB,				/* ClockEnum */
				OutputPin0<PortB> >	/* ChannelOutputPin */
		{
			struct CompareMatchInterrupt : Interrupt<Bits<_TIMSK, _OCIE0>, Bits<_TIFR, _OCF0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE0>, Bits<_TIFR, _TOV0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter0
		
		
		struct TimerCounter1 : Internal::OldTwoChannel16BitTimer <
				_TCNT1,				/* CounterRegister */
				_OCR1A,				/* OutputCompareRegisterA */
				_OCR1B,				/* OutputCompareRegisterB */
				_ICR1,				/* InputCaptureRegister */
				_TCCR1A,			/* ControlRegisterA */
				_TCCR1B,			/* ControlRegisterB */
				ClockB,				/* ClockEnum */
				OutputPin5<PortD>,	/* ChannelAOutputPin */
				OutputPin2<PortE>,	/* ChannelBOutputPin */
				InputPin0<PortE> >	/* InputCaptureInputPin */
		{
			struct InputCaptureInterrupt : Interrupt<Bits<_TIMSK, _TICIE1>, Bits<_TIFR, _ICF1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchAInterrupt : Interrupt<Bits<_TIMSK, _OCIE1A>, Bits<_TIFR, _OCF1A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_TIMSK, _OCIE1B>, Bits<_TIFR, _OCF1B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE1>, Bits<_TIFR, _TOV1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter1
		
	} // namespace Timer
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA8515_TIMER_H__
