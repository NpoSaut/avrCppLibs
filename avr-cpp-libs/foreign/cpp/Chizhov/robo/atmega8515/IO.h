/**********************************************************************************************************************\

	C++ library for Atmel AVR microcontrollers
	Copyright (C) 2007 Lauri Kirikal, Mikk Leini, Rasmus Raag, MTU TTU Robotiklubi

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

	MTU TTU Robotiklubi  http://www.robotiklubi.ee robotiklubi@gmail.com
	Lauri Kirikal        laurikirikal@gmail.com
	Mikk Leini           mikk.leini@gmail.com

\**********************************************************************************************************************/

#ifndef __AVR_CPP_ATMEGA8515_IO_H__
#define __AVR_CPP_ATMEGA8515_IO_H__

#if defined(__DOXYGEN__) && !defined(__AVR_CPP_IO_H__)
#include <avr/cpp/IO.h>
#endif

#ifndef __AVR_CPP_IO_H__
#error "Include <avr/cpp/IO.h> instead of <avr/cpp/atmega8515/IO.h>."
#else


/**********************************************************************************************************************\

	atmega8515 registers, bits and ports declarations.
	This file is generated. Do not modify manually.

\**********************************************************************************************************************/

// Registers
namespace AVRCpp
{
	__DECLARE_8BIT_REGISTER__(SREG);
	__DECLARE_8BIT_REGISTER__(SPH);
	__DECLARE_8BIT_REGISTER__(SPL);
	__DECLARE_8BIT_REGISTER__(GICR);
	__DECLARE_8BIT_REGISTER__(GIFR);
	__DECLARE_8BIT_REGISTER__(TIMSK);
	__DECLARE_8BIT_REGISTER__(TIFR);
	__DECLARE_8BIT_REGISTER__(SPMCR);
	__DECLARE_8BIT_REGISTER__(EMCUCR);
	__DECLARE_8BIT_REGISTER__(MCUCR);
	__DECLARE_8BIT_REGISTER__(MCUCSR);
	__DECLARE_8BIT_REGISTER__(TCCR0);
	__DECLARE_8BIT_REGISTER__(TCNT0);
	__DECLARE_8BIT_REGISTER__(OCR0);
	__DECLARE_8BIT_REGISTER__(SFIOR);
	__DECLARE_8BIT_REGISTER__(TCCR1A);
	__DECLARE_8BIT_REGISTER__(TCCR1B);
	__DECLARE_8BIT_REGISTER__(TCNT1H);
	__DECLARE_8BIT_REGISTER__(TCNT1L);
	__DECLARE_8BIT_REGISTER__(OCR1AH);
	__DECLARE_8BIT_REGISTER__(OCR1AL);
	__DECLARE_8BIT_REGISTER__(OCR1BH);
	__DECLARE_8BIT_REGISTER__(OCR1BL);
	__DECLARE_8BIT_REGISTER__(ICR1H);
	__DECLARE_8BIT_REGISTER__(ICR1L);
	__DECLARE_8BIT_REGISTER__(WDTCR);
	__DECLARE_8BIT_REGISTER__(UBRRH);
	__DECLARE_8BIT_REGISTER__(UCSRC);
	__DECLARE_8BIT_REGISTER__(EEARH);
	__DECLARE_8BIT_REGISTER__(EEARL);
	__DECLARE_8BIT_REGISTER__(EEDR);
	__DECLARE_8BIT_REGISTER__(EECR);
	__DECLARE_8BIT_REGISTER__(PORTA);
	__DECLARE_8BIT_REGISTER__(DDRA);
	__DECLARE_8BIT_REGISTER__(PINA);
	__DECLARE_8BIT_REGISTER__(PORTB);
	__DECLARE_8BIT_REGISTER__(DDRB);
	__DECLARE_8BIT_REGISTER__(PINB);
	__DECLARE_8BIT_REGISTER__(PORTC);
	__DECLARE_8BIT_REGISTER__(DDRC);
	__DECLARE_8BIT_REGISTER__(PINC);
	__DECLARE_8BIT_REGISTER__(PORTD);
	__DECLARE_8BIT_REGISTER__(DDRD);
	__DECLARE_8BIT_REGISTER__(PIND);
	__DECLARE_8BIT_REGISTER__(SPDR);
	__DECLARE_8BIT_REGISTER__(SPSR);
	__DECLARE_8BIT_REGISTER__(SPCR);
	__DECLARE_8BIT_REGISTER__(UDR);
	__DECLARE_8BIT_REGISTER__(UCSRA);
	__DECLARE_8BIT_REGISTER__(UCSRB);
	__DECLARE_8BIT_REGISTER__(UBRRL);
	__DECLARE_8BIT_REGISTER__(ACSR);
	__DECLARE_8BIT_REGISTER__(PORTE);
	__DECLARE_8BIT_REGISTER__(DDRE);
	__DECLARE_8BIT_REGISTER__(PINE);
	__DECLARE_8BIT_REGISTER__(OSCCAL);
	__DECLARE_16BIT_REGISTER__(SP);
	__DECLARE_16BIT_REGISTER__(TCNT1);
	__DECLARE_16BIT_REGISTER__(OCR1A);
	__DECLARE_16BIT_REGISTER__(OCR1B);
	__DECLARE_16BIT_REGISTER__(ICR1);

} // namespace AVRCpp


// SREG
#define _SREG_I 0x80
#define _SREG_T 0x40
#define _SREG_H 0x20
#define _SREG_S 0x10
#define _SREG_V 0x8
#define _SREG_N 0x4
#define _SREG_Z 0x2
#define _SREG_C 0x1

// SPH
#define _SP15 0x80
#define _SP14 0x40
#define _SP13 0x20
#define _SP12 0x10
#define _SP11 0x8
#define _SP10 0x4
#define _SP9 0x2
#define _SP8 0x1

// SPL
#define _SP7 0x80
#define _SP6 0x40
#define _SP5 0x20
#define _SP4 0x10
#define _SP3 0x8
#define _SP2 0x4
#define _SP1 0x2
#define _SP0 0x1

// GICR
#define _INT1 0x80
#define _INT0 0x40
#define _INT2 0x20
#define _IVSEL 0x2
#define _IVCE 0x1

// GIFR
#define _INTF1 0x80
#define _INTF0 0x40
#define _INTF2 0x20

// TIMSK
#define _TOIE1 0x80
#define _OCIE1A 0x40
#define _OCIE1B 0x20
#define _TICIE1 0x8
#define _TOIE0 0x2
#define _OCIE0 0x1

// TIFR
#define _TOV1 0x80
#define _OCF1A 0x40
#define _OCF1B 0x20
#define _ICF1 0x8
#define _TOV0 0x2
#define _OCF0 0x1

// SPMCR
#define _SPMIE 0x80
#define _RWWSB 0x40
#define _RWWSRE 0x10
#define _BLBSET 0x8
#define _PGWRT 0x4
#define _PGERS 0x2
#define _SPMEN 0x1

// EMCUCR
#define _SM0 0x80
#define _SRL2 0x40
#define _SRL1 0x20
#define _SRL0 0x10
#define _SRW01 0x8
#define _SRW00 0x4
#define _SRW11 0x2
#define _ISC2 0x1

// MCUCR
#define _SRE 0x80
#define _SRW10 0x40
#define _SE 0x20
#define _SM1 0x10
#define _ISC11 0x8
#define _ISC10 0x4
#define _ISC01 0x2
#define _ISC00 0x1

// MCUCSR
#define _SM2 0x20
#define _WDRF 0x8
#define _BORF 0x4
#define _EXTRF 0x2
#define _PORF 0x1

// TCCR0
#define _FOC0 0x80
#define _WGM00 0x40
#define _COM01 0x20
#define _COM00 0x10
#define _WGM01 0x8
#define _CS02 0x4
#define _CS01 0x2
#define _CS00 0x1

// SFIOR
#define _XMBK 0x40
#define _XMM2 0x20
#define _XMM1 0x10
#define _XMM0 0x8
#define _PUD 0x4
#define _PSR10 0x1

// TCCR1A
#define _COM1A1 0x80
#define _COM1A0 0x40
#define _COM1B1 0x20
#define _COM1B0 0x10
#define _FOC1A 0x8
#define _FOC1B 0x4
#define _WGM11 0x2
#define _WGM10 0x1

// TCCR1B
#define _ICNC1 0x80
#define _ICES1 0x40
#define _WGM13 0x10
#define _WGM12 0x8
#define _CS12 0x4
#define _CS11 0x2
#define _CS10 0x1

// WDTCR
#define _WDCE 0x10
#define _WDE 0x8
#define _WDP2 0x4
#define _WDP1 0x2
#define _WDP0 0x1

// UCSRC
#define _URSEL 0x80
#define _UMSEL 0x40
#define _UPM1 0x20
#define _UPM0 0x10
#define _USBS 0x8
#define _UCSZ1 0x4
#define _UCSZ0 0x2
#define _UCPOL 0x1

// EEARH
#define _EEAR8 0x1

// EECR
#define _EERIE 0x8
#define _EEMWE 0x4
#define _EEWE 0x2
#define _EERE 0x1

// PORTA
#define _PA7 0x80
#define _PA6 0x40
#define _PA5 0x20
#define _PA4 0x10
#define _PA3 0x8
#define _PA2 0x4
#define _PA1 0x2
#define _PA0 0x1

// DDRA
#define _DDA7 0x80
#define _DDA6 0x40
#define _DDA5 0x20
#define _DDA4 0x10
#define _DDA3 0x8
#define _DDA2 0x4
#define _DDA1 0x2
#define _DDA0 0x1

// PINA
#define _PINA7 0x80
#define _PINA6 0x40
#define _PINA5 0x20
#define _PINA4 0x10
#define _PINA3 0x8
#define _PINA2 0x4
#define _PINA1 0x2
#define _PINA0 0x1

// PORTB
#define _PB7 0x80
#define _PB6 0x40
#define _PB5 0x20
#define _PB4 0x10
#define _PB3 0x8
#define _PB2 0x4
#define _PB1 0x2
#define _PB0 0x1

// DDRB
#define _DDB7 0x80
#define _DDB6 0x40
#define _DDB5 0x20
#define _DDB4 0x10
#define _DDB3 0x8
#define _DDB2 0x4
#define _DDB1 0x2
#define _DDB0 0x1

// PINB
#define _PINB7 0x80
#define _PINB6 0x40
#define _PINB5 0x20
#define _PINB4 0x10
#define _PINB3 0x8
#define _PINB2 0x4
#define _PINB1 0x2
#define _PINB0 0x1

// PORTC
#define _PC7 0x80
#define _PC6 0x40
#define _PC5 0x20
#define _PC4 0x10
#define _PC3 0x8
#define _PC2 0x4
#define _PC1 0x2
#define _PC0 0x1

// DDRC
#define _DDC7 0x80
#define _DDC6 0x40
#define _DDC5 0x20
#define _DDC4 0x10
#define _DDC3 0x8
#define _DDC2 0x4
#define _DDC1 0x2
#define _DDC0 0x1

// PINC
#define _PINC7 0x80
#define _PINC6 0x40
#define _PINC5 0x20
#define _PINC4 0x10
#define _PINC3 0x8
#define _PINC2 0x4
#define _PINC1 0x2
#define _PINC0 0x1

// PORTD
#define _PD7 0x80
#define _PD6 0x40
#define _PD5 0x20
#define _PD4 0x10
#define _PD3 0x8
#define _PD2 0x4
#define _PD1 0x2
#define _PD0 0x1

// DDRD
#define _DDD7 0x80
#define _DDD6 0x40
#define _DDD5 0x20
#define _DDD4 0x10
#define _DDD3 0x8
#define _DDD2 0x4
#define _DDD1 0x2
#define _DDD0 0x1

// PIND
#define _PIND7 0x80
#define _PIND6 0x40
#define _PIND5 0x20
#define _PIND4 0x10
#define _PIND3 0x8
#define _PIND2 0x4
#define _PIND1 0x2
#define _PIND0 0x1

// SPSR
#define _SPIF 0x80
#define _WCOL 0x40
#define _SPI2X 0x1

// SPCR
#define _SPIE 0x80
#define _SPE 0x40
#define _DORD 0x20
#define _MSTR 0x10
#define _CPOL 0x8
#define _CPHA 0x4
#define _SPR1 0x2
#define _SPR0 0x1

// UCSRA
#define _RXC 0x80
#define _TXC 0x40
#define _UDRE 0x20
#define _FE 0x10
#define _DOR 0x8
#define _PE 0x4
#define _U2X 0x2
#define _MPCM 0x1

// UCSRB
#define _RXCIE 0x80
#define _TXCIE 0x40
#define _UDRIE 0x20
#define _RXEN 0x10
#define _TXEN 0x8
#define _UCSZ2 0x4
#define _RXB8 0x2
#define _TXB8 0x1

// ACSR
#define _ACD 0x80
#define _ACBG 0x40
#define _ACO 0x20
#define _ACI 0x10
#define _ACIE 0x8
#define _ACIC 0x4
#define _ACIS1 0x2
#define _ACIS0 0x1

// PORTE
#define _PE2 0x4
#define _PE1 0x2
#define _PE0 0x1

// DDRE
#define _DDE2 0x4
#define _DDE1 0x2
#define _DDE0 0x1

// PINE
#define _PINE2 0x4
#define _PINE1 0x2
#define _PINE0 0x1


// General ports
namespace AVRCpp
{
	__DECLARE_PORT__(A);
	__DECLARE_PORT__(B);
	__DECLARE_PORT__(C);
	__DECLARE_PORT__(D);
	__DECLARE_PORT__(E);
	
} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_IO_H__
#endif // ifndef __AVR_CPP_ATMEGA8515_IO_H__
