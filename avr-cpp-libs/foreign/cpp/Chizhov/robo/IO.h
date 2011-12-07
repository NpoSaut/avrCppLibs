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


/**********************************************************************************************************************\

	AVRCppLib general IO functionality classes

\**********************************************************************************************************************/

#ifndef __AVR_CPP_IO_H__
#define __AVR_CPP_IO_H__

#include <avr/io.h>

#ifndef __cplusplus
#error "IO.h needs C++ compiler."
#else

// Compatibility test
#if !(defined(__AVR__) && __GNUC__ == 4 && __GNUC_MINOR__ == 1 && __GNUC_PATCHLEVEL__ == 2)
#warning "AVR C++ Lib is tested on avr-gcc (GCC) 4.1.2 (WinAVR 20070525). You are not using this compiler. AVR C++ Lib may not work properly."
#endif

namespace AVRCpp
{
	typedef volatile uint16_t & reg16_t;
	typedef volatile uint8_t & reg8_t;
	
	template <class Register> inline void SetBits(typename Register::Type flags)
	{
		Register::Set(Register::Get() | flags);
		
	} // SetBits
	
	template <class Register> inline void ClearBits(typename Register::Type flags)
	{
		Register::Set(Register::Get() & ~flags);
		
	} // ClearBits
	
	template <class Register> inline void SetBitsTo(typename Register::Type flags, bool value)
	{
		if (value)
			SetBits<Register>(flags);
		else
			ClearBits<Register>(flags);
		
	} // SetBitsTo
	
	template <class Register> inline void ToggleBits(typename Register::Type flags)
	{
		Register::Set(Register::Get() ^ flags);
		
	} // ToggleBits
	
	template <class Register> inline void ChangeBits(typename Register::Type selection, typename Register::Type value)
	{
		typename Register::Type tmp = Register::Get() & ~selection;
		
		value &= selection;
		Register::Set(tmp + value);
		
	} // ChangeBits
	
	
	template <class Register> inline typename Register::Type SelectBits(typename Register::Type selection)
	{
		return Register::Get() & selection;
		
	} // IsBitsSet
	
	template <class Register> inline bool IsAnyBitSet(typename Register::Type flags)
	{
		return SelectBits<Register>(flags) != 0 ? true : false;
		
	} // IsBitsSet
	
	template <class Register> inline bool IsBitsSet(typename Register::Type flags)
	{
		return SelectBits<Register>(flags) == flags ? true : false;
		
	} // IsAllBitsSet
	
	
	namespace Internal
	{
		template <class Derived> struct Register8
		{
			typedef uint8_t Type;
			typedef reg8_t RegType;
			
			static inline reg8_t Get() { return Derived::GetRegister(); }
			static inline void Set(uint8_t flags) { Derived::GetRegister() = flags; }
			
		}; // struct Register8
		
		template <class Derived> struct Register16
		{
			typedef uint16_t Type;
			typedef reg16_t RegType;
			
			struct Low : Register8<Low>
			{
				static inline reg8_t GetRegister() { return (reg8_t)Derived::GetRegister(); } 
				
			}; // struct Low
			
			struct High : Register8<High>
			{
				static inline reg8_t GetRegister() { return *(((volatile uint8_t *)(&Derived::GetRegister())) + 1); }
				
			}; // struct High
			
			static inline reg16_t Get() { return Derived::GetRegister(); }
			static inline void Set(uint16_t flags) { Derived::GetRegister() = flags; }
			
		}; // struct Register16
		
	} // namespace Internal
	
	
#define __DECLARE_8BIT_REGISTER__(registerName) \
	struct _ ## registerName : Internal::Register8<_ ## registerName> { static inline reg8_t GetRegister() { return registerName; } }

#define __DECLARE_16BIT_REGISTER__(registerName) \
	struct _ ## registerName : Internal::Register16<_ ## registerName> { static inline reg16_t GetRegister() { return registerName; } }
	
	
	template <typename DDRReg, typename PORTReg, typename PINReg> struct Port
	{
		typedef PORTReg Output;
		typedef PINReg Input;
		
		static inline void SetAsTriStateInput(uint8_t flags) { ClearBits<PORTReg>(flags), ClearBits<DDRReg>(flags); }
		static inline void SetAsInput(uint8_t flags) { SetBits<PORTReg>(flags), ClearBits<DDRReg>(flags); }
		static inline void SetAsOutput(uint8_t flags) { SetBits<DDRReg>(flags); }
		static inline bool IsOutput(uint8_t flags) { return IsBitsSet<DDRReg>(flags); }
		static inline bool IsInput(uint8_t flags) { return !IsOutput(); }
		static inline bool IsPulledUpInput(uint8_t flags) { return IsBitsSet<PORTReg>(flags) && !IsBitsSet<DDRReg>(flags); }
		static inline bool IsTriStateInput(uint8_t flags) { return !IsBitsSet<PORTReg>(flags) && !IsBitsSet<DDRReg>(flags); }

	}; // struct Port
	
	template <class PortClass, uint8_t flags> struct OutputPins
	{
		typedef PortClass MyPort;
		typedef typename MyPort::Output Pins;
		
		static const uint8_t myFlags = flags;
		
		static inline void InitOutput() { MyPort::SetAsOutput(flags); }
		static inline void Close() { MyPort::SetAsTriStateInput(flags); }
		static inline void Set() { SetBits<Pins>(flags); }
		static inline void SetTo(bool value) { SetBitsTo<Pins>(flags, value); }
		static inline void Toggle() { ToggleBits<Pins>(flags); }
		static inline void Clear() { ClearBits<Pins>(flags); }
		static inline bool IsAnySet() { return IsAnyBitSet<Pins>(flags); }
		static inline bool IsSet() { return IsBitsSet<Pins>(flags); }
		
	}; // struct OutputPins
	
	template <class PortClass, uint8_t flags> struct InputPins
	{
		typedef PortClass MyPort;
		typedef typename MyPort::Input Pins;
		
		static const uint8_t myFlags = flags;
		
		static inline void InitInput() { MyPort::SetAsInput(flags); }
		static inline void InitDefaultInput() { MyPort::SetAsTriStateInput(flags); }
		static inline bool IsAnySet() { return IsAnyBitSet<Pins>(flags); }
		static inline bool IsSet() { return IsBitsSet<Pins>(flags); }
		
	}; // struct InputPins
	
	template <class PortClass, uint8_t flags> struct Pins
	{
		typedef InputPins<PortClass, flags> Input;
		typedef OutputPins<PortClass, flags> Output;

		static inline bool IsOutput() { return PortClass::IsOutput(flags); }
		static inline bool IsInput() { return PortClass::IsInput(flags); }
		static inline bool IsPulledUpInput() { return PortClass::IsPulledUpInput(flags); }
		static inline bool IsTriStateInput() { return PortClass::IsTriStateInput(flags); }
		
	}; // struct Pins
	
	
#define __DECLARE_PORT__(portLetter) \
	typedef struct Port<_DDR ## portLetter, _PORT ## portLetter, _PIN ## portLetter> Port ## portLetter

#define __DECLARE_PORT_PIN__(pinNr) \
	template <class PortClass> struct InputPin ## pinNr : InputPins<PortClass, _P ## pinNr> {}; \
	template <class PortClass> struct OutputPin ## pinNr : OutputPins<PortClass, _P ## pinNr> {}; \
	template <class PortClass> struct Pin ## pinNr : Pins<PortClass, _P ## pinNr> {}
	
	
	template <class Register, uint16_t bitFlags> struct Bits
	{
		static inline void Set() { SetBits<Register>(bitFlags); }
		static inline void Clear() { ClearBits<Register>(bitFlags); }
		static inline void Toggle() { ToggleBits<Register>(bitFlags); }
		static inline bool IsAnySet() { return IsAnyBitSet<Register>(bitFlags); }
		static inline bool IsSet() { return IsBitsSet<Register>(bitFlags); }
		static inline void SetTo(bool value) { SetBitsTo<Register>(bitFlags, value); }
		static inline void Change(typename Register::Type value) { ChangeBits<Register>(bitFlags, value); }
		static inline typename Register::Type Select() { return SelectBits<Register>(bitFlags); }
		
	}; // struct Bits
	
	
	template <class EnableBit> struct BasicInterrupt
	{
		static inline void Enable() { EnableBit::Set(); }
		static inline void Disable() { EnableBit::Clear(); }
		static inline bool IsEnabled() { return EnableBit::IsSet(); }
		
	}; // struct BasicInterrupt
	
	
	template <class EnableBit, class FlagBit> struct Interrupt : BasicInterrupt<EnableBit>
	{
		static inline void ClearFlag() { FlagBit::Set(); }
		static inline bool IsTriggered() { return FlagBit::IsSet(); }
		
	}; // struct Interrupt
	
} // namespace AVRCpp

#define __INTERRUPT_HANDLER_SUPPORT__ \
		static void Evoke(); \
		template <class DelegateType> static DelegateType & Me(); \
		template <class ControllerType> static ControllerType & Controller();

#define __DECLARE_BASIC_INTERRUPT__(interruptName, enableBitStart, enableBitEnd) \
		struct interruptName ## Interrupt : BasicInterrupt<enableBitStart, enableBitEnd> { __INTERRUPT_HANDLER_SUPPORT__ }

#define __DECLARE_INTERRUPT__(interruptName, enableBitStart, enableBitEnd, flagBitStart, flagBitEnd) \
		struct interruptName ## Interrupt : Interrupt<enableBitStart, enableBitEnd, flagBitStart, flagBitEnd> { __INTERRUPT_HANDLER_SUPPORT__ }


/* Universal PORT */
#define _P7		0x80
#define _P6		0x40
#define _P5		0x20
#define _P4		0x10
#define _P3		0x08
#define _P2		0x04
#define _P1		0x02
#define _P0		0x01

/* Universal DDR */
#define _DD7	0x80
#define _DD6	0x40
#define _DD5	0x20
#define _DD4	0x10
#define _DD3	0x08
#define _DD2	0x04
#define _DD1	0x02
#define _DD0	0x01

/* Universal PIN */
#define _PIN7	0x80
#define _PIN6	0x40
#define _PIN5	0x20
#define _PIN4	0x10
#define _PIN3	0x08
#define _PIN2	0x04
#define _PIN1	0x02
#define _PIN0	0x01

/* Include controller specific files */
#if defined(__AVR_AT90USB1287__)
#include "at90usb1287/IO.h"
#elif defined(__AVR_AT90CAN128__)
#include "at90can128/IO.h"
#elif defined(__AVR_ATmega128__)
#include "atmega128/IO.h"
#elif defined(__AVR_ATmega64__)
#include "atmega64/IO.h"
#elif defined(__AVR_ATmega8__)
#include "atmega8/IO.h"
#elif defined(__AVR_ATmega8515__)
#include "atmega8515/IO.h"
#elif defined(__AVR_ATmega88__)
#include "atmega88/IO.h"
#elif defined(__AVR_ATmega48__)
#include "atmega48/IO.h"
#elif defined(__AVR_ATmega168__)
#include "atmega168/IO.h"
#elif defined(__AVR_ATmega164P__)
#include "atmega164p/IO.h"
#elif defined(__AVR_ATmega324P__)
#include "atmega324p/IO.h"
#elif defined(__AVR_ATmega644P__)
#include "atmega644p/IO.h"
#elif defined(__AVR_ATmega644__)
#include "atmega644/IO.h"
#else
#error "Device is not selected or selected device is not supported."
#endif

namespace AVRCpp
{	
	__DECLARE_PORT_PIN__(0);
	__DECLARE_PORT_PIN__(1);
	__DECLARE_PORT_PIN__(2);
	__DECLARE_PORT_PIN__(3);
	__DECLARE_PORT_PIN__(4);
	__DECLARE_PORT_PIN__(5);
	__DECLARE_PORT_PIN__(6);
	__DECLARE_PORT_PIN__(7);

} // namespace AVRCpp

#ifndef __DOXYGEN__

#undef __DECLARE_PORT__
#undef __DECLARE_PORT_PIN__
#undef __DECLARE_8BIT_REGISTER__
#undef __DECLARE_16BIT_REGISTER__

#endif // ifndef __DOXYGEN__

#endif // ifdef __cplusplus

#endif // ifndef __AVR_CPP_IO_H__
