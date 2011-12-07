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

#ifndef __AVR_CPP_ATMEGA48_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_ATMEGA48_EXTERNAL_INTERRUPT_H__

/* This file should only be included from <avr/cpp/ExternalInterrupt.h>, never directly. */

#ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__
#ifdef __DOXYGEN__
#include <avr/cpp/ExternalInterrupt.h>
#else
#error "Include <avr/cpp/ExternalInterrupt.h> instead of <avr/cpp/atmega48/ExternalInterrupt.h>."
#endif
#endif // ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__

#ifndef __AVR_CPP_XXX_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_XXX_EXTERNAL_INTERRUPT_H__ "atmega48/ExternalInterrupt.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/ExternalInterrupt.h> file."
#endif

#define INT0_ns		ExternalInterrupt
#define INT1_ns		ExternalInterrupt
#define PCINT0_ns	ExternalInterrupt
#define PCINT1_ns	ExternalInterrupt
#define PCINT2_ns	ExternalInterrupt

#define INT0_struct		ExternalInterrupt::Interrupt0
#define INT1_struct		ExternalInterrupt::Interrupt1
#define PCINT0_struct	ExternalInterrupt::PinChangeInterrupt0
#define PCINT1_struct	ExternalInterrupt::PinChangeInterrupt1
#define PCINT2_struct	ExternalInterrupt::PinChangeInterrupt2


namespace AVRCpp
{
	namespace ExternalInterrupt
	{
		struct Interrupt0 : Internal::InterruptBase <
				InputPin2<PortD>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_EICRA, _ISC00 | _ISC01>,	/* EventBits */
				Bits<_EIMSK, _INT0>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF0>,			/* InterruptFlagBit */
				0 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt0
		
		struct Interrupt1 : Internal::InterruptBase <
				InputPin3<PortD>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_EICRA, _ISC10 | _ISC11>,	/* EventBits */
				Bits<_EIMSK, _INT1>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF1>,			/* InterruptFlagBit */
				2 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt1
		
		struct PinChangeInterrupt0 : Internal::PinChangeInterruptBase < 
			_PCMSK0,							/* MaskRegister */
			Bits<_PCICR, _PCIE0>,				/* InterruptEnableBit */ 
			Bits<_PCIFR, _PCIF0> >				/* InterruptFlagBit */

		{ __INTERRUPT_HANDLER_SUPPORT__ }; // PinChangeInterrupt0
		
		struct PinChangeInterrupt1 : Internal::PinChangeInterruptBase < 
			_PCMSK1,							/* MaskRegister */
			Bits<_PCICR, _PCIE1>,				/* InterruptEnableBit */ 
			Bits<_PCIFR, _PCIF1> >				/* InterruptFlagBit */

		{ __INTERRUPT_HANDLER_SUPPORT__ }; // PinChangeInterrupt1
		
		struct PinChangeInterrupt2 : Internal::PinChangeInterruptBase < 
			_PCMSK2,							/* MaskRegister */
			Bits<_PCICR, _PCIE2>,				/* InterruptEnableBit */ 
			Bits<_PCIFR, _PCIF2> >				/* InterruptFlagBit */

		{ __INTERRUPT_HANDLER_SUPPORT__ }; // PinChangeInterrupt2

	} // namespace ExternalInterrupts
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA48_EXTERNAL_INTERRUPT_H__
