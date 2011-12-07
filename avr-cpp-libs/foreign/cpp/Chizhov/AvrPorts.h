//*****************************************************************************
//
// Title		: C++ IO for ATMEL AVR
// Author		: Konstantin Chizhov
// Date			: 2010
// Target MCU	: Atmel mega AVR, TINY avr AND Xmega Series
//
//       This code is distributed under the GNU Public License
//       which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#pragma once

#ifndef IOPORTS_HPP
#error "Do not include this file directly. Use ioports.h instead."
#endif

namespace IO
{

	//Port definitions for AtTiny, AtMega families.

	#define MAKE_PORT(portName, ddrName, pinName, className, ID) \
		class className{\
		public:\
			typedef uint8_t DataT;\
		private:\
			static volatile DataT &data()\
			{\
				return portName;\
			}\
			static volatile DataT &dir()\
			{\
				return ddrName;\
			}\
			static volatile DataT &pin()\
			{\
				return pinName;\
			}\
		public:\
			static void write(DataT value)\
			{\
				data() = value;\
			}\
			static void clearAndSet(DataT clearMask, DataT value)\
			{\
				data() = (data() & ~clearMask) | value;\
			}\
			static DataT read()\
			{\
				return data();\
			}\
			static void DirWrite(DataT value)\
			{\
				dir() = value;\
			}\
			static DataT DirRead()\
			{\
				return dir();\
			}\
			static void set(DataT value)\
			{\
				data() |= value;\
			}\
			static void clear(DataT value)\
			{\
				data() &= ~value;\
			}\
			static void Togle(DataT value)\
			{\
				data() ^= value;\
			}\
			static void DirSet(DataT value)\
			{\
				dir() |= value;\
			}\
			static void DirClear(DataT value)\
			{\
				dir() &= ~value;\
			}\
			static void DirTogle(DataT value)\
			{\
				dir() ^= value;\
			}\
			static DataT pinRead()\
			{\
				return pin();\
			}\
			enum{Id = ID};\
			enum{Width=sizeof(DataT)*8};\
		};

	#ifdef PORTA
	#define USE_PORTA
	MAKE_PORT(PORTA, DDRA, PINA, Porta, 'A')
	#endif


	#ifdef PORTB
	#define USE_PORTB
	MAKE_PORT(PORTB, DDRB, PINB, Portb, 'B')
	#endif


	#ifdef PORTC
	#define USE_PORTC
	MAKE_PORT(PORTC, DDRC, PINC, Portc, 'C')
	#endif


	#ifdef PORTD
	#define USE_PORTD
	MAKE_PORT(PORTD, DDRD, PIND, Portd, 'D')
	#endif


	#ifdef PORTE
	#define USE_PORTE
	MAKE_PORT(PORTE, DDRE, PINE, Porte, 'E')
	#endif


	#ifdef PORTF
	#define USE_PORTF
	MAKE_PORT(PORTF, DDRF, PINF, Portf, 'F')
	#endif

	#ifdef PORTG
	#define USE_PORTG
	MAKE_PORT(PORTG, DDRG, PING, Portg, 'G')
	#endif

}
