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

#ifndef __AVR_CPP_ATMEGA324P_USART_H__
#define __AVR_CPP_ATMEGA324P_USART_H__

/* This file should only be included from <avr/cpp/USART.h>, never directly. */

#ifndef __AVR_CPP_USART_H__
#ifdef __DOXYGEN__
#include <avr/cpp/USART.h>
#else
#error "Include <avr/cpp/USART.h> instead of <avr/cpp/atmega324p/USART.h>."
#endif
#endif // ifndef __AVR_CPP_USART_H__

#ifndef __AVR_CPP_XXX_USART_H__
#define __AVR_CPP_XXX_USART_H__ "atmega324p/USART.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/USART.h> file."
#endif

#define USART0_RX_ns	USART
#define USART0_TX_ns	USART
#define USART0_UDRE_ns	USART
#define USART1_RX_ns	USART
#define USART1_TX_ns	USART
#define USART1_UDRE_ns	USART

#define USART0_RX_struct	USART::USART0::ReceiveCompleteInterrupt
#define USART0_TX_struct	USART::USART0::TransferCompleteInterrupt
#define USART0_UDRE_struct	USART::USART0::DataRegisterEmptyInterrupt
#define USART1_RX_struct	USART::USART1::ReceiveCompleteInterrupt
#define USART1_TX_struct	USART::USART1::TransferCompleteInterrupt
#define USART1_UDRE_struct	USART::USART1::DataRegisterEmptyInterrupt


namespace AVRCpp
{
	namespace USART
	{
		// Functions from this namespace should not be called by user
		namespace Internal
		{
			bool &Cancel0();
			bool &Cancel1();
			
		} // namespace Internal
		
		struct USART0 : Internal::USARTBase <
				_UBRR0H,					/* BaudRateRegisterHigh */
				_UBRR0L,					/* BaudRateRegisterLow */
				_UCSR0A,					/* ControlRegisterA */
				_UCSR0B,					/* ControlRegisterB */
				_UCSR0C,					/* ControlRegisterC */
				_UDR0,						/* DataRegister */
				Pin0<PortB>,				/* TransferClockPin */
				Internal::NoRegisterSelect,	/* registerSelect */
				Internal::Cancel0 >			/* Cancel */
		{
			struct ReceiveCompleteInterrupt : BasicInterrupt<Bits<_UCSR0B, _RXCIE0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct TransferCompleteInterrupt : BasicInterrupt<Bits<_UCSR0B, _TXCIE0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct DataRegisterEmptyInterrupt : BasicInterrupt<Bits<_UCSR0B, _UDRIE0> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct USART0
		
		struct USART1 : Internal::USARTBase <
				_UBRR1H,					/* BaudRateRegisterHigh */
				_UBRR1L,					/* BaudRateRegisterLow */
				_UCSR1A,					/* ControlRegisterA */
				_UCSR1B,					/* ControlRegisterB */
				_UCSR1C,					/* ControlRegisterC */
				_UDR1,						/* DataRegister */
				Pin4<PortD>,				/* TransferClockPin */
				Internal::NoRegisterSelect,	/* registerSelect */
				Internal::Cancel1 >			/* Cancel */
		{
			struct ReceiveCompleteInterrupt : BasicInterrupt<Bits<_UCSR1B, _RXCIE1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct TransferCompleteInterrupt : BasicInterrupt<Bits<_UCSR1B, _TXCIE1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct DataRegisterEmptyInterrupt : BasicInterrupt<Bits<_UCSR1B, _UDRIE1> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct USART1
		
	} // namespace USART
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA324P_USART_H__
