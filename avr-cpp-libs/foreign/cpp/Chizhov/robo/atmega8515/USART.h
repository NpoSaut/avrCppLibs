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

#ifndef __AVR_CPP_ATMEGA8515_USART_H__
#define __AVR_CPP_ATMEGA8515_USART_H__

/* This file should only be included from <avr/cpp/USART.h>, never directly. */

#ifndef __AVR_CPP_USART_H__
#ifdef __DOXYGEN__
#include <avr/cpp/USART.h>
#else
#error "Include <avr/cpp/USART.h> instead of <avr/cpp/atmega8515/USART.h>."
#endif
#endif // ifndef __AVR_CPP_USART_H__

#ifndef __AVR_CPP_XXX_USART_H__
#define __AVR_CPP_XXX_USART_H__ "atmega8515/USART.h"
#else
#error "Attempt to include more than one <avr/cpp/XXX/USART.h> file."
#endif

#define USART_RXC_ns	USART
#define USART_TXC_ns	USART
#define USART_UDRE_ns	USART

#define USART_RXC_struct	USART::USART0::ReceiveCompleteInterrupt
#define USART_TXC_struct	USART::USART0::TransferCompleteInterrupt
#define USART_UDRE_struct	USART::USART0::DataRegisterEmptyInterrupt


namespace AVRCpp
{
	namespace USART
	{
		// Functions from this namespace should not be called by user
		namespace Internal
		{
			bool &Cancel0();
			
		} // namespace Internal
		
		struct USART0 : Internal::USARTBase <
				_UBRRH,							/* BaudRateRegisterHigh */
				_UBRRL,							/* BaudRateRegisterLow */
				_UCSRA,							/* ControlRegisterA */
				_UCSRB,							/* ControlRegisterB */
				_UCSRC,							/* ControlRegisterC */
				_UDR,							/* DataRegister */
				Pin4<PortD>,					/* TransferClockPin */
				Internal::HasRegisterSelect,	/* registerSelect */
				Internal::Cancel0 >				/* Cancel */
		{
			struct ReceiveCompleteInterrupt : BasicInterrupt<Bits<_UCSRB, _RXCIE> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct TransferCompleteInterrupt : BasicInterrupt<Bits<_UCSRB, _TXCIE> > { __INTERRUPT_HANDLER_SUPPORT__ };
			struct DataRegisterEmptyInterrupt : BasicInterrupt<Bits<_UCSRB, _UDRIE> > { __INTERRUPT_HANDLER_SUPPORT__ };
			
		}; // struct USART0
		
	} // namespace USART
	
} // namespace AVRCpp

#endif // ifndef __AVR_CPP_ATMEGA8515_USART_H__
