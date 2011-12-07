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

#ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__
#define __AVR_CPP_EXTERNAL_INTERRUPT_H__

#include "IO.h"


namespace AVRCpp
{
	namespace ExternalInterrupt
	{
		enum Event
		{
			LowLevel		= 0x00,
			LogicalChange	= 0x01,
			Fall			= 0x02,
			Rise			= 0x03
			
		}; // enum Event
		
		enum AsyncEvent
		{
			ALowLevel		= 0x00,
			AFall			= 0x02,
			ARise			= 0x03
			
		}; // enum AsyncEvent
	
		enum SimpleAsyncEvent
		{
			SAFall			= 0x00,
			SARise			= 0x01
			
		}; // enum SimpleAsyncEvent
	
		namespace Internal
		{
			template <
					class InputPin,
					class EventEnum,
					class EventBits,
					class InterruptEnableBit,
					class InterruptFlagBit,
					uint8_t eventShift >
			
			struct InterruptBase : Interrupt<InterruptEnableBit, InterruptFlagBit>
			{
				typedef InputPin Pin;
				
				static inline void SetEvent(EventEnum event) { EventBits::Change(event << eventShift); }
				static inline uint8_t GetEvent() { return EventBits::Select() >> eventShift; }
				
				static inline void SetDisabledEvent(EventEnum event)
				{
					BasicInterrupt<InterruptEnableBit>::Disable();
					SetEvent(event);
					Interrupt<InterruptEnableBit, InterruptFlagBit>::ClearFlag();
					
				} // SetDisabledEvent
				
				static inline void SetEnabledEvent(EventEnum event)
				{
					SetDisabledEvent(event);
					BasicInterrupt<InterruptEnableBit>::Enable();
					
				} // SetEnabledEvent
				
				
			}; // struct InterruptBase
			
			template <
					class MaskRegister,
					class InterruptEnableBit,
					class InterruptFlagBit >
			
			struct PinChangeInterruptBase : Interrupt<InterruptEnableBit, InterruptFlagBit>
			{
				typedef MaskRegister Mask;
				
			}; // struct PinChangeInterruptBase
			
		} // namespace Internal
		
	} // namespace ExternalInterrupt

} // namespace AVRCpp
	
/* Include controller specific files */
#if defined(__AVR_AT90USB1287__)
#include "at90usb1287/ExternalInterrupt.h"
#elif defined(__AVR_AT90CAN128__)
#include "at90can128/ExternalInterrupt.h"
#elif defined(__AVR_ATmega128__)
#include "atmega128/ExternalInterrupt.h"
#elif defined(__AVR_ATmega64__)
#include "atmega64/ExternalInterrupt.h"
#elif defined(__AVR_ATmega88__)
#include "atmega88/ExternalInterrupt.h"
#elif defined(__AVR_ATmega8__)
#include "atmega8/ExternalInterrupt.h"
#elif defined(__AVR_ATmega8515__)
#include "atmega8515/ExternalInterrupt.h"
#elif defined(__AVR_ATmega48__)
#include "atmega48/ExternalInterrupt.h"
#elif defined(__AVR_ATmega168__)
#include "atmega168/ExternalInterrupt.h"
#elif defined(__AVR_ATmega164P__)
#include "atmega164p/ExternalInterrupt.h"
#elif defined(__AVR_ATmega324P__)
#include "atmega324p/ExternalInterrupt.h"
#elif defined(__AVR_ATmega644P__)
#include "atmega644p/ExternalInterrupt.h"
#elif defined(__AVR_ATmega644__)
#include "atmega644/ExternalInterrupt.h"
#else
#error "Device is not selected or selected device is not supported."
#endif

#endif // ifndef __AVR_CPP_EXTERNAL_INTERRUPT_H__
