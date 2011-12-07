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

#ifndef __AVR_CPP_AT90USB1287_IO_H__
#define __AVR_CPP_AT90USB1287_IO_H__

#if defined(__DOXYGEN__) && !defined(__AVR_CPP_IO_H__)
#include <avr/cpp/IO.h>
#endif

#ifndef __AVR_CPP_IO_H__
#error "Include <avr/cpp/IO.h> instead of <avr/cpp/at90usb1287/IO.h>."
#else


/**********************************************************************************************************************\

	at90usb1287 registers, bits and ports declarations.
	This file is generated. Do not modify manually.

\**********************************************************************************************************************/

// Registers
namespace AVRCpp
{
	__DECLARE_8BIT_REGISTER__(OTGTCON);
	__DECLARE_8BIT_REGISTER__(UPINT);
	__DECLARE_8BIT_REGISTER__(UPBCHX);
	__DECLARE_8BIT_REGISTER__(UPBCLX);
	__DECLARE_8BIT_REGISTER__(UPERRX);
	__DECLARE_8BIT_REGISTER__(UEINT);
	__DECLARE_8BIT_REGISTER__(UEBCHX);
	__DECLARE_8BIT_REGISTER__(UEBCLX);
	__DECLARE_8BIT_REGISTER__(UEDATX);
	__DECLARE_8BIT_REGISTER__(UEIENX);
	__DECLARE_8BIT_REGISTER__(UESTA1X);
	__DECLARE_8BIT_REGISTER__(UESTA0X);
	__DECLARE_8BIT_REGISTER__(UECFG1X);
	__DECLARE_8BIT_REGISTER__(UECFG0X);
	__DECLARE_8BIT_REGISTER__(UECONX);
	__DECLARE_8BIT_REGISTER__(UERST);
	__DECLARE_8BIT_REGISTER__(UENUM);
	__DECLARE_8BIT_REGISTER__(UEINTX);
	__DECLARE_8BIT_REGISTER__(UDTST);
	__DECLARE_8BIT_REGISTER__(UDMFN);
	__DECLARE_8BIT_REGISTER__(UDFNUMH);
	__DECLARE_8BIT_REGISTER__(UDFNUML);
	__DECLARE_8BIT_REGISTER__(UDADDR);
	__DECLARE_8BIT_REGISTER__(UDIEN);
	__DECLARE_8BIT_REGISTER__(UDINT);
	__DECLARE_8BIT_REGISTER__(UDCON);
	__DECLARE_8BIT_REGISTER__(OTGINT);
	__DECLARE_8BIT_REGISTER__(OTGIEN);
	__DECLARE_8BIT_REGISTER__(OTGCON);
	__DECLARE_8BIT_REGISTER__(UDPADDH);
	__DECLARE_8BIT_REGISTER__(UDPADDL);
	__DECLARE_8BIT_REGISTER__(USBINT);
	__DECLARE_8BIT_REGISTER__(USBSTA);
	__DECLARE_8BIT_REGISTER__(USBCON);
	__DECLARE_8BIT_REGISTER__(UHWCON);
	__DECLARE_8BIT_REGISTER__(UDR1);
	__DECLARE_8BIT_REGISTER__(UBRR1H);
	__DECLARE_8BIT_REGISTER__(UBRR1L);
	__DECLARE_8BIT_REGISTER__(UCSR1C);
	__DECLARE_8BIT_REGISTER__(UCSR1B);
	__DECLARE_8BIT_REGISTER__(UCSR1A);
	__DECLARE_8BIT_REGISTER__(TWAMR);
	__DECLARE_8BIT_REGISTER__(TWCR);
	__DECLARE_8BIT_REGISTER__(TWDR);
	__DECLARE_8BIT_REGISTER__(TWAR);
	__DECLARE_8BIT_REGISTER__(TWSR);
	__DECLARE_8BIT_REGISTER__(TWBR);
	__DECLARE_8BIT_REGISTER__(ASSR);
	__DECLARE_8BIT_REGISTER__(OCR2B);
	__DECLARE_8BIT_REGISTER__(OCR2A);
	__DECLARE_8BIT_REGISTER__(TCNT2);
	__DECLARE_8BIT_REGISTER__(TCCR2B);
	__DECLARE_8BIT_REGISTER__(TCCR2A);
	__DECLARE_8BIT_REGISTER__(UPDATX);
	__DECLARE_8BIT_REGISTER__(UPIENX);
	__DECLARE_8BIT_REGISTER__(UPCFG2X);
	__DECLARE_8BIT_REGISTER__(UPSTAX);
	__DECLARE_8BIT_REGISTER__(UPCFG1X);
	__DECLARE_8BIT_REGISTER__(UPCFG0X);
	__DECLARE_8BIT_REGISTER__(UPCONX);
	__DECLARE_8BIT_REGISTER__(UPRST);
	__DECLARE_8BIT_REGISTER__(UPNUM);
	__DECLARE_8BIT_REGISTER__(UPINTX);
	__DECLARE_8BIT_REGISTER__(UPINRQX);
	__DECLARE_8BIT_REGISTER__(UHFLEN);
	__DECLARE_8BIT_REGISTER__(UHFNUMH);
	__DECLARE_8BIT_REGISTER__(UHFNUML);
	__DECLARE_8BIT_REGISTER__(UHADDR);
	__DECLARE_8BIT_REGISTER__(UHIEN);
	__DECLARE_8BIT_REGISTER__(UHINT);
	__DECLARE_8BIT_REGISTER__(UHCON);
	__DECLARE_8BIT_REGISTER__(OCR3CH);
	__DECLARE_8BIT_REGISTER__(OCR3CL);
	__DECLARE_8BIT_REGISTER__(OCR3BH);
	__DECLARE_8BIT_REGISTER__(OCR3BL);
	__DECLARE_8BIT_REGISTER__(OCR3AH);
	__DECLARE_8BIT_REGISTER__(OCR3AL);
	__DECLARE_8BIT_REGISTER__(ICR3H);
	__DECLARE_8BIT_REGISTER__(ICR3L);
	__DECLARE_8BIT_REGISTER__(TCNT3H);
	__DECLARE_8BIT_REGISTER__(TCNT3L);
	__DECLARE_8BIT_REGISTER__(TCCR3C);
	__DECLARE_8BIT_REGISTER__(TCCR3B);
	__DECLARE_8BIT_REGISTER__(TCCR3A);
	__DECLARE_8BIT_REGISTER__(OCR1CH);
	__DECLARE_8BIT_REGISTER__(OCR1CL);
	__DECLARE_8BIT_REGISTER__(OCR1BH);
	__DECLARE_8BIT_REGISTER__(OCR1BL);
	__DECLARE_8BIT_REGISTER__(OCR1AH);
	__DECLARE_8BIT_REGISTER__(OCR1AL);
	__DECLARE_8BIT_REGISTER__(ICR1H);
	__DECLARE_8BIT_REGISTER__(ICR1L);
	__DECLARE_8BIT_REGISTER__(TCNT1H);
	__DECLARE_8BIT_REGISTER__(TCNT1L);
	__DECLARE_8BIT_REGISTER__(TCCR1C);
	__DECLARE_8BIT_REGISTER__(TCCR1B);
	__DECLARE_8BIT_REGISTER__(TCCR1A);
	__DECLARE_8BIT_REGISTER__(DIDR1);
	__DECLARE_8BIT_REGISTER__(DIDR0);
	__DECLARE_8BIT_REGISTER__(ADMUX);
	__DECLARE_8BIT_REGISTER__(ADCSRB);
	__DECLARE_8BIT_REGISTER__(ADCSRA);
	__DECLARE_8BIT_REGISTER__(ADCH);
	__DECLARE_8BIT_REGISTER__(ADCL);
	__DECLARE_8BIT_REGISTER__(XMCRB);
	__DECLARE_8BIT_REGISTER__(XMCRA);
	__DECLARE_8BIT_REGISTER__(TIMSK3);
	__DECLARE_8BIT_REGISTER__(TIMSK2);
	__DECLARE_8BIT_REGISTER__(TIMSK1);
	__DECLARE_8BIT_REGISTER__(TIMSK0);
	__DECLARE_8BIT_REGISTER__(PCMSK0);
	__DECLARE_8BIT_REGISTER__(EICRB);
	__DECLARE_8BIT_REGISTER__(EICRA);
	__DECLARE_8BIT_REGISTER__(PCICR);
	__DECLARE_8BIT_REGISTER__(OSCCAL);
	__DECLARE_8BIT_REGISTER__(PRR1);
	__DECLARE_8BIT_REGISTER__(PRR0);
	__DECLARE_8BIT_REGISTER__(CLKPR);
	__DECLARE_8BIT_REGISTER__(WDTCSR);
	__DECLARE_8BIT_REGISTER__(SREG);
	__DECLARE_8BIT_REGISTER__(SPH);
	__DECLARE_8BIT_REGISTER__(SPL);
	__DECLARE_8BIT_REGISTER__(RAMPZ);
	__DECLARE_8BIT_REGISTER__(SPMCSR);
	__DECLARE_8BIT_REGISTER__(MCUCR);
	__DECLARE_8BIT_REGISTER__(MCUSR);
	__DECLARE_8BIT_REGISTER__(SMCR);
	__DECLARE_8BIT_REGISTER__(OCDR);
	__DECLARE_8BIT_REGISTER__(MONDR);
	__DECLARE_8BIT_REGISTER__(ACSR);
	__DECLARE_8BIT_REGISTER__(SPDR);
	__DECLARE_8BIT_REGISTER__(SPSR);
	__DECLARE_8BIT_REGISTER__(SPCR);
	__DECLARE_8BIT_REGISTER__(GPIOR2);
	__DECLARE_8BIT_REGISTER__(GPIOR1);
	__DECLARE_8BIT_REGISTER__(PLLCSR);
	__DECLARE_8BIT_REGISTER__(OCR0B);
	__DECLARE_8BIT_REGISTER__(OCR0A);
	__DECLARE_8BIT_REGISTER__(TCNT0);
	__DECLARE_8BIT_REGISTER__(TCCR0B);
	__DECLARE_8BIT_REGISTER__(TCCR0A);
	__DECLARE_8BIT_REGISTER__(GTCCR);
	__DECLARE_8BIT_REGISTER__(EEARH);
	__DECLARE_8BIT_REGISTER__(EEARL);
	__DECLARE_8BIT_REGISTER__(EEDR);
	__DECLARE_8BIT_REGISTER__(EECR);
	__DECLARE_8BIT_REGISTER__(GPIOR0);
	__DECLARE_8BIT_REGISTER__(EIMSK);
	__DECLARE_8BIT_REGISTER__(EIFR);
	__DECLARE_8BIT_REGISTER__(PCIFR);
	__DECLARE_8BIT_REGISTER__(TIFR3);
	__DECLARE_8BIT_REGISTER__(TIFR2);
	__DECLARE_8BIT_REGISTER__(TIFR1);
	__DECLARE_8BIT_REGISTER__(TIFR0);
	__DECLARE_8BIT_REGISTER__(PORTF);
	__DECLARE_8BIT_REGISTER__(DDRF);
	__DECLARE_8BIT_REGISTER__(PINF);
	__DECLARE_8BIT_REGISTER__(PORTE);
	__DECLARE_8BIT_REGISTER__(DDRE);
	__DECLARE_8BIT_REGISTER__(PINE);
	__DECLARE_8BIT_REGISTER__(PORTD);
	__DECLARE_8BIT_REGISTER__(DDRD);
	__DECLARE_8BIT_REGISTER__(PIND);
	__DECLARE_8BIT_REGISTER__(PORTC);
	__DECLARE_8BIT_REGISTER__(DDRC);
	__DECLARE_8BIT_REGISTER__(PINC);
	__DECLARE_8BIT_REGISTER__(PORTB);
	__DECLARE_8BIT_REGISTER__(DDRB);
	__DECLARE_8BIT_REGISTER__(PINB);
	__DECLARE_8BIT_REGISTER__(PORTA);
	__DECLARE_8BIT_REGISTER__(DDRA);
	__DECLARE_8BIT_REGISTER__(PINA);
	__DECLARE_16BIT_REGISTER__(UDFNUM);
	__DECLARE_16BIT_REGISTER__(UDPADD);
	__DECLARE_16BIT_REGISTER__(UHFNUM);
	__DECLARE_16BIT_REGISTER__(OCR3C);
	__DECLARE_16BIT_REGISTER__(OCR3B);
	__DECLARE_16BIT_REGISTER__(OCR3A);
	__DECLARE_16BIT_REGISTER__(ICR3);
	__DECLARE_16BIT_REGISTER__(TCNT3);
	__DECLARE_16BIT_REGISTER__(OCR1C);
	__DECLARE_16BIT_REGISTER__(OCR1B);
	__DECLARE_16BIT_REGISTER__(OCR1A);
	__DECLARE_16BIT_REGISTER__(ICR1);
	__DECLARE_16BIT_REGISTER__(TCNT1);
	__DECLARE_16BIT_REGISTER__(ADC);
	__DECLARE_16BIT_REGISTER__(SP);

} // namespace AVRCpp


// UEIENX
#define _FLERRE 0x80
#define _NAKINE 0x40
#define _NAKOUTE 0x10
#define _RXSTPE 0x8
#define _RXOUTE 0x4
#define _STALLEDE 0x2
#define _TXINE 0x1

// UEINTX
#define _FIFOCON 0x80
#define _NAKINI 0x40
#define _RWAL 0x20
#define _NAKOUTI 0x10
#define _RXSTPI 0x8
#define _RXOUTI 0x4
#define _STALLEDI 0x2
#define _TXINI 0x1

// UCSR1C
#define _UMSEL11 0x80
#define _UMSEL10 0x40
#define _UPM11 0x20
#define _UPM10 0x10
#define _USBS1 0x8
#define _UCSZ11 0x4
#define _UCSZ10 0x2
#define _UCPOL1 0x1

// UCSR1B
#define _RXCIE1 0x80
#define _TXCIE1 0x40
#define _UDRIE1 0x20
#define _RXEN1 0x10
#define _TXEN1 0x8
#define _UCSZ12 0x4
#define _RXB81 0x2
#define _TXB81 0x1

// UCSR1A
#define _RXC1 0x80
#define _TXC1 0x40
#define _UDRE1 0x20
#define _FE1 0x10
#define _DOR1 0x8
#define _UPE1 0x4
#define _U2X1 0x2
#define _MPCM1 0x1

// TWAMR
#define _TWAM6 0x80
#define _TWAM5 0x40
#define _TWAM4 0x20
#define _TWAM3 0x10
#define _TWAM2 0x8
#define _TWAM1 0x4
#define _TWAM0 0x2

// TWCR
#define _TWINT 0x80
#define _TWEA 0x40
#define _TWSTA 0x20
#define _TWSTO 0x10
#define _TWWC 0x8
#define _TWEN 0x4
#define _TWIE 0x1

// TWAR
#define _TWA6 0x80
#define _TWA5 0x40
#define _TWA4 0x20
#define _TWA3 0x10
#define _TWA2 0x8
#define _TWA1 0x4
#define _TWA0 0x2
#define _TWGCE 0x1

// TWSR
#define _TWS7 0x80
#define _TWS6 0x40
#define _TWS5 0x20
#define _TWS4 0x10
#define _TWS3 0x8
#define _TWPS1 0x2
#define _TWPS0 0x1

// ASSR
#define _EXCLK 0x40
#define _AS2 0x20
#define _TCN2UB 0x10
#define _OCR2AUB 0x8
#define _OCR2BUB 0x4
#define _TCR2AUB 0x2
#define _TCR2BUB 0x1

// TCCR2B
#define _FOC2A 0x80
#define _FOC2B 0x40
#define _WGM22 0x8
#define _CS22 0x4
#define _CS21 0x2
#define _CS20 0x1

// TCCR2A
#define _COM2A1 0x80
#define _COM2A0 0x40
#define _COM2B1 0x20
#define _COM2B0 0x10
#define _WGM21 0x2
#define _WGM20 0x1

// UPIENX
#define _FLERRE 0x80
#define _NAKEDE 0x40
#define _PERRE 0x10
#define _TXSTPE 0x8
#define _TXOUTE 0x4
#define _RXSTALLE 0x2
#define _RXINE 0x1

// UPINTX
#define _FIFOCON 0x80
#define _NAKEDI 0x40
#define _RWAL 0x20
#define _PERRI 0x10
#define _TXSTPI 0x8
#define _TXOUTI 0x4
#define _RXSTALLI 0x2
#define _RXINI 0x1

// TCCR3C
#define _FOC3A 0x80
#define _FOC3B 0x40
#define _FOC3C 0x20

// TCCR3B
#define _ICNC3 0x80
#define _ICES3 0x40
#define _WGM33 0x10
#define _WGM32 0x8
#define _CS32 0x4
#define _CS31 0x2
#define _CS30 0x1

// TCCR3A
#define _COM3A1 0x80
#define _COM3A0 0x40
#define _COM3B1 0x20
#define _COM3B0 0x10
#define _COM3C1 0x8
#define _COM3C0 0x4
#define _WGM31 0x2
#define _WGM30 0x1

// TCCR1C
#define _FOC1A 0x80
#define _FOC1B 0x40
#define _FOC1C 0x20

// TCCR1B
#define _ICNC1 0x80
#define _ICES1 0x40
#define _WGM13 0x10
#define _WGM12 0x8
#define _CS12 0x4
#define _CS11 0x2
#define _CS10 0x1

// TCCR1A
#define _COM1A1 0x80
#define _COM1A0 0x40
#define _COM1B1 0x20
#define _COM1B0 0x10
#define _COM1C1 0x8
#define _COM1C0 0x4
#define _WGM11 0x2
#define _WGM10 0x1

// DIDR1
#define _AIN1D 0x2
#define _AIN0D 0x1

// DIDR0
#define _ADC7D 0x80
#define _ADC6D 0x40
#define _ADC5D 0x20
#define _ADC4D 0x10
#define _ADC3D 0x8
#define _ADC2D 0x4
#define _ADC1D 0x2
#define _ADC0D 0x1

// ADMUX
#define _REFS1 0x80
#define _REFS0 0x40
#define _ADLAR 0x20
#define _MUX4 0x10
#define _MUX3 0x8
#define _MUX2 0x4
#define _MUX1 0x2
#define _MUX0 0x1

// ADCSRB
#define _ADHSM 0x80
#define _ACME 0x40
#define _MUX5 0x8
#define _ADTS2 0x4
#define _ADTS1 0x2
#define _ADTS0 0x1

// ADCSRA
#define _ADEN 0x80
#define _ADSC 0x40
#define _ADATE 0x20
#define _ADIF 0x10
#define _ADIE 0x8
#define _ADPS2 0x4
#define _ADPS1 0x2
#define _ADPS0 0x1

// XMCRB
#define _XMBK 0x80
#define _XMM2 0x4
#define _XMM1 0x2
#define _XMM0 0x1

// XMCRA
#define _SRE 0x80
#define _SRL2 0x40
#define _SRL1 0x20
#define _SRL0 0x10
#define _SRW11 0x8
#define _SRW10 0x4
#define _SRW01 0x2
#define _SRW00 0x1

// TIMSK3
#define _ICIE3 0x20
#define _OCIE3C 0x8
#define _OCIE3B 0x4
#define _OCIE3A 0x2
#define _TOIE3 0x1

// TIMSK2
#define _OCIE2B 0x4
#define _OCIE2A 0x2
#define _TOIE2 0x1

// TIMSK1
#define _ICIE1 0x20
#define _OCIE1C 0x8
#define _OCIE1B 0x4
#define _OCIE1A 0x2
#define _TOIE1 0x1

// TIMSK0
#define _OCIE0B 0x4
#define _OCIE0A 0x2
#define _TOIE0 0x1

// PCMSK0
#define _PCINT7 0x80
#define _PCINT6 0x40
#define _PCINT5 0x20
#define _PCINT4 0x10
#define _PCINT3 0x8
#define _PCINT2 0x4
#define _PCINT1 0x2
#define _PCINT0 0x1

// EICRB
#define _ISC71 0x80
#define _ISC70 0x40
#define _ISC61 0x20
#define _ISC60 0x10
#define _ISC51 0x8
#define _ISC50 0x4
#define _ISC41 0x2
#define _ISC40 0x1

// EICRA
#define _ISC31 0x80
#define _ISC30 0x40
#define _ISC21 0x20
#define _ISC20 0x10
#define _ISC11 0x8
#define _ISC10 0x4
#define _ISC01 0x2
#define _ISC00 0x1

// PCICR
#define _PCIE0 0x1

// PRR1
#define _PRUSB 0x80
#define _PRTIM3 0x8
#define _PRUSART1 0x1

// PRR0
#define _PRTWI 0x80
#define _PRTIM2 0x40
#define _PRTIM0 0x20
#define _PRTIM1 0x8
#define _PRSPI 0x4
#define _PRADC 0x1

// CLKPR
#define _CLKPCE 0x80
#define _CLKPS3 0x8
#define _CLKPS2 0x4
#define _CLKPS1 0x2
#define _CLKPS0 0x1

// WDTCSR
#define _WDIF 0x80
#define _WDIE 0x40
#define _WDP3 0x20
#define _WDCE 0x10
#define _WDE 0x8
#define _WDP2 0x4
#define _WDP1 0x2
#define _WDP0 0x1

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

// RAMPZ
#define _RAMPZ1 0x2
#define _RAMPZ0 0x1

// SPMCSR
#define _SPMIE 0x80
#define _RWWSB 0x40
#define _SIGRD 0x20
#define _RWWSRE 0x10
#define _BLBSET 0x8
#define _PGWRT 0x4
#define _PGERS 0x2
#define _SPMEN 0x1

// MCUCR
#define _JTD 0x80
#define _PUD 0x10
#define _IVSEL 0x2
#define _IVCE 0x1

// MCUSR
#define _JTRF 0x10
#define _WDRF 0x8
#define _BORF 0x4
#define _EXTRF 0x2
#define _PORF 0x1

// SMCR
#define _SM2 0x8
#define _SM1 0x4
#define _SM0 0x2
#define _SE 0x1

// OCDR
#define _OCDR7 0x80
#define _OCDR6 0x40
#define _OCDR5 0x20
#define _OCDR4 0x10
#define _OCDR3 0x8
#define _OCDR2 0x4
#define _OCDR1 0x2
#define _OCDR0 0x1

// ACSR
#define _ACD 0x80
#define _ACBG 0x40
#define _ACO 0x20
#define _ACI 0x10
#define _ACIE 0x8
#define _ACIC 0x4
#define _ACIS1 0x2
#define _ACIS0 0x1

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

// PLLCSR
#define _PLLP2 0x10
#define _PLLP1 0x8
#define _PLLP0 0x4
#define _PLLE 0x2
#define _PLOCK 0x1

// TCCR0B
#define _FOC0A 0x80
#define _FOC0B 0x40
#define _WGM02 0x8
#define _CS02 0x4
#define _CS01 0x2
#define _CS00 0x1

// TCCR0A
#define _COM0A1 0x80
#define _COM0A0 0x40
#define _COM0B1 0x20
#define _COM0B0 0x10
#define _WGM01 0x2
#define _WGM00 0x1

// GTCCR
#define _TSM 0x80
#define _PSRASY 0x2
#define _PSRSYNC 0x1

// EECR
#define _EEPM1 0x20
#define _EEPM0 0x10
#define _EERIE 0x8
#define _EEMPE 0x4
#define _EEPE 0x2
#define _EERE 0x1

// EIMSK
#define _INT7 0x80
#define _INT6 0x40
#define _INT5 0x20
#define _INT4 0x10
#define _INT3 0x8
#define _INT2 0x4
#define _INT1 0x2
#define _INT0 0x1

// EIFR
#define _INTF7 0x80
#define _INTF6 0x40
#define _INTF5 0x20
#define _INTF4 0x10
#define _INTF3 0x8
#define _INTF2 0x4
#define _INTF1 0x2
#define _INTF0 0x1

// PCIFR
#define _PCIF0 0x1

// TIFR3
#define _ICF3 0x20
#define _OCF3C 0x8
#define _OCF3B 0x4
#define _OCF3A 0x2
#define _TOV3 0x1

// TIFR2
#define _OCF2B 0x4
#define _OCF2A 0x2
#define _TOV2 0x1

// TIFR1
#define _ICF1 0x20
#define _OCF1C 0x8
#define _OCF1B 0x4
#define _OCF1A 0x2
#define _TOV1 0x1

// TIFR0
#define _OCF0B 0x4
#define _OCF0A 0x2
#define _TOV0 0x1

// PORTF
#define _PF7 0x80
#define _PF6 0x40
#define _PF5 0x20
#define _PF4 0x10
#define _PF3 0x8
#define _PF2 0x4
#define _PF1 0x2
#define _PF0 0x1

// DDRF
#define _DDF7 0x80
#define _DDF6 0x40
#define _DDF5 0x20
#define _DDF4 0x10
#define _DDF3 0x8
#define _DDF2 0x4
#define _DDF1 0x2
#define _DDF0 0x1

// PINF
#define _PINF7 0x80
#define _PINF6 0x40
#define _PINF5 0x20
#define _PINF4 0x10
#define _PINF3 0x8
#define _PINF2 0x4
#define _PINF1 0x2
#define _PINF0 0x1

// PORTE
#define _PE7 0x80
#define _PE6 0x40
#define _PE5 0x20
#define _PE4 0x10
#define _PE3 0x8
#define _PE2 0x4
#define _PE1 0x2
#define _PE0 0x1

// DDRE
#define _DDE7 0x80
#define _DDE6 0x40
#define _DDE5 0x20
#define _DDE4 0x10
#define _DDE3 0x8
#define _DDE2 0x4
#define _DDE1 0x2
#define _DDE0 0x1

// PINE
#define _PINE7 0x80
#define _PINE6 0x40
#define _PINE5 0x20
#define _PINE4 0x10
#define _PINE3 0x8
#define _PINE2 0x4
#define _PINE1 0x2
#define _PINE0 0x1

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


// General ports
namespace AVRCpp
{
	__DECLARE_PORT__(F);
	__DECLARE_PORT__(E);
	__DECLARE_PORT__(D);
	__DECLARE_PORT__(C);
	__DECLARE_PORT__(B);
	__DECLARE_PORT__(A);
	
} // namespace AVRCpp


/**********************************************************************************************************************/

#endif // ifndef __AVR_CPP_IO_H__
#endif // ifndef __AVR_CPP_AT90USB1287_IO_H__
