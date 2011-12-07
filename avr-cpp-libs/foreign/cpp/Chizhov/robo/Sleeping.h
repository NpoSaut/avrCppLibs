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
#ifndef __AVR_CPP_SLEEPING_H__
#define __AVR_CPP_SLEEPING_H__


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)

#define __SLEEPING_NUMBER_OF_MODES__	5
#define __SLEEPING_REGISTER__			_SMCR

#elif defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega644__) \
		|| defined(__AVR_ATmega644P__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega164P__)

#define __SLEEPING_NUMBER_OF_MODES__	6
#define __SLEEPING_REGISTER__			_SMCR

#elif defined(__AVR_ATmega8__)

#define __SLEEPING_NUMBER_OF_MODES__	5
#define __SLEEPING_REGISTER__			_MCUCR

#elif defined(__AVR_ATmega128__) || defined(__AVR_ATmega64__)

#define __SLEEPING_NUMBER_OF_MODES__	6
#define __SLEEPING_REGISTER__			_MCUCR

#elif defined(__AVR_ATmega8515__)

#define __SLEEPING_NUMBER_OF_MODES__	3
// __SLEEPING_REGISTER__ is not defined here because bits are scattered into various registers.

#else

#error "Device is not selected or selected device is not supported."

#endif


#if defined(__SLEEPING_NUMBER_OF_MODES__)

#include "IO.h"
#include "Assembler.h"

namespace AVRCpp
{
	namespace Sleeping
	{
		enum EnabledFlag
		{
			Disabled	= 0x00,
			Enabled		= _SE
			
		}; // EnabledFlag
		
		
#if __SLEEPING_NUMBER_OF_MODES__ == 6
		
		enum SleepMode
		{
			Idle				= 0x00,	
			ADCNoiseReduction	= _SM0,
			PowerDown			= _SM1,
			PowerSave			= _SM1 | _SM0,
			Standby				= _SM2 | _SM1,
			ExtendedStandby		= _SM2 | _SM1 | _SM0
			
		}; // enum SleepMode
		
#elif __SLEEPING_NUMBER_OF_MODES__ == 5
		
		enum SleepMode
		{
			Idle				= 0x00,	
			ADCNoiseReduction	= _SM0,
			PowerDown			= _SM1,
			PowerSave			= _SM1 | _SM0,
			Standby				= _SM2 | _SM1
			
		}; // enum SleepMode
		
#elif __SLEEPING_NUMBER_OF_MODES__ == 3
		
		enum SleepMode
		{
			Idle				= 0x00,	
			PowerDown			= _SM1,
			Standby				= _SM2 | _SM1
			
		}; // enum SleepMode
		
#endif // if __SLEEPING_NUMBER_OF_MODES__ == ?
		
		
#ifdef __SLEEPING_REGISTER__
		
		inline void SetUp(SleepMode sleepMode, EnabledFlag enabled)
		{
			ChangeBits<__SLEEPING_REGISTER__>(_SM0 | _SM1 | _SM2 | _SE, sleepMode | enabled);
			
		} // SetUp
		
		inline void FallAsleep() { Assembler::SLEEP(); }
		
		inline void Enable() { SetBits<__SLEEPING_REGISTER__>(_SE); }
		inline void Disable() { ClearBits<__SLEEPING_REGISTER__>(_SE); }
		inline uint8_t IsEnabled() { return IsBitsSet<__SLEEPING_REGISTER__>(_SE); }
		
		inline uint8_t GetSleepMode() { return SelectBits<__SLEEPING_REGISTER__>(_SM0 | _SM1 | _SM2); }
		inline void SetSleepMode(SleepMode sleepMode) { ChangeBits<__SLEEPING_REGISTER__>(_SM0 | _SM1 | _SM2, sleepMode); }
		
#undef __SLEEPING_REGISTER__

#else // __SLEEPING_REGISTER__ not defined

		inline void SetUp(SleepMode sleepMode, EnabledFlag enabled)
		{
			ChangeBits<_MCUCR>(_SM1 | _SE, sleepMode | enabled);
			ChangeBits<_MCUCSR>(_SM2, sleepMode);
			ChangeBits<_EMCUCR>(_SM0, sleepMode);
			
		} // SetUp
		
		inline void FallAsleep() { Assembler::SLEEP(); }
		
		inline void Enable() { SetBits<_MCUCR>(_SE); }
		inline void Disable() { ClearBits<_MCUCR>(_SE); }
		inline uint8_t IsEnabled() { return IsBitsSet<_MCUCR>(_SE); }
		
		inline uint8_t GetSleepMode()
		{
			return ( SelectBits<_MCUCR>(_SM1)
					| SelectBits<_MCUCSR>(_SM2)
					| SelectBits<_EMCUCR>(_SM0) );

		} // GetSleepMode

		inline void SetSleepMode(SleepMode sleepMode)
		{
			ChangeBits<_MCUCR>(_SM1, sleepMode);
			ChangeBits<_MCUCSR>(_SM2, sleepMode);
			ChangeBits<_EMCUCR>(_SM0, sleepMode);

		} // SetSleepMode

#endif // ifdef __SLEEPING_REGISTER__

		
	} // namespace Sleeping

} // namespace AVRCpp


#endif // if defined(__SLEEPING_NUMBER_OF_MODES__)

#endif // ifndef __AVR_CPP_SLEEPING_H__
