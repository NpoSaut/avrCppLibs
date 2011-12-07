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

#ifndef __AVR_CPP_AT90USB1287_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_AT90USB1287_EXTERNAL_INTERRUPT_H__

/* This file should only be included from <avr/cpp/ExternalInterrupt.h>, never directly. */

#ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__
#ifdef __DOXYGEN__
#include <avr/cpp/ExternalInterrupt.h>
#else
#error "Include <avr/cpp/ExternalInterrupt.h> instead of <avr/cpp/at90usb1287/ExternalInterrupt.h>."
#endif
#endif

#ifndef __AVR_CPP_XXX_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_XXX_EXTERNAL_INTERRUPT_H__ "at90usb1287/ExternalInterrupt.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/ExternalInterrupt.h> file."
#endif

#define INT0_ns ExternalInterrupt
#define INT1_ns	ExternalInterrupt
#define INT2_ns	ExternalInterrupt
#define INT3_ns	ExternalInterrupt
#define INT4_ns	ExternalInterrupt
#define INT5_ns	ExternalInterrupt
#define INT6_ns	ExternalInterrupt
#define INT7_ns	ExternalInterrupt
#define PCINT0_ns ExternalInterrupt

#define INT0_struct	ExternalInterrupt::Interrupt0
#define INT1_struct	ExternalInterrupt::Interrupt1
#define INT2_struct	ExternalInterrupt::Interrupt2
#define INT3_struct	ExternalInterrupt::Interrupt3
#define INT4_struct	ExternalInterrupt::Interrupt4
#define INT5_struct	ExternalInterrupt::Interrupt5
#define INT6_struct	ExternalInterrupt::Interrupt6
#define INT7_struct	ExternalInterrupt::Interrupt7
#define PCINT0_struct ExternalInterrupt::PinChangeInterrupt0


namespace AVRCpp
{
	namespace ExternalInterrupt
	{
		struct Interrupt0 : Internal::InterruptBase <
				InputPin0<PortD>,				/* InputPin */
				AsyncEvent,						/* EventEnum */
				Bits<_EICRA, _ISC00 | _ISC01>,	/* EventBits */
				Bits<_EIMSK, _INT0>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF0>,			/* InterruptFlagBit */
				0 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt0
		
		struct Interrupt1 : Internal::InterruptBase <
				InputPin1<PortD>,				/* InputPin */
				AsyncEvent,						/* EventEnum */
				Bits<_EICRA, _ISC10 | _ISC11>,	/* EventBits */
				Bits<_EIMSK, _INT1>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF1>,			/* InterruptFlagBit */
				2 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt1
		
		struct Interrupt2 : Internal::InterruptBase <
				InputPin2<PortD>,				/* InputPin */
				AsyncEvent,						/* EventEnum */
				Bits<_EICRA, _ISC20 | _ISC21>,	/* EventBits */
				Bits<_EIMSK, _INT2>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF2>,			/* InterruptFlagBit */
				4 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt2
		
		struct Interrupt3 : Internal::InterruptBase <
				InputPin3<PortD>,				/* InputPin */
				AsyncEvent,						/* EventEnum */
				Bits<_EICRA, _ISC30 | _ISC31>,	/* EventBits */
				Bits<_EIMSK, _INT3>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF3>,			/* InterruptFlagBit */
				6 >								/* eventShift */
					
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt3
		
		struct Interrupt4 : Internal::InterruptBase <
				InputPin4<PortE>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_EICRB, _ISC40 | _ISC41>,	/* EventBits */
				Bits<_EIMSK, _INT4>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF4>,			/* InterruptFlagBit */
				0 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt4
		
		struct Interrupt5 : Internal::InterruptBase <
				InputPin5<PortE>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_EICRB, _ISC50 | _ISC51>,	/* EventBits */
				Bits<_EIMSK, _INT5>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF5>,			/* InterruptFlagBit */
				2 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt5
		
		struct Interrupt6 : Internal::InterruptBase <
				InputPin6<PortE>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_EICRB, _ISC60 | _ISC61>,	/* EventBits */
				Bits<_EIMSK, _INT6>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF6>,			/* InterruptFlagBit */
				4 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt6
		
		struct Interrupt7 : Internal::InterruptBase <
				InputPin7<PortE>,				/* InputPin */
				Event,							/* EventEnum */
				Bits<_EICRB, _ISC70 | _ISC71>,	/* EventBits */
				Bits<_EIMSK, _INT7>,			/* InterruptEnableBit */
				Bits<_EIFR, _INTF7>,			/* InterruptFlagBit */
				6 >								/* eventShift */
				
		{ __INTERRUPT_HANDLER_SUPPORT__ }; // Interrupt7
		
		struct PinChangeInterrupt0 : Internal::PinChangeInterruptBase < 
			_PCMSK0,							/* MaskRegister */
			Bits<_PCICR, _PCIE0>,				/* InterruptEnableBit */ 
			Bits<_PCIFR, _PCIF0> >				/* InterruptFlagBit */

		{ __INTERRUPT_HANDLER_SUPPORT__ }; // PinChangeInterrupt0
		
	} // namespace ExternalInterrupts
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_AT90USB1287_EXTERNAL_INTERRUPT_H__
