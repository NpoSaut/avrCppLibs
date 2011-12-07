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

#ifndef __AVR_CPP_ATMEGA8515_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_ATMEGA8515_EXTERNAL_INTERRUPT_H__

/* This file should only be included from <avr/cpp/ExternalInterrupt.h>, never directly. */

#ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__
#ifdef __DOXYGEN__
#include <avr/cpp/ExternalInterrupt.h>
#else
#error "Include <avr/cpp/ExternalInterrupt.h> instead of <avr/cpp/atmega8515/ExternalInterrupt.h>."
#endif
#endif // ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__

#ifndef __AVR_CPP_XXX_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_XXX_EXTERNAL_INTERRUPT_H__ "atmega8515/ExternalInterrupt.h"
#else
#error "Attempt to include more than one <avr/cpp/XXXX/ExternalInterrupt.h> file."
#endif

#define INT0_ns	ExternalInterrupt
#define INT1_ns	ExternalInterrupt
#define INT2_ns	ExternalInterrupt

#define INT0_struct	INT0_ns::Interrupt0
#define INT1_struct	INT1_ns::Interrupt1
#define INT2_struct	INT1_ns::Interrupt2


namespace AVRCpp
{
	namespace ExternalInterrupt
	{
		struct Interrupt0 : Internal::InterruptBase <
				InputPin2<PortD>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_MCUCR, _ISC00 | _ISC01>,	/* EventBits */
				Bits<_GICR, _INT0>,				/* InterruptEnableBit */
				Bits<_GIFR, _INTF0>,			/* InterruptFlagBit */
				0 >								/* eventShift */

		{ __INTERRUPT_HANDLER_SUPPORT__	}; // struct Interrupt0
		
		struct Interrupt1 : Internal::InterruptBase <
				InputPin3<PortD>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_MCUCR, _ISC10 | _ISC11>,	/* EventBits */
				Bits<_GICR, _INT1>,				/* InterruptEnableBit */
				Bits<_GIFR, _INTF1>,			/* InterruptFlagBit */
				2 >								/* eventShift */
		
		{ __INTERRUPT_HANDLER_SUPPORT__	}; // struct Interrupt1
		
		struct Interrupt2 : Internal::InterruptBase <
				InputPin0<PortE>,				/* InputPin */
				SimpleAsyncEvent,				/* EventEnum */
				Bits<_EMCUCR, _ISC2>,			/* EventBits */
				Bits<_GICR, _INT2>,				/* InterruptEnableBit */
				Bits<_GIFR, _INTF2>,			/* InterruptFlagBit */
				0 >								/* eventShift */
		
		{ __INTERRUPT_HANDLER_SUPPORT__	}; // struct Interrupt2

	} // ExternalInterrupt
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA8515_EXTERNAL_INTERRUPT_H__
