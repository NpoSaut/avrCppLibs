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

#ifndef __AVR_CPP_ATMEGA64_TIMER_H__
#define __AVR_CPP_ATMEGA64_TIMER_H__

/* This file should only be included from <avr/cpp/Timer.h>, never directly. */

#ifndef __AVR_CPP_TIMER_H__
#ifdef __DOXYGEN__
#include <avr/cpp/Timer.h>
#else
#error "Include <avr/cpp/Timer.h> instead of <avr/cpp/atmega64/Timer.h>."
#endif
#endif // ifdef __AVR_CPP_TIMER_H__

#ifndef __AVR_CPP_XXX_TIMER_H__
#define __AVR_CPP_XXX_TIMER_H__ "atmega64/Timer.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/Timer.h> file."
#endif

#define TIMER0_COMP_ns	Timer
#define TIMER0_OVF_ns	Timer
#define TIMER1_COMPA_ns	Timer
#define TIMER1_COMPB_ns	Timer
#define TIMER1_COMPC_ns	Timer
#define TIMER1_OVF_ns	Timer
#define TIMER1_CAPT_ns	Timer
#define TIMER2_COMP_ns	Timer
#define TIMER2_OVF_ns	Timer
#define TIMER3_COMPA_ns	Timer
#define TIMER3_COMPB_ns	Timer
#define TIMER3_COMPC_ns	Timer
#define TIMER3_OVF_ns	Timer
#define TIMER3_CAPT_ns	Timer

#define TIMER0_COMP_struct	Timer::TimerCounter0::CompareMatchInterrupt
#define TIMER0_OVF_struct	Timer::TimerCounter0::OverflowInterrupt

#define TIMER1_COMPA_struct Timer::TimerCounter1::CompareMatchAInterrupt
#define TIMER1_COMPB_struct	Timer::TimerCounter1::CompareMatchBInterrupt
#define TIMER1_COMPC_struct	Timer::TimerCounter1::CompareMatchCInterrupt
#define TIMER1_OVF_struct	Timer::TimerCounter1::OverflowInterrupt
#define TIMER1_CAPT_struct	Timer::TimerCounter1::InputCaptureInterrupt

#define TIMER2_COMP_struct	Timer::TimerCounter2::CompareMatchInterrupt
#define TIMER2_OVF_struct	Timer::TimerCounter2::OverflowInterrupt

#define TIMER3_COMPA_struct Timer::TimerCounter3::CompareMatchAInterrupt
#define TIMER3_COMPB_struct	Timer::TimerCounter3::CompareMatchBInterrupt
#define TIMER3_COMPC_struct	Timer::TimerCounter3::CompareMatchCInterrupt
#define TIMER3_OVF_struct	Timer::TimerCounter3::OverflowInterrupt
#define TIMER3_CAPT_struct	Timer::TimerCounter3::InputCaptureInterrupt


namespace AVRCpp
{
	namespace Timer
	{
		inline void StartSynchronization() { SetBits<_SFIOR>(_TSM); }
		inline void EndSynchronization() { ClearBits<_SFIOR>(_TSM); }
		
		inline void PrescalerReset0() { SetBits<_SFIOR>(_PSR0); }
		inline void PrescalerReset321() { SetBits<_SFIOR>(_PSR321); }
		
		
		struct TimerCounter0 : Internal::OneChannel8BitTimerWithAsynchronousOperation <
				_TCNT0,							/* CounterRegister */
				_OCR0,							/* OutputCompareRegister */
				_TCCR0,							/* ControlRegister */
				_ASSR,							/* AsyncStatusRegister */
				Bits<_TIMSK, _OCIE0 | _TOIE0>,	/* InterruptEnableBits */
				Bits<_TIFR, _OCF0 | _TOV0>,		/* InterruptFlagBits */
				OutputPin4<PortB> >				/* ChannelOutputPin */
		{
			struct CompareMatchInterrupt : Interrupt<Bits<_TIMSK, _OCIE0>, Bits<_TIFR, _OCF0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE0>, Bits<_TIFR, _TOV0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter0
		
		
		struct TimerCounter1 : Internal::ThreeChannel16BitTimer <
				_TCNT1,				/* CounterRegister */
				_OCR1A,				/* OutputCompareRegisterA */
				_OCR1B,				/* OutputCompareRegisterB */
				_OCR1C,				/* OutputCompareRegisterC */
				_ICR1,				/* InputCaptureRegister */
				_TCCR1A,			/* ControlRegisterA */
				_TCCR1B,			/* ControlRegisterB */
				_TCCR1C,			/* ControlRegisterC */
				ClockB,				/* ClockEnum */
				OutputPin5<PortB>,	/* ChannelAOutputPin */
				OutputPin6<PortB>,	/* ChannelBOutputPin */
				OutputPin7<PortB>,	/* ChannelCOutputPin */
				InputPin4<PortD> >	/* InputCaptureInputPin */
		{
			struct CompareMatchAInterrupt : Interrupt<Bits<_TIMSK, _OCIE1A>, Bits<_TIFR, _OCF1A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_TIMSK, _OCIE1B>, Bits<_TIFR, _OCF1B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchCInterrupt : Interrupt<Bits<_ETIMSK, _OCIE1C>, Bits<_ETIFR, _OCF1C> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE1>, Bits<_TIFR, _TOV1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct InputCaptureInterrupt : Interrupt<Bits<_TIMSK, _TICIE1>, Bits<_TIFR, _ICF1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter1
		
		
		struct TimerCounter2 : Internal::OneChannel8BitTimer <
				_TCNT2,				/* CounterRegister */
				_OCR2,				/* OutputCompareRegister */
				_TCCR2,				/* ControlRegister */
				ClockB,				/* ClockEnum */
				OutputPin7<PortB> >	/* ChannelOutputPin */
		{
			struct CompareMatchInterrupt : Interrupt<Bits<_TIMSK, _OCIE2>, Bits<_TIFR, _OCF2> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_TIMSK, _TOIE2>, Bits<_TIFR, _TOV2> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter2
		
		
		struct TimerCounter3 : Internal::ThreeChannel16BitTimer <
				_TCNT3,				/* CounterRegister */
				_OCR3A,				/* OutputCompareRegisterA */
				_OCR3B,				/* OutputCompareRegisterB */
				_OCR3C,				/* OutputCompareRegisterC */
				_ICR3,				/* InputCaptureRegister */
				_TCCR3A,			/* ControlRegisterA */
				_TCCR3B,			/* ControlRegisterB */
				_TCCR3C,			/* ControlRegisterC */
				ClockB,				/* ClockEnum */
				OutputPin3<PortE>,	/* ChannelAOutputPin */
				OutputPin4<PortE>,	/* ChannelBOutputPin */
				OutputPin5<PortE>,	/* ChannelCOutputPin */
				InputPin7<PortE> >	/* InputCaptureInputPin */
		{
			struct CompareMatchAInterrupt : Interrupt<Bits<_ETIMSK, _OCIE3A>, Bits<_ETIFR, _OCF3A> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchBInterrupt : Interrupt<Bits<_ETIMSK, _OCIE3B>, Bits<_ETIFR, _OCF3B> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct CompareMatchCInterrupt : Interrupt<Bits<_ETIMSK, _OCIE3C>, Bits<_ETIFR, _OCF3C> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct OverflowInterrupt : Interrupt<Bits<_ETIMSK, _TOIE3>, Bits<_ETIFR, _TOV3> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct InputCaptureInterrupt : Interrupt<Bits<_ETIMSK, _TICIE3>, Bits<_ETIFR, _ICF3> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct TimerCounter3
		
	} // namespace Timer
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA64_TIMER_H__
