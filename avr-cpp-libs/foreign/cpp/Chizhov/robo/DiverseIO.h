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

#ifndef __AVR_CPP_DIVERSE_IO_H__
#define __AVR_CPP_DIVERSE_IO_H__

#include "IO.h"


/**********************************************************************************************************************\

	AVRCppLib miscellaneous IO pins functionality classes

\**********************************************************************************************************************/

namespace AVRCpp
{


/**********************************************************************************************************************\

	Multi-port input and output pins

\**********************************************************************************************************************/

#ifndef EXCLUDE_MULTI_PORT_PINS

template <	class Port0, uint8_t flags0,
			class Port1, uint8_t flags1,
			class Port2 = PortB, uint8_t flags2 = 0,
			class Port3 = PortB, uint8_t flags3 = 0,
			class Port4 = PortB, uint8_t flags4 = 0,
			class Port5 = PortB, uint8_t flags5 = 0,
			class Port6 = PortB, uint8_t flags6 = 0,
			class Port7 = PortB, uint8_t flags7 = 0 >

class MultiPortInputPins
{
protected:

	typedef typename Port0::Input Pins0;
	typedef typename Port1::Input Pins1;
	typedef typename Port2::Input Pins2;
	typedef typename Port3::Input Pins3;
	typedef typename Port4::Input Pins4;
	typedef typename Port5::Input Pins5;
	typedef typename Port6::Input Pins6;
	typedef typename Port7::Input Pins7;

public:

	static inline void InitInput()
	{
		if (flags0) Port0::SetAsInput(flags0);
		if (flags1) Port1::SetAsInput(flags1);
		if (flags2) Port2::SetAsInput(flags2);
		if (flags3) Port3::SetAsInput(flags3);
		if (flags4) Port4::SetAsInput(flags4);
		if (flags5) Port5::SetAsInput(flags5);
		if (flags6) Port6::SetAsInput(flags6);
		if (flags7) Port7::SetAsInput(flags7);
		
	} // InitInput

	static inline void InitDefaultInput()
	{
		if (flags0) Port0::SetAsTriStateInput(flags0);
		if (flags1) Port1::SetAsTriStateInput(flags1);
		if (flags2) Port2::SetAsTriStateInput(flags2);
		if (flags3) Port3::SetAsTriStateInput(flags3);
		if (flags4) Port4::SetAsTriStateInput(flags4);
		if (flags5) Port5::SetAsTriStateInput(flags5);
		if (flags6) Port6::SetAsTriStateInput(flags6);
		if (flags7) Port7::SetAsTriStateInput(flags7);
		
	} // InitDefaultInput

	static inline bool IsAnySet()
	{
		return		(flags0 ? IsAnyBitSet<Pins0>(flags0) : false)
				||	(flags1 ? IsAnyBitSet<Pins1>(flags1) : false)
				||	(flags2 ? IsAnyBitSet<Pins2>(flags2) : false)
				||	(flags3 ? IsAnyBitSet<Pins3>(flags3) : false)
				||	(flags4 ? IsAnyBitSet<Pins4>(flags4) : false)
				||	(flags5 ? IsAnyBitSet<Pins5>(flags5) : false)
				||	(flags6 ? IsAnyBitSet<Pins6>(flags6) : false)
				||	(flags7 ? IsAnyBitSet<Pins7>(flags7) : false);
		
	} // IsSet
	
	static inline bool IsSet()
	{
		return		(flags0 ? IsBitsSet<Pins0>(flags0) : true)
				&&	(flags1 ? IsBitsSet<Pins1>(flags1) : true)
				&&	(flags2 ? IsBitsSet<Pins2>(flags2) : true)
				&&	(flags3 ? IsBitsSet<Pins3>(flags3) : true)
				&&	(flags4 ? IsBitsSet<Pins4>(flags4) : true)
				&&	(flags5 ? IsBitsSet<Pins5>(flags5) : true)
				&&	(flags6 ? IsBitsSet<Pins6>(flags6) : true)
				&&	(flags7 ? IsBitsSet<Pins7>(flags7) : true);
		
	} // IsAllSet

}; // class MultiPortInputPins


template <	class Port0, uint8_t flags0,
			class Port1, uint8_t flags1,
			class Port2 = PortB, uint8_t flags2 = 0,
			class Port3 = PortB, uint8_t flags3 = 0,
			class Port4 = PortB, uint8_t flags4 = 0,
			class Port5 = PortB, uint8_t flags5 = 0,
			class Port6 = PortB, uint8_t flags6 = 0,
			class Port7 = PortB, uint8_t flags7 = 0 >

class MultiPortOutputPins
{
protected:

	typedef typename Port0::Output Pins0;
	typedef typename Port1::Output Pins1;
	typedef typename Port2::Output Pins2;
	typedef typename Port3::Output Pins3;
	typedef typename Port4::Output Pins4;
	typedef typename Port5::Output Pins5;
	typedef typename Port6::Output Pins6;
	typedef typename Port7::Output Pins7;

public:

	static inline void InitOutput()
	{
		if (flags0) Port0::SetAsOutput(flags0);
		if (flags1) Port1::SetAsOutput(flags1);
		if (flags2) Port2::SetAsOutput(flags2);
		if (flags3) Port3::SetAsOutput(flags3);
		if (flags4) Port4::SetAsOutput(flags4);
		if (flags5) Port5::SetAsOutput(flags5);
		if (flags6) Port6::SetAsOutput(flags6);
		if (flags7) Port7::SetAsOutput(flags7);
		
	} // InitOutput

	static inline void Close()
	{
		if (flags0) Port0::SetAsTriStateInput(flags0);
		if (flags1) Port1::SetAsTriStateInput(flags1);
		if (flags2) Port2::SetAsTriStateInput(flags2);
		if (flags3) Port3::SetAsTriStateInput(flags3);
		if (flags4) Port4::SetAsTriStateInput(flags4);
		if (flags5) Port5::SetAsTriStateInput(flags5);
		if (flags6) Port6::SetAsTriStateInput(flags6);
		if (flags7) Port7::SetAsTriStateInput(flags7);
		
	} // Close

	static inline void Set()
	{
		if (flags0) SetBits<Pins0>(flags0);
		if (flags1) SetBits<Pins1>(flags1);
		if (flags2) SetBits<Pins2>(flags2);
		if (flags3) SetBits<Pins3>(flags3);
		if (flags4) SetBits<Pins4>(flags4);
		if (flags5) SetBits<Pins5>(flags5);
		if (flags6) SetBits<Pins6>(flags6);
		if (flags7) SetBits<Pins7>(flags7);
		
	} // Set

	static inline void SetTo(bool value)
	{
		if (flags0) SetBitsTo<Pins0>(flags0, value);
		if (flags1) SetBitsTo<Pins1>(flags1, value);
		if (flags2) SetBitsTo<Pins2>(flags2, value);
		if (flags3) SetBitsTo<Pins3>(flags3, value);
		if (flags4) SetBitsTo<Pins4>(flags4, value);
		if (flags5) SetBitsTo<Pins5>(flags5, value);
		if (flags6) SetBitsTo<Pins6>(flags6, value);
		if (flags7) SetBitsTo<Pins7>(flags7, value);

	} // SetTo

	static inline void Clear()
	{
		if (flags0) ClearBits<Pins0>(flags0);
		if (flags1) ClearBits<Pins1>(flags1);
		if (flags2) ClearBits<Pins2>(flags2);
		if (flags3) ClearBits<Pins3>(flags3);
		if (flags4) ClearBits<Pins4>(flags4);
		if (flags5) ClearBits<Pins5>(flags5);
		if (flags6) ClearBits<Pins6>(flags6);
		if (flags7) ClearBits<Pins7>(flags7);
		
	} // Clear

	static inline void Toggle()
	{
		if (flags0) ToggleBits<Pins0>(flags0);
		if (flags1) ToggleBits<Pins1>(flags1);
		if (flags2) ToggleBits<Pins2>(flags2);
		if (flags3) ToggleBits<Pins3>(flags3);
		if (flags4) ToggleBits<Pins4>(flags4);
		if (flags5) ToggleBits<Pins5>(flags5);
		if (flags6) ToggleBits<Pins6>(flags6);
		if (flags7) ToggleBits<Pins7>(flags7);
		
	} // Toggle

	static inline bool IsAnySet()
	{
		return		(flags0 ? IsAnyBitSet<Pins0>(flags0) : false)
				||	(flags1 ? IsAnyBitSet<Pins1>(flags1) : false)
				||	(flags2 ? IsAnyBitSet<Pins2>(flags2) : false)
				||	(flags3 ? IsAnyBitSet<Pins3>(flags3) : false)
				||	(flags4 ? IsAnyBitSet<Pins4>(flags4) : false)
				||	(flags5 ? IsAnyBitSet<Pins5>(flags5) : false)
				||	(flags6 ? IsAnyBitSet<Pins6>(flags6) : false)
				||	(flags7 ? IsAnyBitSet<Pins7>(flags7) : false);
		
	} // IsSet
	
	static inline bool IsSet()
	{
		return		(flags0 ? IsBitsSet<Pins0>(flags0) : true)
				&&	(flags1 ? IsBitsSet<Pins1>(flags1) : true)
				&&	(flags2 ? IsBitsSet<Pins2>(flags2) : true)
				&&	(flags3 ? IsBitsSet<Pins3>(flags3) : true)
				&&	(flags4 ? IsBitsSet<Pins4>(flags4) : true)
				&&	(flags5 ? IsBitsSet<Pins5>(flags5) : true)
				&&	(flags6 ? IsBitsSet<Pins6>(flags6) : true)
				&&	(flags7 ? IsBitsSet<Pins7>(flags7) : true);
		
	} // IsAllSet

}; // class MultiPortOutputPins


template <	class InputPins0,
			class InputPins1,
			class InputPins2 = InputPins<PortB, 0>,
			class InputPins3 = InputPins<PortB, 0>,
			class InputPins4 = InputPins<PortB, 0>,
			class InputPins5 = InputPins<PortB, 0>,
			class InputPins6 = InputPins<PortB, 0>,
			class InputPins7 = InputPins<PortB, 0> >

class CombinedInputPins : public MultiPortInputPins <	typename InputPins0::MyPort, InputPins0::myFlags,
														typename InputPins1::MyPort, InputPins1::myFlags,
														typename InputPins2::MyPort, InputPins2::myFlags,
														typename InputPins3::MyPort, InputPins3::myFlags,
														typename InputPins4::MyPort, InputPins4::myFlags,
														typename InputPins5::MyPort, InputPins5::myFlags,
														typename InputPins6::MyPort, InputPins6::myFlags,
														typename InputPins7::MyPort, InputPins7::myFlags > {};

template <	class OutputPins0,
			class OutputPins1,
			class OutputPins2 = OutputPins<PortB, 0>,
			class OutputPins3 = OutputPins<PortB, 0>,
			class OutputPins4 = OutputPins<PortB, 0>,
			class OutputPins5 = OutputPins<PortB, 0>,
			class OutputPins6 = OutputPins<PortB, 0>,
			class OutputPins7 = OutputPins<PortB, 0> >

class CombinedOutputPins : public MultiPortOutputPins <	typename OutputPins0::MyPort, OutputPins0::myFlags,
														typename OutputPins1::MyPort, OutputPins1::myFlags,
														typename OutputPins2::MyPort, OutputPins2::myFlags,
														typename OutputPins3::MyPort, OutputPins3::myFlags,
														typename OutputPins4::MyPort, OutputPins4::myFlags,
														typename OutputPins5::MyPort, OutputPins5::myFlags,
														typename OutputPins6::MyPort, OutputPins6::myFlags,
														typename OutputPins7::MyPort, OutputPins7::myFlags > {};

#endif // ifndef EXCLUDE_MULTI_PORT_PINS


/**********************************************************************************************************************\

	Input pins with state change watcher

\**********************************************************************************************************************/

#ifndef EXCLUDE_STATE_WATCH_PINS

template <class InputPinsClass> class StateWatchInputPins : public InputPinsClass
{
protected:

	bool prevState;

public:

	inline void InitInput()
	{
		InputPinsClass::InitInput();
		prevState = InputPinsClass::IsSet();

	} // InitInput

	inline void InitDefaultInput()
	{
		InputPinsClass::InitDefaultInput();
		prevState = InputPinsClass::IsSet();

	} // InitDefaultInput

	inline void Reset() { prevState = InputPinsClass::IsSet(); }

	inline bool HasChanged(bool doNotReset = false)
	{
		bool now = InputPinsClass::IsSet();

		if (now != prevState)
		{
		    if (!doNotReset) prevState = now;
			return true;
		}

		return false;

	} // HasChanged

}; // class StateWatchInputPins

#define __DECLARE_STATE_WATCH_PORT_INPUT_PIN__(pinNr) \
	template <class PortClass> class StateWatchInputPin ## pinNr : public StateWatchInputPins<InputPins<PortClass, _P ## pinNr> > {}

__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(0);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(1);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(2);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(3);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(4);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(5);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(6);
__DECLARE_STATE_WATCH_PORT_INPUT_PIN__(7);

#undef __DECLARE_STATE_WATCH_PORT_INPUT_PIN__

#endif // #ifndef EXCLUDE_STATE_WATCH_PINS


/**********************************************************************************************************************\

	Output pins with only ground pulled or loose output

\**********************************************************************************************************************/

#ifndef EXCLUDE_GROUND_PULL_PINS

template <class OutputPinsClass> class GroundPullOutputPins : public OutputPinsClass
{
public:
	static inline void Pull()
    {
       	OutputPinsClass::InitOutput();
        OutputPinsClass::Clear();
	}
	
	static inline void Release()
	{
		OutputPinsClass::Close();
	}

    static inline void PullTo(bool bDown)
    {
       	if (bDown)
		{
        	OutputPinsClass::InitOutput();
        	OutputPinsClass::Clear();
        } else {
        	OutputPinsClass::Close();
        }
	}
}; // class GroundPullOutputPins

#define __DECLARE_ROUND_PULL_PORT_PIN__(pinNr) \
	template <class PortClass> class GroundPullOutputPin ## pinNr : public GroundPullOutputPins<OutputPins<PortClass, _P ## pinNr> > {}

__DECLARE_ROUND_PULL_PORT_PIN__(0);
__DECLARE_ROUND_PULL_PORT_PIN__(1);
__DECLARE_ROUND_PULL_PORT_PIN__(2);
__DECLARE_ROUND_PULL_PORT_PIN__(3);
__DECLARE_ROUND_PULL_PORT_PIN__(4);
__DECLARE_ROUND_PULL_PORT_PIN__(5);
__DECLARE_ROUND_PULL_PORT_PIN__(6);
__DECLARE_ROUND_PULL_PORT_PIN__(7);

#undef __DECLARE_ROUND_PULL_PORT_PIN__

#endif // #ifndef EXCLUDE_GROUND_PULL_PINS


/**********************************************************************************************************************\

	Bitmask handling classes

\**********************************************************************************************************************/

#ifndef EXCLUDE_FLAGS_BUFFER

template <typename T> class FlagsBuffer
{
protected:

	T flags;

public:

	FlagsBuffer() : flags(0) {}
	FlagsBuffer(T initFlags) : flags(initFlags) {}
	
	inline void Set(T value) { flags = value; }
	inline T Get() { return flags; }
	inline void SetBits(T flagsSet) { flags |= flagsSet; }
	inline void ClearBits(T flagsCleared) { flags &= ~flagsCleared; }
	inline void ToggleBits(T flagsToggled) { flags ^= flagsToggled; }
	inline T SelectBits(T flagsSelected) { return flags & flagsSelected; }
	inline bool IsBitsSet(T flagsTested) { return SelectBits(flagsTested) != 0 ? true : false; }
	template<class Register> inline void FromRegister() { flags = Register::Get(); }
	template<class Register> inline void IntoRegister() { Register::Set(flags); }

	inline void ChangeBits(T selection, T value)
	{
		T tmp = flags & ~selection;
		
		value &= selection;
		flags = tmp + value;
		
	} // ChangeBits
	
}; // class FlagsBuffer


class FlagsBuffer8 : public	FlagsBuffer<uint8_t>
{
public:

	FlagsBuffer8() :FlagsBuffer<uint8_t>() {}
	FlagsBuffer8(uint8_t initFlags) : FlagsBuffer<uint8_t>(initFlags) {}

}; // class FlagsBuffer8


class FlagsBuffer16	: public FlagsBuffer<uint16_t>
{
public:

	FlagsBuffer16() :FlagsBuffer<uint16_t>() {}
	FlagsBuffer16(uint16_t initFlags) : FlagsBuffer<uint16_t>(initFlags) {}

}; // class FlagsBuffer16

#endif // ifndef EXCLUDE_FLAGS_BUFFER


/**********************************************************************************************************************\

	Base class (struct) for desired register bit handling

\**********************************************************************************************************************/

#ifndef EXCLUDE_BIT_NUMBERS

#define __DECLARE_BIT_NUMBER__(bitNr) \
	template <class RegisterClass> struct Bit ## bitNr : Bits<RegisterClass, _P ## bitNr> {}

__DECLARE_BIT_NUMBER__(0);
__DECLARE_BIT_NUMBER__(1);
__DECLARE_BIT_NUMBER__(2);
__DECLARE_BIT_NUMBER__(3);
__DECLARE_BIT_NUMBER__(4);
__DECLARE_BIT_NUMBER__(5);
__DECLARE_BIT_NUMBER__(6);
__DECLARE_BIT_NUMBER__(7);

#undef __DECLARE_BIT_NUMBER__

#endif // ifndef EXCLUDE_BIT_NUMBERS


/**********************************************************************************************************************/

} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_DIVERSE_IO_H__
