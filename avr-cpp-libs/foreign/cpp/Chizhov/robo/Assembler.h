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

#ifndef __AVR_CPP_ASSEMBLER_H__
#define __AVR_CPP_ASSEMBLER_H__

#ifndef __cplusplus
#error "EEPROM.h needs C++ compiler."
#else


/**********************************************************************************************************************\

	General assembler functions

\**********************************************************************************************************************/

namespace AVRCpp
{
	namespace Assembler
	{
		inline void CLI() { __asm__ __volatile__ ("cli"); }
		inline void SEI() { __asm__ __volatile__ ("sei"); }
		inline void NOP() { __asm__ __volatile__ ("nop"); }
		inline void WDR() { __asm__ __volatile__ ("wdr"); }
		inline void SLEEP() { __asm__ __volatile__ ("sleep"); }
		
	} // namespace Assembler

} // namespace AVRCpp

/**********************************************************************************************************************/

#endif // ifndef __cplusplus
#endif // ifndef __AVR_CPP_ASSEMBLER_H__
